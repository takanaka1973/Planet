//
//	Sphereクラスの実装
//

#include "common.h"
#include "Sphere.h"
#include "Vector3D.h"

//
//	コンストラクタ
//
Sphere::Sphere(double radius)
: m_radius(radius)
{
	assert(radius > 0.0);
}

//
//	デストラクタ
//
Sphere::~Sphere()
{
}

//
//	レンダリングする
//
void Sphere::render(const Vector3D& position)
{
	// quadricオブジェクトを作成
	GLUquadricObj *quad = gluNewQuadric();
	assert(quad != NULL);

	// 現在の行列を保存
	glPushMatrix();

	// 平行移動
	glTranslated(position.getX(), position.getY(), position.getZ());

	// 球をレンダリング
	gluSphere(quad, m_radius, 16, 16);

	// 行列を元に戻す
	glPopMatrix();

	// quadricオブジェクトを削除
	gluDeleteQuadric(quad);
}

