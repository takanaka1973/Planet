//
//	UniverseObserver�N���X�̒�`
//

#pragma once

class Universe;

//
//	�F���̊ώ@��
//
class UniverseObserver
{
public:

	// �f�X�g���N�^
	virtual ~UniverseObserver() {}

	// �V�[�����ω��������Ƃ�ʒm����
	virtual void notifySceneChanged(Universe *sender) = 0;

};

