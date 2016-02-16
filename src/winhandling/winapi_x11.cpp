/*
 * winapi_x11.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: janne
 */

#include "winhandling/winapi_x11.h"
#include "winhandling/graphicsobject_x11.h"
#include "winhandling/graphicsobjectstorage_x11.h"

#include <iostream>

WinApi_X11::WinApi_X11(const Coord& _winSize) :
winSize(_winSize),
displayPtr(nullptr),
screenNo(-1),
running(false)
{
	XInitThreads();
	displayPtr = XOpenDisplay(NULL);

	screenNo = DefaultScreen(displayPtr);

	window = XCreateSimpleWindow(displayPtr,
								 RootWindow(displayPtr, screenNo),
								 10,
								 10,
								 winSize.GetX(),
								 winSize.GetY(),
								 1,
	                             BlackPixel(displayPtr, screenNo),
								 WhitePixel(displayPtr, screenNo));

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
	GraphicsObjectString_X11* testString = new GraphicsObjectString_X11(Coord(20, 20), "Hej");

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
			GraphicsObjectStorage_X11::GetApi()->Paint(displayPtr, &window, screenNo);
		}

		if(e.type == ButtonPress)
		{

		}

		if(e.type == ButtonRelease)
		{

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
