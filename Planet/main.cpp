//
//	WinMain�֐��̎���
//

#include "common.h"
#include "Application.h"

//
//	�G���g���|�C���g
//
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	int ret = 0;
	Application app;

	if (app.init()) {
		ret = app.run();
		app.term();
	}

	return ret;
}

