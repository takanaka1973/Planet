//
//	Cube�N���X�̒�`
//

#pragma once

#include "Shape.h"

//
//	������
//
class Cube : public Shape
{
public:

	// �R���X�g���N�^
	Cube(double edge_length, double rotation_x, double rotation_y);
	// �f�X�g���N�^
	virtual ~Cube();

	// �����_�����O���� <override>
	virtual void render(const Vector3D& position);

private:

	double m_edge_length;	// ��ӂ̒���
	double m_rotation_x;	// x���̎���̉�]�p
	double m_rotation_y;	// y���̎���̉�]�p

	Cube(const Cube&);
	Cube& operator=(const Cube&);
};

