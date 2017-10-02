//
//	Star�N���X�̎���
//

#include "common.h"
#include "Star.h"
#include "Surface.h"
#include "Shape.h"
#include "LightSource.h"
#include "Vector3D.h"

//
//	�R���X�g���N�^
//
Star::Star(double mass, Surface *surface, Shape *shape, LightSource *light_source)
: m_mass(mass),
  m_surface(surface),
  m_shape(shape),
  m_light_source(light_source)
{
	assert(mass > 0.0);
	assert(surface != NULL);
	assert(shape != NULL);
	// light_source��NULL��
}

//
//	�f�X�g���N�^
//
Star::~Star()
{
	delete m_surface;
	delete m_shape;
	if (m_light_source != NULL) {
		delete m_light_source;
	}
}

//
//	���ʂ��擾����
//
double Star::getMass()
{
	return m_mass;
}

//
//	������˂���
//
void Star::emitLight()
{
	if (m_light_source != NULL) {
		// �����Ɏw��
		m_light_source->emitLight(getPosition());
	}
}

//
//	�����_�����O����
//
void Star::render()
{
	// �\�ʂɎw��
	m_surface->activate();
	// �`�Ɏw��
	m_shape->render(getPosition());
}

