//
//	Planetクラスの実装
//

#include "common.h"
#include "Planet.h"

//
//	コンストラクタ
//
Planet::Planet(double mass,
	Surface *surface, Shape *shape, LightSource *light_source,
	const Vector3D& initial_position, const Vector3D& initial_velocity)
: Star(mass, surface, shape, light_source),
  m_position(initial_position),
  m_velocity(initial_velocity)
{
}

//
//	デストラクタ
//
Planet::~Planet()
{
}

//
//	位置を取得する
//
Vector3D Planet::getPosition()
{
	return m_position;
}

//
//	重力場を取得する
//
GravityField *Planet::getGravityField()
{
	// 惑星は重力場を持たないことにする
	return NULL;
}

//
//	時間の経過を通知する
//
void Planet::tick(int timespan, const GravityFieldList& gravity_fields)
{
	assert(timespan > 0);

	for (int i = 0; i < timespan; i++) {

		// Runge-Kutta法で計算する

		static const double dt = 1.0;

		Vector3D x0 = m_position;
		Vector3D v0 = m_velocity;

		Vector3D x1 = dt * v0;
		Vector3D v1 = dt * (1.0 / getMass()) * calcGravity(x0, gravity_fields);

		Vector3D x2 = dt * (v0 + 0.5 * v1);
		Vector3D v2 = dt * (1.0 / getMass()) * calcGravity(x0 + 0.5 * x1, gravity_fields);

		Vector3D x3 = dt * (v0 + 0.5 * v2);
		Vector3D v3 = dt * (1.0 / getMass()) * calcGravity(x0 + 0.5 * x2, gravity_fields);

		Vector3D x4 = dt * (v0 + v3);
		Vector3D v4 = dt * (1.0 / getMass()) * calcGravity(x0 + x3, gravity_fields);

		Vector3D k = (1.0 / 6.0) * (x1 + 2.0 * x2 + 2.0 * x3 + x4);
		Vector3D l = (1.0 / 6.0) * (v1 + 2.0 * v2 + 2.0 * v3 + v4);

		m_position += k;
		m_velocity += l;

	}
}

//
//	重力を計算する
//
Vector3D Planet::calcGravity(const Vector3D& pos, const GravityFieldList& gfs)
{
	Vector3D g;

	GravityFieldList::const_iterator it = gfs.begin();
	for (; it != gfs.end(); ++it) {
		GravityField *gf = *it;
		g += gf->getGravity(this, pos);
	}

	return g;
}

