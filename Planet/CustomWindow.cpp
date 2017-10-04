//
//	CustomWindow�N���X�̎���
//

#include "common.h"
#include "CustomWindow.h"
#include "WndMsgDispatcher.h"

// �E�B���h�E�N���X��
const LPCTSTR CustomWindow::WINDOW_CLASS_NAME = _T("CustomWindow");

// �E�B���h�E�N���X���o�^�ς݂��ǂ���
bool CustomWindow::s_window_class_registered = false;

//
//	�R���X�g���N�^
//
CustomWindow::CustomWindow(Window *parent, DWORD style, DWORD ex_style)
: Window(parent, WINDOW_CLASS_NAME, style, ex_style),
  m_dispatcher(WndMsgDispatcher::getInstance())
{
}

//
//	�f�X�g���N�^
//
CustomWindow::~CustomWindow()
{
	destroy();
}

//
//	�쐬����
//
bool CustomWindow::create(int x, int y, int width, int height)
{
	if (getHandle() != NULL) {
		return false;	// ���łɍ쐬�ς�
	}

	// �E�B���h�E�N���X�����o�^�̏ꍇ�͓o�^����
	if (!s_window_class_registered) {
		if (registerWindowClass()) {
			s_window_class_registered = true;
		} else {
			return false;
		}
	}

	// �E�B���h�E���쐬����
	if (!Window::create(x, y, width, height)) {
		return false;
	}

	// �E�B���h�E���b�Z�[�W�f�B�X�p�b�`���ɓo�^����
	m_dispatcher->registerWindow(this);

	return true;
}

//
//	�폜����
//
void CustomWindow::destroy()
{
	if (getHandle() != NULL) {
	// �쐬�ς݂̏ꍇ�̂�
		// �E�B���h�E���b�Z�[�W�f�B�X�p�b�`������o�^��������
		m_dispatcher->unregisterWindow(this);
		// �E�B���h�E���폜����
		Window::destroy();
	}
}

//
//	�E�B���h�E�N���X��o�^����
//
bool CustomWindow::registerWindowClass()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= CS_DBLCLKS;
	wc.lpfnWndProc		= m_dispatcher->getWindowProc();
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= GetModuleHandle(NULL);
	wc.hIcon			= NULL;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= WINDOW_CLASS_NAME;
	wc.hIconSm			= NULL;

	if (RegisterClassEx(&wc) != 0) {
		return true;
	} else {
		return false;
	}
}

//
//	�E�B���h�E���b�Z�[�W����������
//
LRESULT CustomWindow::handleWndMsg(UINT message, WPARAM wParam, LPARAM lParam)
{
	assert(getHandle() != NULL);

	LRESULT ret = 0;

	switch (message) {
	case WM_LBUTTONDOWN:
		onLButtonDown();
		break;
	case WM_KEYDOWN:
		onKeyDown(wParam);
		break;
	case WM_SIZE:
		onSize();
		break;
	case WM_SETFOCUS:
		onSetFocus();
		break;
	case WM_CLOSE:
		onClose();
		break;
	case WM_PAINT:
		onPaint();
		break;
	default:
		ret = DefWindowProc(getHandle(), message, wParam, lParam);
	}

	return ret;
}

//
//	WM_LBUTTONDOWN�̃��b�Z�[�W�n���h��
//
void CustomWindow::onLButtonDown()
{
}

//
//	WM_KEYDOWN�̃��b�Z�[�W�n���h��
//
void CustomWindow::onKeyDown(UINT_PTR key_code)
{
}

//
//	WM_SIZE�̃��b�Z�[�W�n���h��
//
void CustomWindow::onSize()
{
}

//
//	WM_SETFOCUS�̃��b�Z�[�W�n���h��
//
void CustomWindow::onSetFocus()
{
}

//
//	WM_CLOSE�̃��b�Z�[�W�n���h��
//
void CustomWindow::onClose()
{
	assert(getHandle() != NULL);

	// �f�t�H���g�ł͖������ɃE�B���h�E���폜����
	destroy();
}

//
//	WM_PAINT�̃��b�Z�[�W�n���h��
//
void CustomWindow::onPaint()
{
	assert(getHandle() != NULL);

	PAINTSTRUCT ps;
	HDC device_context = BeginPaint(getHandle(), &ps);

	if (device_context != NULL) {
		onPaintWithDC(device_context);
		verify(EndPaint(getHandle(), &ps));
	}
}

//
//	WM_PAINT�̃��b�Z�[�W�n���h��(�f�o�C�X�R���e�L�X�g�t��)
//
void CustomWindow::onPaintWithDC(HDC device_context)
{
}

