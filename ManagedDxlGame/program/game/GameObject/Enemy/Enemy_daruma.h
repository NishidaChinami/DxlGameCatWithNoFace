#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy.h"

class Player;
class Mapchip;
//-------------------------------------------------------------------------------------------------//
//エネミー子クラス①　後ろから猛ダッシュ型
//-------------------------------------------------------------------------------------------------//
class EnemyDaruma final: public Enemy
{
public:
	EnemyDaruma(const tnl::Vector3& pos, float size);
	~EnemyDaruma();
	
	TNL_CO_SEQUENCE(EnemyDaruma, &EnemyDaruma::Daruma);
	tnl::Sequence<EnemyDaruma> seq_ = tnl::Sequence<EnemyDaruma>(this, &EnemyDaruma::Daruma);//敵の挙動のコルーチン

	void Move(float delta_time, const std::shared_ptr<Player>player)override;//ダルマタイプの行動関数
	void Hit(const std::list<std::shared_ptr<Mapchip>>& mapchip, const std::shared_ptr<Player>player)override;//ダルマ型とマップの当たり判定更新の関数
	bool Daruma(const float delta_time);//ダルマ型攻撃パターンコルーチン
private:
	bool active_ = false;//敵の動くタイミングを制御するフラグ
	tnl::Vector3 prev_pos_;	//敵のの補正前の座標
};