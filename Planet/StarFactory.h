//
//	StarFactory�N���X�̒�`
//

#pragma once

#include "StarList.h"

class FixedStar;
class Planet;
class Color;
class Vector3D;

//
//	���̃t�@�N�g��
//
class StarFactory
{
public:

	// �R���X�g���N�^
	StarFactory();
	// �f�X�g���N�^
	virtual ~StarFactory();

	// �����쐬����
	virtual bool createStars(StarList& list);

private:

	// �P�����쐬����
	FixedStar *createFixedStar(
		double mass, double radius, int light_source_no,
		const Color& color, const Vector3D& pos, GravityType gravity_type);
	// �f�����쐬����
	Planet *createPlanet(double mass, double radius,
		const Color& color, const Vector3D& p0, const Vector3D& v0);

	StarFactory(const StarFactory&);
	StarFactory& operator=(const StarFactory&);
};

