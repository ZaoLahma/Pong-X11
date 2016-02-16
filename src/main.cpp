#include "../inc/coord.h"
#include "jobdispatcher/jobdispatcher.h"
#include "winhandling/graphicsobjectstorage_x11.h"
#include "winhandling/winapi_x11.h"

int main(void)
{
	WinApi_X11 winApi(Coord(300, 300));

	winApi.EventLoop();

	GraphicsObjectStorage_X11::GetApi()->DropInstance();

	JobDispatcher::GetApi()->DropInstance();

	return 0;
}
