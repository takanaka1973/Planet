//
//	FixedStar�N���X�̎���
//

#include "common.h"
#include "FixedStar.h"

//
//	�R���X�g���N�^
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
//	�f�X�g���N�^
//
FixedStar::~FixedStar()
{
	delete m_gravity_field;
}

//
//	�ʒu���擾����
//
Vector3D FixedStar::getPosition()
{
	return m_fixed_position;
}

//
//	�d�͏���擾����
//
GravityField *FixedStar::getGravityField()
{
	return m_gravity_field;
}

//
//	���Ԃ̌o�߂�ʒm����
//
void FixedStar::tick(int timespan, const GravityFieldList& gravity_fields)
{
	// �P���͈ړ����Ȃ����Ƃɂ���
}

