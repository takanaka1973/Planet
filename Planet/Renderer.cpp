//
//	Rendererクラスの実装
//

#include "common.h"
#include "Renderer.h"
#include "Universe.h"
#include "RendererSetting.h"
#include "Camera.h"
#include "Vector3D.h"
#include "Color.h"

//
//	コンストラクタ
//
Renderer::Renderer(Universe *universe, RendererSetting *setting)
: m_universe(universe),
  m_setting(setting),
  m_camera(new Camera()),
  m_initialized(false),
  m_rendering_context(NULL),
  m_device_context(NULL),
  m_viewport_x(0),
  m_viewport_y(0),
  m_viewport_width(0),
  m_viewport_height(0)
{
	assert(universe != NULL);
	assert(setting != NULL);
}

//
//	デストラクタ
//
Renderer::~Renderer()
{
	term();

	delete m_setting;
	delete m_camera;
}

//
//	初期化する
//
bool Renderer::init(HDC device_context)
{
	assert(device_context != NULL);

	if (m_initialized) {
		return false;	// すでに初期化済み
	}

	// レンダリングコンテキストを作成する
	HGLRC rendering_context = wglCreateContext(device_context);
	if (rendering_context == NULL) {
		return false;
	}

	// カレントにする
	if (!wglMakeCurrent(device_context, rendering_context)) {
		verify(wglDeleteContext(rendering_context));
		return false;
	}

	// 一度だけ行えばよい設定
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	// カレントから外す
	verify(wglMakeCurrent(NULL, NULL));

	// カメラの初期設定
	m_camera->setPosition(m_setting->getCameraInitialPosition());
	m_camera->setRefPoint(m_setting->getCameraInitialRefPoint());
	m_camera->setUpDirection(m_setting->getCameraInitialUpDirection());

	// ビューポートの設定値を初期化
	m_viewport_x = 0;
	m_viewport_y = 0;
	m_viewport_width = 0;
	m_viewport_height = 0;

	// メンバ変数の設定
	m_rendering_context = rendering_context;
	m_device_context = device_context;
	m_initialized = true;

	return true;
}

//
//	終了する
//
void Renderer::term()
{
	if (m_initialized) {
	// 初期化済みの場合のみ

		// レンダリングコンテキストを削除する
		verify(wglDeleteContext(m_rendering_context));

		// メンバ変数のクリア
		m_rendering_context = NULL;
		m_device_context = NULL;
		m_initialized = false;

	}
}

//
//	レンダリングする
//
void Renderer::render()
{
	assert(m_initialized);

	// カレントにする
	verify(wglMakeCurrent(m_device_context, m_rendering_context));

	// バッファをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ビューポートを設定する
	glViewport(m_viewport_x, m_viewport_y, m_viewport_width, m_viewport_height);

	// 投影行列を設定する
	setProjectionMatrix();

	// モデル行列をカレントの行列にする
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// カメラに焦点合わせを指示
	m_camera->focus();

	// 宇宙にレンダリングを指示
	glEnable(GL_LIGHTING);
	m_universe->render();
	glDisable(GL_LIGHTING);

	// xy平面を描画する
	drawXYPlane();

	// レンダリング完了
	glFinish();

	// 画面に表示する
	verify(SwapBuffers(m_device_context));

	// カレントから外す
	verify(wglMakeCurrent(NULL, NULL));
}

//
//	ビューポートを設定する
//
void Renderer::setViewport(int x, int y, int width, int height)
{
	assert(m_initialized);
	assert(width >= 0);
	assert(height >= 0);

	// ここでは値を保存するだけ
	m_viewport_x = x;
	m_viewport_y = y;
	m_viewport_width = width;
	m_viewport_height = height;
}

//
//	カメラを移動する
//
void Renderer::moveCamera(const Vector3D& delta)
{
	assert(m_initialized);

	m_camera->move(delta);
}

//
//	投影行列を設定する
//
void Renderer::setProjectionMatrix()
{
	assert(m_initialized);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double view_angle = 45.0;
	double aspect_ratio = 1.0;
	if (m_viewport_width > 0 && m_viewport_height > 0) {
		aspect_ratio = static_cast<double>(m_viewport_width) / m_viewport_height;
	}
	double near_plane = 1.0;
	double far_plane = 1000.0;

	gluPerspective(view_angle, aspect_ratio, near_plane, far_plane);
}

//
//	xy平面を描画する
//
void Renderer::drawXYPlane()
{
	assert(m_initialized);

	static const Color color(0.7, 0.7, 0.7);

	float c[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	color.getRGBA(c);
	glColor4fv(c);

	glBegin(GL_LINES);

	static const int C = 30;
	static const int D = 5;

	// x軸方向
	for (int y = - C; y <= C; y += D) {
		glVertex3d(- static_cast<double>(C), static_cast<double>(y), 0.0);
		glVertex3d(  static_cast<double>(C), static_cast<double>(y), 0.0);
	}

	// y軸方向
	for (int x = - C; x <= C; x += D) {
		glVertex3d(static_cast<double>(x), - static_cast<double>(C), 0.0);
		glVertex3d(static_cast<double>(x),   static_cast<double>(C), 0.0);
	}

	glEnd();
}

