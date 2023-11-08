
#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Scene_Base.h"


class SaveLoad;
class UIOperation;

//-------------------------------------------------------------------------------------------------//
//Scene�̎q�N���X
// 
// �^�C�g����ʂ̃N���X
//-------------------------------------------------------------------------------------------------//
class SceneTitle final: public SceneBase {
public:
	SceneTitle();
	~SceneTitle()override;
	void Update(float delta_time)override;//�^�C�g���V�[���̍X�V�֐�
	void Draw()override;//�^�C�g���V�[���̕`��֐�

private:
	tnl::Sequence<SceneTitle> sequence_ = tnl::Sequence<SceneTitle>(this, &SceneTitle::seqIdle);//�V�[���J�ڂ̃e���v���[�g
	bool seqIdle(float delta_time);

	std::shared_ptr<SaveLoad>load = nullptr;
	std::shared_ptr<UIOperation>op = nullptr;
	//SaveLoad* load = nullptr;									//�Z�[�u�N���X�̃|�C���^
	//UIOperation* op = nullptr;									//UI�̗V�ѕ��p�̃N���X�|�C���^
	
	int title_gpc_hdl = 0;										//�^�C�g���̔w�i�̃O���t�B�b�N�n���h��
	int title_movie_hdl;										//����ǂݍ��݂̕`��n���h��
	int title_screen_hdl;										//����Đ��p�̉摜�n���h��
	int title_bgm_sound_hdl;									//�^�C�g��BGM�̃T�E���h�n���h��
	int title_effect_sound_hdl;									//�^�C�g���̑I�����̃T�E���h�n���h��
	int title_select_sound_hdl;									//�^�C�g���̌��艹�̃T�E���h�n���h��
	
	const tnl::Vector3 START_BUTTON_POS = {DXE_WINDOW_WIDTH>>1,500,0};	//�^�C�g���̕����̊�ʒu
	const float TITLE_FONT_SIZE = 40;									//�^�C�g���̕����̃T�C�Y
	const static int BUTTON_NUM = 3;									//�^�C�g���̕����̔z��
	const std::string start_button[BUTTON_NUM] = { "START","�Z�[�u����n�߂�","�V�ѕ�" };//�^�C�g���̑I������
	const std::string chose_box = {"[�Q�Q�Q�Q�Q�Q�Q�Q]"};								//�I�����Ă�����̂���������
	int chose_start_button_ = 0;															//�^�C�g���{�^���̑I����\���ϐ�
	
};

