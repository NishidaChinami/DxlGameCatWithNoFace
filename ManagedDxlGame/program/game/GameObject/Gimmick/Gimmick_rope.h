#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Gimmick.h"
class Player;
class Camera;
//-------------------------------------------------------------------------------------------------//
//�M�~�b�N�q�N���X�B�@���[�v
//-------------------------------------------------------------------------------------------------//
class GimmickRope : public Gimmick
{
public:
	GimmickRope(int type,tnl::Vector3& pos, float width, float hight);
	~GimmickRope() override{}
	void Move(float delta_time, const std::shared_ptr<Player>player)override;//���[�v�̋����֐�
	void Draw(const std::shared_ptr<Camera>camera)override;//���[�v�̕`��֐�

	bool &Getactive_() { return rope_active_; }		//���[�v�Ƀv���C���[���G��Ă��邩��Ԃ��֐�
	tnl::Vector3 GetLopePos()const { return e_; }	//���[�v�̏I�_���W��Ԃ��֐�
	void SetRotVel(float rot) {rot_vel_ += rot;}	//���[�v�ɂ�����͂�ύX����֐�

private:
	float rot_vel_ = 0;			//��]�̗͂̋���
	tnl::Vector3 s_;			//�U��q�̎n�_
	tnl::Vector3 e_;			//�U��q�̏I�_
	float max_length_ = 300.0f;	//�R�̍ő�̒���
	bool rope_active_ = false;	//���[�v�ɐG��Ă��邩�ǂ����̃t���O(�X�s�[�h����������Ə���ɗ���Ă��܂�����)
};


