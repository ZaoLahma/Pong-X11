/*
 * graphicsobject_x11.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: janne
 */


#include "winhandling/graphicsobject_x11.h"
#include "winhandling/graphicsobjectstorage_x11.h"
#include "winhandling/graphicsevents.h"
#include "jobdispatcher/jobdispatcher.h"
#include "jobdispatcher/uniqueidprovider.h"

#include <iostream>

GraphicsObject_X11::GraphicsObject_X11(const Coord& _pos) :
pos(_pos),
winDataPtr(GraphicsObjectStorage_X11::GetApi()->GetWinDataPtr()),
objectId(UniqueIdProvider::GetApi()->GetUniqueId())
{
	GraphicsObjectStorage_X11::GetApi()->AddObject(this);

	graphicsContext = XCreateGC(winDataPtr->displayPtr, *winDataPtr->winPtr, 0, 0);
	colormap = DefaultColormap(winDataPtr->displayPtr, winDataPtr->screenNo);

	XColor xcolor;
	xcolor.red = 00000; xcolor.green = 65000; xcolor.blue = 00000;
	xcolor.flags = DoRed | DoGreen | DoBlue;
	XAllocColor(winDataPtr->displayPtr, colormap, &xcolor);

	colorsMap[COLOR_GREEN] = xcolor;

	xcolor.red = 65000; xcolor.green = 00000; xcolor.blue = 00000;
	xcolor.flags = DoRed | DoGreen | DoBlue;
	XAllocColor(winDataPtr->displayPtr, colormap, &xcolor);

	colorsMap[COLOR_RED] = xcolor;

	xcolor.red = 00000; xcolor.green = 00000; xcolor.blue = 65000;
	xcolor.flags = DoRed | DoGreen | DoBlue;
	XAllocColor(winDataPtr->displayPtr, colormap, &xcolor);

	colorsMap[COLOR_BLUE] = xcolor;

	xcolor.red = 65000; xcolor.green = 65000; xcolor.blue = 00000;
	xcolor.flags = DoRed | DoGreen | DoBlue;
	XAllocColor(winDataPtr->displayPtr, colormap, &xcolor);

	colorsMap[COLOR_YELLOW] = xcolor;

	xcolor.red = 65000; xcolor.green = 65000; xcolor.blue = 65000;
	xcolor.flags = DoRed | DoGreen | DoBlue;
	XAllocColor(winDataPtr->displayPtr, colormap, &xcolor);

	colorsMap[COLOR_WHITE] = xcolor;

	xcolor.red = 00000; xcolor.green = 00000; xcolor.blue = 00000;
	xcolor.flags = DoRed | DoGreen | DoBlue;
	XAllocColor(winDataPtr->displayPtr, colormap, &xcolor);

	colorsMap[COLOR_BLACK] = xcolor;

	XSetForeground(winDataPtr->displayPtr, graphicsContext, xcolor.pixel);
}

GraphicsObject_X11::~GraphicsObject_X11()
{
	GraphicsObjectStorage_X11::GetApi()->RemoveObject(objectId);
	XFreeGC(winDataPtr->displayPtr, graphicsContext);
}

uint32_t GraphicsObject_X11::GetObjectId() const
{
	return objectId;
}

const Coord& GraphicsObject_X11::GetPos()
{
	return pos;
}

const Coord& GraphicsObject_X11::GetSize()
{
	return size;
}

void GraphicsObject_X11::SetPos(const Coord& _pos)
{
	pos = _pos;
}

//Basic string
GraphicsObjectString_X11::GraphicsObjectString_X11(const Coord& _pos, const std::string& _str) :
GraphicsObject_X11(_pos),
str(_str)
{

}

void GraphicsObjectString_X11::Paint()
{
	std::unique_lock<std::mutex> rwLock(readWriteMutex);
	XDrawString(winDataPtr->displayPtr, *winDataPtr->winPtr, graphicsContext, pos.GetX(), pos.GetY(), str.c_str(), str.length());
}

void GraphicsObjectString_X11::SetString(const std::string& _str)
{
	std::unique_lock<std::mutex> rwLock(readWriteMutex);
	str = _str;
}

