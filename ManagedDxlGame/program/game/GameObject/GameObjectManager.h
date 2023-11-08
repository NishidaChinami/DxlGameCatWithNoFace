#pragma once
class Camera;
class Player;
class Enemy;
class Gimmick;
class Stage;


//-------------------------------------------------------------------------------------------------//
//GameObject�̃|�����t�B�Y���p���ۃN���X
//-------------------------------------------------------------------------------------------------//
class GameObjectManager {
public:
	GameObjectManager(){}
	GameObjectManager(int type) { actorType_ = type; }
	virtual~GameObjectManager() {};
	virtual void Update(float delta_time, const std::shared_ptr<Player>player) {};//�I�u�W�F�N�g�̍X�V
	virtual void Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player) {};//�I�u�W�F�N�g�̕`��֐�

	//�����蔻������֐�
	
	
	// arg1...�X�e�[�W���W��ǂݎ��
	// arg2...�v���C���[�̍��W�A�T�C�Y�̓ǂݎ��
	// arg3...�}�b�v�`�b�v�̍��W�A�T�C�Y�̓ǂݎ��
	// arg4...�G�l�~�[�̍��W�A�T�C�Y�̓ǂݎ��
	// arg5...�J�������W�̓ǂݎ��
	virtual void Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player,
		const std::list<std::shared_ptr<Gimmick>>&gimmick, const std::list<std::shared_ptr<Enemy>>&enemy,std::shared_ptr<Camera>camera) {};//�I�u�W���N�g�̓����蔻��
	
	int GetActType()const { return actorType_; }//�I�u�W�F�N�g�̔��ʂ�����Getter
protected:
	int stage_id_ = 0;//�X�e�[�WID
private:
	int actorType_ = 0;//�I�u�W���N�g�������𔻕ʂ���ϐ�(0:player,1:enemy 2:gimmick3:mob) 

};