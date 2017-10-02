//
//	Colorクラスの定義
//

#pragma once

//
//	色
//
class Color
{
public:

	// デフォルトコンストラクタ
	Color();
	// コンストラクタ(RGB)
	Color(double red, double green, double blue);
	// コンストラクタ(RGBA)
	Color(double red, double green, double blue, double alpha);
	// コピーコンストラクタ
	Color(const Color& src);
	// デストラクタ
	virtual ~Color();

	// 代入演算子
	Color& operator=(const Color& src);

	// RGBAを取得する
	virtual void getRGBA(float *array) const;

	// 赤色成分を取得する
	virtual double getRed() const;
	// 緑色成分を取得する
	virtual double getGreen() const;
	// 青色成分を取得する
	virtual double getBlue() const;
	// アルファ成分を取得する
	virtual double getAlpha() const;

private:

	double m_red;		// 赤色成分
	double m_green;		// 緑色成分
	double m_blue;		// 青色成分
	double m_alpha;		// アルファ成分

};

