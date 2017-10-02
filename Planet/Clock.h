//
//	Clockクラスの定義
//

#pragma once

#pragma warning(disable:4786)

#include <map>

class ClockObserver;

//
//	時計
//
class Clock
{
public:

	// コンストラクタ
	explicit Clock(ClockObserver *observer);
	// デストラクタ
	virtual ~Clock();

	// 始動する
	virtual bool start();
	// 停止する
	virtual void stop();

private:

	// タイマーのコールバック関数
	void timerCallback();

	// タイマーのコールバック関数(代表)
	static void CALLBACK baseTimerCallback(
		HWND handle, UINT message, UINT timer_id, DWORD system_time);

	// タイマーIDと時計オブジェクトのマップ
	typedef std::map<UINT, Clock*> ClockMap;
	static ClockMap s_clock_map;

	ClockObserver *m_observer;	// 観察者
	bool m_working;				// 動作中かどうか
	UINT m_timer_id;			// タイマーID
	DWORD m_last_time;			// 前回の時間

	Clock(const Clock&);
	Clock& operator=(const Clock&);
};

