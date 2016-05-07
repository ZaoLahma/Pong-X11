/*
 * pongAI.cc
 *
 *  Created on: May 6, 2016
 *      Author: janne
 */

#include "gamelogic/pongAI.h"
#include "jobdispatcher/jobdispatcher.h"
#include "winhandling/graphicsevents.h"

PongAI::PongAI(PongPaddleGameObject* paddlePtr) :
paddle(paddlePtr), xDistance(0)
{

}

void PongAI::TrackBall(PongBallGameObject* ballPtr)
{
	double prevXDistance = xDistance;

	xDistance = paddle->GetPos().GetX() - ballPtr->GetPos().GetX();
	if(0 < xDistance)
	{
		xDistance = -xDistance;
	}

	if(xDistance > prevXDistance)
	{
		double paddleSize = paddle->GetGraphicsObjects()[0]->GetSize().GetY();

		if(ballPtr->GetPos().GetY() > paddle->GetPos().GetY() + paddleSize / 2)
		{
			JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_KEY_PRESSED_EVENT, new KeyPressedData(0xff));
		}

		if(ballPtr->GetPos().GetY() < paddle->GetPos().GetY() - paddleSize / 2)
		{
			JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_KEY_PRESSED_EVENT, new KeyPressedData(0xfe));
		}
	}
}
