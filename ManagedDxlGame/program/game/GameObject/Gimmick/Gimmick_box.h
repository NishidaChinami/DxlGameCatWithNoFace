#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Gimmick.h"

class Player;
class Camera;
//-------------------------------------------------------------------------------------------------//
//�M�~�b�N�̎q�N���X�@�@�����锠
//-------------------------------------------------------------------------------------------------//
class GimmickBox: public Gimmick
{
public:
	GimmickBox(int type, tnl::Vector3& pos, float width, float hight)
		:Gimmick(type, pos, width, hight) {}
	~GimmickBox()override {}
	void Move(float delta_time, const std::shared_ptr<Player>player)override;//�������̋����֐�
	void Draw(const std::shared_ptr<Camera>camera)override;//�������̕`��֐�
	void Hit(const std::list<std::shared_ptr<Mapchip>>&mapchip, const std::shared_ptr<Player>player)override;//�������Ƃ̓����蔻��X�V�̊֐�
	int Getfacenum() { return surface_num_; }//�������ƃv���C���[���ǂ̖ʂŐڂ��邩��Ԃ��֐�
private:
	int surface_num_ = 0;//���̂ǂ̖ʂɐG�ꂽ���������ϐ�
	tnl::Vector3 prev_pos_;//���̕␳�O���W
};

