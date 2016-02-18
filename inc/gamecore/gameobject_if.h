/*
 * gameobject.h
 *
 *  Created on: Feb 18, 2016
 *      Author: janne
 */

#ifndef INC_GAMECORE_GAMEOBJECT_IF_H_
#define INC_GAMECORE_GAMEOBJECT_IF_H_

class GameObjectIf
{
public:
	virtual ~GameObjectIf();

	virtual void Update() = 0;

protected:

private:
};


#endif /* INC_GAMECORE_GAMEOBJECT_IF_H_ */
