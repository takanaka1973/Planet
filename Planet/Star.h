//
//	Starクラスの定義
//

#pragma once

#include "GravityFieldList.h"

class Surface;
class Shape;
class LightSource;
class Vector3D;

//
//	星
//
class Star
{
public:

	// コンストラクタ
	Star(double mass, Surface *surface, Shape *shape, LightSource *light_source);
	// デストラクタ
	virtual ~Star();

	// 質量を取得する
	virtual double getMass();
	// 位置を取得する
	virtual Vector3D getPosition() = 0;
	// 重力場を取得する
	virtual GravityField *getGravityField() = 0;

	// 光を放射する
	virtual void emitLight();
	// レンダリングする
	virtual void render();

	// 時間の経過を通知する
	virtual void tick(int timespan, const GravityFieldList& gravity_fields) = 0;

private:

	double m_mass;					// 質量
	Surface *m_surface;				// 表面
	Shape *m_shape;					// 形
	LightSource *m_light_source;	// 光源

	Star(const Star&);
	Star& operator=(const Star&);
};

