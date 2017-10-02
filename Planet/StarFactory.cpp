//
//	StarFactory�N���X�̎���
//

#include "common.h"
#include "StarFactory.h"
#include "FixedStar.h"
#include "Planet.h"
#include "Surface.h"
#include "Sphere.h"
#include "Cube.h"
#include "LightSource.h"

//
//	�R���X�g���N�^
//
StarFactory::StarFactory()
{
}

//
//	�f�X�g���N�^
//
StarFactory::~StarFactory()
{
}

//
//	�P�����쐬����
//
FixedStar *StarFactory::createFixedStar(
	double mass, double radius, int light_source_no,
	const Color& color, const Vector3D& pos, GravityType gravity_type)
{
	Surface *s = new Surface();
	s->setEmissionColor(color);

	LightSource *l = new LightSource(light_source_no);
	l->setAttenuation(1.0, 0.0, 0.0001);
	l->setAmbientColor(Color(0.2, 0.2, 0.2));
	l->setDiffuseColor(Color(1.0, 1.0, 1.0));
	l->setSpecularColor(Color(0.2, 0.2, 0.2));

	return new FixedStar(mass, s, new Sphere(radius), l, pos, gravity_type);
}

//
//	�f�����쐬����
//
Planet *StarFactory::createPlanet(double mass, double radius,
	const Color& color, const Vector3D& p0, const Vector3D& v0)
{
	Surface *s = new Surface();
	s->setAmbientColor(color);
	s->setDiffuseColor(color);
	s->setSpecularColor(Color(0.2, 0.2, 0.2));
	s->setShininess(5.0);

	return new Planet(mass, s, new Sphere(radius), NULL, p0, v0);
}

//
//	�����쐬����
//
bool StarFactory::createStars(StarList& list)
{
	// �P��

	int light_source_no = 0;

	list.push_back(createFixedStar(100.0, 1.5, light_source_no++,
		Color(0.7, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0), NORMAL_GRAVITY));

	// �f��

	static const double STD_MASS = 5.0;
	static const double STD_RADIUS = 1.0;

	// ��
	list.push_back(createPlanet(STD_MASS, STD_RADIUS,
		Color(0.0, 0.0, 0.8), Vector3D(30.0, 0.0, 0.0), Vector3D(0.0, 0.5, 0.0)));
	// ��
	list.push_back(createPlanet(STD_MASS, STD_RADIUS,
		Color(0.0, 0.8, 0.0), Vector3D(-30.0, 0.0, 0.0), Vector3D(-0.4, -0.4, 0.0)));
	// ��
	list.push_back(createPlanet(STD_MASS, STD_RADIUS,
		Color(0.8, 0.0, 0.8), Vector3D(-20.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.5)));
	// ��
	list.push_back(createPlanet(STD_MASS, STD_RADIUS,
		Color(0.8, 0.8, 0.0), Vector3D(20.0, 0.0, 0.0), Vector3D(0.0, 0.6, -0.2)));
	// ���F
	list.push_back(createPlanet(STD_MASS, STD_RADIUS,
		Color(0.0, 0.8, 0.8), Vector3D(35.0, 0.0, 0.0), Vector3D(0.0, 0.3, -0.3)));

	return true;
}

