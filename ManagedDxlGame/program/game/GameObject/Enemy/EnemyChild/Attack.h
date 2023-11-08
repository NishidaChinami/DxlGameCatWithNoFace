#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../game/GameObject/Camera/Camera.h"
//-------------------------------------------------------------------------------------------------//
//ボスエネミーの攻撃クラス
//-------------------------------------------------------------------------------------------------//
class Attack {
public:
	tnl::Vector3 pos_; //ゲーム内座標
	tnl::Vector3 draw_pos_;//描画座標
	int gpc_hdl = 0;   //攻撃のグラフィックハンドル
	const float ATTACKSIZE = 32;//攻撃のサイズ
	float random_pos_ = (rand() % 1280) + 6720;//攻撃のスポーン位置をランダムに返す
	Attack() {
		pos_ = { random_pos_,0,0 };
		gpc_hdl = LoadGraph("graphics/tear.png");
	}
	~Attack() {
		DeleteGraph(gpc_hdl);
	}

	void Move() {
		pos_.y += 2.0;
	}
	void Draw(const std::shared_ptr<Camera>camera) {
		draw_pos_ = pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
		DrawRotaGraph(draw_pos_.x, draw_pos_.y, 1, 0, gpc_hdl, true);
	}
};