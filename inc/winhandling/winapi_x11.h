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
#include <mutex>
#include <atomic>
#include <cstdint>
#include "coord.h"
#include "jobdispatcher/eventlistenerbase.h"

struct WinDataS;

class WinApi_X11 : public EventListenerBase
{
public:
	WinApi_X11(const Coord& _winSize);
	~WinApi_X11();

	void EventLoop();

	void HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr);

	void ResizeWindow(const Coord& newSize);
protected:

private:
	WinApi_X11();

	void RedrawWindow();

	std::mutex redrawMutex;

	std::atomic<bool> active;
	Coord winSize;
	Display* displayPtr;
	Window window;
	Atom WM_DELETE_WINDOW;

	int screenNo;
	bool running;

	WinDataS* winDataPtr;

};


#endif /* INC_WINHANDLING_WINAPI_X11_H_ */
