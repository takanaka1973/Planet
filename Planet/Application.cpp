//
//	Applicationクラスの実装
//

#include "common.h"
#include "Application.h"
#include "Clock.h"
#include "Universe.h"
#include "MainWindow.h"

//
//	コンストラクタ
//
Application::Application()
: m_initialized(false),
  m_running(false)
{
	m_clock = new Clock(this);
	m_universe = new Universe();
	m_main_window = new MainWindow(this, m_universe);
}

//
//	デストラクタ
//
Application::~Application()
{
	term();

	delete m_main_window;
	delete m_universe;
	delete m_clock;
}

//
//	初期化する
//
bool Application::init()
{
	if (m_initialized) {
		return false;	// すでに初期化済み
	}

	// 宇宙を初期化する
	if (!m_universe->init()) {
		return false;
	}

	// メインウィンドウを作成する
	if (!m_main_window->create(
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT)) {
		m_universe->term();
		return false;
	}

	m_main_window->optimizeSize();

	m_initialized = true;
	return true;
}

//
//	実行する
//
int Application::run()
{
	assert(m_initialized);

	int ret = 0;

	// メインウィンドウを表示する
	m_main_window->show();
	m_main_window->update();

	// 時計を始動
	if (m_clock->start()) {

		m_running = true;

		// メッセージループ
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		m_running = false;

		// 時計を停止
		m_clock->stop();

		ret = msg.wParam;
	}

	return ret;
}

//
//	終了する
//
void Application::term()
{
	if (m_initialized) {
		m_main_window->destroy();
		m_universe->term();
		m_initialized = false;
	}
}

//
//	メインウィンドウが削除されたことを通知する
//
void Application::notifyMainWindowDestroyed(MainWindow *sender)
{
	assert(sender == m_main_window);

	if (m_running) {
		// メッセージループを終了させる
		PostQuitMessage(1);
	}
}

//
//	時間の経過を通知する
//
void Application::tick(Clock *sender, int timespan)
{
	assert(sender == m_clock);
	assert(timespan > 0);

	// 宇宙に伝達する
	m_universe->tick(timespan);
}

