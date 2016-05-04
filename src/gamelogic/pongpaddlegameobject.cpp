/*
 * pongpaddlegameobject.cpp
 *
 *  Created on: May 3, 2016
 *      Author: janne
 */

#include "gamelogic/pongpaddlegameobject.h"
#include "winhandling/graphicsevents.h"

PongPaddleGameObject::PongPaddleGameObject(const Coord& _pos, const Coord& _playFieldSize) :
GameObject_X11(_pos, Coord(0, 0)),
playFieldSize(_playFieldSize)
{
	graphicsObjects.push_back(new PongPaddleGraphicsObject(_pos));

	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_KEY_PRESSED_EVENT,
											  this);
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
	if(ball->GetPos().GetX() <= pos.GetX())
	{
		double lowerLimit = (graphicsObjects[0]->GetPos().GetY() +
			    		  graphicsObjects[0]->GetSize().GetY() / 2);

		double upperLimit = (graphicsObjects[0]->GetPos().GetY() -
						  graphicsObjects[0]->GetSize().GetY() / 2);

		printf("lowerLimit: %f, upperLimit: %f, ball->GetPos().GetY(): %f\n",
				lowerLimit,
				upperLimit,
				ball->GetPos().GetY());

		if((ball->GetPos().GetY() < lowerLimit) &&
		   (ball->GetPos().GetY() > upperLimit))
		{
			printf("Bounce!\n");
			ball->SetMov(Coord(-ball->GetMov().GetX(),
					            ball->GetMov().GetY()));
		}
	}

	return false;
}

void PongPaddleGameObject::HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr)
{
	switch(eventNo)
	{
	case GRAPHICS_KEY_PRESSED_EVENT:
	{
		const KeyPressedData* keyPressedDataPtr = static_cast<const KeyPressedData*>(dataPtr);

		if(keyPressedDataPtr->GetChar() == 0x86)
		{
			if(pos.GetY() > graphicsObjects[0]->GetSize().GetY())
			{
				SetPos(Coord(pos.GetX(), pos.GetY() - 30));
			}
			else
			{
				SetPos(Coord(pos.GetX(),
						     graphicsObjects[0]->GetSize().GetY() / 2));
			}
		}
		if(keyPressedDataPtr->GetChar() == 0x85)
		{
			if(pos.GetY() < playFieldSize.GetY() - graphicsObjects[0]->GetSize().GetY())
			{
				SetPos(Coord(pos.GetX(), pos.GetY() + 30));
			}
			else
			{
				SetPos(Coord(pos.GetX(),
						     playFieldSize.GetY() -
							 graphicsObjects[0]->GetSize().GetY() / 2));
			}
		}
	}
	break;

	default:
		break;
	}
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
