/*
 * pongfieldgameobject.h
 *
 *  Created on: Mar 21, 2016
 *      Author: janne
 */

#ifndef INC_GAMELOGIC_PONGFIELDGAMEOBJECT_H_
#define INC_GAMELOGIC_PONGFIELDGAMEOBJECT_H_

#include "gamecore/gameobject_x11.h"

class PongFieldGameObject : public GameObject_X11
{
public:
	PongFieldGameObject(const Coord& _pos);
	void Update();

protected:

private:

	class PongFieldGraphicsObject : public GraphicsObject_X11
	{
	public:
		PongFieldGraphicsObject(const Coord& _size);
		void Paint();

	protected:

	private:
		PongFieldGraphicsObject();
		XColor color;
		Coord size;
	};
};



#endif /* INC_GAMELOGIC_PONGFIELDGAMEOBJECT_H_ */
