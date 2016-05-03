/*
 * pongfieldgameobject.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: janne
 */

#include "gamelogic/pongfieldgameobject.h"

PongFieldGameObject::PongFieldGameObject(const Coord& _size) :
GameObject_X11(Coord(0, 0), Coord(0, 0))
{
	onCollision = Coord(-1, -1);
	graphicsObjects.push_back(new PongFieldGameObject::PongFieldGraphicsObject(_size));
}

void PongFieldGameObject::Update()
{
	//Nothing to do here
}


//Graphics object
PongFieldGameObject::PongFieldGraphicsObject::PongFieldGraphicsObject(const Coord& _size) :
GraphicsObject_X11(Coord(0, 0)),
size(_size)
{

}

void PongFieldGameObject::PongFieldGraphicsObject::Paint()
{
	color = colorsMap.find(COLOR_GREEN)->second;
	XSetForeground(winDataPtr->displayPtr, graphicsContext, color.pixel);
	//XFillRectangle(display, d, gc, x, y, width, height)
	XFillRectangle(winDataPtr->displayPtr,
			       *winDataPtr->winPtr,
				   graphicsContext,
				   pos.GetX(),
				   pos.GetY(),
				   size.GetX(),
				   size.GetY());

	color = colorsMap.find(COLOR_WHITE)->second;
	XSetForeground(winDataPtr->displayPtr, graphicsContext, color.pixel);

	XDrawRectangle(winDataPtr->displayPtr,
				   *winDataPtr->winPtr,
				   graphicsContext,
				   pos.GetX() + 5,
				   pos.GetY() + 5,
				   size.GetX() - 10,
				   size.GetY() - 10);

	XDrawRectangle(winDataPtr->displayPtr,
				   *winDataPtr->winPtr,
				   graphicsContext,
				   pos.GetX() + 5,
				   pos.GetY() + 5,
				   size.GetX() - 10,
				   30);

	XDrawRectangle(winDataPtr->displayPtr,
				   *winDataPtr->winPtr,
				   graphicsContext,
				   pos.GetX() + 5,
				   pos.GetY() + size.GetY() - 35,
				   size.GetX() - 10,
				   30);

	//UP
	XDrawRectangle(winDataPtr->displayPtr,
				   *winDataPtr->winPtr,
				   graphicsContext,
				   (pos.GetX() + 5 + size.GetX()) / 4,
				   (pos.GetY() + 5) + 30,
				   (size.GetX() - 10) / 2,
				   (size.GetY() / 2) - 35);

	//DOWN
	XDrawRectangle(winDataPtr->displayPtr,
				   *winDataPtr->winPtr,
				   graphicsContext,
				   (pos.GetX() + 5 + size.GetX()) / 4,
				   ((pos.GetY() + size.GetY()) / 2),
				   (size.GetX() - 10) / 2,
				   (size.GetY() / 2) - 35);

	//"NET"
	//XDrawLine(display, d, gc, x1, y1, x2, y2)
	XDrawLine(winDataPtr->displayPtr,
			  *winDataPtr->winPtr,
			  graphicsContext,
			  ((pos.GetX() + size.GetX()) / 2) + 5,
			  ((pos.GetY() + 5) + 30),
			  ((pos.GetX() + size.GetX()) / 2) + 5,
			  ((size.GetY() - 35)));
}
