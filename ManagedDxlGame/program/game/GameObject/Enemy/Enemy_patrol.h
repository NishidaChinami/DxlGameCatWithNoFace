#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy.h"

class Player;
//-------------------------------------------------------------------------------------------------//
//�G�l�~�[�q�N���X�A�@����^
//-------------------------------------------------------------------------------------------------//
class EnemyPatrol final:public Enemy
{
public:
	EnemyPatrol(const tnl::Vector3& pos, float size);
	~EnemyPatrol();
	//�p�g���[���^�̍U���p�^�[���̃R���[�`��
	TNL_CO_SEQUENCE(EnemyPatrol, &EnemyPatrol::Patrol);
	tnl::Sequence<EnemyPatrol> seq_ = tnl::Sequence<EnemyPatrol>(this, &EnemyPatrol::Patrol);	//�p�g���[���^�̃R���[�`���p�e���v���[�g
	bool Patrol (const float delta_time);	//�p�g���[���^�̍U���p�^�[���̃R���[�`��
	void Move(float delta_time,const std::shared_ptr<Player>player)override;//�p�g���[���^�̋����̊֐�
};


