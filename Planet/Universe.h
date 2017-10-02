//
//	Universeクラスの定義
//

#pragma once

#pragma warning(disable:4786)

#include <set>
#include "StarList.h"
#include "UniverseObserver.h"

class StarFactory;

//
//	宇宙
//
class Universe
{
public:

	// コンストラクタ
	Universe();
	// デストラクタ
	virtual ~Universe();

	// 初期化する
	virtual bool init();
	// 終了する
	virtual void term();

	// 観察者を登録する
	virtual void registerObserver(UniverseObserver *observer);
	// 観察者を登録解除する
	virtual void unregisterObserver(UniverseObserver *observer);

	// 時間の経過を通知する
	virtual void tick(int timespan);
	// レンダリングする
	virtual void render();

private:

	bool m_initialized;				// 初期化済みかどうか
	StarFactory *m_star_factory;	// 星のファクトリ
	StarList m_stars;				// 星

	// 観察者
	typedef std::set<UniverseObserver*> UniverseObserverContainer;
	UniverseObserverContainer m_observers;

	Universe(const Universe&);
	Universe& operator=(const Universe&);
};

