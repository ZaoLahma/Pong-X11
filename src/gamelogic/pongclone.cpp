/*
 * pongclone.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: janne
 */

#include "gamelogic/pongclone.h"
#include "gamelogic/pongballgameobject.h"
#include "jobdispatcher/jobdispatcher.h"
#include "winhandling/graphicsevents.h"
#include "coord.h"

#define TEST_TIMEOUT_EVENT 0x00004500

PongClone::PongClone()
{
	//Testing purposes
	gameObjectPtr = new PongBallGameObject(Coord(90, 90), Coord(5, 5));

	JobDispatcher::GetApi()->SubscribeToEvent(TEST_TIMEOUT_EVENT, this);

	JobDispatcher::GetApi()->RaiseEventIn(TEST_TIMEOUT_EVENT, nullptr, 100);
}

PongClone::~PongClone()
{
	JobDispatcher::GetApi()->UnsubscribeToEvent(TEST_TIMEOUT_EVENT, this);
	delete gameObjectPtr;
	gameObjectPtr = nullptr;
}

void PongClone::HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr)
{
	switch(eventNo)
	{
	case TEST_TIMEOUT_EVENT:
		gameObjectPtr->Update();
		JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_REDRAW_EVENT, nullptr);
		JobDispatcher::GetApi()->RaiseEventIn(TEST_TIMEOUT_EVENT, nullptr, 100);
		break;
	default:
		break;
	}
}
