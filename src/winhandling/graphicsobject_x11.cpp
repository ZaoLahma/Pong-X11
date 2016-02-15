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


GraphicsObjectString_X11::GraphicsObjectString_X11(const std::string& _str) :
str(_str)
{

}

void GraphicsObjectString_X11::Paint(Display* displayPtr, Window* winPtr, const int screenNo)
{
	XDrawString(displayPtr, *winPtr, DefaultGC(displayPtr, screenNo), 100, 100, str.c_str(), str.length());
}
