#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy.h"
class Player;
//-------------------------------------------------------------------------------------------------//
//�G�l�~�[�q�N���X�A�@�ǔ��^
//-------------------------------------------------------------------------------------------------//
class EnemyTrack final:public Enemy
{
public:
	EnemyTrack(const tnl::Vector3& pos, float size);
	~EnemyTrack();
	void Move(float delta_time,const std::shared_ptr<Player>player)override;//�ǔ��^�̋����̊֐�
};
