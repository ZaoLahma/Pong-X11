/*
 * collisiondetector_x11.h
 *
 *  Created on: Mar 21, 2016
 *      Author: janne
 */

#ifndef INC_GAMECORE_COLLISIONDETECTOR_X11_H_
#define INC_GAMECORE_COLLISIONDETECTOR_X11_H_

#include <cstdint>
#include "winhandling/graphicsobject_x11.h"

class CollisionDetector_X11
{
public:
	void Detect(uint32_t deltaTimeMs);

protected:

private:
	bool CollisionOccurred(GraphicsObjectVector& objects_1, GraphicsObjectVector& objects_2);
};



#endif /* INC_GAMECORE_COLLISIONDETECTOR_X11_H_ */
