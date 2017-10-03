//
//	CustomWindowクラスの定義
//

#pragma once

#include "Window.h"

class WndMsgDispatcher;

//
//	カスタムウィンドウ
//
class CustomWindow : public Window
{
public:

	// コンストラクタ
	CustomWindow(Window *parent, DWORD style, DWORD ex_style);
	// デストラクタ
	virtual ~CustomWindow();

	// 作成する <override>
	virtual bool create(int x, int y, int width, int height);
	// 削除する <override>
	virtual void destroy();

	// ウィンドウメッセージを処理する
	virtual LRESULT handleWndMsg(UINT message, WPARAM wParam, LPARAM lParam);

protected:

	// メッセージハンドラ
	virtual void onLButtonDown();					// WM_LBUTTONDOWN
	virtual void onKeyDown(UINT_PTR key_code);		// WM_KEYDOWN
	virtual void onSize();							// WM_SIZE
	virtual void onClose();							// WM_CLOSE
	virtual void onPaint();							// WM_PAINT
	virtual void onPaintWithDC(HDC device_context);	// WM_PAINT(デバイスコンテキスト付き)

private:

	// ウィンドウクラスを登録する
	bool registerWindowClass();

	WndMsgDispatcher *m_dispatcher;		// ウィンドウメッセージディスパッチャ

	static const LPCTSTR WINDOW_CLASS_NAME;	// ウィンドウクラス名
	static bool s_window_class_registered;	// ウィンドウクラスが登録済みかどうか

	CustomWindow(const CustomWindow&);
	CustomWindow& operator=(const CustomWindow&);
};

