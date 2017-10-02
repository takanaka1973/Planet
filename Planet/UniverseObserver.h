//
//	UniverseObserverクラスの定義
//

#pragma once

class Universe;

//
//	宇宙の観察者
//
class UniverseObserver
{
public:

	// デストラクタ
	virtual ~UniverseObserver() {}

	// シーンが変化したことを通知する
	virtual void notifySceneChanged(Universe *sender) = 0;

};

