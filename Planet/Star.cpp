//
//	Starクラスの実装
//

#include "common.h"
#include "Star.h"
#include "Surface.h"
#include "Shape.h"
#include "LightSource.h"
#include "Vector3D.h"

//
//	コンストラクタ
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
	// light_sourceはNULL可
}

//
//	デストラクタ
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
//	質量を取得する
//
double Star::getMass()
{
	return m_mass;
}

//
//	光を放射する
//
void Star::emitLight()
{
	if (m_light_source != NULL) {
		// 光源に指示
		m_light_source->emitLight(getPosition());
	}
}

//
//	レンダリングする
//
void Star::render()
{
	// 表面に指示
	m_surface->activate();
	// 形に指示
	m_shape->render(getPosition());
}

