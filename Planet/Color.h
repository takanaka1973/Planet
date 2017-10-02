//
//	Color�N���X�̒�`
//

#pragma once

//
//	�F
//
class Color
{
public:

	// �f�t�H���g�R���X�g���N�^
	Color();
	// �R���X�g���N�^(RGB)
	Color(double red, double green, double blue);
	// �R���X�g���N�^(RGBA)
	Color(double red, double green, double blue, double alpha);
	// �R�s�[�R���X�g���N�^
	Color(const Color& src);
	// �f�X�g���N�^
	virtual ~Color();

	// ������Z�q
	Color& operator=(const Color& src);

	// RGBA���擾����
	virtual void getRGBA(float *array) const;

	// �ԐF�������擾����
	virtual double getRed() const;
	// �ΐF�������擾����
	virtual double getGreen() const;
	// �F�������擾����
	virtual double getBlue() const;
	// �A���t�@�������擾����
	virtual double getAlpha() const;

private:

	double m_red;		// �ԐF����
	double m_green;		// �ΐF����
	double m_blue;		// �F����
	double m_alpha;		// �A���t�@����

};

