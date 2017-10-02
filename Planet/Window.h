//
//	Window�N���X�̒�`
//

#pragma once

//
//	�E�B���h�E
//
class Window
{
public:

	// �R���X�g���N�^
	Window(Window *parent, LPCTSTR window_class_name, DWORD style, DWORD ex_style);
	// �f�X�g���N�^
	virtual ~Window();

	// �쐬����
	virtual bool create(int x, int y, int width, int height);
	// �폜����
	virtual void destroy();

	// �E�B���h�E�n���h�����擾����
	virtual HWND getHandle();

	// �\������
	virtual void show();
	// �X�V����
	virtual void update();
	// ��`���擾����
	virtual void getRect(RECT *rc);
	// �N���C�A���g�̈�̃T�C�Y���擾����
	virtual void getClientAreaSize(int *width, int *height);
	// ���T�C�Y����
	virtual void resize(int x, int y, int width, int height);
	// �t�H�[�J�X��ݒ肷��
	virtual void setFocus();

	// �^�C�g����ݒ肷��
	virtual void setTitle(LPCTSTR title);
	// �A�C�R����ݒ肷��
	virtual bool setIcon(int icon_res_id);

	// �N���C�A���g�̈�̕\�����e�𖳌�������
	virtual void invalidateClientArea();
	// �N���C�A���g�̈�̕\�����e��L��������
	virtual void validateClientArea();

protected:

	// �f�o�C�X�R���e�L�X�g���擾����
	virtual HDC getDeviceContext();
	// �f�o�C�X�R���e�L�X�g���������
	virtual void releaseDeviceContext(HDC device_context);

private:

	HWND m_handle;					// �E�B���h�E�n���h��
	Window *m_parent;				// �e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E
	LPTSTR m_window_class_name;		// �E�B���h�E�N���X��
	DWORD m_style;					// �E�B���h�E�X�^�C��
	DWORD m_ex_style;				// �E�B���h�E�g���X�^�C��

	Window(const Window&);
	Window& operator=(const Window&);
};

