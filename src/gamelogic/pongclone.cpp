/*
 * pongclone.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: janne
 */

#include "gamecore/gameobjectstorage_x11.h"
#include "gamelogic/pongclone.h"
#include "gamelogic/pongballgameobject.h"
#include "gamelogic/pongfieldgameobject.h"
#include "gamelogic/pongpaddlegameobject.h"
#include "jobdispatcher/jobdispatcher.h"
#include "winhandling/graphicsevents.h"
#include "coord.h"

#include <iostream>

#define PONG_GAME_TIMEOUT_EVENT 0x00004500

PongClone::PongClone() :
pongBallPtr(nullptr),
fieldSize(900, 500)
{
	pongFieldPtr = new PongFieldGameObject(fieldSize);
	pongBallPtr = new PongBallGameObject(Coord(90, 90), Coord(1, 1), fieldSize);
	pongPaddlePtr = new PongPaddleGameObject(Coord(10, fieldSize.GetY() / 2));

	playerOneScoreText = new GraphicsObjectString_X11(Coord(10, 25), "Player 1 score: " + std::to_string(playerOneScore));

	playerTwoScoreText = new GraphicsObjectString_X11(Coord(fieldSize.GetX() - 113, 25), "Player 2 score: " + std::to_string(playerTwoScore));


	JobDispatcher::GetApi()->SubscribeToEvent(BALL_HIT_WALL_EVENT, this);

	JobDispatcher::GetApi()->SubscribeToEvent(PONG_GAME_TIMEOUT_EVENT, this);

	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_AVAIL_EVENT, this);

	JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_WIN_RESIZE_EVENT, new WinResizeEventData(fieldSize));

	JobDispatcher::GetApi()->RaiseEventIn(PONG_GAME_TIMEOUT_EVENT, nullptr, 3000);
}

PongClone::~PongClone()
{
	JobDispatcher::GetApi()->UnsubscribeToEvent(PONG_GAME_TIMEOUT_EVENT, this);
	JobDispatcher::GetApi()->UnsubscribeToEvent(GRAPHICS_AVAIL_EVENT, this);
	GameObjectStorage_X11::GetApi()->DropInstance();

	std::cout<<"PongClone DTOR exiting"<<std::endl;
}

void PongClone::HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr)
{
	switch(eventNo)
	{
	case PONG_GAME_TIMEOUT_EVENT:
		GameObjectStorage_X11::GetApi()->Update();
		pongPaddlePtr->CheckCollision(pongBallPtr);
		JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_REDRAW_EVENT, nullptr);
		JobDispatcher::GetApi()->RaiseEventIn(PONG_GAME_TIMEOUT_EVENT, nullptr, 2);
		break;
	case GRAPHICS_AVAIL_EVENT:
		JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_WIN_RESIZE_EVENT, new WinResizeEventData(fieldSize));
		break;
	case BALL_HIT_WALL_EVENT:
	{
		const BallResetEventData* ballResetEventDataPtr = static_cast<const BallResetEventData*>(dataPtr);

		if(ballResetEventDataPtr->wall == LEFT_WALL)
		{
			playerTwoScore++;
			playerTwoScoreText->SetString("Player 2 score: " + std::to_string(playerTwoScore));
			printf("Player 2 scored\n");
		}
	}
	break;
	default:
		break;
	}
}
