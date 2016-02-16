/*
 * graphicsobject_x11.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: janne
 */


#include "winhandling/graphicsobject_x11.h"

GraphicsObject_X11::GraphicsObject_X11()
{

}

GraphicsObject_X11::~GraphicsObject_X11()
{

}

//Basic string
GraphicsObjectString_X11::GraphicsObjectString_X11(const std::string& _str) :
str(_str)
{

}

void GraphicsObjectString_X11::Paint(Display* displayPtr, Window* winPtr, const int screenNo)
{
	std::unique_lock<std::mutex> rwLock(readWriteMutex);
	XDrawString(displayPtr, *winPtr, DefaultGC(displayPtr, screenNo), 100, 100, str.c_str(), str.length());
}

void GraphicsObjectString_X11::SetString(const std::string& _str)
{
	std::unique_lock<std::mutex> rwLock(readWriteMutex);
	str = _str;
}
