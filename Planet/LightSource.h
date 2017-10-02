//
//	LightSourceクラスの定義
//

#pragma once

#include "Color.h"

class Vector3D;

//
//	光源
//
class LightSource
{
public:

	// コンストラクタ
	explicit LightSource(int light_source_no);
	// デストラクタ
	virtual ~LightSource();

	// 光の減衰率を設定する
	virtual void setAttenuation(
		double constant, double linear, double quadratic);

	// 環境光の色を設定する
	virtual void setAmbientColor(const Color& color);
	// 拡散光の色を設定する
	virtual void setDiffuseColor(const Color& color);
	// 鏡面光の色を設定する
	virtual void setSpecularColor(const Color& color);

	// 光を放射する
	virtual void emitLight(const Vector3D& position);

private:

	int m_light_source_no;			// 光源番号

	double m_constant_attenuation;	// 光の減衰率(0次)
	double m_linear_attenuation;	// 光の減衰率(1次)
	double m_quadratic_attenuation;	// 光の減衰率(2次)

	Color m_ambient_color;			// 環境光の色
	Color m_diffuse_color;			// 拡散光の色
	Color m_specular_color;			// 鏡面光の色

	LightSource(const LightSource&);
	LightSource& operator=(const LightSource&);
};

