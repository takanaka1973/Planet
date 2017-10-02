//
//	Shape�N���X�̒�`
//

#pragma once

class Vector3D;

//
//	�`
//
class Shape
{
public:

	// �R���X�g���N�^
	Shape();
	// �f�X�g���N�^
	virtual ~Shape();

	// �����_�����O����
	virtual void render(const Vector3D& position) = 0;

private:

	Shape(const Shape&);
	Shape& operator=(const Shape&);
};

