//
//	MainWindowクラスの実装
//

#include "common.h"
#include "MainWindow.h"
#include "Application.h"
#include "Universe.h"
#include "View.h"
#include "RendererSetting.h"
#include "resource.h"

// ウィンドウスタイル
static const DWORD WINDOW_STYLE =
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN;
// ウィンドウ拡張スタイル
static const DWORD WINDOW_EX_STYLE = 0;

// 各ビューの幅
static const int VIEW_WIDTH = 400;
// 各ビューの高さ
static const int VIEW_HEIGHT = 400;
// ビューの間隔
static const int VIEW_INTERVAL = 5;

// タイトル
static LPCTSTR TITLE = _T("Planet");

//
//	コンストラクタ
//
MainWindow::MainWindow(Application *app, Universe *universe)
: CustomWindow(NULL, WINDOW_STYLE, WINDOW_EX_STYLE),
  m_app(app)
{
	assert(app != NULL);
	assert(universe != NULL);

	// メインビューを作成する
	RendererSetting *main_view_setting = new RendererSetting();
	main_view_setting->setCameraInitialPosition(Vector3D(0.0, 0.0, 80.0));
	main_view_setting->setCameraInitialRefPoint(Vector3D(0.0, 0.0, 0.0));
	main_view_setting->setCameraInitialUpDirection(Vector3D(0.0, 1.0, 0.0));
	m_main_view = new View(this, universe, main_view_setting);

	// サブビューを作成する
	RendererSetting *sub_view_setting = new RendererSetting();
	sub_view_setting->setCameraInitialPosition(Vector3D(-70.0, 0.0, 20.0));
	sub_view_setting->setCameraInitialRefPoint(Vector3D(0.0, 0.0, 0.0));
	sub_view_setting->setCameraInitialUpDirection(Vector3D(0.0, 1.0, 0.0));
	m_sub_view = new View(this, universe, sub_view_setting);
}

//
//	デストラクタ
//
MainWindow::~MainWindow()
{
	destroy();

	delete m_sub_view;
	delete m_main_view;
}

//
//	作成する
//
bool MainWindow::create(int x, int y, int width, int height)
{
	if (getHandle() != NULL) {
		return false;	// すでに作成済み
	}

	bool completed = false;
	do {
		// 自分のウィンドウを作成する
		if (!CustomWindow::create(x, y, width, height)) {
			break;
		}

		// ビューのウィンドウを作成する
		if (!m_main_view->create(0, 0, VIEW_WIDTH, VIEW_HEIGHT)) {
			break;
		}
		if (!m_sub_view->create(VIEW_WIDTH + VIEW_INTERVAL, 0, VIEW_WIDTH, VIEW_HEIGHT)) {
			break;
		}

		// タイトルを設定する
		setTitle(TITLE);

		// アイコンを設定する(エラー無視)
		bool res = setIcon(IDI_APP);

		completed = true;
	} while (false);

	if (!completed) {
		// 失敗したので後始末
		m_sub_view->destroy();
		m_main_view->destroy();
		CustomWindow::destroy();
		return false;
	}

	return true;
}

//
//	削除する
//
void MainWindow::destroy()
{
	if (getHandle() != NULL) {
	// 作成済みの場合のみ

		// ビューのウィンドウを削除する
		m_sub_view->destroy();
		m_main_view->destroy();

		// 自分のウィンドウを削除する
		CustomWindow::destroy();

		// アプリケーションに通知する
		m_app->notifyMainWindowDestroyed(this);

	}
}

//
//	サイズを最適化する
//
void MainWindow::optimizeSize()
{
	assert(getHandle() != NULL);

	// ウィンドウの矩形を取得する
	RECT rc;
	ZeroMemory(&rc, sizeof(RECT));
	getRect(&rc);
	int window_width = rc.right - rc.left;
	int window_height = rc.bottom - rc.top;

	// クライアント領域のサイズを取得する
	int client_width = 0;
	int client_height = 0;
	getClientAreaSize(&client_width, &client_height);

	// リサイズする
	int optimized_width = VIEW_WIDTH * 2 + VIEW_INTERVAL + (window_width - client_width);
	int optimized_height = VIEW_HEIGHT + (window_height - client_height);
	resize(rc.left, rc.top, optimized_width, optimized_height);
}

//
//	WM_SETFOCUSのメッセージハンドラ
//
void MainWindow::onSetFocus()
{
	assert(getHandle() != NULL);

	// 常にサブビューにフォーカスを設定する
	m_sub_view->setFocus();
}

//
//	WM_PAINTのメッセージハンドラ(デバイスコンテキスト付き)
//
void MainWindow::onPaintWithDC(HDC device_context)
{
	assert(getHandle() != NULL);
	assert(device_context != NULL);

	// クライアント領域のサイズを取得する
	int width = 0;
	int height = 0;
	getClientAreaSize(&width, &height);

	// クライアント領域を塗りつぶす
	RECT rc;
	rc.left		= 0;
	rc.top		= 0;
	rc.right	= width;
	rc.bottom	= height;
	verify(FillRect(device_context, &rc,
		reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH))) != 0);
}

