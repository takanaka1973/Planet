//
//	FixedStarクラスの定義
//

#pragma once

#include "Star.h"
#include "Vector3D.h"
#include "GravityType.h"

//
//	恒星
//
class FixedStar : public Star
{
public:

	// コンストラクタ
	FixedStar(double mass,
		Surface *surface, Shape *shape, LightSource *light_source,
		const Vector3D& position, GravityType gravity_type);
	// デストラクタ
	virtual ~FixedStar();

	// 位置を取得する <override>
	virtual Vector3D getPosition();
	// 重力場を取得する <override>
	virtual GravityField *getGravityField();

	// 時間の経過を通知する <override>
	virtual void tick(int timespan, const GravityFieldList& gravity_fields);

private:

	Vector3D m_fixed_position;		// 固定位置
	GravityField *m_gravity_field;	// 重力場

	FixedStar(const FixedStar&);
	FixedStar& operator=(const FixedStar&);
};

