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
#include <mutex>

#include "coord.h"

class Coord;

class GraphicsObject_X11
{
public:
	GraphicsObject_X11(const Coord& _pos);
	virtual ~GraphicsObject_X11();
	virtual void Paint(Display* display, Window* win, int screenNo) = 0;

	uint32_t GetObjectId() const;

	const Coord& GetPos();

protected:
	Coord pos;

private:
	GraphicsObject_X11();
	uint32_t objectId;
};

class GraphicsObjectString_X11 : public GraphicsObject_X11
{
public:
	GraphicsObjectString_X11(const Coord& _pos, const std::string& _str);
	void Paint(Display* display, Window* win, int screenNo);
	void SetString(const std::string& _str);

protected:

private:
	GraphicsObjectString_X11();
	std::string str;

	//Needed to ensure the string is not altered while being rendered
	std::mutex readWriteMutex;
};


#endif /* INC_WINHANDLING_GRAPHICSOBJECT_X11_H_ */
