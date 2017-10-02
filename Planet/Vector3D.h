//
//	Vector3D�N���X�̒�`
//

#pragma once

//
//	�O�����x�N�g��
//
class Vector3D
{
public:

	// �f�t�H���g�R���X�g���N�^
	Vector3D();
	// �R���X�g���N�^
	Vector3D(double x, double y, double z);
	// �R�s�[�R���X�g���N�^
	Vector3D(const Vector3D& src);

	// �f�X�g���N�^
	virtual ~Vector3D();

	// ������Z�q
	Vector3D& operator=(const Vector3D& src);

	// x�������擾����
	virtual double getX() const;
	// y�������擾����
	virtual double getY() const;
	// z�������擾����
	virtual double getZ() const;

	// ��Βl���擾����
	virtual double getAbs() const;

	// x������ݒ肷��
	virtual void setX(double value);
	// y������ݒ肷��
	virtual void setY(double value);
	// z������ݒ肷��
	virtual void setZ(double value);

	// operator+=
	Vector3D& operator+=(const Vector3D& src);

private:

	double m_x;		// x����
	double m_y;		// y����
	double m_z;		// z����

};

// operator+
Vector3D operator+(const Vector3D& left, const Vector3D& right);
// operator-
Vector3D operator-(const Vector3D& left, const Vector3D& right);
// operator*
Vector3D operator*(double s, const Vector3D& v);

