//
//	Planetクラスの定義
//

#pragma once

#include "Star.h"
#include "Vector3D.h"

//
//	惑星
//
class Planet : public Star
{
public:

	// コンストラクタ
	Planet(double mass,
		Surface *surface, Shape *shape, LightSource *light_source,
		const Vector3D& initial_position, const Vector3D& initial_velocity);
	// デストラクタ
	virtual ~Planet();

	// 位置を取得する <override>
	virtual Vector3D getPosition();
	// 重力場を取得する <override>
	virtual GravityField *getGravityField();

	// 時間の経過を通知する <override>
	virtual void tick(int timespan, const GravityFieldList& gravity_fields);

private:

	// 重力を計算する
	Vector3D calcGravity(const Vector3D& pos, const GravityFieldList& gfs);

	Vector3D m_position;	// 位置
	Vector3D m_velocity;	// 速度

	Planet(const Planet&);
	Planet& operator=(const Planet&);
};

