/*
 * gameobject_11.h
 *
 *  Created on: Feb 18, 2016
 *      Author: janne
 */

#ifndef INC_GAMECORE_GAMEOBJECT_X11_H_
#define INC_GAMECORE_GAMEOBJECT_X11_H_

#include <map>
#include "winhandling/graphicsobject_x11.h"

#include "jobdispatcher/jobdispatcher.h"
#include "coord.h"

class GameObject_X11
{
public:
	GameObject_X11(const Coord& _pos, const Coord& _mov);
	virtual ~GameObject_X11();

	virtual void Update() = 0;

	uint32_t GetGameObjectId() const;

	Coord& GetPos();

	Coord& GetMov();

	void SetMov(const Coord&);

	GraphicsObjectVector& GetGraphicsObjects();

	const Coord& GetOnCollision();

protected:
	const uint32_t gameObjectId;
	Coord pos;
	Coord mov;
	Coord onCollision;
	GraphicsObjectVector graphicsObjects;

private:
	GameObject_X11();
};


#endif /* INC_GAMECORE_GAMEOBJECT_X11_H_ */
