//
//	Cameraクラスの定義
//

#pragma once

#include "Vector3D.h"

//
//	カメラ
//
class Camera
{
public:

	// コンストラクタ
	Camera();
	// デストラクタ
	virtual ~Camera();

	// 位置を設定する
	virtual void setPosition(const Vector3D& v);
	// 参照点を設定する
	virtual void setRefPoint(const Vector3D& v);
	// 上方向を設定する
	virtual void setUpDirection(const Vector3D& v);

	// 焦点を合わせる
	virtual void focus();

	// 移動する
	virtual void move(const Vector3D& delta);
	// Y軸に沿って回転する
	virtual void rotateAroundYAxis(double angleDelta);

private:

	Vector3D m_position;		// 位置
	Vector3D m_ref_point;		// 参照点
	Vector3D m_up_direction;	// 上方向

	Camera(const Camera&);
	Camera& operator=(const Camera&);
};

