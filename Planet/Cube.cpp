//
//	Cubeクラスの実装
//

#include "common.h"
#include "Cube.h"
#include "Vector3D.h"

//
//	コンストラクタ
//
Cube::Cube(double edge_length, double rotation_x, double rotation_y)
: m_edge_length(edge_length),
  m_rotation_x(rotation_x),
  m_rotation_y(rotation_y)
{
	assert(edge_length > 0.0);
}

//
//	デストラクタ
//
Cube::~Cube()
{
}

//
//	レンダリングする
//
void Cube::render(const Vector3D& position)
{
	// 現在の行列を保存
	glPushMatrix();

	// 平行移動
	glTranslated(position.getX(), position.getY(), position.getZ());

	// 回転
	glRotated(m_rotation_y, 0.0, 1.0, 0.0);
	glRotated(m_rotation_x, 1.0, 0.0, 0.0);

	// 一辺の長さの半分を計算
	double half_len = m_edge_length / 2.0;

	// 頂点指定を開始
	glBegin(GL_QUADS);

	glNormal3d(1.0, 0.0, 0.0);
	glVertex3d(half_len,  half_len,  half_len);
	glVertex3d(half_len, -half_len,  half_len);
	glVertex3d(half_len, -half_len, -half_len);
	glVertex3d(half_len,  half_len, -half_len);

	glNormal3d(-1.0, 0.0, 0.0);
	glVertex3d(-half_len,  half_len,  half_len);
	glVertex3d(-half_len,  half_len, -half_len);
	glVertex3d(-half_len, -half_len, -half_len);
	glVertex3d(-half_len, -half_len,  half_len);

	glNormal3d(0.0, 1.0, 0.0);
	glVertex3d( half_len, half_len,  half_len);
	glVertex3d( half_len, half_len, -half_len);
	glVertex3d(-half_len, half_len, -half_len);
	glVertex3d(-half_len, half_len,  half_len);

	glNormal3d(0.0, -1.0, 0.0);
	glVertex3d( half_len, -half_len,  half_len);
	glVertex3d(-half_len, -half_len,  half_len);
	glVertex3d(-half_len, -half_len, -half_len);
	glVertex3d( half_len, -half_len, -half_len);

	glNormal3d(0.0, 0.0, 1.0);
	glVertex3d( half_len,  half_len, half_len);
	glVertex3d(-half_len,  half_len, half_len);
	glVertex3d(-half_len, -half_len, half_len);
	glVertex3d( half_len, -half_len, half_len);

	glNormal3d(0.0, 0.0, -1.0);
	glVertex3d( half_len,  half_len, -half_len);
	glVertex3d( half_len, -half_len, -half_len);
	glVertex3d(-half_len, -half_len, -half_len);
	glVertex3d(-half_len,  half_len, -half_len);

	// 頂点指定を終了
	glEnd();

	// 行列を元に戻す
	glPopMatrix();
}

