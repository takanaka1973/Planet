//
//	MainWindowクラスの定義
//

#pragma once

#include "CustomWindow.h"

class Application;
class Universe;
class View;

//
//	メインウィンドウ
//
class MainWindow : public CustomWindow
{
public:

	// コンストラクタ
	MainWindow(Application *app, Universe *universe);
	// デストラクタ
	virtual ~MainWindow();

	// 作成する <override>
	virtual bool create(int x, int y, int width, int height);
	// 削除する <override>
	virtual void destroy();

	// サイズを最適化する
	virtual void optimizeSize();

protected:

	// メッセージハンドラ <override>
	virtual void onPaintWithDC(HDC device_context);	// WM_PAINT(デバイスコンテキスト付き)

private:

	Application *m_app;		// アプリケーション
	View *m_main_view;		// メインビュー
	View *m_sub_view;		// サブビュー

	MainWindow(const MainWindow&);
	MainWindow& operator=(const MainWindow&);
};

