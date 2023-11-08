#include "../dxlib_ext/dxlib_ext.h"
#include"Mapchip.h"
#include"../Camera/Camera.h"

Mapchip::Mapchip(const tnl::Vector3& pos, int gfx_hdl, int type) : chip_pos_(pos) {

	chip_gpc_hdl_ = gfx_hdl;
	collition_type_ = type;
	chip_pos_ = pos;
}
Mapchip::~Mapchip() {
	DeleteGraph(chip_gpc_hdl_);
}
//ï`âÊèàóù
void Mapchip::Mapchipdraw(const std::shared_ptr<Camera>camera) {
	draw_pos_ = chip_pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawRotaGraph(draw_pos_.x, draw_pos_.y, 1, 0, chip_gpc_hdl_, true);
}
