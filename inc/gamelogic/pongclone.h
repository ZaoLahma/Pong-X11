/*
 * pongclone.h
 *
 *  Created on: Feb 17, 2016
 *      Author: janne
 */

#ifndef INC_PONGCLONE_H_
#define INC_PONGCLONE_H_

#include "jobdispatcher/eventlistenerbase.h"

class PongBallGameObject;
class PongFieldGameObject;
class PongPaddleGameObject;
class PongAI;

class PongClone : public EventListenerBase
{
public:
	PongClone();
	~PongClone();
	void HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr);

protected:

private:
	PongBallGameObject* pongBallPtr;
	PongFieldGameObject* pongFieldPtr;
	PongPaddleGameObject* pongPaddleOnePtr;
	PongPaddleGameObject* pongPaddleTwoPtr;
	GraphicsObjectString_X11* playerOneScoreText;
	GraphicsObjectString_X11* playerTwoScoreText;
	PongAI* pongAITwo;
	PongAI* pongAIOne;

	uint8_t playerOneScore;
	uint8_t playerTwoScore;

	Coord fieldSize;
};



#endif /* INC_PONGCLONE_H_ */
