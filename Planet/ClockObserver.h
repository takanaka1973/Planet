//
//	ClockObserverクラスの定義
//

#pragma once

class Clock;

//
//	時計の観察者
//
class ClockObserver
{
public:

	// デストラクタ
	virtual ~ClockObserver() {}

	// 時間の経過を通知する
	virtual void tick(Clock *sender, int timespan) = 0;

};

