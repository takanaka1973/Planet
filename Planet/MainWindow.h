//
//	MainWindow�N���X�̒�`
//

#pragma once

#include "CustomWindow.h"

class Application;
class Universe;
class View;

//
//	���C���E�B���h�E
//
class MainWindow : public CustomWindow
{
public:

	// �R���X�g���N�^
	MainWindow(Application *app, Universe *universe);
	// �f�X�g���N�^
	virtual ~MainWindow();

	// �쐬���� <override>
	virtual bool create(int x, int y, int width, int height);
	// �폜���� <override>
	virtual void destroy();

	// �T�C�Y���œK������
	virtual void optimizeSize();

protected:

	// ���b�Z�[�W�n���h�� <override>
	virtual void onPaintWithDC(HDC device_context);	// WM_PAINT(�f�o�C�X�R���e�L�X�g�t��)

private:

	Application *m_app;		// �A�v���P�[�V����
	View *m_main_view;		// ���C���r���[
	View *m_sub_view;		// �T�u�r���[

	MainWindow(const MainWindow&);
	MainWindow& operator=(const MainWindow&);
};

