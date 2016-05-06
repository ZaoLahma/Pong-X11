/*
 * pongballgameobject.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: janne
 */

#include "gamelogic/pongballgameobject.h"

PongBallGameObject::PongBallGameObject(const Coord& _pos, const Coord& _mov, const Coord& _playFieldSize) :
GameObject_X11(_pos, _mov),
playFieldSize(_playFieldSize),
counter(0)
{
	graphicsObjects.push_back(new PongBallGameObject::PongBallGraphicsObject(_pos));
}

void PongBallGameObject::Update()
{
	if(counter > 50)
	{
		counter = 0;
		//static_cast<PongBallGameObject::PongBallGraphicsObject*>(graphicsObjects[0])->SwitchColor();
	}

	counter++;

	Coord newPos = mov + graphicsObjects[0]->GetPos();

	pos = newPos;

	if(newPos.GetY() > playFieldSize.GetY() - 5)
	{
		mov.SetY(-mov.GetY());
	}

	if(newPos.GetY() < 5)
	{
		mov.SetY(-mov.GetY());
	}

	if(newPos.GetX() > playFieldSize.GetX() - 5)
	{
		newPos = Coord(playFieldSize.GetX() / 2,
				       playFieldSize.GetY() / 2);
		pos = newPos;
		JobDispatcher::GetApi()->RaiseEvent(BALL_HIT_WALL_EVENT,
											new BallResetEventData(RIGHT_WALL));
	}

	if(newPos.GetX() < 5)
	{
		newPos = Coord(playFieldSize.GetX() / 2,
				       playFieldSize.GetY() / 2);
		pos = newPos;
		JobDispatcher::GetApi()->RaiseEvent(BALL_HIT_WALL_EVENT,
											new BallResetEventData(LEFT_WALL));
	}

	graphicsObjects[0]->SetPos(newPos);
}

void PongBallGameObject::HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr)
{

}

//Graphics object
PongBallGameObject::PongBallGraphicsObject::PongBallGraphicsObject(const Coord& _pos) :
GraphicsObject_X11(_pos),
colorOffset(0)
{
	currentColor = colorsMap.find(COLOR_YELLOW)->second;
}

void PongBallGameObject::PongBallGraphicsObject::Paint()
{
	XSetForeground(winDataPtr->displayPtr, graphicsContext, currentColor.pixel);
	XFillArc(winDataPtr->displayPtr, *winDataPtr->winPtr, graphicsContext, pos.GetX() - 10, pos.GetY() - 10, 20, 20, 0 * 64, 360 * 64);
}

void PongBallGameObject::PongBallGraphicsObject::SwitchColor()
{
	colorOffset++;

	if(colorOffset > COLOR_YELLOW)
	{
		colorOffset = 1;
	}

	currentColor = colorsMap.find(COLOR_GREEN + colorOffset)->second;
}
