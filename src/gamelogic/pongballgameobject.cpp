/*
 * pongballgameobject.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: janne
 */

#include "gamelogic/pongballgameobject.h"

PongBallGameObject::PongBallGameObject(const Coord& _pos, const Coord& _mov) :
GameObject_X11(_pos, _mov),
counter(0),
colorOffset(0)
{
	currentColor = colorsMap.find(COLOR_GREEN + colorOffset)->second;
}

void PongBallGameObject::Update()
{
	if(counter > 10)
	{
		counter = 0;
		mov.SetX(-mov.GetX());
		mov.SetY(-mov.GetY());

		colorOffset++;

		if(colorOffset > COLOR_YELLOW)
		{
			colorOffset = 0;
		}

		currentColor = colorsMap.find(COLOR_GREEN + colorOffset)->second;
	}

	counter++;

	Coord newPos = mov + GetPos();
	SetPos(newPos);
}

void PongBallGameObject::Paint()
{
	XSetForeground(winDataPtr->displayPtr, graphicsContext, currentColor.pixel);
	XFillArc(winDataPtr->displayPtr, *winDataPtr->winPtr, graphicsContext, pos.GetX() - 2, pos.GetY(), 80, 80, 0 * 64, 360 * 64);
}


