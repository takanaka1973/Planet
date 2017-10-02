//
//	Surface�N���X�̒�`
//

#pragma once

#include "Color.h"

//
//	�\��
//
class Surface
{
public:

	// �R���X�g���N�^
	Surface();
	// �f�X�g���N�^
	virtual ~Surface();

	// �������˂̐F��ݒ肷��
	virtual void setAmbientColor(const Color& color);
	// �g�U�����˂̐F��ݒ肷��
	virtual void setDiffuseColor(const Color& color);
	// ���ʌ����˂̐F��ݒ肷��
	virtual void setSpecularColor(const Color& color);
	// ���ʌ����˂̎w����ݒ肷��
	virtual void setShininess(double shininess);
	// ���ˌ��̐F��ݒ肷��
	virtual void setEmissionColor(const Color& color);

	// �A�N�e�B�u�ɂ���
	virtual void activate();

private:

	Color m_ambient_color;	// �������˂̐F
	Color m_diffuse_color;	// �g�U�����˂̐F
	Color m_specular_color;	// ���ʌ����˂̐F
	double m_shininess;		// ���ʌ����˂̎w��(0�`128)
	Color m_emission_color;	// ���ˌ��̐F

	Surface(const Surface&);
	Surface& operator=(const Surface&);
};

