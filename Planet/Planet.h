//
//	Planet�N���X�̒�`
//

#pragma once

#include "Star.h"
#include "Vector3D.h"

//
//	�f��
//
class Planet : public Star
{
public:

	// �R���X�g���N�^
	Planet(double mass,
		Surface *surface, Shape *shape, LightSource *light_source,
		const Vector3D& initial_position, const Vector3D& initial_velocity);
	// �f�X�g���N�^
	virtual ~Planet();

	// �ʒu���擾���� <override>
	virtual Vector3D getPosition();
	// �d�͏���擾���� <override>
	virtual GravityField *getGravityField();

	// ���Ԃ̌o�߂�ʒm���� <override>
	virtual void tick(int timespan, const GravityFieldList& gravity_fields);

private:

	// �d�͂��v�Z����
	Vector3D calcGravity(const Vector3D& pos, const GravityFieldList& gfs);

	Vector3D m_position;	// �ʒu
	Vector3D m_velocity;	// ���x

	Planet(const Planet&);
	Planet& operator=(const Planet&);
};

