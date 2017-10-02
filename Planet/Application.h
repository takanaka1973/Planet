//
//	Application�N���X�̒�`
//

#pragma once

#include "ClockObserver.h"

class Clock;
class Universe;
class MainWindow;

//
//	�A�v���P�[�V����
//
class Application : public ClockObserver
{
public:

	// �R���X�g���N�^
	Application();
	// �f�X�g���N�^
	virtual ~Application();

	// ����������
	virtual bool init();
	// ���s����
	virtual int run();
	// �I������
	virtual void term();

	// ���C���E�B���h�E���폜���ꂽ���Ƃ�ʒm����
	virtual void notifyMainWindowDestroyed(MainWindow *sender);

	// ���Ԃ̌o�߂�ʒm���� <override>
	virtual void tick(Clock *sender, int timespan);

private:

	bool m_initialized;			// �������ς݂��ǂ���
	bool m_running;				// ���s�����ǂ���

	Clock *m_clock;				// ���v
	Universe *m_universe;		// �F��
	MainWindow *m_main_window;	// ���C���E�B���h�E

	Application(const Application&);
	Application& operator=(const Application&);
};

