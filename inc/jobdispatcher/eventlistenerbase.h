/*
 * eventlistenerbase.h
 *
 *  Created on: Feb 7, 2016
 *      Author: janne
 */

#ifndef INC_EVENTLISTENERBASE_H_
#define INC_EVENTLISTENERBASE_H_

#include <vector>
#include <map>

class EventDataBase
{
public:
	virtual ~EventDataBase() {}
	virtual EventDataBase* clone() const = 0;
protected:

public:
};

class EventListenerBase
{
public:
	virtual ~EventListenerBase() {}
	virtual void HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr) = 0;

protected:

private:

};

typedef std::vector<EventListenerBase*> EventListenerBasePtrVector;

typedef std::map<uint32_t, EventListenerBasePtrVector> EventNoToEventListenersMap;


#endif /* INC_EVENTLISTENERBASE_H_ */
