//
//	MainWindow�N���X�̎���
//

#include "common.h"
#include "MainWindow.h"
#include "Application.h"
#include "Universe.h"
#include "View.h"
#include "RendererSetting.h"
#include "resource.h"

// �E�B���h�E�X�^�C��
static const DWORD WINDOW_STYLE =
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN;
// �E�B���h�E�g���X�^�C��
static const DWORD WINDOW_EX_STYLE = 0;

// �e�r���[�̕�
static const int VIEW_WIDTH = 400;
// �e�r���[�̍���
static const int VIEW_HEIGHT = 400;
// �r���[�̊Ԋu
static const int VIEW_INTERVAL = 5;

// �^�C�g��
static LPCTSTR TITLE = _T("Planet");

//
//	�R���X�g���N�^
//
MainWindow::MainWindow(Application *app, Universe *universe)
: CustomWindow(NULL, WINDOW_STYLE, WINDOW_EX_STYLE),
  m_app(app)
{
	assert(app != NULL);
	assert(universe != NULL);

	// ���C���r���[���쐬����
	RendererSetting *main_view_setting = new RendererSetting();
	main_view_setting->setCameraInitialPosition(Vector3D(0.0, 0.0, 80.0));
	main_view_setting->setCameraInitialRefPoint(Vector3D(0.0, 0.0, 0.0));
	main_view_setting->setCameraInitialUpDirection(Vector3D(0.0, 1.0, 0.0));
	m_main_view = new View(this, universe, main_view_setting);

	// �T�u�r���[���쐬����
	RendererSetting *sub_view_setting = new RendererSetting();
	sub_view_setting->setCameraInitialPosition(Vector3D(-70.0, 0.0, 20.0));
	sub_view_setting->setCameraInitialRefPoint(Vector3D(0.0, 0.0, 0.0));
	sub_view_setting->setCameraInitialUpDirection(Vector3D(0.0, 1.0, 0.0));
	m_sub_view = new View(this, universe, sub_view_setting);
}

//
//	�f�X�g���N�^
//
MainWindow::~MainWindow()
{
	destroy();

	delete m_sub_view;
	delete m_main_view;
}

//
//	�쐬����
//
bool MainWindow::create(int x, int y, int width, int height)
{
	if (getHandle() != NULL) {
		return false;	// ���łɍ쐬�ς�
	}

	bool completed = false;
	do {
		// �����̃E�B���h�E���쐬����
		if (!CustomWindow::create(x, y, width, height)) {
			break;
		}

		// �r���[�̃E�B���h�E���쐬����
		if (!m_main_view->create(0, 0, VIEW_WIDTH, VIEW_HEIGHT)) {
			break;
		}
		if (!m_sub_view->create(VIEW_WIDTH + VIEW_INTERVAL, 0, VIEW_WIDTH, VIEW_HEIGHT)) {
			break;
		}

		// �^�C�g����ݒ肷��
		setTitle(TITLE);

		// �A�C�R����ݒ肷��(�G���[����)
		bool res = setIcon(IDI_APP);

		completed = true;
	} while (false);

	if (!completed) {
		// ���s�����̂Ō�n��
		m_sub_view->destroy();
		m_main_view->destroy();
		CustomWindow::destroy();
		return false;
	}

	return true;
}

//
//	�폜����
//
void MainWindow::destroy()
{
	if (getHandle() != NULL) {
	// �쐬�ς݂̏ꍇ�̂�

		// �r���[�̃E�B���h�E���폜����
		m_sub_view->destroy();
		m_main_view->destroy();

		// �����̃E�B���h�E���폜����
		CustomWindow::destroy();

		// �A�v���P�[�V�����ɒʒm����
		m_app->notifyMainWindowDestroyed(this);

	}
}

//
//	�T�C�Y���œK������
//
void MainWindow::optimizeSize()
{
	assert(getHandle() != NULL);

	// �E�B���h�E�̋�`���擾����
	RECT rc;
	ZeroMemory(&rc, sizeof(RECT));
	getRect(&rc);
	int window_width = rc.right - rc.left;
	int window_height = rc.bottom - rc.top;

	// �N���C�A���g�̈�̃T�C�Y���擾����
	int client_width = 0;
	int client_height = 0;
	getClientAreaSize(&client_width, &client_height);

	// ���T�C�Y����
	int optimized_width = VIEW_WIDTH * 2 + VIEW_INTERVAL + (window_width - client_width);
	int optimized_height = VIEW_HEIGHT + (window_height - client_height);
	resize(rc.left, rc.top, optimized_width, optimized_height);
}

//
//	WM_SETFOCUS�̃��b�Z�[�W�n���h��
//
void MainWindow::onSetFocus()
{
	assert(getHandle() != NULL);

	// ��ɃT�u�r���[�Ƀt�H�[�J�X��ݒ肷��
	m_sub_view->setFocus();
}

//
//	WM_PAINT�̃��b�Z�[�W�n���h��(�f�o�C�X�R���e�L�X�g�t��)
//
void MainWindow::onPaintWithDC(HDC device_context)
{
	assert(getHandle() != NULL);
	assert(device_context != NULL);

	// �N���C�A���g�̈�̃T�C�Y���擾����
	int width = 0;
	int height = 0;
	getClientAreaSize(&width, &height);

	// �N���C�A���g�̈��h��Ԃ�
	RECT rc;
	rc.left		= 0;
	rc.top		= 0;
	rc.right	= width;
	rc.bottom	= height;
	verify(FillRect(device_context, &rc,
		reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH))) != 0);
}

