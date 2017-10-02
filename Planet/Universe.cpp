//
//	Universe�N���X�̎���
//

#include "common.h"
#include "Universe.h"
#include "StarFactory.h"
#include "GravityFieldList.h"

//
//	�R���X�g���N�^
//
Universe::Universe()
: m_initialized(false),
  m_star_factory(new StarFactory())
{
}

//
//	�f�X�g���N�^
//
Universe::~Universe()
{
	term();
	delete m_star_factory;
}

//
//	����������
//
bool Universe::init()
{
	if (m_initialized) {
		return false;	// ���łɏ������ς�
	}

	// �����쐬����
	if (!m_star_factory->createStars(m_stars)) {
		return false;
	}

	m_initialized = true;
	return true;
}

//
//	�I������
//
void Universe::term()
{
	if (m_initialized) {
	// �������ς݂̏ꍇ�̂�
		// �����폜����
		StarList::iterator it = m_stars.begin();
		for (; it != m_stars.end(); ++it) {
			delete *it;
		}
		m_stars.clear();

		m_initialized = false;
	}
}

//
//	�ώ@�҂�o�^����
//
void Universe::registerObserver(UniverseObserver *observer)
{
	assert(observer != NULL);
	m_observers.insert(observer);
}

//
//	�ώ@�҂�o�^��������
//
void Universe::unregisterObserver(UniverseObserver *observer)
{
	assert(observer != NULL);
	m_observers.erase(observer);
}

//
//	���Ԃ̌o�߂�ʒm����
//
void Universe::tick(int timespan)
{
	assert(m_initialized);
	assert(timespan > 0);

	// �d�͏�̃��X�g���쐬����
	GravityFieldList gravity_fields;
	StarList::iterator it1 = m_stars.begin();
	for (; it1 != m_stars.end(); ++it1) {
		GravityField *gf = (*it1)->getGravityField();
		if (gf != NULL) {
			gravity_fields.push_back(gf);
		}
	}

	// ���Ɏ��Ԃ̌o�߂�ʒm����
	StarList::iterator it2 = m_stars.begin();
	for (; it2 != m_stars.end(); ++it2) {
		(*it2)->tick(timespan, gravity_fields);
	}

	// �S�Ă̊ώ@�҂ɃV�[�����ω��������Ƃ�ʒm����
	UniverseObserverContainer::iterator it3 = m_observers.begin();
	for (; it3 != m_observers.end(); ++it3) {
		(*it3)->notifySceneChanged(this);
	}
}

//
//	�����_�����O����
//
void Universe::render()
{
	assert(m_initialized);

	// ���Ɍ��̕��˂��w��
	StarList::iterator it1 = m_stars.begin();
	for (; it1 != m_stars.end(); ++it1) {
		(*it1)->emitLight();
	}

	// ���Ƀ����_�����O���w��
	StarList::iterator it2 = m_stars.begin();
	for (; it2 != m_stars.end(); ++it2) {
		(*it2)->render();
	}
}

