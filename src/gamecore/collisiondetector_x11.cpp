/*
 * collisiondetector_x11.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: janne
 */

#include "gamecore/collisiondetector_x11.h"
#include "gamecore/gameobjectstorage_x11.h"

#include <math.h>

void CollisionDetector_X11::Detect(uint32_t deltaTimeMs)
{
	/*
	 * Naive implementation treating all objects as circles
	 */

	GameObjectPair allGameObjects = GameObjectStorage_X11::GetApi()->GetAllObjects();

	GameObjectMap::iterator objectIter = allGameObjects.first;

	for(; objectIter != allGameObjects.second; ++objectIter)
	{
		GameObjectMap::iterator otherObjectIter = allGameObjects.first;

		for(; otherObjectIter != allGameObjects.second; ++otherObjectIter)
		{
			if(otherObjectIter->first == objectIter->first)
			{
				continue;
			}

			GameObject_X11* gameObject = objectIter->second;
			GameObject_X11* otherGameObject = otherObjectIter->second;

			GraphicsObjectVector& graphicsObjects = gameObject->GetGraphicsObjects();
			GraphicsObjectVector& otherGraphicsObjects = otherGameObject->GetGraphicsObjects();

			/*
			 * Oof... this is bad. I don't like this even one bit.
			 */
			if(true == CollisionOccurred(graphicsObjects, otherGraphicsObjects))
			{
				//Do stuff...
			}
		}
	}
}

bool CollisionDetector_X11::CollisionOccurred(GraphicsObjectVector& objects_1, GraphicsObjectVector& objects_2)
{
	GraphicsObjectVector::iterator graphicsIter_1 = objects_1.begin();
	GraphicsObjectVector::iterator graphicsIter_2 = objects_2.begin();

	for(; graphicsIter_1 != objects_1.end(); ++graphicsIter_1)
	{
		for(; graphicsIter_2 != objects_2.end(); ++graphicsIter_2)
		{
			double distance = sqrt((*graphicsIter_1)->GetPos().GetX() * (*graphicsIter_2)->GetPos().GetX() +
								   (*graphicsIter_1)->GetPos().GetY() * (*graphicsIter_2)->GetPos().GetY());

			if(distance < (((*graphicsIter_1)->GetSize().GetX() + (*graphicsIter_2)->GetSize().GetX()) / 2))
			{
				//Collision!
				return true;
			}
		}
	}

	return false;
}
