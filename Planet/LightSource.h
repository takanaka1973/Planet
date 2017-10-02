//
//	LightSource�N���X�̒�`
//

#pragma once

#include "Color.h"

class Vector3D;

//
//	����
//
class LightSource
{
public:

	// �R���X�g���N�^
	explicit LightSource(int light_source_no);
	// �f�X�g���N�^
	virtual ~LightSource();

	// ���̌�������ݒ肷��
	virtual void setAttenuation(
		double constant, double linear, double quadratic);

	// �����̐F��ݒ肷��
	virtual void setAmbientColor(const Color& color);
	// �g�U���̐F��ݒ肷��
	virtual void setDiffuseColor(const Color& color);
	// ���ʌ��̐F��ݒ肷��
	virtual void setSpecularColor(const Color& color);

	// ������˂���
	virtual void emitLight(const Vector3D& position);

private:

	int m_light_source_no;			// �����ԍ�

	double m_constant_attenuation;	// ���̌�����(0��)
	double m_linear_attenuation;	// ���̌�����(1��)
	double m_quadratic_attenuation;	// ���̌�����(2��)

	Color m_ambient_color;			// �����̐F
	Color m_diffuse_color;			// �g�U���̐F
	Color m_specular_color;			// ���ʌ��̐F

	LightSource(const LightSource&);
	LightSource& operator=(const LightSource&);
};

