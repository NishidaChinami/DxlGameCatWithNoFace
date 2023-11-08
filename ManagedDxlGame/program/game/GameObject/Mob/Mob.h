#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Player;
class Camera;


//-------------------------------------------------------------------------------------------------//
//�X�g�[���[�����o�L�����N�^�[
//-------------------------------------------------------------------------------------------------//
class Mob
{
public:
	// arg1...Mob�����X�g�[�������b�߂�
	// arg2...�L�����N�^�[�̈ʒu
	// arg3...�L�����N�^�[�T�C�Y
	// arg4...Mob�L�����N�^�[�̉摜�n���h��
	Mob(int chapter, const tnl::Vector3& pos, float size, int gpc_hdl);
	~Mob();
	void Update(float delta_time);//Mob�L�����N�^�[���X�V����֐�	
	void Draw(const std::shared_ptr<Camera>camera);//Mob�̕`��֐�
	void Collition(const std::shared_ptr<Player>player);//Mob�ƃv���C���[�Ƃ̓����蔻��̎擾�̊֐�

	tnl::Vector3 GetMobDrawPos()const { return draw_pos_; }	//Mob�̕`����W��Ԃ��֐�
	bool Getmob() const{ return mob_collition_; }			//Mob�ɓ����������𔻒肷��t���O��Ԃ��֐�
	int Getchapter() const { return mob_chapter_; }			//Mob���`���v�^�[�����̃X�g�[���[�������Ԃ��֐�

private:
	tnl::Vector3 mob_pos_;				//Mob�Q�[�������W
	tnl::Vector3 draw_pos_;				//Mob�̕`����W
	int mob_gpc_hdl;					//Mob�̉摜�n���h��
	float mob_size_ ;					//Mob�̃T�C�Y
	bool mob_collition_ = false;		//�v���C���[�Ƃ̓����蔻��̃t���O
	int mob_chapter_;					//���̃X�g�[���[������Mob���𔻕ʂ���ϐ�
};
