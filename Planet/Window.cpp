//
//	Windowクラスの実装
//

#include "common.h"
#include "Window.h"

//
//	コンストラクタ
//
Window::Window(Window *parent, LPCTSTR window_class_name, DWORD style, DWORD ex_style)
: m_handle(NULL),
  m_parent(parent),
  m_style(style),
  m_ex_style(ex_style)
{
	// ウィンドウクラス名をコピーする
	if (window_class_name != NULL) {
		m_window_class_name = _tcsdup(window_class_name);
	} else {
		m_window_class_name = _tcsdup(_T(""));
	}
}

//
//	デストラクタ
//
Window::~Window()
{
	destroy();
	free(m_window_class_name);
}

//
//	作成する
//
bool Window::create(int x, int y, int width, int height)
{
	if (m_handle != NULL) {
		return false;	// すでに作成済み
	}

	// 親ウィンドウのウィンドウハンドルを取得する
	HWND parent_handle = NULL;
	if (m_parent != NULL) {
		parent_handle = m_parent->getHandle();
		if (parent_handle == NULL) {
			// 親ウィンドウが未作成
			return false;
		}
	}

	// 実際にウィンドウを作成する
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
//	削除する
//
void Window::destroy()
{
	if (m_handle != NULL) {
	// 作成済みの場合のみ
		verify(DestroyWindow(m_handle));
		m_handle = NULL;
	}
}

//
//	ウィンドウハンドルを取得する
//
HWND Window::getHandle()
{
	return m_handle;
}

//
//	表示する
//
void Window::show()
{
	assert(m_handle != NULL);

	ShowWindow(m_handle, SW_SHOW);
}

//
//	更新する
//
void Window::update()
{
	assert(m_handle != NULL);

	verify(UpdateWindow(m_handle));
}

//
//	矩形を取得する
//
void Window::getRect(RECT *rc)
{
	assert(m_handle != NULL);
	assert(rc != NULL);

	verify(GetWindowRect(m_handle, rc));
}

//
//	クライアント領域のサイズを取得する
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
//	リサイズする
//
void Window::resize(int x, int y, int width, int height)
{
	assert(m_handle != NULL);

	verify(MoveWindow(m_handle, x, y, width, height, TRUE));
}

//
//	フォーカスを設定する
//
void Window::setFocus()
{
	assert(m_handle != NULL);

	SetFocus(m_handle);
}

//
//	タイトルを設定する
//
void Window::setTitle(LPCTSTR title)
{
	assert(m_handle != NULL);
	assert(title != NULL);

	verify(SetWindowText(m_handle, title));
}

//
//	アイコンを設定する
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
//	クライアント領域の表示内容を無効化する
//
void Window::invalidateClientArea()
{
	assert(m_handle != NULL);

	verify(InvalidateRect(m_handle, NULL, TRUE));
}

//
//	クライアント領域の表示内容を有効化する
//
void Window::validateClientArea()
{
	assert(m_handle != NULL);

	verify(ValidateRect(m_handle, NULL));
}

//
//	デバイスコンテキストを取得する
//
HDC Window::getDeviceContext()
{
	assert(m_handle != NULL);

	return GetDC(m_handle);
}

//
//	デバイスコンテキストを解放する
//
void Window::releaseDeviceContext(HDC device_context)
{
	assert(m_handle != NULL);
	assert(device_context != NULL);

	verify(ReleaseDC(m_handle, device_context) == 1);
}

