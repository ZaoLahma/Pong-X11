/*
 * jobdispatcher.h
 *
 *  Created on: Feb 3, 2016
 *      Author: janne
 */

#ifndef INC_JOBDISPATCHER_H_
#define INC_JOBDISPATCHER_H_

#include <mutex>
#include <atomic>
#include <map>
#include <cinttypes>
#include <chrono>

#include <vector>
#include <condition_variable>

#include "eventlistenerbase.h"
#include "internal/timerstorage.h"
#include "internal/worker.h"
#include "jobbase.h"

#define TIMEOUT_EVENT_ID 0x0 //Move me to appropriate place

class JobDispatcher
{
public:
	static void DropInstance();

	virtual ~JobDispatcher();

	//Main access point
	static JobDispatcher* GetApi();

	//API
	void Log(const char* formatString, ...);

	void ExecuteJob(JobBase* jobPtr);

	void ExecuteJobIn(JobBase* jobPtr, const uint32_t ms);

	void SubscribeToEvent(const uint32_t eventNo, EventListenerBase* eventListenerPtr);

	void UnsubscribeToEvent(const uint32_t eventNo, EventListenerBase* eventListenerPtr);

	void RaiseEvent(const uint32_t eventNo, const EventDataBase* eventDataPtr);

	void RaiseEventIn(const uint32_t eventNo, const EventDataBase* eventDataPtr, const uint32_t ms);

	void WaitForExecutionFinished();

	void NotifyExecutionFinished();

protected:

private:
	std::string GetTimeStamp();

	//Private attrbutes
	uint32_t noOfCores;

	std::mutex workerCreationMutex;

	std::mutex eventListenersAccessMutex;

	std::mutex executionFinishedNotificationMutex;
	std::unique_lock<std::mutex> executionFinishedNotificationLock;
	std::condition_variable executionFinishedNotification;

	typedef std::vector<Worker*> WorkerPtrVector;

	WorkerPtrVector workers;

	JobQueue jobQueuePtr;

	EventNoToEventListenersMap eventEventListeners;

	TimerStorage timerStorage;

	JobDispatcher();
	static std::mutex instanceCreationMutex;
	static JobDispatcher* instance;
};



#endif /* INC_JOBDISPATCHER_H_ */
