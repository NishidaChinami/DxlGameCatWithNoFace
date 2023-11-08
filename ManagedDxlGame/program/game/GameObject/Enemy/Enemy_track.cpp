#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy_track.h"
#include"../Player/Player.h"

EnemyTrack::EnemyTrack(const tnl::Vector3& pos, float size)
: Enemy( pos, size) {
	enemy_gpc_hdl_ = LoadGraph("graphics/tracking.png");
	enemy_voice_sound_hdl = LoadSoundMem("sound/track.wav");
	boss_hp_ = 100;
}
EnemyTrack::~EnemyTrack()
{
}

//追尾型
void EnemyTrack::Move(float delta_time,const std::shared_ptr<Player>player) {
	tnl::Vector3 target = { 0,0,0 };
	int hypotenuse = 0;
	static float life_count = 0;
	life_count += delta_time;
	//敵とプレイヤーの距離の差をx.y軸それぞれ求める
	target = player->GetPlayerPos() - enemy_pos_;
	//敵とプレイヤーの距離の差を計算する
	target.normalize();

	//１フレーム当たり4ドット移動するようにする。
	if (life_count >= 10)enemy_pos_ -= target * 1.0f;
	else if(enemy_pos_.x >= player->GetPlayerPos().x + 20) enemy_pos_ += target * 1.0f;
	else if(enemy_pos_.x < player->GetPlayerPos().x + 20) enemy_pos_ += target * 4.0f;
}
