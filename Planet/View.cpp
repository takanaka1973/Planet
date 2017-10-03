//
//	View�N���X�̎���
//

#include "common.h"
#include "View.h"
#include "Universe.h"
#include "RendererSetting.h"
#include "Renderer.h"
#include "Vector3D.h"

// �E�B���h�E�X�^�C��
static const DWORD WINDOW_STYLE =
	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
// �E�B���h�E�g���X�^�C��
static const DWORD WINDOW_EX_STYLE = 0;

//
//	�R���X�g���N�^
//
View::View(Window *parent, Universe *universe, RendererSetting *setting)
: CustomWindow(parent, WINDOW_STYLE, WINDOW_EX_STYLE),
  m_universe(universe),
  m_device_context(NULL),
  m_renderer(new Renderer(universe, setting))
{
	assert(parent != NULL);		// �q�E�B���h�E��p
	assert(universe != NULL);
	assert(setting != NULL);
}

//
//	�f�X�g���N�^
//
View::~View()
{
	destroy();
	delete m_renderer;
}

//
//	�쐬����
//
bool View::create(int x, int y, int width, int height)
{
	if (getHandle() != NULL) {
		return false;	// ���łɍ쐬�ς�
	}

	bool completed = false;
	do {
		// �E�B���h�E���쐬����
		if (!CustomWindow::create(x, y, width, height)) {
			break;
		}

		// �f�o�C�X�R���e�L�X�g���擾����
		m_device_context = getDeviceContext();
		if (m_device_context == NULL) {
			break;
		}

		// �s�N�Z���t�H�[�}�b�g��ݒ肷��
		if (!setPixelFormat(m_device_context)) {
			break;
		}

		// �����_���[������������
		if (!m_renderer->init(m_device_context)) {
			break;
		}

		// �r���[�|�[�g��ݒ肷��
		setViewport();

		// �F���Ɋώ@�҂Ƃ��Ď�����o�^����
		m_universe->registerObserver(this);

		completed = true;
	} while (false);

	if (!completed) {
		// ���s�����̂Ō�n��
		m_renderer->term();
		if (m_device_context != NULL) {
			releaseDeviceContext(m_device_context);
			m_device_context = NULL;
		}
		CustomWindow::destroy();
		return false;
	}

	return true;
}

//
//	�폜����
//
void View::destroy()
{
	if (getHandle() != NULL) {
	// �쐬�ς݂̏ꍇ�̂�

		// �F�����玩����o�^��������
		m_universe->unregisterObserver(this);

		// �����_���[���I������
		m_renderer->term();

		// �f�o�C�X�R���e�L�X�g���������
		releaseDeviceContext(m_device_context);
		m_device_context = NULL;

		// �E�B���h�E���폜����
		CustomWindow::destroy();

	}
}

//
//	�V�[�����ω��������Ƃ�ʒm����
//
void View::notifySceneChanged(Universe *sender)
{
	assert(sender == m_universe);
	assert(getHandle() != NULL);

	// �ĕ`��v��
	invalidateClientArea();
}

//
//	�s�N�Z���t�H�[�}�b�g��ݒ肷��
//
bool View::setPixelFormat(HDC device_context)
{
	assert(device_context != NULL);

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize			= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion		= 1;
	pfd.dwFlags			= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType		= PFD_TYPE_RGBA;
	pfd.cColorBits		= 24;
	pfd.cAlphaBits		= 0;
	pfd.cAccumBits		= 0;
	pfd.cDepthBits		= 32;
	pfd.cStencilBits	= 0;
	pfd.cAuxBuffers		= 0;
	pfd.iLayerType		= PFD_MAIN_PLANE;

	int pfindex = ChoosePixelFormat(device_context, &pfd);
	if (pfindex == 0) {
		return false;
	}

	if (!SetPixelFormat(device_context, pfindex, &pfd)) {
		return false;
	}

	return true;
}

//
//	�r���[�|�[�g��ݒ肷��
//
void View::setViewport()
{
	assert(getHandle() != NULL);

	int width = 0;
	int height = 0;
	getClientAreaSize(&width, &height);

	m_renderer->setViewport(0, 0, width, height);
}

//
//	WM_LBUTTONDOWN�̃��b�Z�[�W�n���h��
//
void View::onLButtonDown()
{
	assert(getHandle() != NULL);

//	// �����Ƀt�H�[�J�X��ݒ肷��
//	setFocus();
}

//
//	WM_KEYDOWN�̃��b�Z�[�W�n���h��
//
void View::onKeyDown(UINT_PTR key_code)
{
	assert(getHandle() != NULL);

	static const double distance = 1.0;
	Vector3D delta;
	bool move = true;

	// �J�����̕ψʂ����肷��
	switch (key_code) {
	case VK_UP:
		delta.setY(distance);
		break;
	case VK_DOWN:
		delta.setY(-distance);
		break;
	case VK_LEFT:
		delta.setX(-distance);
		break;
	case VK_RIGHT:
		delta.setX(distance);
		break;
	default:
		move = false;
	}

	if (move) {
		// �J�����𓮂���
		m_renderer->moveCamera(delta);

		// �ĕ`��v��
		invalidateClientArea();
	}
}

//
//	WM_SIZE�̃��b�Z�[�W�n���h��
//
void View::onSize()
{
	assert(getHandle() != NULL);

	// �r���[�|�[�g��ݒ肷��
	setViewport();

	// �ĕ`��v��
	invalidateClientArea();
}

//
//	WM_PAINT�̃��b�Z�[�W�n���h��
//
void View::onPaint()
{
	assert(getHandle() != NULL);

	// �����_�����O����
	m_renderer->render();

	// �\�����e��L����
	validateClientArea();
}

