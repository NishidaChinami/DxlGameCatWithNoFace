#pragma once
#include "../library/tnl_sequence.h"

class SceneBase;
//-------------------------------------------------------------------------------------------------//
//�}�l�[�W���[�N���X

//-------------------------------------------------------------------------------------------------//
class GameManager {
public:
	static GameManager* GetInstance(std::shared_ptr<SceneBase>start_scene = nullptr);//�}�l�[�W���[�̃C���X�^���X�擾
	static void Destroy();//�f�X�g���N�^�֐�
	void ChangeScene(std::shared_ptr<SceneBase>next_scene, float trans_time = 0.5f);//�V�[���؂�ւ��p�̊֐�
	void Update(float delta_time);//�}�l�[�W���[�̍X�V�֐�

private:
	GameManager(std::shared_ptr<SceneBase>start_scene);
	//�V�[���؂�ւ��p�̃|�C���^�ϐ�
	std::shared_ptr<SceneBase>now_scene_ = nullptr;
	std::shared_ptr<SceneBase>next_scene_ = nullptr;

	int tansition_graph_hdl = 0;//�t�F�[�h�A�E�g�p�̍��摜�̃n���h��
	float trans_time_ = 0.5f;//�t�F�[�h�̑��x�ϐ�

	tnl::Sequence<GameManager> sequence_ = tnl::Sequence<GameManager>(this, &GameManager::seqTransIn);//�t�F�[�h�C���t�F�[�h�A�E�g�p
	bool seqTransIn(const float delta_time);//�t�F�[�h�C��
	bool seqTransOut(const float delta_time);//�t�F�[�h�A�E�g
	bool seqRunScene(const float delta_time);//�ҋ@���

};