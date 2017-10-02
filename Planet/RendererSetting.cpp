//
//	RendererSetting�N���X�̎���
//

#include "common.h"
#include "RendererSetting.h"

//
//	�R���X�g���N�^
//
RendererSetting::RendererSetting()
{
}

//
//	�f�X�g���N�^
//
RendererSetting::~RendererSetting()
{
}

//
//	�J�����̏����ʒu��ݒ肷��
//
void RendererSetting::setCameraInitialPosition(const Vector3D& v)
{
	m_camera_ini_position = v;
}

//
//	�J�����̏����Q�Ɠ_��ݒ肷��
//
void RendererSetting::setCameraInitialRefPoint(const Vector3D& v)
{
	m_camera_ini_ref_point = v;
}

//
//	�J�����̏����������ݒ肷��
//
void RendererSetting::setCameraInitialUpDirection(const Vector3D& v)
{
	m_camera_ini_up_direction = v;
}

//
//	�J�����̏����ʒu���擾����
//
Vector3D RendererSetting::getCameraInitialPosition()
{
	return m_camera_ini_position;
}

//
//	�J�����̏����Q�Ɠ_���擾����
//
Vector3D RendererSetting::getCameraInitialRefPoint()
{
	return m_camera_ini_ref_point;
}

//
//	�J�����̏�����������擾����
//
Vector3D RendererSetting::getCameraInitialUpDirection()
{
	return m_camera_ini_up_direction;
}

