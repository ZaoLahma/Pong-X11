/*
 * pongAI.cc
 *
 *  Created on: May 6, 2016
 *      Author: janne
 */

#include "gamelogic/pongAI.h"
#include "jobdispatcher/jobdispatcher.h"
#include "winhandling/graphicsevents.h"

PongAI::PongAI(PongPaddleGameObject* paddlePtr, uint32_t _player) :
paddle(paddlePtr), xDistance(0), player(_player)
{
	if(player == 2)
	{
		KEY_UP = 0xfe;
		KEY_DOWN = 0xff;
	}
	else if(player == 1)
	{
		KEY_UP = 0x86;
		KEY_DOWN = 0x85;
	}
}

void PongAI::TrackBall(PongBallGameObject* ballPtr)
{
	double prevXDistance = xDistance;

	xDistance = paddle->GetPos().GetX() - ballPtr->GetPos().GetX();
	if(0 > xDistance)
	{
		xDistance = -xDistance;
	}

	if(xDistance < prevXDistance)
	{
		double paddleSize = paddle->GetGraphicsObjects()[0]->GetSize().GetY();

		if(ballPtr->GetPos().GetY() > paddle->GetPos().GetY() + paddleSize / 2)
		{
			JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_KEY_PRESSED_EVENT, new KeyPressedData(KEY_DOWN));
		}

		if(ballPtr->GetPos().GetY() < paddle->GetPos().GetY() - paddleSize / 2)
		{
			JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_KEY_PRESSED_EVENT, new KeyPressedData(KEY_UP));
		}
	}
}
