//
//	WndMsgDispatcherクラスの実装
//

#include "common.h"
#include "WndMsgDispatcher.h"
#include "CustomWindow.h"

// 唯一のインスタンス
WndMsgDispatcher WndMsgDispatcher::s_instance;

//
//	インスタンスを取得する
//
WndMsgDispatcher *WndMsgDispatcher::getInstance()
{
	return &s_instance;
}

//
//	コンストラクタ
//
WndMsgDispatcher::WndMsgDispatcher()
{
}

//
//	デストラクタ
//
WndMsgDispatcher::~WndMsgDispatcher()
{
	// ウィンドウは全て登録解除されているはず
	assert(m_registered_windows.empty());
}

//
//	ウィンドウを登録する
//
void WndMsgDispatcher::registerWindow(CustomWindow *window)
{
	assert(window != NULL);

	m_registered_windows.insert(window);
}

//
//	ウィンドウを登録解除する
//
void WndMsgDispatcher::unregisterWindow(CustomWindow *window)
{
	assert(window != NULL);

	m_registered_windows.erase(window);
}

//
//	ウィンドウプロシージャを取得する
//
WNDPROC WndMsgDispatcher::getWindowProc()
{
	return baseWindowProc;
}

//
//	ベースウィンドウプロシージャ
//
LRESULT CALLBACK WndMsgDispatcher::baseWindowProc(
	HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	// インスタンスメソッドに委譲する
	return s_instance.windowProc(handle, message, wParam, lParam);
}

//
//	ウィンドウプロシージャ
//
LRESULT WndMsgDispatcher::windowProc(
	HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	// 対象のウィンドウを探す
	CustomWindow *window = findWindow(handle);

	if (window != NULL) {
		// 見つかった場合は呼び出す
		ret = window->handleWndMsg(message, wParam, lParam);
	} else {
		// 見つからなかった場合はデフォルト処理
		ret = DefWindowProc(handle, message, wParam, lParam);
	}

	return ret;
}

//
//	ウィンドウを探す
//
CustomWindow *WndMsgDispatcher::findWindow(HWND handle)
{
	CustomWindow *dst_window = NULL;

	if (handle != NULL) {
		// 登録されているウィンドウ群からウィンドウハンドルが合致するものを探す
		CustomWindowContainer::iterator it = m_registered_windows.begin();
		for (; it != m_registered_windows.end(); ++it) {
			CustomWindow *window = *it;
			if (window->getHandle() == handle) {
				// 発見した
				dst_window = window;
				break;
			}
		}
	}

	return dst_window;
}

