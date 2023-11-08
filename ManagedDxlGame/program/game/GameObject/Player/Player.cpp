#include "../dxlib_ext/dxlib_ext.h"
#include"Player.h"
#include<cmath>
#include "Math.h"
#include"../Stage/Mapchip.h"
#include"../Gimmick/Gimmick.h"
#include"../Camera/Camera.h"
#include"../Gimmick/Gimmick_rope.h"
#include"../Gimmick/Gimmick_box.h"
#include"../Enemy/Enemy.h"
#include"../Enemy/Enemy_boss.h"
#include"../game/Etc/Save.h"


Player::Player(const std::shared_ptr<SaveLoad>save){
	player_pos_ = save->GetLoadPos();
	intermediate_save_ = save->GetLoadCameraPos();
	stage_pass_ = save->GetLoadStage();
	save_pos_ = player_pos_;
	player_death_sound_hdl = LoadSoundMem("sound/death.mp3");
	death_gpc_hdl = LoadGraph("graphics/nc283570.png");

	for (int i = 0; i < static_cast<int>(ANIMTYPE::DIR_MAX); ++i) {
		LoadDivGraph(files[i].c_str(),frame_count_,frame_width_,frame_hight_,size_width_,size_hight_,anim_hdls[i]);					
	}
}

Player::~Player() {
	DeleteSoundMem(player_death_sound_hdl);
	DeleteGraph(death_gpc_hdl);
	for (int i = 0; i < static_cast<int>(ANIMTYPE::DIR_MAX); ++i) {
		for (int k = 0; k < 4; k++) {
			DeleteGraph(anim_hdls[i][k]);
		}
	}
	
}


void Player::Update(float delta_time) {
	//アニメーションフレームを回す
	static float anim_time_count = 0;
	anim_time_count += delta_time;
	if (anim_time_count > 0.2f) {
		anim_ctrl_frame_++;
		anim_ctrl_frame_ %= 4;
		anim_time_count = 0;
	}

	//1フレーム前の座標を取得
	prev_pos_ = player_pos_;
	player_death_ = false;
	sequence_.Update(delta_time);
	
}

//プレイヤーの描画
void Player::Draw(const std::shared_ptr<Camera>camera) {
	draw_pos_ = player_pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawRotaGraph(draw_pos_.x, draw_pos_.y-32,0.4f , 0, anim_hdls[static_cast<int>(anim_ctrl_dir)][anim_ctrl_frame_], true);
	//プレイヤーが画面が画面右端から出たらステージ切り替え
	if (draw_pos_.x >= 1280 && start_battle_ == false) {
		stage_pass_ += 1;
		player_pos_ = INITIAL_POS;
		intermediate_save_ = { 0,0,0 };
		save_pos_ = player_pos_;
	}
}

