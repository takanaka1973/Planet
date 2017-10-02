//
//	RendererSettingクラスの実装
//

#include "common.h"
#include "RendererSetting.h"

//
//	コンストラクタ
//
RendererSetting::RendererSetting()
{
}

//
//	デストラクタ
//
RendererSetting::~RendererSetting()
{
}

//
//	カメラの初期位置を設定する
//
void RendererSetting::setCameraInitialPosition(const Vector3D& v)
{
	m_camera_ini_position = v;
}

//
//	カメラの初期参照点を設定する
//
void RendererSetting::setCameraInitialRefPoint(const Vector3D& v)
{
	m_camera_ini_ref_point = v;
}

//
//	カメラの初期上方向を設定する
//
void RendererSetting::setCameraInitialUpDirection(const Vector3D& v)
{
	m_camera_ini_up_direction = v;
}

//
//	カメラの初期位置を取得する
//
Vector3D RendererSetting::getCameraInitialPosition()
{
	return m_camera_ini_position;
}

//
//	カメラの初期参照点を取得する
//
Vector3D RendererSetting::getCameraInitialRefPoint()
{
	return m_camera_ini_ref_point;
}

//
//	カメラの初期上方向を取得する
//
Vector3D RendererSetting::getCameraInitialUpDirection()
{
	return m_camera_ini_up_direction;
}

