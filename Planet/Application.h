//
//	Applicationクラスの定義
//

#pragma once

#include "ClockObserver.h"

class Clock;
class Universe;
class MainWindow;

//
//	アプリケーション
//
class Application : public ClockObserver
{
public:

	// コンストラクタ
	Application();
	// デストラクタ
	virtual ~Application();

	// 初期化する
	virtual bool init();
	// 実行する
	virtual int run();
	// 終了する
	virtual void term();

	// メインウィンドウが削除されたことを通知する
	virtual void notifyMainWindowDestroyed(MainWindow *sender);

	// 時間の経過を通知する <override>
	virtual void tick(Clock *sender, int timespan);

private:

	bool m_initialized;			// 初期化済みかどうか
	bool m_running;				// 実行中かどうか

	Clock *m_clock;				// 時計
	Universe *m_universe;		// 宇宙
	MainWindow *m_main_window;	// メインウィンドウ

	Application(const Application&);
	Application& operator=(const Application&);
};

