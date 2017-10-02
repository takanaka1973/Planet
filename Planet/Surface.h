//
//	Surfaceクラスの定義
//

#pragma once

#include "Color.h"

//
//	表面
//
class Surface
{
public:

	// コンストラクタ
	Surface();
	// デストラクタ
	virtual ~Surface();

	// 環境光反射の色を設定する
	virtual void setAmbientColor(const Color& color);
	// 拡散光反射の色を設定する
	virtual void setDiffuseColor(const Color& color);
	// 鏡面光反射の色を設定する
	virtual void setSpecularColor(const Color& color);
	// 鏡面光反射の指数を設定する
	virtual void setShininess(double shininess);
	// 放射光の色を設定する
	virtual void setEmissionColor(const Color& color);

	// アクティブにする
	virtual void activate();

private:

	Color m_ambient_color;	// 環境光反射の色
	Color m_diffuse_color;	// 拡散光反射の色
	Color m_specular_color;	// 鏡面光反射の色
	double m_shininess;		// 鏡面光反射の指数(0～128)
	Color m_emission_color;	// 放射光の色

	Surface(const Surface&);
	Surface& operator=(const Surface&);
};

