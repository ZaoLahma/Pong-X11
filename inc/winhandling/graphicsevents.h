/*
 * graphicsevents.h
 *
 *  Created on: Feb 16, 2016
 *      Author: janne
 */

#ifndef INC_WINHANDLING_GRAPHICSEVENTS_H_
#define INC_WINHANDLING_GRAPHICSEVENTS_H_

#include "jobdispatcher/eventlistenerbase.h"
#include "coord.h"

#define GRAPHICS_EVENTS_BASE 0x70000000

#define GRAPHICS_AVAIL_EVENT          GRAPHICS_EVENTS_BASE + 0x0
#define GRAPHICS_WIN_RESIZE_EVENT     GRAPHICS_EVENTS_BASE + 0x1
#define GRAPHICS_MOUSE_CLICKED_EVENT  GRAPHICS_EVENTS_BASE + 0x2
#define GRAPHICS_MOUSE_RELEASED_EVENT GRAPHICS_EVENTS_BASE + 0x3
#define GRAPHICS_REDRAW_EVENT         GRAPHICS_EVENTS_BASE + 0x4

class WinResizeEventData : public EventDataBase
{
public:
	EventDataBase* clone() const
	{
		return new WinResizeEventData(*this);
	}

	WinResizeEventData(const Coord& _newSize) :
	newSize(_newSize)
	{

	}

	const Coord& GetNewSize() const
	{
		return newSize;
	}

protected:

private:
	WinResizeEventData();

	Coord newSize;
};

class MouseClickedData : public EventDataBase
{
public:
	EventDataBase* clone() const
	{
		return new MouseClickedData(*this);
	}

	MouseClickedData(const Coord& _pos) :
	pos(_pos)
	{

	}

	const Coord& GetPos() const
	{
		return pos;
	}

protected:

private:
	MouseClickedData();

	Coord pos;
};

#endif /* INC_WINHANDLING_GRAPHICSEVENTS_H_ */
