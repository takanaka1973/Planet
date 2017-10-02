//
//	WinMain関数の実装
//

#include "common.h"
#include "Application.h"

//
//	エントリポイント
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

