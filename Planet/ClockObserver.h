//
//	ClockObserver�N���X�̒�`
//

#pragma once

class Clock;

//
//	���v�̊ώ@��
//
class ClockObserver
{
public:

	// �f�X�g���N�^
	virtual ~ClockObserver() {}

	// ���Ԃ̌o�߂�ʒm����
	virtual void tick(Clock *sender, int timespan) = 0;

};

