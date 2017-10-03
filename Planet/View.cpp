//
//	Viewクラスの実装
//

#include "common.h"
#include "View.h"
#include "Universe.h"
#include "RendererSetting.h"
#include "Renderer.h"
#include "Vector3D.h"

// ウィンドウスタイル
static const DWORD WINDOW_STYLE =
	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
// ウィンドウ拡張スタイル
static const DWORD WINDOW_EX_STYLE = 0;

//
//	コンストラクタ
//
View::View(Window *parent, Universe *universe, RendererSetting *setting)
: CustomWindow(parent, WINDOW_STYLE, WINDOW_EX_STYLE),
  m_universe(universe),
  m_device_context(NULL),
  m_renderer(new Renderer(universe, setting))
{
	assert(parent != NULL);		// 子ウィンドウ専用
	assert(universe != NULL);
	assert(setting != NULL);
}

//
//	デストラクタ
//
View::~View()
{
	destroy();
	delete m_renderer;
}

//
//	作成する
//
bool View::create(int x, int y, int width, int height)
{
	if (getHandle() != NULL) {
		return false;	// すでに作成済み
	}

	bool completed = false;
	do {
		// ウィンドウを作成する
		if (!CustomWindow::create(x, y, width, height)) {
			break;
		}

		// デバイスコンテキストを取得する
		m_device_context = getDeviceContext();
		if (m_device_context == NULL) {
			break;
		}

		// ピクセルフォーマットを設定する
		if (!setPixelFormat(m_device_context)) {
			break;
		}

		// レンダラーを初期化する
		if (!m_renderer->init(m_device_context)) {
			break;
		}

		// ビューポートを設定する
		setViewport();

		// 宇宙に観察者として自分を登録する
		m_universe->registerObserver(this);

		completed = true;
	} while (false);

	if (!completed) {
		// 失敗したので後始末
		m_renderer->term();
		if (m_device_context != NULL) {
			releaseDeviceContext(m_device_context);
			m_device_context = NULL;
		}
		CustomWindow::destroy();
		return false;
	}

	return true;
}

//
//	削除する
//
void View::destroy()
{
	if (getHandle() != NULL) {
	// 作成済みの場合のみ

		// 宇宙から自分を登録解除する
		m_universe->unregisterObserver(this);

		// レンダラーを終了する
		m_renderer->term();

		// デバイスコンテキストを解放する
		releaseDeviceContext(m_device_context);
		m_device_context = NULL;

		// ウィンドウを削除する
		CustomWindow::destroy();

	}
}

//
//	シーンが変化したことを通知する
//
void View::notifySceneChanged(Universe *sender)
{
	assert(sender == m_universe);
	assert(getHandle() != NULL);

	// 再描画要求
	invalidateClientArea();
}

//
//	ピクセルフォーマットを設定する
//
bool View::setPixelFormat(HDC device_context)
{
	assert(device_context != NULL);

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize			= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion		= 1;
	pfd.dwFlags			= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType		= PFD_TYPE_RGBA;
	pfd.cColorBits		= 24;
	pfd.cAlphaBits		= 0;
	pfd.cAccumBits		= 0;
	pfd.cDepthBits		= 32;
	pfd.cStencilBits	= 0;
	pfd.cAuxBuffers		= 0;
	pfd.iLayerType		= PFD_MAIN_PLANE;

	int pfindex = ChoosePixelFormat(device_context, &pfd);
	if (pfindex == 0) {
		return false;
	}

	if (!SetPixelFormat(device_context, pfindex, &pfd)) {
		return false;
	}

	return true;
}

//
//	ビューポートを設定する
//
void View::setViewport()
{
	assert(getHandle() != NULL);

	int width = 0;
	int height = 0;
	getClientAreaSize(&width, &height);

	m_renderer->setViewport(0, 0, width, height);
}

//
//	WM_LBUTTONDOWNのメッセージハンドラ
//
void View::onLButtonDown()
{
	assert(getHandle() != NULL);

//	// 自分にフォーカスを設定する
//	setFocus();
}

//
//	WM_KEYDOWNのメッセージハンドラ
//
void View::onKeyDown(UINT_PTR key_code)
{
	assert(getHandle() != NULL);

	static const double distance = 1.0;
	Vector3D delta;
	bool move = true;

	// カメラの変位を決定する
	switch (key_code) {
	case VK_UP:
		delta.setY(distance);
		break;
	case VK_DOWN:
		delta.setY(-distance);
		break;
	case VK_LEFT:
		delta.setX(-distance);
		break;
	case VK_RIGHT:
		delta.setX(distance);
		break;
	default:
		move = false;
	}

	if (move) {
		// カメラを動かす
		m_renderer->moveCamera(delta);

		// 再描画要求
		invalidateClientArea();
	}
}

//
//	WM_SIZEのメッセージハンドラ
//
void View::onSize()
{
	assert(getHandle() != NULL);

	// ビューポートを設定する
	setViewport();

	// 再描画要求
	invalidateClientArea();
}

//
//	WM_PAINTのメッセージハンドラ
//
void View::onPaint()
{
	assert(getHandle() != NULL);

	// レンダリングする
	m_renderer->render();

	// 表示内容を有効化
	validateClientArea();
}

