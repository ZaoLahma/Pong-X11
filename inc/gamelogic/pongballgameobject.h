/*
 * pongballgameobject.h
 *
 *  Created on: Feb 18, 2016
 *      Author: janne
 */

#ifndef INC_GAMELOGIC_PONGBALLGAMEOBJECT_H_
#define INC_GAMELOGIC_PONGBALLGAMEOBJECT_H_

#include "gamecore/gameobject_x11.h"
#include "jobdispatcher/eventlistenerbase.h"
#include "jobdispatcher/eventdatabase.h"

#define BALL_HIT_WALL_EVENT 0x00000057

enum WallIdentifier
{
	LEFT_WALL,
	RIGHT_WALL
};

class BallResetEventData : public EventDataBase
{
public:
	BallResetEventData(const WallIdentifier& _wall) :
	wall(_wall)
	{

	}

	EventDataBase* clone() const
	{
		return new BallResetEventData(*this);
	}

	WallIdentifier wall;

private:
	BallResetEventData();
};

class PongBallGameObject : public GameObject_X11, public EventListenerBase
{
public:
	PongBallGameObject(const Coord& _pos,
			           const Coord& _mov,
					   const Coord& _playFieldSize);
	void Update();

	void HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr);

protected:

private:
	class PongBallGraphicsObject : public GraphicsObject_X11
	{
	public:
		PongBallGraphicsObject(const Coord& _pos);
		void Paint();
		void SwitchColor();

	protected:

	private:
		PongBallGraphicsObject();
		uint32_t colorOffset;
		XColor currentColor;
	};

	PongBallGameObject();
	Coord playFieldSize;
	uint32_t counter;

};


#endif /* INC_GAMELOGIC_PONGBALLGAMEOBJECT_H_ */
