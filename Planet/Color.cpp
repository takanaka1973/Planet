//
//	Colorクラスの実装
//

#include "common.h"
#include "Color.h"

// アルファ成分のデフォルト値
static const double ALPHA_DEFAULT = 1.0;

//
//	デフォルトコンストラクタ
//
Color::Color()
: m_red(0.0),
  m_green(0.0),
  m_blue(0.0),
  m_alpha(ALPHA_DEFAULT)
{
}

//
//	コンストラクタ(RGB)
//
Color::Color(double red, double green, double blue)
: m_red(red),
  m_green(green),
  m_blue(blue),
  m_alpha(ALPHA_DEFAULT)
{
}

//
//	コンストラクタ(RGBA)
//
Color::Color(double red, double green, double blue, double alpha)
: m_red(red),
  m_green(green),
  m_blue(blue),
  m_alpha(alpha)
{
}

//
//	コピーコンストラクタ
//
Color::Color(const Color& src)
: m_red(src.m_red),
  m_green(src.m_green),
  m_blue(src.m_blue),
  m_alpha(src.m_alpha)
{
}

//
//	デストラクタ
//
Color::~Color()
{
}

//
//	代入演算子
//
Color& Color::operator=(const Color& src)
{
	if (this != &src) {
		m_red	= src.m_red;
		m_green	= src.m_green;
		m_blue	= src.m_blue;
		m_alpha	= src.m_alpha;
	}

	return *this;
}

//
//	RGBAを取得する
//
void Color::getRGBA(float *array) const
{
	assert(array != NULL);

	array[0] = static_cast<float>(m_red);
	array[1] = static_cast<float>(m_green);
	array[2] = static_cast<float>(m_blue);
	array[3] = static_cast<float>(m_alpha);
}

//
//	赤色成分を取得する
//
double Color::getRed() const
{
	return m_red;
}

//
//	緑色成分を取得する
//
double Color::getGreen() const
{
	return m_green;
}

//
//	青色成分を取得する
//
double Color::getBlue() const
{
	return m_blue;
}

//
//	アルファ成分を取得する
//
double Color::getAlpha() const
{
	return m_alpha;
}

