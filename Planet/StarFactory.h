//
//	StarFactoryクラスの定義
//

#pragma once

#include "StarList.h"

class FixedStar;
class Planet;
class Color;
class Vector3D;

//
//	星のファクトリ
//
class StarFactory
{
public:

	// コンストラクタ
	StarFactory();
	// デストラクタ
	virtual ~StarFactory();

	// 星を作成する
	virtual bool createStars(StarList& list);

private:

	// 恒星を作成する
	FixedStar *createFixedStar(
		double mass, double radius, int light_source_no,
		const Color& color, const Vector3D& pos, GravityType gravity_type);
	// 惑星を作成する
	Planet *createPlanet(double mass, double radius,
		const Color& color, const Vector3D& p0, const Vector3D& v0);

	StarFactory(const StarFactory&);
	StarFactory& operator=(const StarFactory&);
};

