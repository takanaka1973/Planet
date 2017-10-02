//
//	WndMsgDispatcher�N���X�̎���
//

#include "common.h"
#include "WndMsgDispatcher.h"
#include "CustomWindow.h"

// �B��̃C���X�^���X
WndMsgDispatcher WndMsgDispatcher::s_instance;

//
//	�C���X�^���X���擾����
//
WndMsgDispatcher *WndMsgDispatcher::getInstance()
{
	return &s_instance;
}

//
//	�R���X�g���N�^
//
WndMsgDispatcher::WndMsgDispatcher()
{
}

//
//	�f�X�g���N�^
//
WndMsgDispatcher::~WndMsgDispatcher()
{
	// �E�B���h�E�͑S�ēo�^��������Ă���͂�
	assert(m_registered_windows.empty());
}

//
//	�E�B���h�E��o�^����
//
void WndMsgDispatcher::registerWindow(CustomWindow *window)
{
	assert(window != NULL);

	m_registered_windows.insert(window);
}

//
//	�E�B���h�E��o�^��������
//
void WndMsgDispatcher::unregisterWindow(CustomWindow *window)
{
	assert(window != NULL);

	m_registered_windows.erase(window);
}

//
//	�E�B���h�E�v���V�[�W�����擾����
//
WNDPROC WndMsgDispatcher::getWindowProc()
{
	return baseWindowProc;
}

//
//	�x�[�X�E�B���h�E�v���V�[�W��
//
LRESULT CALLBACK WndMsgDispatcher::baseWindowProc(
	HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	// �C���X�^���X���\�b�h�ɈϏ�����
	return s_instance.windowProc(handle, message, wParam, lParam);
}

//
//	�E�B���h�E�v���V�[�W��
//
LRESULT WndMsgDispatcher::windowProc(
	HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	// �Ώۂ̃E�B���h�E��T��
	CustomWindow *window = findWindow(handle);

	if (window != NULL) {
		// ���������ꍇ�͌Ăяo��
		ret = window->handleWndMsg(message, wParam, lParam);
	} else {
		// ������Ȃ������ꍇ�̓f�t�H���g����
		ret = DefWindowProc(handle, message, wParam, lParam);
	}

	return ret;
}

//
//	�E�B���h�E��T��
//
CustomWindow *WndMsgDispatcher::findWindow(HWND handle)
{
	CustomWindow *dst_window = NULL;

	if (handle != NULL) {
		// �o�^����Ă���E�B���h�E�Q����E�B���h�E�n���h�������v������̂�T��
		CustomWindowContainer::iterator it = m_registered_windows.begin();
		for (; it != m_registered_windows.end(); ++it) {
			CustomWindow *window = *it;
			if (window->getHandle() == handle) {
				// ��������
				dst_window = window;
				break;
			}
		}
	}

	return dst_window;
}

