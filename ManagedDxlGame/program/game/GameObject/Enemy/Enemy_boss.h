#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy.h"
#include"../Camera/Camera.h"

class Player;
class Attack;
class Item;
class Camera;
class Efect;

class EnemyBoss final:public Enemy
{
public:
	EnemyBoss(const tnl::Vector3& pos, float size);
	~EnemyBoss()override;
	//ボスの攻撃のコルーチン
	TNL_CO_SEQUENCE(EnemyBoss, &EnemyBoss::Magic);
	tnl::Sequence<EnemyBoss> seq_ = tnl::Sequence<EnemyBoss>(this, &EnemyBoss::Magic);
	
	bool Magic(const float delta_time);//ボスの攻撃コルーチン用フラグ
	void Move(float delta_time, const std::shared_ptr<Player>player)override;//ボスの挙動関数
	void Draw(const std::shared_ptr<Camera>camera)override;//ボスの描画関数
	int GetBossHP(){ return boss_hp_; }		//ボスのHPを返す関数
private:

	std::list<std::shared_ptr<Attack>>attack;								//涙攻撃のリスト
	std::shared_ptr<Item>item = nullptr;									//攻撃アイテムのクラスポインタ
	std::shared_ptr<Efect>fire_anim = nullptr;							//エフェクトクラスのポインタ
	const tnl::Vector3 EFECT_POS = { 7360,200,0 };			//エフェクト座標
	float enemyspeed = 3.0f;									//攻撃の横移動の速度
	tnl::Vector3 attack_pos = { 6720,DXE_WINDOW_HEIGHT >> 1,0 };//攻撃が出る座標	
	const int ATTACKSIZE = 250;									//攻撃サイズ
	bool player_attack = false;									//プレイヤーの攻撃フラグ
	int attack_sound_hdl;										//攻撃サウンドのハンドル
	int death_sound_hdl;										//ボスの死ぬサウンドハンドル


};



