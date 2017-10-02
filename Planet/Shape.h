//
//	Shapeクラスの定義
//

#pragma once

class Vector3D;

//
//	形
//
class Shape
{
public:

	// コンストラクタ
	Shape();
	// デストラクタ
	virtual ~Shape();

	// レンダリングする
	virtual void render(const Vector3D& position) = 0;

private:

	Shape(const Shape&);
	Shape& operator=(const Shape&);
};

