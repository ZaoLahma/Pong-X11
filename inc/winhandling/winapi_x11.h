/*
 * winapi_x11.h
 *
 *  Created on: Feb 15, 2016
 *      Author: janne
 */

#ifndef INC_WINHANDLING_WINAPI_X11_H_
#define INC_WINHANDLING_WINAPI_X11_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

class WinApi_X11
{
public:
	WinApi_X11();
	void EventLoop();

protected:

private:
	Display* displayPtr;
	Window window;
	Atom WM_DELETE_WINDOW;

	int screenNo;
	bool running;

};


#endif /* INC_WINHANDLING_WINAPI_X11_H_ */