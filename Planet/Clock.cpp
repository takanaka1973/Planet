//
//	Clock�N���X�̎���
//

#include "common.h"
#include "Clock.h"
#include "ClockObserver.h"

// �^�C�}�[�̃R�[���o�b�N�Ԋu(ms)
static const UINT TIMER_INTERVAL = 10;

// 1 timespan�̎���(ms)
static const DWORD UNIT_TIMESPAN_MS = 100;

// �^�C�}�[ID�Ǝ��v�I�u�W�F�N�g�̃}�b�v
Clock::ClockMap Clock::s_clock_map;

//
//	�R���X�g���N�^
//
Clock::Clock(ClockObserver *observer)
: m_observer(observer),
  m_working(false),
  m_timer_id(0),
  m_last_time(0)
{
	assert(observer != NULL);
}

//
//	�f�X�g���N�^
//
Clock::~Clock()
{
	stop();
}

//
//	�n������
//
bool Clock::start()
{
	bool ret = false;

	if (!m_working) {
		UINT timer_id = SetTimer(NULL, 0, TIMER_INTERVAL, baseTimerCallback);
		if (timer_id != 0) {
			s_clock_map.insert(ClockMap::value_type(timer_id, this));
			m_working = true;
			m_timer_id = timer_id;
			m_last_time = GetTickCount();
			ret = true;
		}
	}

	return ret;
}

//
//	��~����
//
void Clock::stop()
{
	if (m_working) {
		verify(KillTimer(NULL, m_timer_id));
		s_clock_map.erase(m_timer_id);
		m_working = false;
		m_timer_id = 0;
		m_last_time = 0;
	}
}

//
//	�^�C�}�[�̃R�[���o�b�N�֐�
//
void Clock::timerCallback()
{
	assert(m_working);

	DWORD current_time = GetTickCount();
	assert(current_time >= m_last_time);

	int timespan = ( current_time - m_last_time ) / UNIT_TIMESPAN_MS;

	if (timespan > 0) {
		m_observer->tick(this, timespan);
		m_last_time += timespan * UNIT_TIMESPAN_MS;
	}
}

//
//	�^�C�}�[�̃R�[���o�b�N�֐�(��\)
//
void CALLBACK Clock::baseTimerCallback(
	HWND handle, UINT message, UINT timer_id, DWORD system_time)
{
	ClockMap::iterator it = s_clock_map.find(timer_id);
	if (it != s_clock_map.end()) {
		it->second->timerCallback();
	}
}

