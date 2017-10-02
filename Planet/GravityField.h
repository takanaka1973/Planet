//
//	GravityField�N���X�̒�`
//

#pragma once

#include "GravityType.h"

class Star;
class Vector3D;

//
//	�d�͏�
//
class GravityField
{
public:

	// �R���X�g���N�^
	GravityField(GravityType type, Star *source);
	// �f�X�g���N�^
	virtual ~GravityField();

	// �d�͂��擾����
	virtual Vector3D getGravity(Star *target, const Vector3D& target_pos);

private:

	GravityType m_type;		// �d�͂̃^�C�v
	Star *m_source;			// �d�͌�

	GravityField(const GravityField&);
	GravityField& operator=(const GravityField&);
};

