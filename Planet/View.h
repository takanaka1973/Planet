//
//	Viewクラスの定義
//

#pragma once

#include "CustomWindow.h"
#include "UniverseObserver.h"

class Universe;
class RendererSetting;
class Renderer;

//
//	ビュー
//
class View : public CustomWindow, public UniverseObserver
{
public:

	// コンストラクタ
	View(Window *parent, Universe *universe, RendererSetting *setting);
	// デストラクタ
	virtual ~View();

	// 作成する <override>
	virtual bool create(int x, int y, int width, int height);
	// 削除する <override>
	virtual void destroy();

	// シーンが変化したことを通知する <override>
	virtual void notifySceneChanged(Universe *sender);

protected:

	// メッセージハンドラ <override>
	virtual void onLButtonDown();			// WM_LBUTTONDOWN
	virtual void onKeyDown(UINT key_code);	// WM_KEYDOWN
	virtual void onSize();					// WM_SIZE
	virtual void onPaint();					// WM_PAINT

private:

	// ピクセルフォーマットを設定する
	bool setPixelFormat(HDC device_context);
	// ビューポートを設定する
	void setViewport();

	Universe *m_universe;	// 宇宙
	HDC m_device_context;	// デバイスコンテキスト
	Renderer *m_renderer;	// レンダラー

	View(const View&);
	View& operator=(const View&);
};

