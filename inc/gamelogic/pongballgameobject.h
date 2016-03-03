/*
 * pongballgameobject.h
 *
 *  Created on: Feb 18, 2016
 *      Author: janne
 */

#ifndef INC_GAMELOGIC_PONGBALLGAMEOBJECT_H_
#define INC_GAMELOGIC_PONGBALLGAMEOBJECT_H_

#include "gamecore/gameobject_x11.h"

class PongBallGameObject : public GameObject_X11
{
public:
	PongBallGameObject(const Coord& _pos, const Coord& _mov);
	void Update();

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
	uint32_t counter;

};


#endif /* INC_GAMELOGIC_PONGBALLGAMEOBJECT_H_ */
