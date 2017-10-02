//
//	Renderer�N���X�̒�`
//

#pragma once

class Universe;
class RendererSetting;
class Camera;
class Vector3D;

//
//	�����_���[
//
class Renderer
{
public:

	// �R���X�g���N�^
	Renderer(Universe *universe, RendererSetting *setting);
	// �f�X�g���N�^
	virtual ~Renderer();

	// ����������
	virtual bool init(HDC device_context);
	// �I������
	virtual void term();

	// �����_�����O����
	virtual void render();

	// �r���[�|�[�g��ݒ肷��
	virtual void setViewport(int x, int y, int width, int height);
	// �J�������ړ�����
	virtual void moveCamera(const Vector3D& delta);

private:

	// ���e�s���ݒ肷��
	void setProjectionMatrix();
	// xy���ʂ�`�悷��
	void drawXYPlane();

	Universe *m_universe;		// �F��
	RendererSetting *m_setting;	// �ݒ�
	Camera *m_camera;			// �J����

	bool m_initialized;			// �������ς݂��ǂ���
	HGLRC m_rendering_context;	// �����_�����O�R���e�L�X�g
	HDC m_device_context;		// �f�o�C�X�R���e�L�X�g

	// �r���[�|�[�g�ݒ�
	int m_viewport_x;
	int m_viewport_y;
	int m_viewport_width;
	int m_viewport_height;

	Renderer(const Renderer&);
	Renderer& operator=(const Renderer&);
};

