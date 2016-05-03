/*
 * pongpaddlegameobject.cpp
 *
 *  Created on: May 3, 2016
 *      Author: janne
 */

#include "gamelogic/pongpaddlegameobject.h"

PongPaddleGameObject::PongPaddleGameObject(const Coord& _pos) :
GameObject_X11(_pos, Coord(0, 0))
{

}

void PongPaddleGameObject::Update()
{

}

bool PongPaddleGameObject::CheckCollision(PongBallGameObject* ball)
{
	return false;
}

void PongPaddleGameObject::HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr)
{

}

PongPaddleGameObject::PongPaddleGraphicsObject::PongPaddleGraphicsObject(const Coord& _pos) :
GraphicsObject_X11(_pos)
{
}

void PongPaddleGameObject::PongPaddleGraphicsObject::Paint()
{
	//colorsMap.find(COLOR_BLACK)->second;

	XSetForeground(winDataPtr->displayPtr,
				   graphicsContext,
				   colorsMap.find(COLOR_BLACK)->second.pixel);

	//XFillRectangle(display, d, gc, x, y, width, height)
	XFillRectangle(winDataPtr->displayPtr,
			       *winDataPtr->winPtr,
				   graphicsContext,
				   pos.GetX(),
				   pos.GetY(),
				   size.GetX(),
				   size.GetY());
}
