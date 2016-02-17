/*
 * pongclone.h
 *
 *  Created on: Feb 17, 2016
 *      Author: janne
 */

#ifndef INC_PONGCLONE_H_
#define INC_PONGCLONE_H_

#include "jobdispatcher/eventlistenerbase.h"

class PongClone : public EventListenerBase
{
public:
	PongClone();
	void HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr);

protected:

private:
};



#endif /* INC_PONGCLONE_H_ */
