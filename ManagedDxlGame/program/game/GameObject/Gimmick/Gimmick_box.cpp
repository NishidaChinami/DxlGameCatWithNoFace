#include "../dxlib_ext/dxlib_ext.h"
#include"Gimmick_box.h"
#include"../Player/Player.h"
#include"../Camera/Camera.h"
#include"../Stage/Mapchip.h"

void GimmickBox::Move(float delta_time, const std::shared_ptr<Player>player) {
	//�␳�p���W
	prev_pos_ = player->GetPlayerPrevPos();
	//�␳������Ȃ����߂̃_�~�[���W
	tnl::Vector3 dummy_pos = player->GetPlayerPos();
	//�ǂ��ɐڐG�������𔻒肵�␳
	surface_num_ = tnl::IsIntersectRectToCorrectPosition(
		dummy_pos, prev_pos_, player->PLAYER_SIZE, player->PLAYER_SIZE,
		gimmick_pos_, gimmick_width_, gimmick_hight_);
	float c = (player->GetPlayerPos().x + gimmick_pos_.x) / 2.0f;
	if(1 == surface_num_) gimmick_pos_.x = c + (gimmick_width_/ 2.0f);
	else if(2 == surface_num_)gimmick_pos_.x = c - (gimmick_width_ / 2.0f);
}
void GimmickBox::Draw(const std::shared_ptr<Camera>camera) {
	//�Q�[�������W����J�����̉e����^���`����W��
	draw_pos_ = gimmick_pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawBoxEx(draw_pos_, gimmick_width_, gimmick_hight_, true, 0xFF734E30);
}

//�_���}�̃}�b�v�`�b�v�␳
void GimmickBox::Hit(const std::list<std::shared_ptr<Mapchip>>&mapchip, const std::shared_ptr<Player>player) {
	for (const std::shared_ptr<Mapchip>chip : mapchip) {
		//�}�b�v�`�b�v�Ƃ̏Փ�
		if (1 == chip->GetCollitionType()) {
			if (tnl::IsIntersectRectToCorrectPosition(
				gimmick_pos_,
				prev_pos_,
				gimmick_width_,
				gimmick_hight_,
				chip->GetChipPos(),
				Mapchip::CHIP_SIZE,
				Mapchip::CHIP_SIZE)) {
			}
		}
	}

}