/*
 * pongpaddleobject.h
 *
 *  Created on: May 3, 2016
 *      Author: janne
 */

#ifndef INC_GAMELOGIC_PONGPADDLEGAMEOBJECT_H_
#define INC_GAMELOGIC_PONGPADDLEGAMEOBJECT_H_

#include "gamelogic/pongballgameobject.h"
#include "gamecore/gameobject_x11.h"
#include "jobdispatcher/eventlistenerbase.h"

class PongPaddleGameObject : public GameObject_X11, public EventListenerBase
{
public:
	PongPaddleGameObject(const Coord& _pos, const Coord& _playFieldSize);

	void Update();

	void SetPos(const Coord& newPos);

	bool CheckCollision(PongBallGameObject* ball);

	void HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr);


protected:

private:
	PongPaddleGameObject();
	const Coord playFieldSize;

	class PongPaddleGraphicsObject : public GraphicsObject_X11
	{
	public:
		PongPaddleGraphicsObject(const Coord& _pos);
		void Paint();

	protected:

	private:

	};
};



#endif /* INC_GAMELOGIC_PONGPADDLEGAMEOBJECT_H_ */
