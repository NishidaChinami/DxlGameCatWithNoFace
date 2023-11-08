#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"UI.h"

class SaveLoad;
class Player;
class Camera;
class ScenePlay;

//-------------------------------------------------------------------------------------------------//
//UI�̎q�N���X
// 
// �v���C��ʂ̐ݒ�UI�`��A���̓N���X
//-------------------------------------------------------------------------------------------------//
class UISetting final: public UI
{
public:
	UISetting();
	~UISetting()override;
	void Draw()override;//�ݒ��ʂ̕`��֐�

	//�ݒ��ʂ̓��͊֐�
	// arg1...Save�֐��Ăяo��
	// arg2...�g�p�Ȃ�
	// arg3...�g�p�Ȃ�
	// arg4...�^�C�g���ɖ߂�t���O
	void Input(std::shared_ptr<SaveLoad>save, std::shared_ptr<Player>player, const std::shared_ptr<Camera>camera, std::shared_ptr<ScenePlay>stage)override;
private:
	//�ݒ�Ɏg���摜

	int setting_bg_hdl = 0;			//�w�i�摜�̃n���h��
	int bar_gpc_hdl = 0;			//�o�[�̉摜�n���h��
	int progress_gpc_hdl = 0;		//�����s���̉摜�n���h��
	int option_gpc_hdl = 0;			//�J�[�\���̉摜�n���h��
	
	int volume_progress_ = 255;		//���ʂ̏����l
	int brightness_progress_ = 255;	//���邳�̏����l
	int volume_unit = 20;			//���ʂ̈ꃁ�����̒P��
	int brightness_unit_ = 20;		//���邳�̈ꃁ�����̒P��
	
	const std::string setting_item[4] = { "����","��ʂ̖��邳","�Z�[�u���ăQ�[�����I���","ESC�ŃQ�[���ɂ��ǂ�"};//�I������
	const tnl::Vector3 OPTION_POS = {300,180,0};								//�I�����Ă�����̂��������摜�̏����ʒu
	const tnl::Vector3 BAR_POS = { 800,180,0 };									//�o�[�̉摜�̈ʒu
	const tnl::Vector3 PROGRESS_POS = { 680,180,0 };							//�v���O���X�̉摜�̈ʒu
	const tnl::Vector3 ITEM_POS = {320,180,0};									//�ݒ�̑I�����ڂ̊�ʒu
	const int SETTING_FONT_SIZE = 30;											//�ݒ�̕����̃T�C�Y
	int chose_item_button_ = 0;													//�ݒ荀�ڂ�I������ϐ�
	int select_sound_hdl;														//�I������Ƃ��̃T�E���h�n���h��

};

