/*
 * graphicsobject_x11.h
 *
 *  Created on: Feb 15, 2016
 *      Author: janne
 */

#ifndef INC_WINHANDLING_GRAPHICSOBJECT_X11_H_
#define INC_WINHANDLING_GRAPHICSOBJECT_X11_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <string>

class GraphicsObject_X11
{
public:
	GraphicsObject_X11();
	virtual ~GraphicsObject_X11();
	virtual void Paint(Display* display, Window* win, int screenNo) = 0;

protected:

private:
};

class GraphicsObjectString_X11 : public GraphicsObject_X11
{
public:
	GraphicsObjectString_X11(const std::string& _str);
	void Paint(Display* display, Window* win, int screenNo);

protected:

private:
	GraphicsObjectString_X11();
	std::string str;
};


#endif /* INC_WINHANDLING_GRAPHICSOBJECT_X11_H_ */
