
#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy.h"
#include"../Player/Player.h"
#include"../Camera/Camera.h"


Enemy::Enemy(const tnl::Vector3 &pos,float size) {
	enemy_pos_ = pos;
	enemy_size_ = size;
	enemy_init_pos_ = pos;
}

Enemy::~Enemy()
{
	DeleteGraph(enemy_gpc_hdl_);
	DeleteSoundMem(enemy_voice_sound_hdl);
}


void Enemy::Draw(const std::shared_ptr<Camera>camera) {
	draw_pos_ = enemy_pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawRotaGraph(draw_pos_.x, draw_pos_.y, 1, 0, enemy_gpc_hdl_, true);

}



