//
//	Star�N���X�̒�`
//

#pragma once

#include "GravityFieldList.h"

class Surface;
class Shape;
class LightSource;
class Vector3D;

//
//	��
//
class Star
{
public:

	// �R���X�g���N�^
	Star(double mass, Surface *surface, Shape *shape, LightSource *light_source);
	// �f�X�g���N�^
	virtual ~Star();

	// ���ʂ��擾����
	virtual double getMass();
	// �ʒu���擾����
	virtual Vector3D getPosition() = 0;
	// �d�͏���擾����
	virtual GravityField *getGravityField() = 0;

	// ������˂���
	virtual void emitLight();
	// �����_�����O����
	virtual void render();

	// ���Ԃ̌o�߂�ʒm����
	virtual void tick(int timespan, const GravityFieldList& gravity_fields) = 0;

private:

	double m_mass;					// ����
	Surface *m_surface;				// �\��
	Shape *m_shape;					// �`
	LightSource *m_light_source;	// ����

	Star(const Star&);
	Star& operator=(const Star&);
};

