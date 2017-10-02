//
//	Sphere�N���X�̒�`
//

#pragma once

#include "Shape.h"

//
//	��
//
class Sphere : public Shape
{
public:

	// �R���X�g���N�^
	explicit Sphere(double radius);
	// �f�X�g���N�^
	virtual ~Sphere();

	// �����_�����O���� <override>
	virtual void render(const Vector3D& position);

private:

	double m_radius;	// ���a

	Sphere(const Sphere&);
	Sphere& operator=(const Sphere&);
};

