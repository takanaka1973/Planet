//
//	Application�N���X�̎���
//

#include "common.h"
#include "Application.h"
#include "Clock.h"
#include "Universe.h"
#include "MainWindow.h"

//
//	�R���X�g���N�^
//
Application::Application()
: m_initialized(false),
  m_running(false)
{
	m_clock = new Clock(this);
	m_universe = new Universe();
	m_main_window = new MainWindow(this, m_universe);
}

//
//	�f�X�g���N�^
//
Application::~Application()
{
	term();

	delete m_main_window;
	delete m_universe;
	delete m_clock;
}

//
//	����������
//
bool Application::init()
{
	if (m_initialized) {
		return false;	// ���łɏ������ς�
	}

	// �F��������������
	if (!m_universe->init()) {
		return false;
	}

	// ���C���E�B���h�E���쐬����
	if (!m_main_window->create(
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT)) {
		m_universe->term();
		return false;
	}

	m_main_window->optimizeSize();

	m_initialized = true;
	return true;
}

//
//	���s����
//
int Application::run()
{
	assert(m_initialized);

	int ret = 0;

	// ���C���E�B���h�E��\������
	m_main_window->show();
	m_main_window->update();

	// ���v���n��
	if (m_clock->start()) {

		m_running = true;

		// ���b�Z�[�W���[�v
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		m_running = false;

		// ���v���~
		m_clock->stop();

		ret = msg.wParam;
	}

	return ret;
}

//
//	�I������
//
void Application::term()
{
	if (m_initialized) {
		m_main_window->destroy();
		m_universe->term();
		m_initialized = false;
	}
}

//
//	���C���E�B���h�E���폜���ꂽ���Ƃ�ʒm����
//
void Application::notifyMainWindowDestroyed(MainWindow *sender)
{
	assert(sender == m_main_window);

	if (m_running) {
		// ���b�Z�[�W���[�v���I��������
		PostQuitMessage(1);
	}
}

//
//	���Ԃ̌o�߂�ʒm����
//
void Application::tick(Clock *sender, int timespan)
{
	assert(sender == m_clock);
	assert(timespan > 0);

	// �F���ɓ`�B����
	m_universe->tick(timespan);
}

