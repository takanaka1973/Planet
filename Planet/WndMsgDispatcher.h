//
//	WndMsgDispatcherクラスの定義
//

#pragma once

#pragma warning(disable:4786)

#include <set>

class CustomWindow;

//
//	ウィンドウメッセージディスパッチャ
//
class WndMsgDispatcher
{
public:

	// デストラクタ
	virtual ~WndMsgDispatcher();

	// ウィンドウプロシージャを取得する
	virtual WNDPROC getWindowProc();

	// ウィンドウを登録する
	virtual void registerWindow(CustomWindow *window);
	// ウィンドウを登録解除する
	virtual void unregisterWindow(CustomWindow *window);

	// インスタンスを取得する
	static WndMsgDispatcher *getInstance();

private:

	// コンストラクタ
	WndMsgDispatcher();

	// ウィンドウプロシージャ
	LRESULT windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	// ウィンドウを探す
	CustomWindow *findWindow(HWND handle);

	// 登録されているウィンドウ群
	typedef std::set<CustomWindow*> CustomWindowContainer;
	CustomWindowContainer m_registered_windows;

	// 唯一のインスタンス
	static WndMsgDispatcher s_instance;

	// ベースウィンドウプロシージャ
	static LRESULT CALLBACK baseWindowProc(
		HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	WndMsgDispatcher(const WndMsgDispatcher&);
	WndMsgDispatcher& operator=(const WndMsgDispatcher&);
};

