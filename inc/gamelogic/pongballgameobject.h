/*
 * pongballgameobject.h
 *
 *  Created on: Feb 18, 2016
 *      Author: janne
 */

#ifndef INC_GAMELOGIC_PONGBALLGAMEOBJECT_H_
#define INC_GAMELOGIC_PONGBALLGAMEOBJECT_H_

#include "gamecore/GameObject_x11.h"

class PongBallGameObject : public GameObject_X11
{
public:
	PongBallGameObject(const Coord& _pos, const Coord& _mov);
	void Update();
	void Paint();

protected:

private:
	PongBallGameObject();

	uint32_t counter;
	uint32_t colorOffset;
	XColor currentColor;

};


#endif /* INC_GAMELOGIC_PONGBALLGAMEOBJECT_H_ */
