/*
 * gameobjectstorage_x11.h
 *
 *  Created on: Mar 2, 2016
 *      Author: janne
 */

#ifndef INC_GAMECORE_GAMEOBJECTSTORAGE_X11_H_
#define INC_GAMECORE_GAMEOBJECTSTORAGE_X11_H_

#include <mutex>
#include "gameobject_x11.h"

class GameObjectStorage_X11
{
public:
	GameObjectStorage_X11* GetApi();


protected:

private:
	GameObjectStorage_X11();
	static GameObjectStorage_X11* instance;
	static std::mutex instanceCreationMutex;
};



#endif /* INC_GAMECORE_GAMEOBJECTSTORAGE_X11_H_ */
