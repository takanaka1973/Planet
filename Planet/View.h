//
//	View�N���X�̒�`
//

#pragma once

#include "CustomWindow.h"
#include "UniverseObserver.h"

class Universe;
class RendererSetting;
class Renderer;

//
//	�r���[
//
class View : public CustomWindow, public UniverseObserver
{
public:

	// �R���X�g���N�^
	View(Window *parent, Universe *universe, RendererSetting *setting);
	// �f�X�g���N�^
	virtual ~View();

	// �쐬���� <override>
	virtual bool create(int x, int y, int width, int height);
	// �폜���� <override>
	virtual void destroy();

	// �V�[�����ω��������Ƃ�ʒm���� <override>
	virtual void notifySceneChanged(Universe *sender);

protected:

	// ���b�Z�[�W�n���h�� <override>
	virtual void onLButtonDown();			// WM_LBUTTONDOWN
	virtual void onKeyDown(UINT key_code);	// WM_KEYDOWN
	virtual void onSize();					// WM_SIZE
	virtual void onPaint();					// WM_PAINT

private:

	// �s�N�Z���t�H�[�}�b�g��ݒ肷��
	bool setPixelFormat(HDC device_context);
	// �r���[�|�[�g��ݒ肷��
	void setViewport();

	Universe *m_universe;	// �F��
	HDC m_device_context;	// �f�o�C�X�R���e�L�X�g
	Renderer *m_renderer;	// �����_���[

	View(const View&);
	View& operator=(const View&);
};

