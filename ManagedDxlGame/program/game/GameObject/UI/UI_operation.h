#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"UI.h"

//-------------------------------------------------------------------------------------------------//
//UI�̎q�N���X
// 
// �X�^�[�g��ʂ̗V�ѕ��̕`��
//-------------------------------------------------------------------------------------------------//
class UIOperation final:public UI 
{
public:
	UIOperation();
	~UIOperation();
	void Draw();//�V�ѕ������̕`��֐�
private:
	int operation_gpc_hdl = 0;//��������̃O���t�B�b�N�n���h��
};


