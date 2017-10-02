//
//	Vector3D�N���X�̎���
//

#include "common.h"
#include "Vector3D.h"

//
//	�f�t�H���g�R���X�g���N�^
//
Vector3D::Vector3D()
: m_x(0.0),
  m_y(0.0),
  m_z(0.0)
{
}

//
//	�R���X�g���N�^
//
Vector3D::Vector3D(double x, double y, double z)
: m_x(x),
  m_y(y),
  m_z(z)
{
}

//
//	�R�s�[�R���X�g���N�^
//
Vector3D::Vector3D(const Vector3D& src)
: m_x(src.m_x),
  m_y(src.m_y),
  m_z(src.m_z)
{
}

//
//	�f�X�g���N�^
//
Vector3D::~Vector3D()
{
}

//
//	������Z�q
//
Vector3D& Vector3D::operator=(const Vector3D& src)
{
	if (this != &src) {
		m_x = src.m_x;
		m_y = src.m_y;
		m_z = src.m_z;
	}

	return *this;
}

//
//	x�������擾����
//
double Vector3D::getX() const
{
	return m_x;
}

//
//	y�������擾����
//
double Vector3D::getY() const
{
	return m_y;
}

//
//	z�������擾����
//
double Vector3D::getZ() const
{
	return m_z;
}

//
//	��Βl���擾����
//
double Vector3D::getAbs() const
{
	return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

//
//	x������ݒ肷��
//
void Vector3D::setX(double value)
{
	m_x = value;
}

//
//	y������ݒ肷��
//
void Vector3D::setY(double value)
{
	m_y = value;
}

//
//	z������ݒ肷��
//
void Vector3D::setZ(double value)
{
	m_z = value;
}

//
//	operator+=
//
Vector3D& Vector3D::operator+=(const Vector3D& src)
{
	m_x += src.m_x;
	m_y += src.m_y;
	m_z += src.m_z;

	return *this;
}

//
//	operator+
//
Vector3D operator+(const Vector3D& left, const Vector3D& right)
{
	return Vector3D(left.getX() + right.getX(),
					left.getY() + right.getY(),
					left.getZ() + right.getZ());
}

//
//	operator-
//
Vector3D operator-(const Vector3D& left, const Vector3D& right)
{
	return Vector3D(left.getX() - right.getX(),
					left.getY() - right.getY(),
					left.getZ() - right.getZ());
}

//
//	operator*
//
Vector3D operator*(double s, const Vector3D& v)
{
	return Vector3D(s * v.getX(), s * v.getY(), s * v.getZ());
}

