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

	//Testing purposes... Remove me
	GraphicsObjectString_X11* testString = new GraphicsObjectString_X11(Coord(20, 20), "This is a text");

	GraphicsObjectButton_X11* testButton = new GraphicsObjectButton_X11(Coord(30, 30), "I am a button");

	GraphicsObjectButton_X11* testButton2 = new GraphicsObjectButton_X11(Coord(30, 70), "I am a another button");

	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_AVAIL_EVENT, this);

	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_WIN_RESIZE_EVENT, this);

	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_REDRAW_EVENT, this);

	JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_AVAIL_EVENT, nullptr);

	//Testing purposes... Remove me
	JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_WIN_RESIZE_EVENT, new WinResizeEventData(Coord(400, 400)));
}

WinApi_X11::~WinApi_X11()
{
	delete winDataPtr;
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

		}

		if ((e.type == ClientMessage) &&
			(static_cast<unsigned int>(e.xclient.data.l[0]) == WM_DELETE_WINDOW))
		{
		  break;
		}
	}
	XDestroyWindow(displayPtr, window);
	XCloseDisplay(displayPtr);

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
	GraphicsObjectStorage_X11::GetApi()->Paint();
}
