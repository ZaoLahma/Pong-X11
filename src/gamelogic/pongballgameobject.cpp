/*
 * pongballgameobject.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: janne
 */

#include "gamelogic/pongballgameobject.h"

PongBallGameObject::PongBallGameObject(const Coord& _pos, const Coord& _mov) :
GameObject_X11(_pos, _mov),
counter(0)
{
	graphicsObjects.push_back(new PongBallGameObject::PongBallGraphicsObject(_pos));
}

void PongBallGameObject::Update()
{
	if(counter > 100)
	{
		counter = 0;
		mov.SetX(-mov.GetX());
		mov.SetY(-mov.GetY());

		static_cast<PongBallGameObject::PongBallGraphicsObject*>(graphicsObjects[0])->SwitchColor();
	}

	counter++;

	Coord newPos = mov + graphicsObjects[0]->GetPos();
	graphicsObjects[0]->SetPos(newPos);
}

//Graphics object
PongBallGameObject::PongBallGraphicsObject::PongBallGraphicsObject(const Coord& _pos) :
GraphicsObject_X11(_pos),
colorOffset(0)
{
	currentColor = colorsMap.find(COLOR_GREEN + colorOffset)->second;
}

void PongBallGameObject::PongBallGraphicsObject::Paint()
{
	XSetForeground(winDataPtr->displayPtr, graphicsContext, currentColor.pixel);
	XFillArc(winDataPtr->displayPtr, *winDataPtr->winPtr, graphicsContext, pos.GetX() - 2, pos.GetY(), 80, 80, 0 * 64, 360 * 64);
}

void PongBallGameObject::PongBallGraphicsObject::SwitchColor()
{
	colorOffset++;

	if(colorOffset > COLOR_YELLOW)
	{
		colorOffset = 0;
	}

	currentColor = colorsMap.find(COLOR_GREEN + colorOffset)->second;
}
