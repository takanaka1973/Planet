//
//	CustomWindow�N���X�̒�`
//

#pragma once

#include "Window.h"

class WndMsgDispatcher;

//
//	�J�X�^���E�B���h�E
//
class CustomWindow : public Window
{
public:

	// �R���X�g���N�^
	CustomWindow(Window *parent, DWORD style, DWORD ex_style);
	// �f�X�g���N�^
	virtual ~CustomWindow();

	// �쐬���� <override>
	virtual bool create(int x, int y, int width, int height);
	// �폜���� <override>
	virtual void destroy();

	// �E�B���h�E���b�Z�[�W����������
	virtual LRESULT handleWndMsg(UINT message, WPARAM wParam, LPARAM lParam);

protected:

	// ���b�Z�[�W�n���h��
	virtual void onLButtonDown();					// WM_LBUTTONDOWN
	virtual void onKeyDown(UINT_PTR key_code);		// WM_KEYDOWN
	virtual void onSize();							// WM_SIZE
	virtual void onClose();							// WM_CLOSE
	virtual void onPaint();							// WM_PAINT
	virtual void onPaintWithDC(HDC device_context);	// WM_PAINT(�f�o�C�X�R���e�L�X�g�t��)

private:

	// �E�B���h�E�N���X��o�^����
	bool registerWindowClass();

	WndMsgDispatcher *m_dispatcher;		// �E�B���h�E���b�Z�[�W�f�B�X�p�b�`��

	static const LPCTSTR WINDOW_CLASS_NAME;	// �E�B���h�E�N���X��
	static bool s_window_class_registered;	// �E�B���h�E�N���X���o�^�ς݂��ǂ���

	CustomWindow(const CustomWindow&);
	CustomWindow& operator=(const CustomWindow&);
};

