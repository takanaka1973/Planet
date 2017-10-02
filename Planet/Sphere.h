//
//	Sphereクラスの定義
//

#pragma once

#include "Shape.h"

//
//	球
//
class Sphere : public Shape
{
public:

	// コンストラクタ
	explicit Sphere(double radius);
	// デストラクタ
	virtual ~Sphere();

	// レンダリングする <override>
	virtual void render(const Vector3D& position);

private:

	double m_radius;	// 半径

	Sphere(const Sphere&);
	Sphere& operator=(const Sphere&);
};

