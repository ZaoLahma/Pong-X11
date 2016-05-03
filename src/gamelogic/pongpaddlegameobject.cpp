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
	graphicsObjects.push_back(new PongPaddleGraphicsObject(_pos));
}

void PongPaddleGameObject::Update()
{

}

void PongPaddleGameObject::SetPos(const Coord& newPos)
{
	pos = newPos;
	graphicsObjects[0]->SetPos(pos);
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
	size = Coord(5, 100);
}

void PongPaddleGameObject::PongPaddleGraphicsObject::Paint()
{
	XSetForeground(winDataPtr->displayPtr,
				   graphicsContext,
				   colorsMap.find(COLOR_BLACK)->second.pixel);

	//XFillRectangle(display, d, gc, x, y, width, height)
	XFillRectangle(winDataPtr->displayPtr,
			       *winDataPtr->winPtr,
				   graphicsContext,
				   pos.GetX(),
				   pos.GetY() - size.GetY() / 2,
				   size.GetX(),
				   size.GetY());
}
