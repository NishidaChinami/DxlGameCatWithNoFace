#pragma once
#include "../dxlib_ext/dxlib_ext.h"

 
class Player;
class Camera;
class Mapchip;

//-------------------------------------------------------------------------------------------------//
//エネミーの親クラス
// 
//※ 動作だけをクラスに分けたストラテジーパターンを実装したかった
//-------------------------------------------------------------------------------------------------//
class Enemy{
public:
	// arg1...エネミーのスポーン座標
	// arg2...エネミーのサイズ（半径）
	Enemy(const tnl::Vector3& pos, float size);
	virtual~Enemy();
	virtual void Hit(const std::list<std::shared_ptr<Mapchip>>& mapchip, const std::shared_ptr<Player>player) {}	//各敵とマップの当たり判定の関数
	virtual void Draw(const std::shared_ptr<Camera>camera);										//各敵の描画関数
	virtual void Move(float delta_time,const std::shared_ptr<Player>player) {}						//各タイプの敵の動きの関数
	
	tnl::Vector3 GetEnemyPos() const { return enemy_pos_; }							//敵の座標を渡す関数
	void SetEnemyPos(tnl::Vector3 pos) { enemy_pos_ = pos; }						//敵の座標を変更する関数
	tnl::Vector3 GetStartPos() const { return enemy_init_pos_; }					//敵の初期位置を返す関数
	tnl::Vector3 GetEnemyDrawPos() const { return draw_pos_; }						//敵の描画座標を返す関数
	float GetEnemySize() const { return enemy_size_; }								//敵のサイズを返す関数
	int GetBossHP()const { return boss_hp_; }											//敵のHPを返す関数
	void SetBossHP(int hp) { boss_hp_ = hp; }										//敵のHPを変更する関数
	bool& GetBossAttack(){ return boss_attack_; }									//敵の攻撃にあたったかを判定するフラグを返す関数

protected:
	tnl::Vector3 enemy_pos_;					//敵のゲーム内座標
	tnl::Vector3 draw_pos_ = { 2000,2000,0 };	//敵の描画座標
	float enemy_size_ = 0;						//敵のサイズ
	int boss_hp_;								//HPのある敵のHP変数
	bool boss_attack_ = false;					//攻撃があたったかどうかのフラグ
	int enemy_gpc_hdl_ = 0;						//敵画像ハンドル
	int enemy_voice_sound_hdl = 0;				//敵サウンドハンドル
	tnl::Vector3 enemy_init_pos_;				//敵の初期地を保存する変数

};