//Clickable
GraphicsObjectClickable_X11::GraphicsObjectClickable_X11(const Coord& _pos, const Coord& _size):
GraphicsObject_X11(_pos),
size(_size),
beingPressed(false)
{
	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_MOUSE_CLICKED_EVENT, this);
	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_MOUSE_RELEASED_EVENT, this);
}

GraphicsObjectClickable_X11::~GraphicsObjectClickable_X11()
{
	JobDispatcher::GetApi()->UnsubscribeToEvent(GRAPHICS_MOUSE_CLICKED_EVENT, this);
	JobDispatcher::GetApi()->UnsubscribeToEvent(GRAPHICS_MOUSE_RELEASED_EVENT, this);
}

void GraphicsObjectClickable_X11::HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr)
{
	switch(eventNo)
	{
	case GRAPHICS_MOUSE_CLICKED_EVENT:
	{
		const MouseClickedData* mouseClickedData = static_cast<const MouseClickedData*>(dataPtr);
		const Coord clickPos = mouseClickedData->GetPos();

		if(clickPos.GetX() >= pos.GetX() && clickPos.GetX() <= pos.GetX() + size.GetX() &&
		   clickPos.GetY() >= pos.GetY() && clickPos.GetY() <= pos.GetY() + size.GetY())
		{
			OnClick();
		}
	}
	break;
	case GRAPHICS_MOUSE_RELEASED_EVENT:
	{
		if(beingPressed)
		{
			OnRelease();
		}
	}
	break;
	default:
		break;
	}
}

//Button
GraphicsObjectButton_X11::GraphicsObjectButton_X11(const Coord& _pos, const std::string& _text) :
GraphicsObjectClickable_X11(_pos, Coord()),
buttonTextPtr(new GraphicsObjectString_X11(Coord(_pos.GetX() + 2, _pos.GetY() + 20), _text))
{
	size = Coord(_text.length() * 6 + 3, 30);
}

GraphicsObjectButton_X11::~GraphicsObjectButton_X11()
{
	delete buttonTextPtr;
	buttonTextPtr = nullptr;
}

void GraphicsObjectButton_X11::Paint()
{
	if(!beingPressed)
	{
		XColor xcolor = colorsMap.find(COLOR_BLUE)->second;
		XSetForeground(winDataPtr->displayPtr, graphicsContext, xcolor.pixel);

		XDrawLine(winDataPtr->displayPtr, *winDataPtr->winPtr, graphicsContext, pos.GetX(), pos.GetY(), pos.GetX() + size.GetX(), pos.GetY()); //Upper line
		XDrawLine(winDataPtr->displayPtr, *winDataPtr->winPtr, graphicsContext, pos.GetX(), pos.GetY() + size.GetY(), pos.GetX() + size.GetX(), pos.GetY() + size.GetY()); //lower line
		XDrawArc(winDataPtr->displayPtr, *winDataPtr->winPtr, graphicsContext, pos.GetX() - 2, pos.GetY(), 4, size.GetY(), -45 * 64, -270 * 64);
		XDrawArc(winDataPtr->displayPtr, *winDataPtr->winPtr, graphicsContext, pos.GetX() + size.GetX() - 2, pos.GetY(), 4, size.GetY(), -90 * 64, 180 * 64);
	}
	else
	{
		XColor xcolor = colorsMap.find(COLOR_YELLOW)->second;
		XSetForeground(winDataPtr->displayPtr, graphicsContext, xcolor.pixel);

		XFillRectangle(winDataPtr->displayPtr, *winDataPtr->winPtr, graphicsContext, pos.GetX(), pos.GetY(), size.GetX(), size.GetY());
		XFillArc(winDataPtr->displayPtr, *winDataPtr->winPtr, graphicsContext, pos.GetX() - 2, pos.GetY(), 4, size.GetY(), -45 * 64, -270 * 64);
		XFillArc(winDataPtr->displayPtr, *winDataPtr->winPtr, graphicsContext, pos.GetX() + size.GetX() - 2, pos.GetY(), 4, size.GetY(), -90 * 64, 180 * 64);
	}
}

void GraphicsObjectButton_X11::OnClick()
{
	beingPressed = true;
	JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_REDRAW_EVENT, nullptr);
}

void GraphicsObjectButton_X11::OnRelease()
{
	beingPressed = false;
	JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_REDRAW_EVENT, nullptr);
}
