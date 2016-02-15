#include "jobdispatcher/jobdispatcher.h"
#include "winhandling/winapi_x11.h"

int main(void)
{
	WinApi_X11 window;

	window.EventLoop();

	JobDispatcher::GetApi()->DropInstance();

	return 0;
}
