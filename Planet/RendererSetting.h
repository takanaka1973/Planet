//
//	RendererSetting�N���X�̒�`
//

#pragma once

#include "Vector3D.h"

//
//	�����_���[�̐ݒ�
//
class RendererSetting
{
public:

	// �R���X�g���N�^
	RendererSetting();
	// �f�X�g���N�^
	virtual ~RendererSetting();

	// �J�����̏����ʒu��ݒ肷��
	virtual void setCameraInitialPosition(const Vector3D& v);
	// �J�����̏����Q�Ɠ_��ݒ肷��
	virtual void setCameraInitialRefPoint(const Vector3D& v);
	// �J�����̏����������ݒ肷��
	virtual void setCameraInitialUpDirection(const Vector3D& v);

	// �J�����̏����ʒu���擾����
	virtual Vector3D getCameraInitialPosition();
	// �J�����̏����Q�Ɠ_���擾����
	virtual Vector3D getCameraInitialRefPoint();
	// �J�����̏�����������擾����
	virtual Vector3D getCameraInitialUpDirection();

private:

	Vector3D m_camera_ini_position;		// �J�����̏����ʒu
	Vector3D m_camera_ini_ref_point;	// �J�����̏����Q�Ɠ_
	Vector3D m_camera_ini_up_direction;	// �J�����̏��������

	RendererSetting(const RendererSetting&);
	RendererSetting& operator=(const RendererSetting&);
};

