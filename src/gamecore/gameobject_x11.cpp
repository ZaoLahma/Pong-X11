/*
 * gameobject_x11.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: janne
 */

#include "gamecore/gameobject_x11.h"
#include "gamecore/gameobjectstorage_x11.h"
#include "jobdispatcher/uniqueidprovider.h"


GameObject_X11::GameObject_X11(const Coord& _pos, const Coord& _mov) :
gameObjectId(UniqueIdProvider::GetApi()->GetUniqueId()),
pos(_pos),
mov(_mov),
onCollision(Coord(1, 1))
{
	GameObjectStorage_X11::GetApi()->AddObject(this);
}

GameObject_X11::~GameObject_X11()
{
	GameObjectStorage_X11::GetApi()->RemoveObject(this);

	for(auto & graphicsObject: graphicsObjects)
	{
		delete graphicsObject;
	}
}

Coord& GameObject_X11::GetPos()
{
	return pos;
}

Coord& GameObject_X11::GetMov()
{
	return mov;
}

void GameObject_X11::SetMov(const Coord& _coord)
{
	this->mov = _coord;
}

GraphicsObjectVector& GameObject_X11::GetGraphicsObjects()
{
	return graphicsObjects;
}

uint32_t GameObject_X11::GetGameObjectId() const
{
	return gameObjectId;
}

const Coord& GameObject_X11::GetOnCollision()
{
	return onCollision;
}
