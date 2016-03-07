#include "../inc/coord.h"
#include "jobdispatcher/jobdispatcher.h"
#include "winhandling/graphicsobjectstorage_x11.h"
#include "winhandling/winapi_x11.h"
#include "gamelogic/pongclone.h"

int main(void)
{
	JobDispatcher::GetApi()->Log("Main called");

	WinApi_X11 winApi(Coord(300, 300));

	PongClone* pongClonePtr = new PongClone();

	winApi.EventLoop();

	delete pongClonePtr;
	pongClonePtr = nullptr;

	GraphicsObjectStorage_X11::GetApi()->DropInstance();

	JobDispatcher::GetApi()->Log("Execution finished");

	JobDispatcher::GetApi()->DropInstance();

	return 0;
}
