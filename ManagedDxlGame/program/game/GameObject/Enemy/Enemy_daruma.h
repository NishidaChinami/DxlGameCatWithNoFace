#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy.h"

class Player;
class Mapchip;
//-------------------------------------------------------------------------------------------------//
//�G�l�~�[�q�N���X�@�@��납��҃_�b�V���^
//-------------------------------------------------------------------------------------------------//
class EnemyDaruma final: public Enemy
{
public:
	EnemyDaruma(const tnl::Vector3& pos, float size);
	~EnemyDaruma();
	
	TNL_CO_SEQUENCE(EnemyDaruma, &EnemyDaruma::Daruma);
	tnl::Sequence<EnemyDaruma> seq_ = tnl::Sequence<EnemyDaruma>(this, &EnemyDaruma::Daruma);//�G�̋����̃R���[�`��

	void Move(float delta_time, const std::shared_ptr<Player>player)override;//�_���}�^�C�v�̍s���֐�
	void Hit(const std::list<std::shared_ptr<Mapchip>>& mapchip, const std::shared_ptr<Player>player)override;//�_���}�^�ƃ}�b�v�̓����蔻��X�V�̊֐�
	bool Daruma(const float delta_time);//�_���}�^�U���p�^�[���R���[�`��
private:
	bool active_ = false;//�G�̓����^�C�~���O�𐧌䂷��t���O
	tnl::Vector3 prev_pos_;	//�G�̂̕␳�O�̍��W
};