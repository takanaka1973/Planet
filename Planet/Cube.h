//
//	Cubeクラスの定義
//

#pragma once

#include "Shape.h"

//
//	立方体
//
class Cube : public Shape
{
public:

	// コンストラクタ
	Cube(double edge_length, double rotation_x, double rotation_y);
	// デストラクタ
	virtual ~Cube();

	// レンダリングする <override>
	virtual void render(const Vector3D& position);

private:

	double m_edge_length;	// 一辺の長さ
	double m_rotation_x;	// x軸の周りの回転角
	double m_rotation_y;	// y軸の周りの回転角

	Cube(const Cube&);
	Cube& operator=(const Cube&);
};

