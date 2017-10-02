//
//	GravityFieldクラスの実装
//

#include "common.h"
#include "GravityField.h"
#include "Star.h"
#include "Vector3D.h"

//
//	コンストラクタ
//
GravityField::GravityField(GravityType type, Star *source)
: m_type(type), m_source(source)
{
	assert(source != NULL);
}

//
//	デストラクタ
//
GravityField::~GravityField()
{
}

//
//	重力を取得する
//
Vector3D GravityField::getGravity(Star *target, const Vector3D& target_pos)
{
	assert(target != NULL);

	Vector3D gravity;

	if (target != m_source) {

		// targetとsourceの変位ベクトル(target ---> source)
		Vector3D delta = m_source->getPosition() - target_pos;

		if (m_type == NORMAL_GRAVITY || m_type == REVERSE_GRAVITY) {

			// targetとsourceの距離
			double distance = delta.getAbs();

			if (distance > 0.0) {

				static const double GRAVITY_CONSTANT = 0.1;		// 重力定数

				double factor = GRAVITY_CONSTANT * m_source->getMass() * target->getMass()
									/ ( distance * distance * distance );

				if (m_type == NORMAL_GRAVITY) {
					// 通常の重力
					gravity = factor * delta;
				} else {
					// 反重力
					gravity = - factor * delta;
				}

			}

		} else if (m_type == SPRING_GRAVITY) {

			static const double X_CONSTANT = 0.0001;

			// ばね型の重力(力の大きさが距離に比例する)
			gravity = X_CONSTANT * m_source->getMass() * target->getMass() * delta;

		}

	}

	return gravity;
}

