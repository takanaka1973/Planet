//
//	Surface�N���X�̎���
//

#include "common.h"
#include "Surface.h"

//
//	�R���X�g���N�^
//
Surface::Surface()
: m_shininess(0.0)
{
}

//
//	�f�X�g���N�^
//
Surface::~Surface()
{
}

//
//	�������˂̐F��ݒ肷��
//
void Surface::setAmbientColor(const Color& color)
{
	m_ambient_color = color;
}

//
//	�g�U�����˂̐F��ݒ肷��
//
void Surface::setDiffuseColor(const Color& color)
{
	m_diffuse_color = color;
}

//
//	���ʌ����˂̐F��ݒ肷��
//
void Surface::setSpecularColor(const Color& color)
{
	m_specular_color = color;
}

//
//	���ʌ����˂̎w����ݒ肷��
//
void Surface::setShininess(double shininess)
{
	assert(shininess >= 0.0 && shininess <= 128.0);
	m_shininess = shininess;
}

//
//	���ˌ��̐F��ݒ肷��
//
void Surface::setEmissionColor(const Color& color)
{
	m_emission_color = color;
}

//
//	�A�N�e�B�u�ɂ���
//
void Surface::activate()
{
	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// �������˂̐F
	m_ambient_color.getRGBA(color);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);

	// �g�U�����˂̐F
	m_diffuse_color.getRGBA(color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	// ���ʌ����˂̐F
	m_specular_color.getRGBA(color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color);

	// ���ʌ����˂̎w��
	glMaterialf(GL_FRONT, GL_SHININESS, static_cast<float>(m_shininess));

	// ���ˌ��̐F
	m_emission_color.getRGBA(color);
	glMaterialfv(GL_FRONT, GL_EMISSION, color);
}

