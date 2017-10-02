//
//	LightSource�N���X�̎���
//

#include "common.h"
#include "LightSource.h"
#include "Vector3D.h"

// �����̍ő��
static const int MAX_LIGHT_SOURCE_NUM = 8;

//
//	�R���X�g���N�^
//
LightSource::LightSource(int light_source_no)
: m_light_source_no(light_source_no),
  m_constant_attenuation(1.0),
  m_linear_attenuation(0.0),
  m_quadratic_attenuation(0.0)
{
	assert(light_source_no >= 0 && light_source_no < MAX_LIGHT_SOURCE_NUM);
}

//
//	�f�X�g���N�^
//
LightSource::~LightSource()
{
}

//
//	���̌�������ݒ肷��
//
void LightSource::setAttenuation(
	double constant, double linear, double quadratic)
{
	assert(constant >= 0.0);
	assert(linear >= 0.0);
	assert(quadratic >= 0.0);

	m_constant_attenuation = constant;
	m_linear_attenuation = linear;
	m_quadratic_attenuation = quadratic;
}

//
//	�����̐F��ݒ肷��
//
void LightSource::setAmbientColor(const Color& color)
{
	m_ambient_color = color;
}

//
//	�g�U���̐F��ݒ肷��
//
void LightSource::setDiffuseColor(const Color& color)
{
	m_diffuse_color = color;
}

//
//	���ʌ��̐F��ݒ肷��
//
void LightSource::setSpecularColor(const Color& color)
{
	m_specular_color = color;
}

//
//	������˂���
//
void LightSource::emitLight(const Vector3D& position)
{
	// ���̌�����
	glLightf(GL_LIGHT0 + m_light_source_no,
		GL_CONSTANT_ATTENUATION, static_cast<float>(m_constant_attenuation));
	glLightf(GL_LIGHT0 + m_light_source_no,
		GL_LINEAR_ATTENUATION, static_cast<float>(m_linear_attenuation));
	glLightf(GL_LIGHT0 + m_light_source_no,
		GL_QUADRATIC_ATTENUATION, static_cast<float>(m_quadratic_attenuation));

	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// �����̐F
	m_ambient_color.getRGBA(color);
	glLightfv(GL_LIGHT0 + m_light_source_no, GL_AMBIENT, color);

	// �g�U���̐F
	m_diffuse_color.getRGBA(color);
	glLightfv(GL_LIGHT0 + m_light_source_no, GL_DIFFUSE, color);

	// ���ʌ��̐F
	m_specular_color.getRGBA(color);
	glLightfv(GL_LIGHT0 + m_light_source_no, GL_SPECULAR, color);

	// �ʒu
	float pos[4] = {
		static_cast<float>(position.getX()),
		static_cast<float>(position.getY()),
		static_cast<float>(position.getZ()), 1.0f };
	glLightfv(GL_LIGHT0 + m_light_source_no, GL_POSITION, pos);

	// �L��������
	glEnable(GL_LIGHT0 + m_light_source_no);
}

