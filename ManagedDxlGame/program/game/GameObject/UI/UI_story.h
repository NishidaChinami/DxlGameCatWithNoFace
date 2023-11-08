#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"UI.h"

class Story;
class SaveLoad;
class Player;
class Camera;
class ScenePlay;

//-------------------------------------------------------------------------------------------------//
//UI�̎q�N���X
// 
// �v���C��ʂ̃X�g�[���[UI�̕\���A���͂̃N���X
//-------------------------------------------------------------------------------------------------//
class UIStory final:public UI
{
public:
	UIStory(int chapter);
	~UIStory()override;

	void Draw()override;									//UI�̕`��֐�
	void Input(std::shared_ptr<SaveLoad>save, std::shared_ptr<Player>player, 
		const std::shared_ptr<Camera>camera, std::shared_ptr<ScenePlay>stage)override {};//UI�̓��͂����m����֐�
private:
	
	int chapter_ = 0;		//�X�g�[���[�̃G�s�\�[�h�ϐ�
	
	std::vector<std::vector<tnl::CsvCell>> story_csv;		//�X�g�[���[�i�[CSV
	std::vector<std::vector<tnl::CsvCell>> story_gpc_csv;	//�`�悳���v���C���[��Mob�L�����̏��CVS
	std::list<std::shared_ptr<Story>> story_one;							//�X�g�[���[���i�[�����N���X�|�C���^
	std::list<std::shared_ptr<Story>>::iterator str;						//�X�g�[���[�̃C�e���[�^�[	

	
	const tnl::Vector3 MOB_POS = { 320,180,0 };		//�X�g�[���[�̃��u�ʒu
	const tnl::Vector3 PLAYER_POS = {960,540,0};	//�X�g�[���[�̃v���C���[�ʒu
	const tnl::Vector3 BACKGROUND_POS = { 640,360,0 };//�X�g�[���[�̔w�i�ʒu
	const tnl::Vector3 INSTRUCTION_POS = { 250,620,0 };//�{�^���w���̍��W

	
	int story_gpc_hdl = 0;						//��b��ʂ̔w�i�n���h��
	int right_chara_gpc_hdl = 0;				//�X�g�[���[�̃v���C���[�摜�n���h��
	int left_chara_gpc_hdl = 0;					//�X�g�[���[��MOB�摜�n���h��
	int select_sound_hdl;						//��b��i�߂�T�E���h
	
	const int STORY_FONT_SIZE = 30;				//�����T�C�Y
	const float FLASHINTIME = 30.0f;			// �����̓_�Ŏ���
	float flashing_time_cont_ = 0;				// �_�Ŏ��Ԃ̃J�E���g�ϐ�
	bool flash_draw_ = true;						// �`��t���O

};