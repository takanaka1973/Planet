//
//	Renderer�N���X�̎���
//

#include "common.h"
#include "Renderer.h"
#include "Universe.h"
#include "RendererSetting.h"
#include "Camera.h"
#include "Vector3D.h"
#include "Color.h"

//
//	�R���X�g���N�^
//
Renderer::Renderer(Universe *universe, RendererSetting *setting)
: m_universe(universe),
  m_setting(setting),
  m_camera(new Camera()),
  m_initialized(false),
  m_rendering_context(NULL),
  m_device_context(NULL),
  m_viewport_x(0),
  m_viewport_y(0),
  m_viewport_width(0),
  m_viewport_height(0)
{
	assert(universe != NULL);
	assert(setting != NULL);
}

//
//	�f�X�g���N�^
//
Renderer::~Renderer()
{
	term();

	delete m_setting;
	delete m_camera;
}

//
//	����������
//
bool Renderer::init(HDC device_context)
{
	assert(device_context != NULL);

	if (m_initialized) {
		return false;	// ���łɏ������ς�
	}

	// �����_�����O�R���e�L�X�g���쐬����
	HGLRC rendering_context = wglCreateContext(device_context);
	if (rendering_context == NULL) {
		return false;
	}

	// �J�����g�ɂ���
	if (!wglMakeCurrent(device_context, rendering_context)) {
		verify(wglDeleteContext(rendering_context));
		return false;
	}

	// ��x�����s���΂悢�ݒ�
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	// �J�����g����O��
	verify(wglMakeCurrent(NULL, NULL));

	// �J�����̏����ݒ�
	m_camera->setPosition(m_setting->getCameraInitialPosition());
	m_camera->setRefPoint(m_setting->getCameraInitialRefPoint());
	m_camera->setUpDirection(m_setting->getCameraInitialUpDirection());

	// �r���[�|�[�g�̐ݒ�l��������
	m_viewport_x = 0;
	m_viewport_y = 0;
	m_viewport_width = 0;
	m_viewport_height = 0;

	// �����o�ϐ��̐ݒ�
	m_rendering_context = rendering_context;
	m_device_context = device_context;
	m_initialized = true;

	return true;
}

//
//	�I������
//
void Renderer::term()
{
	if (m_initialized) {
	// �������ς݂̏ꍇ�̂�

		// �����_�����O�R���e�L�X�g���폜����
		verify(wglDeleteContext(m_rendering_context));

		// �����o�ϐ��̃N���A
		m_rendering_context = NULL;
		m_device_context = NULL;
		m_initialized = false;

	}
}

//
//	�����_�����O����
//
void Renderer::render()
{
	assert(m_initialized);

	// �J�����g�ɂ���
	verify(wglMakeCurrent(m_device_context, m_rendering_context));

	// �o�b�t�@���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �r���[�|�[�g��ݒ肷��
	glViewport(m_viewport_x, m_viewport_y, m_viewport_width, m_viewport_height);

	// ���e�s���ݒ肷��
	setProjectionMatrix();

	// ���f���s����J�����g�̍s��ɂ���
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// �J�����ɏœ_���킹���w��
	m_camera->focus();

	// �F���Ƀ����_�����O���w��
	glEnable(GL_LIGHTING);
	m_universe->render();
	glDisable(GL_LIGHTING);

	// xy���ʂ�`�悷��
	drawXYPlane();

	// �����_�����O����
	glFinish();

	// ��ʂɕ\������
	verify(SwapBuffers(m_device_context));

	// �J�����g����O��
	verify(wglMakeCurrent(NULL, NULL));
}

//
//	�r���[�|�[�g��ݒ肷��
//
void Renderer::setViewport(int x, int y, int width, int height)
{
	assert(m_initialized);
	assert(width >= 0);
	assert(height >= 0);

	// �����ł͒l��ۑ����邾��
	m_viewport_x = x;
	m_viewport_y = y;
	m_viewport_width = width;
	m_viewport_height = height;
}

//
//	�J�������ړ�����
//
void Renderer::moveCamera(const Vector3D& delta)
{
	assert(m_initialized);

	m_camera->move(delta);
}

//
//	���e�s���ݒ肷��
//
void Renderer::setProjectionMatrix()
{
	assert(m_initialized);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double view_angle = 45.0;
	double aspect_ratio = 1.0;
	if (m_viewport_width > 0 && m_viewport_height > 0) {
		aspect_ratio = static_cast<double>(m_viewport_width) / m_viewport_height;
	}
	double near_plane = 1.0;
	double far_plane = 1000.0;

	gluPerspective(view_angle, aspect_ratio, near_plane, far_plane);
}

//
//	xy���ʂ�`�悷��
//
void Renderer::drawXYPlane()
{
	assert(m_initialized);

	static const Color color(0.7, 0.7, 0.7);

	float c[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	color.getRGBA(c);
	glColor4fv(c);

	glBegin(GL_LINES);

	static const int C = 30;
	static const int D = 5;

	// x������
	for (int y = - C; y <= C; y += D) {
		glVertex3d(- static_cast<double>(C), static_cast<double>(y), 0.0);
		glVertex3d(  static_cast<double>(C), static_cast<double>(y), 0.0);
	}

	// y������
	for (int x = - C; x <= C; x += D) {
		glVertex3d(static_cast<double>(x), - static_cast<double>(C), 0.0);
		glVertex3d(static_cast<double>(x),   static_cast<double>(C), 0.0);
	}

	glEnd();
}

