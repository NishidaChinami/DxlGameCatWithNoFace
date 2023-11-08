#include "../dxlib_ext/dxlib_ext.h"
#include"Efect.h"
#include"../Camera/Camera.h"

Efect::Efect(const std::string &gh_pass, const tnl::Vector3 &pos, int w_num, int h_num, int w_size, int h_size, int frame_count, int delay)
	:effect_pos_(pos),width_num_(w_num), height_num_(h_num), width_size_(w_size),height_size_(h_size), frame_num_(frame_count),
	current_frame_(0), frame_interval_(delay), timer_(0), state(EfectState::STOP), efect_gpc_hdl(nullptr)
{
	efect_gpc_hdl = new int[frame_num_];
	LoadDivGraph(gh_pass.c_str(), frame_num_, width_num_, height_num_, width_size_, height_size_, efect_gpc_hdl);

}

Efect::~Efect()
{
	delete[] efect_gpc_hdl;
}


void Efect::PlayEfect()
{
	state = EfectState::PLAYING;
}

void Efect::StopEfect()
{
	state = EfectState::STOP;
	current_frame_ = 0;
	timer_ = 0;
}

void Efect::PauseEfect()
{
	state = EfectState::PAUSE;
}




void Efect::Update(const float delta_time)
{
	if (state == EfectState::PLAYING) {
		timer_++;
		//タイマーが一定時間に達したら０にして次のフレームへ
		if (timer_ >= frame_interval_) {
				timer_ = 0;
				current_frame_++;
			//フレームがフレーム総数と一致したら最初のフレームへ
			if (current_frame_ >= frame_num_) {
				current_frame_ = 0;
			}
		}
	}
}

void Efect::Draw(const std::shared_ptr<Camera>camera)
{
	if (efect_gpc_hdl != nullptr && (state == EfectState::PLAYING || state == EfectState::PAUSE)) {
		draw_pos_ = effect_pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
		DrawRotaGraph(draw_pos_.x, draw_pos_.y, 2.5, 0.0, efect_gpc_hdl[current_frame_], true);
	}
}
