//
//	LightSourceクラスの実装
//

#include "common.h"
#include "LightSource.h"
#include "Vector3D.h"

// 光源の最大個数
static const int MAX_LIGHT_SOURCE_NUM = 8;

//
//	コンストラクタ
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
//	デストラクタ
//
LightSource::~LightSource()
{
}

//
//	光の減衰率を設定する
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
//	環境光の色を設定する
//
void LightSource::setAmbientColor(const Color& color)
{
	m_ambient_color = color;
}

//
//	拡散光の色を設定する
//
void LightSource::setDiffuseColor(const Color& color)
{
	m_diffuse_color = color;
}

//
//	鏡面光の色を設定する
//
void LightSource::setSpecularColor(const Color& color)
{
	m_specular_color = color;
}

//
//	光を放射する
//
void LightSource::emitLight(const Vector3D& position)
{
	// 光の減衰率
	glLightf(GL_LIGHT0 + m_light_source_no,
		GL_CONSTANT_ATTENUATION, static_cast<float>(m_constant_attenuation));
	glLightf(GL_LIGHT0 + m_light_source_no,
		GL_LINEAR_ATTENUATION, static_cast<float>(m_linear_attenuation));
	glLightf(GL_LIGHT0 + m_light_source_no,
		GL_QUADRATIC_ATTENUATION, static_cast<float>(m_quadratic_attenuation));

	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// 環境光の色
	m_ambient_color.getRGBA(color);
	glLightfv(GL_LIGHT0 + m_light_source_no, GL_AMBIENT, color);

	// 拡散光の色
	m_diffuse_color.getRGBA(color);
	glLightfv(GL_LIGHT0 + m_light_source_no, GL_DIFFUSE, color);

	// 鏡面光の色
	m_specular_color.getRGBA(color);
	glLightfv(GL_LIGHT0 + m_light_source_no, GL_SPECULAR, color);

	// 位置
	float pos[4] = {
		static_cast<float>(position.getX()),
		static_cast<float>(position.getY()),
		static_cast<float>(position.getZ()), 1.0f };
	glLightfv(GL_LIGHT0 + m_light_source_no, GL_POSITION, pos);

	// 有効化する
	glEnable(GL_LIGHT0 + m_light_source_no);
}

