#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy_boss.h"
#include"../Player/Player.h"
#include"../Efect/Efect.h"
#include"../Enemy/EnemyChild/Attack.h"
#include"../Enemy/EnemyChild/Item.h"


//-------------------------------------------------------------------------------------------------//
//エネミーの子クラス　ボスキャラ
//-------------------------------------------------------------------------------------------------//

EnemyBoss::EnemyBoss(const tnl::Vector3& pos, float size)
	: Enemy(pos, size) {
	enemy_gpc_hdl_ = LoadGraph("graphics/boss.png");
	boss_hp_ = 30;
	//サウンドデーター読み込み
	enemy_voice_sound_hdl = LoadSoundMem("sound/Bossbgm.mp3");
	attack_sound_hdl = LoadSoundMem("sound/attack.wav");
	death_sound_hdl = LoadSoundMem("sound/Bossdeath.wav");
	//ボスBGMのループ再生
	PlaySoundMem(enemy_voice_sound_hdl, DX_PLAYTYPE_LOOP);
	//攻撃エフェクト読み込み
	fire_anim = std::make_shared<Efect>("graphics/fire.png",EFECT_POS, 8, 1, 128, 128, 8, 6);
}
EnemyBoss::~EnemyBoss()
{
	DeleteSoundMem(attack_sound_hdl);
	DeleteSoundMem(death_sound_hdl);
	DeleteGraph(enemy_gpc_hdl_);
	DeleteSoundMem(enemy_voice_sound_hdl);
}

bool EnemyBoss::Magic(const float delta_time) {
		while (-1) {
			//10秒間右へ
			TNL_SEQ_CO_TIM_YIELD_RETURN(10, delta_time, [&]() {
				attack_pos.x += enemyspeed;
				//if (boss_hp_ <= 10) TNL_SEQ_CO_BREAK;
				
			});

			//10秒間左へ
			TNL_SEQ_CO_TIM_YIELD_RETURN(10, delta_time, [&]() {
				attack_pos.x -= enemyspeed;
				//if (boss_hp_ <= 10) TNL_SEQ_CO_BREAK;
				
			});

			//１０秒間涙が降る
			TNL_SEQ_CO_TIM_YIELD_RETURN(10, delta_time, [&]() {
				//上からランダムに涙が降る
				static float time_count = 0;
				time_count += delta_time;
				if (time_count >= 0.5) {
					attack.emplace_back(new Attack);
					time_count = 0;
				}
				auto it = attack.begin();
				while (it != attack.end()) {
					(*it)->Move();
					it++;
				}
				//if (boss_hp_ <= 10) TNL_SEQ_CO_BREAK;
				});
			//攻撃ターン
			TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]() {
				//涙消して
				auto it = attack.begin();
				while (it != attack.end()) {
					(*it) = nullptr;
					continue;
					it++;
				}
				
			});
			
		}
	
	TNL_SEQ_CO_END;
	
}


void EnemyBoss::Draw(std::shared_ptr<Camera>camera) {
	//ボス本体の描画
	draw_pos_ = enemy_pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawRotaGraph(draw_pos_.x, draw_pos_.y, 1, 0, enemy_gpc_hdl_, true);
	//線攻撃
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	draw_pos_ = attack_pos - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawLine(draw_pos_.x, draw_pos_.y - (DXE_WINDOW_HEIGHT>>1),
		draw_pos_.x, draw_pos_.y + (DXE_WINDOW_HEIGHT >> 1),
		0xFFFF00000, ATTACKSIZE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//涙
	auto it = attack.begin();
	while (it != attack.end()) {
		(*it)->Draw(camera);
		it++;
	}
	if(item)item->Draw(camera);
	//モーション入れる
	fire_anim->Draw(camera);
	
}
void EnemyBoss::Move(float delta_time, const std::shared_ptr<Player>player) {
	if(boss_hp_ > 10)tnl_sequence_.Update(delta_time);
	fire_anim->Update(delta_time);
	static float time = 0;
	static float efect_count = 0;
	//攻撃用アイテム落とす
	time += delta_time;
	if (!item && time >= 5) {
		item = std::make_shared<Item>();
		time = 0;
	}
	//攻撃フラグが真であればItemはデリート
	if (player_attack || time >= 5) {
		item = nullptr;
		time = 0;
	}
	if (player_attack) {
		fire_anim->PlayEfect();
		efect_count += delta_time;
		if (efect_count >= 2) {
			fire_anim->StopEfect();
			player_attack = false;
			efect_count = 0;
		}
	}
	//コルーチンで動かしていたらフリーズしたため応急処置
	if (boss_hp_ <= 10 && boss_hp_ > 0) {
		PlaySoundMem(death_sound_hdl, DX_PLAYTYPE_BACK);
		boss_hp_ -= 10;
	}
	//光の当たり判定
	if (tnl::IsIntersectRect(
		player->GetPlayerPos(),
		player->PLAYER_SIZE,
		player->PLAYER_SIZE,
		attack_pos,
		ATTACKSIZE,
		DXE_WINDOW_HEIGHT)) {
		boss_attack_ = true;
		
	}
	//涙の当たり判定
	for (auto tear : attack) {
		if (tnl::IsIntersectSphere(
			player->GetPlayerPos(),
			player->PLAYER_SIZE,
			tear->pos_,
			tear->ATTACKSIZE)) {
			boss_attack_ = true;
		}
	}
	//攻撃アイテムの当たり判定
	if (item) {
		if (tnl::IsIntersectSphere(
			player->GetPlayerPos(),
			player->PLAYER_SIZE,
			item->pos_,
			item->ITEMSIZE)) {
			DrawStringEx(640, 360, -1, "Enter/A");
			if (GetJoypadNum() == 1) { DrawStringEx(640, 360, -1, "Aで攻撃"); }
			else { DrawStringEx(640, 360, -1, "Enterで攻撃"); }
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)|| tnl::Input::IsPadDownTrigger(ePad::KEY_0)) {
				boss_hp_ -= 10;
				PlaySoundMem(attack_sound_hdl, DX_PLAYTYPE_BACK);
				player_attack = true;
			}

		}
	}
	
}

