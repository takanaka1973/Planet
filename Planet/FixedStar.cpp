//
//	FixedStarクラスの実装
//

#include "common.h"
#include "FixedStar.h"

//
//	コンストラクタ
//
FixedStar::FixedStar(double mass,
	Surface *surface, Shape *shape, LightSource *light_source,
	const Vector3D& position, GravityType gravity_type)
: Star(mass, surface, shape, light_source),
  m_fixed_position(position)
{
	m_gravity_field = new GravityField(gravity_type, this);
}

//
//	デストラクタ
//
FixedStar::~FixedStar()
{
	delete m_gravity_field;
}

//
//	位置を取得する
//
Vector3D FixedStar::getPosition()
{
	return m_fixed_position;
}

//
//	重力場を取得する
//
GravityField *FixedStar::getGravityField()
{
	return m_gravity_field;
}

//
//	時間の経過を通知する
//
void FixedStar::tick(int timespan, const GravityFieldList& gravity_fields)
{
	// 恒星は移動しないことにする
}

