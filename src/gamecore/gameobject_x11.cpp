/*
 * gameobject_x11.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: janne
 */

#include "gamecore/gameobject_x11.h"

GameObject_X11::GameObject_X11(const Coord& _pos, const Coord& _mov) :
GraphicsObject_X11(_pos),
mov(_mov)
{

}

void GameObject_X11::Update()
{
	Coord newPos = mov + GetPos();
	SetPos(newPos);
}

void GameObject_X11::Paint()
{
	XFillArc(winDataPtr->displayPtr, *winDataPtr->winPtr, graphicsContext, pos.GetX() - 2, pos.GetY(), 80, 80, 0 * 64, 90 * 64);
}
