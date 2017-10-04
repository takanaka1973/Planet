//
//	Camera�N���X�̒�`
//

#pragma once

#include "Vector3D.h"

//
//	�J����
//
class Camera
{
public:

	// �R���X�g���N�^
	Camera();
	// �f�X�g���N�^
	virtual ~Camera();

	// �ʒu��ݒ肷��
	virtual void setPosition(const Vector3D& v);
	// �Q�Ɠ_��ݒ肷��
	virtual void setRefPoint(const Vector3D& v);
	// �������ݒ肷��
	virtual void setUpDirection(const Vector3D& v);

	// �œ_�����킹��
	virtual void focus();

	// �ړ�����
	virtual void move(const Vector3D& delta);
	// Y���ɉ����ĉ�]����
	virtual void rotateAroundYAxis(double angleDelta);

private:

	Vector3D m_position;		// �ʒu
	Vector3D m_ref_point;		// �Q�Ɠ_
	Vector3D m_up_direction;	// �����

	Camera(const Camera&);
	Camera& operator=(const Camera&);
};

