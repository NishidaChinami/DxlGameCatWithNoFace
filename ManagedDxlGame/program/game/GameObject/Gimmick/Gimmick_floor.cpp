#include "../dxlib_ext/dxlib_ext.h"
#include"Gimmick_floor.h"
#include"../Player/Player.h"
#include"../Camera/Camera.h"


bool GimmickFloor::Motion(float delta_time) {
	while (-1) {
		//5•bŠÔ‚Ð‚¾‚è‚Ö
		TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]() {
			gimmick_pos_.x += floor_speed_;
			});
		//5•bŠÔ‰E‚Ö
		TNL_SEQ_CO_TIM_YIELD_RETURN(5, delta_time, [&]() {
			gimmick_pos_.x -= floor_speed_;
			});
	}

	TNL_SEQ_CO_END;

}

void GimmickFloor::Move(float delta_time, const std::shared_ptr<Player>player) {
	tnl_sequence_.Update(delta_time);
}
void GimmickFloor::Draw(const std::shared_ptr<Camera>camera) {
	draw_pos_ = gimmick_pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawBoxEx(draw_pos_, gimmick_width_, gimmick_hight_,true, 0xFF734E30);
}