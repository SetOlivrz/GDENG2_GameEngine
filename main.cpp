#include "AppWindow.h"

int main()
{
	AppWindow app;

	// game loop
	if (app.init())
	{
		while (app.isRun())
		{
			app.broadcast();
		}
	}

	return 0;
}