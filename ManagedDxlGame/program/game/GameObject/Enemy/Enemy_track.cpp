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

//�ǔ��^
void EnemyTrack::Move(float delta_time,const std::shared_ptr<Player>player) {
	tnl::Vector3 target = { 0,0,0 };
	int hypotenuse = 0;
	static float life_count = 0;
	life_count += delta_time;
	//�G�ƃv���C���[�̋����̍���x.y�����ꂼ�ꋁ�߂�
	target = player->GetPlayerPos() - enemy_pos_;
	//�G�ƃv���C���[�̋����̍����v�Z����
	target.normalize();

	//�P�t���[��������4�h�b�g�ړ�����悤�ɂ���B
	if (life_count >= 10)enemy_pos_ -= target * 1.0f;
	else if(enemy_pos_.x >= player->GetPlayerPos().x + 20) enemy_pos_ += target * 1.0f;
	else if(enemy_pos_.x < player->GetPlayerPos().x + 20) enemy_pos_ += target * 4.0f;
}
