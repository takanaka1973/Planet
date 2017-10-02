//
//	Surfaceクラスの実装
//

#include "common.h"
#include "Surface.h"

//
//	コンストラクタ
//
Surface::Surface()
: m_shininess(0.0)
{
}

//
//	デストラクタ
//
Surface::~Surface()
{
}

//
//	環境光反射の色を設定する
//
void Surface::setAmbientColor(const Color& color)
{
	m_ambient_color = color;
}

//
//	拡散光反射の色を設定する
//
void Surface::setDiffuseColor(const Color& color)
{
	m_diffuse_color = color;
}

//
//	鏡面光反射の色を設定する
//
void Surface::setSpecularColor(const Color& color)
{
	m_specular_color = color;
}

//
//	鏡面光反射の指数を設定する
//
void Surface::setShininess(double shininess)
{
	assert(shininess >= 0.0 && shininess <= 128.0);
	m_shininess = shininess;
}

//
//	放射光の色を設定する
//
void Surface::setEmissionColor(const Color& color)
{
	m_emission_color = color;
}

//
//	アクティブにする
//
void Surface::activate()
{
	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// 環境光反射の色
	m_ambient_color.getRGBA(color);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);

	// 拡散光反射の色
	m_diffuse_color.getRGBA(color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	// 鏡面光反射の色
	m_specular_color.getRGBA(color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color);

	// 鏡面光反射の指数
	glMaterialf(GL_FRONT, GL_SHININESS, static_cast<float>(m_shininess));

	// 放射光の色
	m_emission_color.getRGBA(color);
	glMaterialfv(GL_FRONT, GL_EMISSION, color);
}