//プレイヤー死亡時の処理
void Player::Death(std::shared_ptr<Camera>camera) {
	sequence_.change(&Player::seqdeath);
	camera->CameRareset(shared_from_this());
	player_pos_ = save_pos_;
	start_battle_ = false;
	player_death_ = true;
	PlaySoundMem(player_death_sound_hdl, DX_PLAYTYPE_BACK);
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 1, 0, death_gpc_hdl, true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//プレイヤーの当たり判定
void Player::Hit(const std::list<std::shared_ptr<Mapchip>>&mapchip,std::shared_ptr<Camera>camera) {
	if (draw_pos_.y > DXE_WINDOW_HEIGHT) Death(camera);
	if (draw_pos_.y < -50)Death(camera);
	damege_ = true;
	// ブロックと衝突判定 & 補正
	for (const std::shared_ptr<Mapchip>chip : mapchip) {	
		//マップチップとの衝突
		if (1 == chip->GetCollitionType()) {
			float c = tnl::IsIntersectRectToCorrectPosition(
				player_pos_,
				prev_pos_,
				PLAYER_SIZE,
				PLAYER_SIZE,
				chip->GetChipPos(),
				Mapchip::CHIP_SIZE,
				Mapchip::CHIP_SIZE);
			if (c == 3 || c == 4) {
				gravity_ = 0;
			}
		}
		if (tnl::IsIntersectRect(
			player_pos_,
			PLAYER_SIZE,
			PLAYER_SIZE,
			chip->GetChipPos(),
			Mapchip::CHIP_SIZE,
			Mapchip::CHIP_SIZE)) {
		//針との衝突と落下死
			if (2 == chip->GetCollitionType() || 9 == chip->GetCollitionType()) Death(camera);
		//梯子との接触
			if (3 == chip->GetCollitionType()) sequence_.change(&Player::seqclimb);
			if (5 == chip->GetCollitionType()) {
				damege_ = false;
			}
			if(6 == chip->GetCollitionType()){
				start_battle_ = true;
			}
			//女神像（セーブポイント）との衝突
			if (10 == chip->GetCollitionType()) {
				//セーブポイント場所を保存
				save_pos_ = player_pos_ - tnl::Vector3(0,100,0);
				//カメラ座標を保存
				intermediate_save_ = camera->GetCameraPos();
			}
		}

		//斜めの坂との補正
		if (4 == chip->GetCollitionType()) {
			float lx = chip->GetChipPos().x - Mapchip::CHIP_SIZE / 2;
			float rx = chip->GetChipPos().x + Mapchip::CHIP_SIZE / 2;
			float ty = chip->GetChipPos().y - Mapchip::CHIP_SIZE / 2;
			float by = chip->GetChipPos().y + Mapchip::CHIP_SIZE / 2;
			tnl::Vector3 np = tnl::GetNearestPointLine(player_pos_, { lx, ty, 0 }, { rx, by, 0 });
			if ((np - player_pos_).length() > PLAYER_SIZE) continue;
			tnl::Vector3 v = tnl::Vector3::Normalize(player_pos_ - np);
			player_pos_ = np + v * PLAYER_SIZE;		
		}
		
	}
}

//ギミックとの当たり判定
void Player::GimmickHit(const std::list<std::shared_ptr<Gimmick>>&gimmick) {
	tnl::Vector3 dummy_pos = player_pos_;
	for (auto gim : gimmick) {
		//動く箱との当たり判定
		std::shared_ptr<GimmickBox>box = std::dynamic_pointer_cast<GimmickBox>(gim);
		if (0 == gim->GetGimmickType()) {
			//where2個数字が入ってる
			if (tnl::IsIntersectRectToCorrectPosition(
				dummy_pos, prev_pos_, PLAYER_SIZE, PLAYER_SIZE,
				gim->GetGimmickPos(), gim->GetGimmickWidth(), gim->GetGimmickHight())) {
				float c = (player_pos_.x + gim->GetGimmickPos().x) / 2.0f;
				if (1 == box->Getfacenum()) player_pos_.x = c - (PLAYER_SIZE / 2.0f);
				else if (2 == box->Getfacenum())player_pos_.x = c + (PLAYER_SIZE / 2.0f);
				else if (0 != box->Getfacenum()) {
					player_pos_ = dummy_pos;
					gravity_ = 0;
				}
				
			}
			
		}
		//動く床との当たり判定
		if (1 == gim->GetGimmickType()) {
			if (tnl::IsIntersectRectToCorrectPosition(
				player_pos_, prev_pos_, PLAYER_SIZE, PLAYER_SIZE,
				gim->GetGimmickPos(), gim->GetGimmickWidth(), gim->GetGimmickHight())) {
				sequence_.change(&Player::seqmovefloor);
				player_pos_.x = gim->GetGimmickPos().x;
				gravity_ = 0;
				if (tnl::Input::IsKeyDown(eKeys::KB_SPACE)|| (tnl::Input::IsPadDownTrigger(ePad::KEY_1))) {
					player_pos_.y = -1.5f;
				}
			}
			
		}
		//ロープとの当たり判定
		if (2 == gim->GetGimmickType()) {
			//ダウンキャスト
			std::shared_ptr<GimmickRope>rope = std::dynamic_pointer_cast<GimmickRope>(gim);
			if (tnl::IsIntersectRect(
				player_pos_,
				PLAYER_SIZE,
				PLAYER_SIZE,
				gim->GetGimmickPos(), 
				gim->GetGimmickWidth(), 
				gim->GetGimmickHight())) {
				sequence_.change(&Player::seqpendulum);
				rope->Getactive_() = true;
			}
			if (rope->Getactive_()) {
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)||
					(tnl::Input::IsPadDownTrigger(ePad::KEY_LEFT)))rope->SetRotVel(2.0f);
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)||
					(tnl::Input::IsPadDownTrigger(ePad::KEY_RIGHT)))rope->SetRotVel(-2.0f);
				player_pos_ = rope->GetLopePos();
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)|| (tnl::Input::IsPadDownTrigger(ePad::KEY_1))) {
					rope->Getactive_() = false;
					player_pos_.x += 40;
					player_pos_.y = -5;
				}
			}	
		}	
	}
}

