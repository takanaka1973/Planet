//
//	Universe�N���X�̒�`
//

#pragma once

#pragma warning(disable:4786)

#include <set>
#include "StarList.h"
#include "UniverseObserver.h"

class StarFactory;

//
//	�F��
//
class Universe
{
public:

	// �R���X�g���N�^
	Universe();
	// �f�X�g���N�^
	virtual ~Universe();

	// ����������
	virtual bool init();
	// �I������
	virtual void term();

	// �ώ@�҂�o�^����
	virtual void registerObserver(UniverseObserver *observer);
	// �ώ@�҂�o�^��������
	virtual void unregisterObserver(UniverseObserver *observer);

	// ���Ԃ̌o�߂�ʒm����
	virtual void tick(int timespan);
	// �����_�����O����
	virtual void render();

private:

	bool m_initialized;				// �������ς݂��ǂ���
	StarFactory *m_star_factory;	// ���̃t�@�N�g��
	StarList m_stars;				// ��

	// �ώ@��
	typedef std::set<UniverseObserver*> UniverseObserverContainer;
	UniverseObserverContainer m_observers;

	Universe(const Universe&);
	Universe& operator=(const Universe&);
};

