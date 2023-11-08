#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Camera/Camera.h"

class Mapchip;
class Camera;
class Gimmick;
class Enemy;
class SaveLoad;


//-------------------------------------------------------------------------------------------------//
//プレイするキャラクタークラス
//-------------------------------------------------------------------------------------------------//
class Player: public std::enable_shared_from_this<Player> {
public:
	Player(const std::shared_ptr<SaveLoad>save);
	~Player();
	void Update(float delta_time);									//プレイヤーの更新する関数
	void Draw(const std::shared_ptr<Camera>camera);								//プレイヤーの描画
	void Hit(const std::list<std::shared_ptr<Mapchip>>&mapchip,std::shared_ptr<Camera>camera);	//プレイヤーとマップの当たり判定
	void GimmickHit(const std::list<std::shared_ptr<Gimmick>>&gimmick);			//プレイヤーとギミックの当たり判定
	void EnemyHit(const std::list<std::shared_ptr<Enemy>>&enemy, std::shared_ptr<Camera>camera);	//プレイヤーと敵の当たり判定
	void Death(std::shared_ptr<Camera>camera);										//死亡・中間セーブの関数
	//アニメーションタイプ
	enum class ANIMTYPE {
		DIR_LEFT,		//左へ歩く
		DIR_RIGHT,		//右へ歩く
		DIR_IDEL,		//入力待ち状態
		DIR_JUMP_LEFT,	//左向きにジャンプ
		DIR_JUMP_RIGHT, //右向きにジャンプ
		DIR_ROPE,		//ロープにつかまる動き
		DIR_LADDER,		//梯子に上る
		DIR_MAX
	};


	
	const static int PLAYER_SIZE = 30;								//プレイヤーサイズ

	tnl::Vector3 GetPlayerPos() const { return player_pos_; }		//プレイヤー座標のGetter
	tnl::Vector3 GetPlayerPrevPos() const { return prev_pos_; }		//プレイヤーの補正前座標のGetter
	tnl::Vector3 Getsavepos() const { return intermediate_save_; }	//中間セーブのカメラ座標のGetter
	tnl::Vector3 GetSavePlayerPos() const { return save_pos_; }		//中間セーブのプレイヤー座標のGetter
	int Getstagepass(){ return stage_pass_; }						//ステージ保存用の変数のGetter
	bool Getbattle() const { return start_battle_; }					//ボス戦開始のフラグのGetter
	bool GetPlayerDeath() const{ return player_death_; }				//プレイヤーが死んだかどうかのフラグのGetter
private:
	tnl::Vector3 player_pos_;										//プレイヤーのゲーム内座標
	tnl::Vector3 draw_pos_ = { 0,0,0 };								//プレイヤー描画座標
	float gravity_ = 0;												//プレイヤーにかかる重力
	tnl::Vector3 force = {0,0,0};									//移動の慣性用変数
	const tnl::Vector3 INITIAL_POS = { PLAYER_SIZE / 2, 200, 0 };	//プレイヤー初期値
	tnl::Vector3 prev_pos_ = { 0,0,0 };								//プレイヤーの補正前の座標
	tnl::Vector3 intermediate_save_;								//カメラリスポーン値を保存
	tnl::Vector3 save_pos_;											//プレイヤーリスポーン値を保存
	int stage_pass_;												//次のステージに行くための演算用のステージ保存変数
	//プレイヤーの移動状態を管理するシークエンス
	tnl::Sequence<Player> sequence_ = tnl::Sequence<Player>(this, &Player::seqIdle);
	//各移動状態
	bool seqIdle(const float delta_time);				//アイドル
	bool seqdeath(const float delta_time);				//死亡
	bool seqRun(const float delta_time);				//通常移動
	bool seqclimb(const float delta_time);				//上下移動
	bool seqstop(const float delta_time);				//停止状態
	bool seqpendulum(const float delta_time);			//縄に捕まっている状態
	bool seqmovefloor(const float delta_time);			//動く床に乗っている状態


	ANIMTYPE anim_ctrl_dir = ANIMTYPE::DIR_IDEL;//アニメーションタイプのID

	//全アニメーション画像
	std::string files[static_cast<int>(ANIMTYPE::DIR_MAX)] = {
		"graphics/AnimWalkL.png",
		"graphics/AnimWalkR.png",
		"graphics/AnimIdleR.png",
		"graphics/AnimJumpL.png",
		"graphics/AnimJumpR.png",
		"graphics/AnimFuriko.png",
		"graphics/AnimLadder.png"
	};

	const int frame_count_ = 4;								// 総フレーム数
	const int frame_width_ = 4;								// 横フレーム数
	const int frame_hight_ = 1;								// 縦フレーム数
	const int size_width_ = 300;							// 横方向へ 1フレームあたりの幅
	const int size_hight_ = 300;							// 縦方向へ 1フレームあたりの幅

	int player_death_sound_hdl;							//プレイヤー死亡時のサウンドハンドル
	int death_gpc_hdl;										//死亡時の画像ハンドル

	int anim_hdls[static_cast<int>(ANIMTYPE::DIR_MAX)][4];	//アニメーション画像の二次元配列
	int anim_ctrl_frame_ = 0;								//アニメのフレーム数
	int body_side_ = 0;										//プレイヤーの体の向き
	bool rope_active_ = false;								//振り子との当たり判定フラグ
	bool start_battle_ = false;								//ボス戦開始のフラグ
	bool damege_ = true;									//プレイヤーにダメージを与えられるかのフラグ
	bool player_death_ = false;								//死亡したかのフラグ

	
};