void Player::EnemyHit(const std::list<std::shared_ptr<Enemy>>&enemy,std::shared_ptr<Camera>camera) {
	//ダメージブールが真の時攻撃が当たる
	if (damege_) {
		for (auto enm : enemy) {
			if (tnl::IsIntersectSphere(
				player_pos_,
				PLAYER_SIZE,
				enm->GetEnemyPos(),
				enm->GetEnemySize())) {
				Death(camera);
			}
			if (enm->GetBossAttack()) {
				Death(camera);
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 行動状態

//アイドル状態
bool Player::seqIdle(float delta_time) {
	anim_ctrl_dir = ANIMTYPE::DIR_IDEL;
	if (tnl::Input::IsKeyDown(eKeys::KB_A, eKeys::KB_D, eKeys::KB_SPACE) ||
		(tnl::Input::IsPadDown(ePad::KEY_RIGHT,ePad::KEY_LEFT,ePad::KEY_1))){
		sequence_.change(&Player::seqRun);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)||
		(tnl::Input::IsPadDownTrigger(ePad::KEY_5))) {
		sequence_.change(&Player::seqstop);
	}
	gravity_ += 0.6f;
	player_pos_.y += gravity_;
	return true;
}
//死んだときの演出
bool Player::seqdeath(float delta_time) {
	static float time = 0.5f;
	int alpha = (sequence_.getProgressTime() / time * 255.0f);
	if (alpha >= 255) {
		SetDrawBright(255, 255, 255);
		sequence_.change(&Player::seqIdle);
	}
	SetDrawBright(alpha, alpha, alpha);
	return true;
}

//移動とジャンプの操作
bool Player::seqRun(float delta_time) {
	tnl::Vector3 move;
	static int jumpcount = 0;
	static float jump_elapsed = 0;
	
	if (tnl::Input::IsKeyDown(eKeys::KB_D) || (tnl::Input::IsPadDown(ePad::KEY_RIGHT))) {
		if (start_battle_ && draw_pos_.x < 1280) {
			move = { 5,0,0 };
			force = move;
		}
		else if (!start_battle_) {
			move = { 5,0,0 };
			force = move;
		}
		body_side_ = 0;
		anim_ctrl_dir = ANIMTYPE::DIR_RIGHT;
	}
	
	if (tnl::Input::IsKeyDown(eKeys::KB_A) || (tnl::Input::IsPadDown(ePad::KEY_LEFT))) {
		if (start_battle_ && draw_pos_.x > 0) {
			move = { -5,0,0 };
			force = move;
		}
		else if (!start_battle_) {
			move = { -5,0,0 };
			force = move;
		}

		body_side_ = 1;
		anim_ctrl_dir = ANIMTYPE::DIR_LEFT;
	}
	
	if (fabs(force.x) > 0) {
		force.x *= 0.9f;
		if (fabs(force.x) < 0.1) {
			force.x = 0;
		}
	}
	player_pos_ += force;

	//ジャンプ
	if (jumpcount == 0) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)|| (tnl::Input::IsPadDownTrigger(ePad::KEY_1))) {
			jumpcount++;
			gravity_ = -16.0f;
			if(body_side_ == 0)anim_ctrl_dir = ANIMTYPE::DIR_JUMP_RIGHT;
			if (body_side_ == 1)anim_ctrl_dir = ANIMTYPE::DIR_JUMP_LEFT;
		}
	}
	else if (jumpcount == 1) {
		jump_elapsed += delta_time;
	//地面についてらリセット
		if (gravity_ == 0) {
			jumpcount = 0;
			jump_elapsed = 0;
		}
	}
	gravity_ += 0.6f;
	player_pos_.y += gravity_;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)|| (tnl::Input::IsPadDownTrigger(ePad::KEY_5))) {
		sequence_.change(&Player::seqstop);
	}
	//アニメーションをアイドルへ
	if (gravity_ >= 0 && force.x == 0 && force.y == 0) {
		anim_ctrl_dir = ANIMTYPE::DIR_IDEL;
	}

	return true;
}

//梯子などを上る動作
bool Player::seqclimb(float delta_time) {
	anim_ctrl_dir = ANIMTYPE::DIR_LADDER;
	tnl::Vector3 move = { 0,0,0 };
	if (tnl::Input::IsKeyDown(eKeys::KB_S))move = { 0,5,0 };
		//|| (tnl::Input::IsPadDown(ePad::KEY_DOWN)))move = { 0,5,0 };
	if (tnl::Input::IsKeyDown(eKeys::KB_W))move = { 0,-5,0 };
		//|| (tnl::Input::IsPadDown(ePad::KEY_UP)))move = { 0,-5,0 };
	player_pos_ += move;

	//左右キーで上り状態解除→アイドル状態へ
	if (tnl::Input::IsKeyDown(eKeys::KB_A) || tnl::Input::IsKeyDown(eKeys::KB_D)) {
		sequence_.change(&Player::seqIdle);
	}
	if (tnl::Input::IsPadDown(ePad::KEY_RIGHT) || tnl::Input::IsPadDown(ePad::KEY_LEFT)) {
		sequence_.change(&Player::seqIdle);
	}
	return true;
}
//振り子にのってるとき
bool Player::seqpendulum(float delta_time) {
	anim_ctrl_dir = ANIMTYPE::DIR_ROPE;
	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE)|| tnl::Input::IsPadDown(ePad::KEY_1)) {
		sequence_.change(&Player::seqIdle);
	}
	return true;
}
//動く床に乗ってるとき
bool Player::seqmovefloor(float delta_time) {
	gravity_ += 0.6f;
	player_pos_.y += gravity_;
	if (tnl::Input::IsKeyDown(eKeys::KB_SPACE)|| tnl::Input::IsPadDown(ePad::KEY_1)) {;
		sequence_.change(&Player::seqIdle);
	}
	return true;
}
//設定画面を開いているとき
bool Player::seqstop(float delta_time) {
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)|| tnl::Input::IsPadDownTrigger(ePad::KEY_5)) {
		sequence_.change(&Player::seqIdle);
	}
	return true;
}