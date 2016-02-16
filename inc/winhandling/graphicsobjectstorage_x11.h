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
#include "graphicsobject_x11.h"

class GraphicsObjectStorage_X11
{
public:
	static GraphicsObjectStorage_X11* GetApi();
protected:

private:
	GraphicsObjectStorage_X11();
	static GraphicsObjectStorage_X11* instance;
	static std::mutex instanceCreationMutex;
};


#endif /* INC_WINHANDLING_GRAPHICSOBJECTSTORAGE_X11_H_ */
