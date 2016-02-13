#include "jobdispatcher/jobdispatcher.h"

int main(void)
{
	JobDispatcher::GetApi()->DropInstance();

	return 0;
}
