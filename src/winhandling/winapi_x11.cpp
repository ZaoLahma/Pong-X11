/*
 * winapi_x11.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: janne
 */

#include "winhandling/winapi_x11.h"
#include "winhandling/graphicsobject_x11.h"
#include "winhandling/graphicsobjectstorage_x11.h"
#include "winhandling/graphicsevents.h"

#include "jobdispatcher/jobdispatcher.h"

#include <iostream>

WinApi_X11::WinApi_X11(const Coord& _winSize) :
active(true),
winSize(_winSize),
displayPtr(nullptr),
screenNo(-1),
running(false),
winDataPtr(new WinDataS())
{
	GraphicsObjectStorage_X11::GetApi()->SetWinDataPtr(winDataPtr);

	XInitThreads();
	displayPtr = XOpenDisplay(NULL);

	winDataPtr->displayPtr = displayPtr;

	screenNo = DefaultScreen(displayPtr);

	winDataPtr->screenNo = screenNo;

	window = XCreateSimpleWindow(displayPtr,
								 RootWindow(displayPtr, screenNo),
								 10,
								 10,
								 winSize.GetX(),
								 winSize.GetY(),
								 1,
	                             BlackPixel(displayPtr, screenNo),
								 WhitePixel(displayPtr, screenNo));

	winDataPtr->winPtr = &window;

	XSelectInput(displayPtr,
			     window,
				 ExposureMask |
				 KeyPressMask |
				 ButtonPressMask |
				 ButtonReleaseMask);

    XMapWindow(displayPtr, window);

    XStoreName(displayPtr, window, "Janne 2D Engine");

	WM_DELETE_WINDOW = XInternAtom(displayPtr, "WM_DELETE_WINDOW", False);

	XSetWMProtocols(displayPtr, window, &WM_DELETE_WINDOW, 1);

	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_AVAIL_EVENT, this);

	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_WIN_RESIZE_EVENT, this);

	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_REDRAW_EVENT, this);

	JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_AVAIL_EVENT, nullptr);
}

WinApi_X11::~WinApi_X11()
{
	std::unique_lock<std::mutex> redrawLock(redrawMutex);

	std::cout<<"WinApi DTOR called"<<std::endl;

	active = false;
	JobDispatcher::GetApi()->UnsubscribeToEvent(GRAPHICS_REDRAW_EVENT, this);
	JobDispatcher::GetApi()->UnsubscribeToEvent(GRAPHICS_WIN_RESIZE_EVENT, this);
	JobDispatcher::GetApi()->UnsubscribeToEvent(GRAPHICS_AVAIL_EVENT, this);

	delete winDataPtr;
	winDataPtr = nullptr;

	XDestroyWindow(displayPtr, window);
	XCloseDisplay(displayPtr);
}

void WinApi_X11::EventLoop()
{
	running = true;

	XEvent e;
	while(running)
	{
		XNextEvent(displayPtr, &e);
		if (e.type == Expose)
		{
			this->RedrawWindow();
		}

		if(e.type == ButtonPress)
		{
			JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_MOUSE_CLICKED_EVENT, new MouseClickedData(Coord(e.xbutton.x, e.xbutton.y)));
		}

		if(e.type == ButtonRelease)
		{
			JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_MOUSE_RELEASED_EVENT, new MouseClickedData(Coord(e.xbutton.x, e.xbutton.y)));
		}

		if (e.type == KeyPress)
		{
			JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_KEY_PRESSED_EVENT, new KeyPressedData(e.xkey.keycode));
		}

		if ((e.type == ClientMessage) &&
			(static_cast<unsigned int>(e.xclient.data.l[0]) == WM_DELETE_WINDOW))
		{
		  break;
		}
	}
}

void WinApi_X11::HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr)
{
	switch(eventNo)
	{
	case GRAPHICS_AVAIL_EVENT:
		break;

	case GRAPHICS_WIN_RESIZE_EVENT:
	{
		const WinResizeEventData* resizeDataPtr = static_cast<const WinResizeEventData*>(dataPtr);
		winSize = resizeDataPtr->GetNewSize();
		JobDispatcher::GetApi()->Log("WinApi_X11::HandleEvent(): Resizing screen to: %d, %d", winSize.GetX(), winSize.GetY());
		ResizeWindow(winSize);
	}
		break;

	case GRAPHICS_REDRAW_EVENT:
		RedrawWindow();
		break;
	default:
		break;
	}
}

void WinApi_X11::ResizeWindow(const Coord& newSize)
{
	XResizeWindow(displayPtr, window, newSize.GetX(), newSize.GetY());
}

void WinApi_X11::RedrawWindow()
{
	std::unique_lock<std::mutex> redrawLock(redrawMutex);
	if(active)
	{
		XClearWindow(winDataPtr->displayPtr, *winDataPtr->winPtr);
		GraphicsObjectStorage_X11::GetApi()->Paint();
		XFlush(winDataPtr->displayPtr);
	}
}
