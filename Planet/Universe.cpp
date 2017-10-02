//
//	Universeクラスの実装
//

#include "common.h"
#include "Universe.h"
#include "StarFactory.h"
#include "GravityFieldList.h"

//
//	コンストラクタ
//
Universe::Universe()
: m_initialized(false),
  m_star_factory(new StarFactory())
{
}

//
//	デストラクタ
//
Universe::~Universe()
{
	term();
	delete m_star_factory;
}

//
//	初期化する
//
bool Universe::init()
{
	if (m_initialized) {
		return false;	// すでに初期化済み
	}

	// 星を作成する
	if (!m_star_factory->createStars(m_stars)) {
		return false;
	}

	m_initialized = true;
	return true;
}

//
//	終了する
//
void Universe::term()
{
	if (m_initialized) {
	// 初期化済みの場合のみ
		// 星を削除する
		StarList::iterator it = m_stars.begin();
		for (; it != m_stars.end(); ++it) {
			delete *it;
		}
		m_stars.clear();

		m_initialized = false;
	}
}

//
//	観察者を登録する
//
void Universe::registerObserver(UniverseObserver *observer)
{
	assert(observer != NULL);
	m_observers.insert(observer);
}

//
//	観察者を登録解除する
//
void Universe::unregisterObserver(UniverseObserver *observer)
{
	assert(observer != NULL);
	m_observers.erase(observer);
}

//
//	時間の経過を通知する
//
void Universe::tick(int timespan)
{
	assert(m_initialized);
	assert(timespan > 0);

	// 重力場のリストを作成する
	GravityFieldList gravity_fields;
	StarList::iterator it1 = m_stars.begin();
	for (; it1 != m_stars.end(); ++it1) {
		GravityField *gf = (*it1)->getGravityField();
		if (gf != NULL) {
			gravity_fields.push_back(gf);
		}
	}

	// 星に時間の経過を通知する
	StarList::iterator it2 = m_stars.begin();
	for (; it2 != m_stars.end(); ++it2) {
		(*it2)->tick(timespan, gravity_fields);
	}

	// 全ての観察者にシーンが変化したことを通知する
	UniverseObserverContainer::iterator it3 = m_observers.begin();
	for (; it3 != m_observers.end(); ++it3) {
		(*it3)->notifySceneChanged(this);
	}
}

//
//	レンダリングする
//
void Universe::render()
{
	assert(m_initialized);

	// 星に光の放射を指示
	StarList::iterator it1 = m_stars.begin();
	for (; it1 != m_stars.end(); ++it1) {
		(*it1)->emitLight();
	}

	// 星にレンダリングを指示
	StarList::iterator it2 = m_stars.begin();
	for (; it2 != m_stars.end(); ++it2) {
		(*it2)->render();
	}
}

