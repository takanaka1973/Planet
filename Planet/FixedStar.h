//
//	FixedStar�N���X�̒�`
//

#pragma once

#include "Star.h"
#include "Vector3D.h"
#include "GravityType.h"

//
//	�P��
//
class FixedStar : public Star
{
public:

	// �R���X�g���N�^
	FixedStar(double mass,
		Surface *surface, Shape *shape, LightSource *light_source,
		const Vector3D& position, GravityType gravity_type);
	// �f�X�g���N�^
	virtual ~FixedStar();

	// �ʒu���擾���� <override>
	virtual Vector3D getPosition();
	// �d�͏���擾���� <override>
	virtual GravityField *getGravityField();

	// ���Ԃ̌o�߂�ʒm���� <override>
	virtual void tick(int timespan, const GravityFieldList& gravity_fields);

private:

	Vector3D m_fixed_position;		// �Œ�ʒu
	GravityField *m_gravity_field;	// �d�͏�

	FixedStar(const FixedStar&);
	FixedStar& operator=(const FixedStar&);
};

