//
//	WndMsgDispatcher�N���X�̒�`
//

#pragma once

#pragma warning(disable:4786)

#include <set>

class CustomWindow;

//
//	�E�B���h�E���b�Z�[�W�f�B�X�p�b�`��
//
class WndMsgDispatcher
{
public:

	// �f�X�g���N�^
	virtual ~WndMsgDispatcher();

	// �E�B���h�E�v���V�[�W�����擾����
	virtual WNDPROC getWindowProc();

	// �E�B���h�E��o�^����
	virtual void registerWindow(CustomWindow *window);
	// �E�B���h�E��o�^��������
	virtual void unregisterWindow(CustomWindow *window);

	// �C���X�^���X���擾����
	static WndMsgDispatcher *getInstance();

private:

	// �R���X�g���N�^
	WndMsgDispatcher();

	// �E�B���h�E�v���V�[�W��
	LRESULT windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	// �E�B���h�E��T��
	CustomWindow *findWindow(HWND handle);

	// �o�^����Ă���E�B���h�E�Q
	typedef std::set<CustomWindow*> CustomWindowContainer;
	CustomWindowContainer m_registered_windows;

	// �B��̃C���X�^���X
	static WndMsgDispatcher s_instance;

	// �x�[�X�E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK baseWindowProc(
		HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	WndMsgDispatcher(const WndMsgDispatcher&);
	WndMsgDispatcher& operator=(const WndMsgDispatcher&);
};

