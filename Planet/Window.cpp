//
//	Window�N���X�̎���
//

#include "common.h"
#include "Window.h"

//
//	�R���X�g���N�^
//
Window::Window(Window *parent, LPCTSTR window_class_name, DWORD style, DWORD ex_style)
: m_handle(NULL),
  m_parent(parent),
  m_style(style),
  m_ex_style(ex_style)
{
	// �E�B���h�E�N���X�����R�s�[����
	if (window_class_name != NULL) {
		m_window_class_name = _tcsdup(window_class_name);
	} else {
		m_window_class_name = _tcsdup(_T(""));
	}
}

//
//	�f�X�g���N�^
//
Window::~Window()
{
	destroy();
	free(m_window_class_name);
}

//
//	�쐬����
//
bool Window::create(int x, int y, int width, int height)
{
	if (m_handle != NULL) {
		return false;	// ���łɍ쐬�ς�
	}

	// �e�E�B���h�E�̃E�B���h�E�n���h�����擾����
	HWND parent_handle = NULL;
	if (m_parent != NULL) {
		parent_handle = m_parent->getHandle();
		if (parent_handle == NULL) {
			// �e�E�B���h�E�����쐬
			return false;
		}
	}

	// ���ۂɃE�B���h�E���쐬����
	HWND handle = CreateWindowEx(
		m_ex_style, m_window_class_name, NULL, m_style,
		x, y, width, height,
		parent_handle, NULL, GetModuleHandle(NULL), NULL);

	if (handle != NULL) {
		m_handle = handle;
		return true;
	} else {
		return false;
	}
}

//
//	�폜����
//
void Window::destroy()
{
	if (m_handle != NULL) {
	// �쐬�ς݂̏ꍇ�̂�
		verify(DestroyWindow(m_handle));
		m_handle = NULL;
	}
}

//
//	�E�B���h�E�n���h�����擾����
//
HWND Window::getHandle()
{
	return m_handle;
}

//
//	�\������
//
void Window::show()
{
	assert(m_handle != NULL);

	ShowWindow(m_handle, SW_SHOW);
}

//
//	�X�V����
//
void Window::update()
{
	assert(m_handle != NULL);

	verify(UpdateWindow(m_handle));
}

//
//	��`���擾����
//
void Window::getRect(RECT *rc)
{
	assert(m_handle != NULL);
	assert(rc != NULL);

	verify(GetWindowRect(m_handle, rc));
}

//
//	�N���C�A���g�̈�̃T�C�Y���擾����
//
void Window::getClientAreaSize(int *width, int *height)
{
	assert(m_handle != NULL);

	RECT rc;
	ZeroMemory(&rc, sizeof(RECT));

	verify(GetClientRect(m_handle, &rc));

	if (width != NULL) {
		*width = rc.right;
	}

	if (height != NULL) {
		*height = rc.bottom;
	}
}

//
//	���T�C�Y����
//
void Window::resize(int x, int y, int width, int height)
{
	assert(m_handle != NULL);

	verify(MoveWindow(m_handle, x, y, width, height, TRUE));
}

//
//	�t�H�[�J�X��ݒ肷��
//
void Window::setFocus()
{
	assert(m_handle != NULL);

	SetFocus(m_handle);
}

//
//	�^�C�g����ݒ肷��
//
void Window::setTitle(LPCTSTR title)
{
	assert(m_handle != NULL);
	assert(title != NULL);

	verify(SetWindowText(m_handle, title));
}

//
//	�A�C�R����ݒ肷��
//
bool Window::setIcon(int icon_res_id)
{
	assert(m_handle != NULL);

	int large_x = GetSystemMetrics(SM_CXICON);
	int large_y = GetSystemMetrics(SM_CYICON);

	HICON icon_large = reinterpret_cast<HICON>(LoadImage(
		GetModuleHandle(NULL), MAKEINTRESOURCE(icon_res_id),
		IMAGE_ICON, large_x, large_y, LR_DEFAULTCOLOR));

	if (icon_large == NULL) {
		return false;
	}

	int small_x = GetSystemMetrics(SM_CXSMICON);
	int small_y = GetSystemMetrics(SM_CYSMICON);

	HICON icon_small = reinterpret_cast<HICON>(LoadImage(
		GetModuleHandle(NULL), MAKEINTRESOURCE(icon_res_id),
		IMAGE_ICON, small_x, small_y, LR_DEFAULTCOLOR));

	if (icon_small == NULL) {
		return false;
	}

	SendMessage(m_handle, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(icon_large));
	SendMessage(m_handle, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(icon_small));

	return true;
}

//
//	�N���C�A���g�̈�̕\�����e�𖳌�������
//
void Window::invalidateClientArea()
{
	assert(m_handle != NULL);

	verify(InvalidateRect(m_handle, NULL, TRUE));
}

//
//	�N���C�A���g�̈�̕\�����e��L��������
//
void Window::validateClientArea()
{
	assert(m_handle != NULL);

	verify(ValidateRect(m_handle, NULL));
}

//
//	�f�o�C�X�R���e�L�X�g���擾����
//
HDC Window::getDeviceContext()
{
	assert(m_handle != NULL);

	return GetDC(m_handle);
}

//
//	�f�o�C�X�R���e�L�X�g���������
//
void Window::releaseDeviceContext(HDC device_context)
{
	assert(m_handle != NULL);
	assert(device_context != NULL);

	verify(ReleaseDC(m_handle, device_context) == 1);
}

