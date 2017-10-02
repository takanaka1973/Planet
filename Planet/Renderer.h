//
//	Rendererクラスの定義
//

#pragma once

class Universe;
class RendererSetting;
class Camera;
class Vector3D;

//
//	レンダラー
//
class Renderer
{
public:

	// コンストラクタ
	Renderer(Universe *universe, RendererSetting *setting);
	// デストラクタ
	virtual ~Renderer();

	// 初期化する
	virtual bool init(HDC device_context);
	// 終了する
	virtual void term();

	// レンダリングする
	virtual void render();

	// ビューポートを設定する
	virtual void setViewport(int x, int y, int width, int height);
	// カメラを移動する
	virtual void moveCamera(const Vector3D& delta);

private:

	// 投影行列を設定する
	void setProjectionMatrix();
	// xy平面を描画する
	void drawXYPlane();

	Universe *m_universe;		// 宇宙
	RendererSetting *m_setting;	// 設定
	Camera *m_camera;			// カメラ

	bool m_initialized;			// 初期化済みかどうか
	HGLRC m_rendering_context;	// レンダリングコンテキスト
	HDC m_device_context;		// デバイスコンテキスト

	// ビューポート設定
	int m_viewport_x;
	int m_viewport_y;
	int m_viewport_width;
	int m_viewport_height;

	Renderer(const Renderer&);
	Renderer& operator=(const Renderer&);
};

