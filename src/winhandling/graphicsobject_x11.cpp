/*
 * graphicsobject_x11.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: janne
 */


#include "winhandling/graphicsobject_x11.h"
#include "winhandling/graphicsobjectstorage_x11.h"
#include "uniqueidprovider.h"

#include <iostream>

GraphicsObject_X11::GraphicsObject_X11(const Coord& _pos) :
pos(_pos),
objectId(UniqueIdProvider::GetApi()->GetUniqueId())
{
	GraphicsObjectStorage_X11::GetApi()->AddObject(this);
}

GraphicsObject_X11::~GraphicsObject_X11()
{
	GraphicsObjectStorage_X11::GetApi()->RemoveObject(objectId);
}

uint32_t GraphicsObject_X11::GetObjectId() const
{
	return objectId;
}

const Coord& GraphicsObject_X11::GetPos()
{
	return pos;
}

//Basic string
GraphicsObjectString_X11::GraphicsObjectString_X11(const Coord& _pos, const std::string& _str) :
GraphicsObject_X11(_pos),
str(_str)
{

}

void GraphicsObjectString_X11::Paint(Display* displayPtr, Window* winPtr, const int screenNo)
{
	std::unique_lock<std::mutex> rwLock(readWriteMutex);
	XDrawString(displayPtr, *winPtr, DefaultGC(displayPtr, screenNo), pos.GetX(), pos.GetY(), str.c_str(), str.length());
}

void GraphicsObjectString_X11::SetString(const std::string& _str)
{
	std::unique_lock<std::mutex> rwLock(readWriteMutex);
	str = _str;
}
