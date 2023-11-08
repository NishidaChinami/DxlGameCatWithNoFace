#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Gimmick.h"
class Player;
class Camera;
//-------------------------------------------------------------------------------------------------//
//�M�~�b�N�̎q�N���X�A�@������
//-------------------------------------------------------------------------------------------------//
class GimmickFloor :public Gimmick
{
public:
	GimmickFloor(int type,tnl::Vector3& pos, float width, float hight)
		:Gimmick(type, pos, width, hight) {}
	~GimmickFloor() override{}
	//���̓����̃R���[�`��
	TNL_CO_SEQUENCE(GimmickFloor, &GimmickFloor::Motion);
	tnl::Sequence<GimmickFloor> seq_ = tnl::Sequence<GimmickFloor>(this, &GimmickFloor::Motion);
	bool Motion(const float delta_time);

	void Move(float delta_time,const std::shared_ptr<Player>player)override;//�������̋����֐�
	void Draw(const std::shared_ptr<Camera>camera)override;//�������̕`��֐�
private:
	const float floor_speed_ = 2.0f;//���̈ړ����x
};

