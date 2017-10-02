//
//	Vector3Dクラスの定義
//

#pragma once

//
//	三次元ベクトル
//
class Vector3D
{
public:

	// デフォルトコンストラクタ
	Vector3D();
	// コンストラクタ
	Vector3D(double x, double y, double z);
	// コピーコンストラクタ
	Vector3D(const Vector3D& src);

	// デストラクタ
	virtual ~Vector3D();

	// 代入演算子
	Vector3D& operator=(const Vector3D& src);

	// x成分を取得する
	virtual double getX() const;
	// y成分を取得する
	virtual double getY() const;
	// z成分を取得する
	virtual double getZ() const;

	// 絶対値を取得する
	virtual double getAbs() const;

	// x成分を設定する
	virtual void setX(double value);
	// y成分を設定する
	virtual void setY(double value);
	// z成分を設定する
	virtual void setZ(double value);

	// operator+=
	Vector3D& operator+=(const Vector3D& src);

private:

	double m_x;		// x成分
	double m_y;		// y成分
	double m_z;		// z成分

};

// operator+
Vector3D operator+(const Vector3D& left, const Vector3D& right);
// operator-
Vector3D operator-(const Vector3D& left, const Vector3D& right);
// operator*
Vector3D operator*(double s, const Vector3D& v);

