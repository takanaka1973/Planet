//
//	Sphere�N���X�̎���
//

#include "common.h"
#include "Sphere.h"
#include "Vector3D.h"

//
//	�R���X�g���N�^
//
Sphere::Sphere(double radius)
: m_radius(radius)
{
	assert(radius > 0.0);
}

//
//	�f�X�g���N�^
//
Sphere::~Sphere()
{
}

//
//	�����_�����O����
//
void Sphere::render(const Vector3D& position)
{
	// quadric�I�u�W�F�N�g���쐬
	GLUquadricObj *quad = gluNewQuadric();
	assert(quad != NULL);

	// ���݂̍s���ۑ�
	glPushMatrix();

	// ���s�ړ�
	glTranslated(position.getX(), position.getY(), position.getZ());

	// ���������_�����O
	gluSphere(quad, m_radius, 16, 16);

	// �s������ɖ߂�
	glPopMatrix();

	// quadric�I�u�W�F�N�g���폜
	gluDeleteQuadric(quad);
}

