#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class Player;
class Camera;
class ScenePlay;

//-------------------------------------------------------------------------------------------------//
//�Z�[�u�����[�h�܂��͐V�����Q�[�����n�߂�̂��Ǘ�����N���X
//-------------------------------------------------------------------------------------------------//
class SaveLoad
{
public:
	SaveLoad();
	~SaveLoad() {};
	void Save(std::shared_ptr<Player>player,const std::shared_ptr<Camera>camera,std::shared_ptr<ScenePlay>stage);//�Z�[�u�����Ƃ��̊֐�
	void Load();//��������n�߂��Ƃ��̊֐�
	void NewGame();//�V�����Q�[�����n�߂��Ƃ��̊֐�

	tnl::Vector3 GetLoadPos()const { return player_save_pos_; }			//�Z�[�u�����v���C���[�ʒu�����[�h����֐�
	tnl::Vector3 GetLoadCameraPos() const { return camera_save_pos_; }	//�Z�[�u�����J�������W�����[�h����֐�
	int GetLoadStage() const { return save_stage_; }						//�Z�[�u�����X�e�[�W�����[�h����֐�
private:
	tnl::Vector3 player_save_pos_;										//�v���C���[���Ō�ɒʂ������ԃZ�[�u�̒n�_
	tnl::Vector3 camera_save_pos_ = {0,0,0};								//�v���C���[���Ō�ɒʂ������ԃZ�[�u�̃J�������W
	const tnl::Vector3 START_POS = { 15,200,0 };						//�v���C���[�̏����l
	int save_stage_;														//�X�e�[�W��ۑ�����ϐ�

};

