//
//	Windowクラスの定義
//

#pragma once

//
//	ウィンドウ
//
class Window
{
public:

	// コンストラクタ
	Window(Window *parent, LPCTSTR window_class_name, DWORD style, DWORD ex_style);
	// デストラクタ
	virtual ~Window();

	// 作成する
	virtual bool create(int x, int y, int width, int height);
	// 削除する
	virtual void destroy();

	// ウィンドウハンドルを取得する
	virtual HWND getHandle();

	// 表示する
	virtual void show();
	// 更新する
	virtual void update();
	// 矩形を取得する
	virtual void getRect(RECT *rc);
	// クライアント領域のサイズを取得する
	virtual void getClientAreaSize(int *width, int *height);
	// リサイズする
	virtual void resize(int x, int y, int width, int height);
	// フォーカスを設定する
	virtual void setFocus();

	// タイトルを設定する
	virtual void setTitle(LPCTSTR title);
	// アイコンを設定する
	virtual bool setIcon(int icon_res_id);

	// クライアント領域の表示内容を無効化する
	virtual void invalidateClientArea();
	// クライアント領域の表示内容を有効化する
	virtual void validateClientArea();

protected:

	// デバイスコンテキストを取得する
	virtual HDC getDeviceContext();
	// デバイスコンテキストを解放する
	virtual void releaseDeviceContext(HDC device_context);

private:

	HWND m_handle;					// ウィンドウハンドル
	Window *m_parent;				// 親ウィンドウまたはオーナーウィンドウ
	LPTSTR m_window_class_name;		// ウィンドウクラス名
	DWORD m_style;					// ウィンドウスタイル
	DWORD m_ex_style;				// ウィンドウ拡張スタイル

	Window(const Window&);
	Window& operator=(const Window&);
};

