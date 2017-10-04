//
//	Camera�N���X�̎���
//

#include "common.h"
#include "Camera.h"
#include <cmath>

//
//	�R���X�g���N�^
//
Camera::Camera()
: m_position(0.0, 0.0, 100.0),
  m_ref_point(0.0, 0.0, 0.0),
  m_up_direction(0.0, 1.0, 0.0)
{
}

//
//	�f�X�g���N�^
//
Camera::~Camera()
{
}

//
//	�ʒu��ݒ肷��
//
void Camera::setPosition(const Vector3D& v)
{
	m_position = v;
}

//
//	�Q�Ɠ_��ݒ肷��
//
void Camera::setRefPoint(const Vector3D& v)
{
	m_ref_point = v;
}

//
//	�������ݒ肷��
//
void Camera::setUpDirection(const Vector3D& v)
{
	m_up_direction = v;
}

//
//	�œ_�����킹��
//
void Camera::focus()
{
	gluLookAt(
		m_position.getX(), m_position.getY(), m_position.getZ(),
		m_ref_point.getX(), m_ref_point.getY(), m_ref_point.getZ(),
		m_up_direction.getX(), m_up_direction.getY(), m_up_direction.getZ());
}

//
//	�ړ�����
//
void Camera::move(const Vector3D& delta)
{
	m_position += delta;
	m_ref_point += delta;
}

//
//	Y���ɉ����ĉ�]����
//
void Camera::rotateAroundYAxis(double angleDelta)
{
	double currentX = m_position.getX();
	double currentZ = m_position.getZ();

	double newX = currentX * std::cos(angleDelta) - currentZ * std::sin(angleDelta);
	double newZ = currentX * std::sin(angleDelta) + currentZ * std::cos(angleDelta);

	m_position.setX(newX);
	m_position.setZ(newZ);
}

