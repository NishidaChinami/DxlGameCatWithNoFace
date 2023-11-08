#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy_Patrol.h"
#include"../Player/Player.h"

EnemyPatrol::EnemyPatrol(const tnl::Vector3& pos, float size)
: Enemy(pos, size) 
{
	enemy_gpc_hdl_ = LoadGraph("graphics/Patrol.png");
	enemy_voice_sound_hdl = LoadSoundMem("sound/Patrol.wav");
	boss_hp_ = 100;
}

EnemyPatrol::~EnemyPatrol()
{
}
//巡回型
bool EnemyPatrol::Patrol(const float delta_time) {
	while (-1) {
		//7秒間ひだりへ
		float enemyspeed = 0.5f;
		TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]() {
			enemy_pos_.x += enemyspeed;
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				TNL_SEQ_CO_BREAK;
			}
		});
		//サウンド
		TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]() {
			PlaySoundMem(enemy_voice_sound_hdl, DX_PLAYTYPE_BACK);
		});
		//7秒間右へ
		TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]() {
			enemy_pos_.x -= enemyspeed;
		});
		//サウンド
		TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]() {
			PlaySoundMem(enemy_voice_sound_hdl, DX_PLAYTYPE_BACK);
		});
	}

	TNL_SEQ_CO_END;
}

void EnemyPatrol::Move(float delta_time, const std::shared_ptr<Player>player) {
	tnl_sequence_.Update(delta_time);
	if (enemy_pos_.x - player->GetPlayerPos().x > (DXE_WINDOW_WIDTH)&& enemy_pos_.x < player->GetPlayerPos().x) {
		if (enemy_voice_sound_hdl) {
			DeleteSoundMem(enemy_voice_sound_hdl);
			enemy_voice_sound_hdl = 0;
		}
	}
}