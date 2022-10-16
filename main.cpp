#include "AppWindow.h"
#include <time.h>
#include <stdlib.h>



int main()
{
	srand(time(NULL));

	AppWindow app;
	if (app.init())
	{
		while (app.isRun())
		{
			app.broadcast();
		}
	}

	return 0;
}