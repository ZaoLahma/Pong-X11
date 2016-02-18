/*
 * gameobject_11.h
 *
 *  Created on: Feb 18, 2016
 *      Author: janne
 */

#ifndef INC_GAMECORE_GAMEOBJECT_X11_H_
#define INC_GAMECORE_GAMEOBJECT_X11_H_


#include "gameobject_if.h"
#include "winhandling/graphicsobject_x11.h"
#include "coord.h"

class GameObject_X11 : public GameObjectIf, public GraphicsObject_X11
{
public:
	GameObject_X11(const Coord& _pos, const Coord& _mov);

	virtual void Update();

	void Paint();

protected:
	Coord mov;

private:
	GameObject_X11();
};


#endif /* INC_GAMECORE_GAMEOBJECT_X11_H_ */
