//
//	RendererSettingクラスの定義
//

#pragma once

#include "Vector3D.h"

//
//	レンダラーの設定
//
class RendererSetting
{
public:

	// コンストラクタ
	RendererSetting();
	// デストラクタ
	virtual ~RendererSetting();

	// カメラの初期位置を設定する
	virtual void setCameraInitialPosition(const Vector3D& v);
	// カメラの初期参照点を設定する
	virtual void setCameraInitialRefPoint(const Vector3D& v);
	// カメラの初期上方向を設定する
	virtual void setCameraInitialUpDirection(const Vector3D& v);

	// カメラの初期位置を取得する
	virtual Vector3D getCameraInitialPosition();
	// カメラの初期参照点を取得する
	virtual Vector3D getCameraInitialRefPoint();
	// カメラの初期上方向を取得する
	virtual Vector3D getCameraInitialUpDirection();

private:

	Vector3D m_camera_ini_position;		// カメラの初期位置
	Vector3D m_camera_ini_ref_point;	// カメラの初期参照点
	Vector3D m_camera_ini_up_direction;	// カメラの初期上方向

	RendererSetting(const RendererSetting&);
	RendererSetting& operator=(const RendererSetting&);
};

