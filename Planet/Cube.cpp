//
//	Cube�N���X�̎���
//

#include "common.h"
#include "Cube.h"
#include "Vector3D.h"

//
//	�R���X�g���N�^
//
Cube::Cube(double edge_length, double rotation_x, double rotation_y)
: m_edge_length(edge_length),
  m_rotation_x(rotation_x),
  m_rotation_y(rotation_y)
{
	assert(edge_length > 0.0);
}

//
//	�f�X�g���N�^
//
Cube::~Cube()
{
}

//
//	�����_�����O����
//
void Cube::render(const Vector3D& position)
{
	// ���݂̍s���ۑ�
	glPushMatrix();

	// ���s�ړ�
	glTranslated(position.getX(), position.getY(), position.getZ());

	// ��]
	glRotated(m_rotation_y, 0.0, 1.0, 0.0);
	glRotated(m_rotation_x, 1.0, 0.0, 0.0);

	// ��ӂ̒����̔������v�Z
	double half_len = m_edge_length / 2.0;

	// ���_�w����J�n
	glBegin(GL_QUADS);

	glNormal3d(1.0, 0.0, 0.0);
	glVertex3d(half_len,  half_len,  half_len);
	glVertex3d(half_len, -half_len,  half_len);
	glVertex3d(half_len, -half_len, -half_len);
	glVertex3d(half_len,  half_len, -half_len);

	glNormal3d(-1.0, 0.0, 0.0);
	glVertex3d(-half_len,  half_len,  half_len);
	glVertex3d(-half_len,  half_len, -half_len);
	glVertex3d(-half_len, -half_len, -half_len);
	glVertex3d(-half_len, -half_len,  half_len);

	glNormal3d(0.0, 1.0, 0.0);
	glVertex3d( half_len, half_len,  half_len);
	glVertex3d( half_len, half_len, -half_len);
	glVertex3d(-half_len, half_len, -half_len);
	glVertex3d(-half_len, half_len,  half_len);

	glNormal3d(0.0, -1.0, 0.0);
	glVertex3d( half_len, -half_len,  half_len);
	glVertex3d(-half_len, -half_len,  half_len);
	glVertex3d(-half_len, -half_len, -half_len);
	glVertex3d( half_len, -half_len, -half_len);

	glNormal3d(0.0, 0.0, 1.0);
	glVertex3d( half_len,  half_len, half_len);
	glVertex3d(-half_len,  half_len, half_len);
	glVertex3d(-half_len, -half_len, half_len);
	glVertex3d( half_len, -half_len, half_len);

	glNormal3d(0.0, 0.0, -1.0);
	glVertex3d( half_len,  half_len, -half_len);
	glVertex3d( half_len, -half_len, -half_len);
	glVertex3d(-half_len, -half_len, -half_len);
	glVertex3d(-half_len,  half_len, -half_len);

	// ���_�w����I��
	glEnd();

	// �s������ɖ߂�
	glPopMatrix();
}

