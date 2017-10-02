//
//	GravityFieldクラスの定義
//

#pragma once

#include "GravityType.h"

class Star;
class Vector3D;

//
//	重力場
//
class GravityField
{
public:

	// コンストラクタ
	GravityField(GravityType type, Star *source);
	// デストラクタ
	virtual ~GravityField();

	// 重力を取得する
	virtual Vector3D getGravity(Star *target, const Vector3D& target_pos);

private:

	GravityType m_type;		// 重力のタイプ
	Star *m_source;			// 重力源

	GravityField(const GravityField&);
	GravityField& operator=(const GravityField&);
};

