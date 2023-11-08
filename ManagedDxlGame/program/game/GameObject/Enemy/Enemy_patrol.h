#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy.h"

class Player;
//-------------------------------------------------------------------------------------------------//
//エネミー子クラス②　巡回型
//-------------------------------------------------------------------------------------------------//
class EnemyPatrol final:public Enemy
{
public:
	EnemyPatrol(const tnl::Vector3& pos, float size);
	~EnemyPatrol();
	//パトロール型の攻撃パターンのコルーチン
	TNL_CO_SEQUENCE(EnemyPatrol, &EnemyPatrol::Patrol);
	tnl::Sequence<EnemyPatrol> seq_ = tnl::Sequence<EnemyPatrol>(this, &EnemyPatrol::Patrol);	//パトロール型のコルーチン用テンプレート
	bool Patrol (const float delta_time);	//パトロール型の攻撃パターンのコルーチン
	void Move(float delta_time,const std::shared_ptr<Player>player)override;//パトロール型の挙動の関数
};


