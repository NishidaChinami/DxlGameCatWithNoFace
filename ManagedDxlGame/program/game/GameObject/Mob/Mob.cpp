#include "../dxlib_ext/dxlib_ext.h"
#include"Mob.h"
#include"../Camera/Camera.h"
#include"../Player/Player.h"

Mob::Mob(int chapter,const tnl::Vector3& pos, float size, int gpc_hdl)
	:mob_chapter_(chapter),mob_pos_(pos), mob_size_(size), mob_gpc_hdl(gpc_hdl) {}

Mob::~Mob()
{
	DeleteGraph(mob_gpc_hdl);
}

void Mob::Update(float delta_time) {
	mob_collition_ = false;
}

void Mob::Draw(const std::shared_ptr<Camera>camera) {
	draw_pos_ = mob_pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawRotaGraph(draw_pos_.x, draw_pos_.y, 0.5, 0, mob_gpc_hdl, true);

}

void Mob::Collition(const std::shared_ptr<Player>player) {
	if (tnl::IsIntersectSphere(mob_pos_, mob_size_, player->GetPlayerPos(), player->PLAYER_SIZE)) {
		if (GetJoypadNum() == 1) { DrawStringEx(500, 500, -1, "A‚Å‰ï˜b"); }
		else { DrawStringEx(500, 500, -1, "Enter‚Å‰ï˜b"); }
		
		if(tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))mob_collition_ = true;
		if(tnl::Input::IsPadDownTrigger(ePad::KEY_0))mob_collition_ = true;
	}
}
