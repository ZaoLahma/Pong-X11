/*
 * graphicsobjectstorage_x11.h
 *
 *  Created on: Feb 16, 2016
 *      Author: janne
 */

#ifndef INC_WINHANDLING_GRAPHICSOBJECTSTORAGE_X11_H_
#define INC_WINHANDLING_GRAPHICSOBJECTSTORAGE_X11_H_
#include <map>
#include <mutex>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include "graphicsobject_x11.h"

class GraphicsObjectStorage_X11
{
public:
	static GraphicsObjectStorage_X11* GetApi();

	void AddObject(GraphicsObject_X11* _obj);

	void Paint(Display* display, Window* win, int screenNo);

protected:

private:
	typedef std::map<uint32_t, GraphicsObject_X11*> IdToObjectPtrMapT;

	GraphicsObjectStorage_X11();
	static GraphicsObjectStorage_X11* instance;
	static std::mutex instanceCreationMutex;

	std::mutex rwMutex;
	IdToObjectPtrMapT objectsMap;
};


#endif /* INC_WINHANDLING_GRAPHICSOBJECTSTORAGE_X11_H_ */
