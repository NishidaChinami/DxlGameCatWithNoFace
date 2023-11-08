#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy_Daruma.h"
#include"../Player/Player.h"
#include"../Stage/Mapchip.h"

EnemyDaruma::EnemyDaruma(const tnl::Vector3& pos, float size)
: Enemy(pos, size) {
	enemy_gpc_hdl_ = LoadGraph("graphics/Daruma.png");
	enemy_voice_sound_hdl = LoadSoundMem("sound/Daruma.wav");
	boss_hp_ = 100;
}

EnemyDaruma::~EnemyDaruma()
{

}
//����܌^
void EnemyDaruma::Move(float delta_time, const std::shared_ptr<Player>player) {
	prev_pos_ = enemy_pos_;
	if (player->GetPlayerPos().x  > enemy_pos_.x+150)active_ = true;
	if(active_)tnl_sequence_.Update(delta_time);
	//���}���u
	if (player->GetPlayerDeath())active_ = false;
}

bool EnemyDaruma::Daruma(float delta_time) {
		while (1) {
			float enemyspeed = 5.0f;
			//2�b�҂���
			//TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]() {});
			TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]() {
				PlaySoundMem(enemy_voice_sound_hdl, DX_PLAYTYPE_BACK);
			});
			//�E�Ɉړ�
			TNL_SEQ_CO_TIM_YIELD_RETURN(10, delta_time, [&]() {
				enemy_pos_.x += enemyspeed;
			});
		}
	
	TNL_SEQ_CO_END;
}
//�_���}�̃}�b�v�`�b�v�␳
void EnemyDaruma::Hit(const std::list<std::shared_ptr<Mapchip>>&mapchip, const std::shared_ptr<Player>player) {
	for (const std::shared_ptr<Mapchip>chip : mapchip) {
		//�}�b�v�`�b�v�Ƃ̏Փ�
		if (1 == chip->GetCollitionType()) {
			if (tnl::IsIntersectRectToCorrectPosition(
				enemy_pos_,
				prev_pos_,
				enemy_size_,
				enemy_size_,
				chip->GetChipPos(),
				Mapchip::CHIP_SIZE,
				Mapchip::CHIP_SIZE)) {
				if (enemy_voice_sound_hdl) {
					DeleteSoundMem(enemy_voice_sound_hdl);
					enemy_voice_sound_hdl = 0;
				}
			}
		}
	}
	
}