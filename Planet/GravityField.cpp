//
//	GravityField�N���X�̎���
//

#include "common.h"
#include "GravityField.h"
#include "Star.h"
#include "Vector3D.h"

//
//	�R���X�g���N�^
//
GravityField::GravityField(GravityType type, Star *source)
: m_type(type), m_source(source)
{
	assert(source != NULL);
}

//
//	�f�X�g���N�^
//
GravityField::~GravityField()
{
}

//
//	�d�͂��擾����
//
Vector3D GravityField::getGravity(Star *target, const Vector3D& target_pos)
{
	assert(target != NULL);

	Vector3D gravity;

	if (target != m_source) {

		// target��source�̕ψʃx�N�g��(target ---> source)
		Vector3D delta = m_source->getPosition() - target_pos;

		if (m_type == NORMAL_GRAVITY || m_type == REVERSE_GRAVITY) {

			// target��source�̋���
			double distance = delta.getAbs();

			if (distance > 0.0) {

				static const double GRAVITY_CONSTANT = 0.1;		// �d�͒萔

				double factor = GRAVITY_CONSTANT * m_source->getMass() * target->getMass()
									/ ( distance * distance * distance );

				if (m_type == NORMAL_GRAVITY) {
					// �ʏ�̏d��
					gravity = factor * delta;
				} else {
					// ���d��
					gravity = - factor * delta;
				}

			}

		} else if (m_type == SPRING_GRAVITY) {

			static const double X_CONSTANT = 0.0001;

			// �΂ˌ^�̏d��(�͂̑傫���������ɔ�Ⴗ��)
			gravity = X_CONSTANT * m_source->getMass() * target->getMass() * delta;

		}

	}

	return gravity;
}

