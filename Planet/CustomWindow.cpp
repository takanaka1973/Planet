//
//	CustomWindowクラスの実装
//

#include "common.h"
#include "CustomWindow.h"
#include "WndMsgDispatcher.h"

// ウィンドウクラス名
const LPCTSTR CustomWindow::WINDOW_CLASS_NAME = _T("CustomWindow");

// ウィンドウクラスが登録済みかどうか
bool CustomWindow::s_window_class_registered = false;

//
//	コンストラクタ
//
CustomWindow::CustomWindow(Window *parent, DWORD style, DWORD ex_style)
: Window(parent, WINDOW_CLASS_NAME, style, ex_style),
  m_dispatcher(WndMsgDispatcher::getInstance())
{
}

//
//	デストラクタ
//
CustomWindow::~CustomWindow()
{
	destroy();
}

//
//	作成する
//
bool CustomWindow::create(int x, int y, int width, int height)
{
	if (getHandle() != NULL) {
		return false;	// すでに作成済み
	}

	// ウィンドウクラスが未登録の場合は登録する
	if (!s_window_class_registered) {
		if (registerWindowClass()) {
			s_window_class_registered = true;
		} else {
			return false;
		}
	}

	// ウィンドウを作成する
	if (!Window::create(x, y, width, height)) {
		return false;
	}

	// ウィンドウメッセージディスパッチャに登録する
	m_dispatcher->registerWindow(this);

	return true;
}

//
//	削除する
//
void CustomWindow::destroy()
{
	if (getHandle() != NULL) {
	// 作成済みの場合のみ
		// ウィンドウメッセージディスパッチャから登録解除する
		m_dispatcher->unregisterWindow(this);
		// ウィンドウを削除する
		Window::destroy();
	}
}

//
//	ウィンドウクラスを登録する
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
//	ウィンドウメッセージを処理する
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
//	WM_LBUTTONDOWNのメッセージハンドラ
//
void CustomWindow::onLButtonDown()
{
}

//
//	WM_KEYDOWNのメッセージハンドラ
//
void CustomWindow::onKeyDown(UINT_PTR key_code)
{
}

//
//	WM_SIZEのメッセージハンドラ
//
void CustomWindow::onSize()
{
}

//
//	WM_SETFOCUSのメッセージハンドラ
//
void CustomWindow::onSetFocus()
{
}

//
//	WM_CLOSEのメッセージハンドラ
//
void CustomWindow::onClose()
{
	assert(getHandle() != NULL);

	// デフォルトでは無条件にウィンドウを削除する
	destroy();
}

//
//	WM_PAINTのメッセージハンドラ
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
//	WM_PAINTのメッセージハンドラ(デバイスコンテキスト付き)
//
void CustomWindow::onPaintWithDC(HDC device_context)
{
}

