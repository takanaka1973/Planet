//
//	Clock�N���X�̒�`
//

#pragma once

#pragma warning(disable:4786)

#include <map>

class ClockObserver;

//
//	���v
//
class Clock
{
public:

	// �R���X�g���N�^
	explicit Clock(ClockObserver *observer);
	// �f�X�g���N�^
	virtual ~Clock();

	// �n������
	virtual bool start();
	// ��~����
	virtual void stop();

private:

	// �^�C�}�[�̃R�[���o�b�N�֐�
	void timerCallback();

	// �^�C�}�[�̃R�[���o�b�N�֐�(��\)
	static void CALLBACK baseTimerCallback(
		HWND handle, UINT message, UINT timer_id, DWORD system_time);

	// �^�C�}�[ID�Ǝ��v�I�u�W�F�N�g�̃}�b�v
	typedef std::map<UINT, Clock*> ClockMap;
	static ClockMap s_clock_map;

	ClockObserver *m_observer;	// �ώ@��
	bool m_working;				// ���쒆���ǂ���
	UINT m_timer_id;			// �^�C�}�[ID
	DWORD m_last_time;			// �O��̎���

	Clock(const Clock&);
	Clock& operator=(const Clock&);
};

