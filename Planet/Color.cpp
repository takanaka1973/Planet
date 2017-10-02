//
//	Color�N���X�̎���
//

#include "common.h"
#include "Color.h"

// �A���t�@�����̃f�t�H���g�l
static const double ALPHA_DEFAULT = 1.0;

//
//	�f�t�H���g�R���X�g���N�^
//
Color::Color()
: m_red(0.0),
  m_green(0.0),
  m_blue(0.0),
  m_alpha(ALPHA_DEFAULT)
{
}

//
//	�R���X�g���N�^(RGB)
//
Color::Color(double red, double green, double blue)
: m_red(red),
  m_green(green),
  m_blue(blue),
  m_alpha(ALPHA_DEFAULT)
{
}

//
//	�R���X�g���N�^(RGBA)
//
Color::Color(double red, double green, double blue, double alpha)
: m_red(red),
  m_green(green),
  m_blue(blue),
  m_alpha(alpha)
{
}

//
//	�R�s�[�R���X�g���N�^
//
Color::Color(const Color& src)
: m_red(src.m_red),
  m_green(src.m_green),
  m_blue(src.m_blue),
  m_alpha(src.m_alpha)
{
}

//
//	�f�X�g���N�^
//
Color::~Color()
{
}

//
//	������Z�q
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
//	RGBA���擾����
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
//	�ԐF�������擾����
//
double Color::getRed() const
{
	return m_red;
}

//
//	�ΐF�������擾����
//
double Color::getGreen() const
{
	return m_green;
}

//
//	�F�������擾����
//
double Color::getBlue() const
{
	return m_blue;
}

//
//	�A���t�@�������擾����
//
double Color::getAlpha() const
{
	return m_alpha;
}

