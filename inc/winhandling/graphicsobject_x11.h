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
#include <map>
#include <vector>

#include "coord.h"
#include "jobdispatcher/eventlistenerbase.h"
#include "windata_s.h"

class Coord;

#define COLOR_GREEN  0x0
#define COLOR_RED    0x1
#define COLOR_BLUE   0x2
#define COLOR_BLACK  0x3
#define COLOR_YELLOW 0x4

class GraphicsObject_X11
{
public:
	GraphicsObject_X11(const Coord& _pos);
	virtual ~GraphicsObject_X11();
	virtual void Paint() = 0;

	uint32_t GetObjectId() const;

	const Coord& GetPos();

	void SetPos(const Coord& _pos);

protected:
	Coord pos;
	const WinDataS* winDataPtr;
	GC graphicsContext;
	std::map<const uint32_t, XColor> colorsMap;
	Colormap colormap;

private:
	GraphicsObject_X11();
	uint32_t objectId;
};

typedef std::vector<GraphicsObject_X11*> GraphicsObjectVector;

class GraphicsObjectString_X11 : public GraphicsObject_X11
{
public:
	GraphicsObjectString_X11(const Coord& _pos, const std::string& _str);
	void Paint();
	void SetString(const std::string& _str);

protected:

private:
	GraphicsObjectString_X11();
	std::string str;

	//Needed to ensure the string is not altered while being rendered
	std::mutex readWriteMutex;
};

class GraphicsObjectClickable_X11 : public GraphicsObject_X11, public EventListenerBase
{
public:
	GraphicsObjectClickable_X11(const Coord& _pos, const Coord& _size);

	virtual ~GraphicsObjectClickable_X11();

	virtual void Paint() = 0;

	void HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr);


protected:
	Coord size;
	bool beingPressed;

private:
	GraphicsObjectClickable_X11();
	virtual void OnClick() = 0;
	virtual void OnRelease() = 0;

};

class GraphicsObjectButton_X11 : public GraphicsObjectClickable_X11
{
public:
	GraphicsObjectButton_X11(const Coord& _pos, const std::string& _text);
	~GraphicsObjectButton_X11();

	void Paint();


protected:

private:
	GraphicsObjectButton_X11();

	GraphicsObjectString_X11* buttonTextPtr;

	void OnClick();
	void OnRelease();
};

#endif /* INC_WINHANDLING_GRAPHICSOBJECT_X11_H_ */
