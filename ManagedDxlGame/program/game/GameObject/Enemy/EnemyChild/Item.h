#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../game/GameObject/Camera/Camera.h"
//-------------------------------------------------------------------------------------------------//
//プレイヤーの攻撃アイテムクラス
//-------------------------------------------------------------------------------------------------//
class Item {
public:
	tnl::Vector3 pos_;  //ゲーム内座標
	tnl::Vector3 draw_pos_;//描画座標
	int gpc_hdl = 0;//アイテムのグラフィックハンドル
	const float ITEMSIZE = 32;//アイテムのサイズ
	float random_pos_ = (rand() % 1280) + 6720;//アイテムがスポーンする位置をランダムに決める
	Item() {
		pos_ = { random_pos_,600,0 };
		gpc_hdl = LoadGraph("graphics/sword.png");
	}
	~Item() {
		DeleteGraph(gpc_hdl);
	}
	void Draw(const std::shared_ptr<Camera>camera) {
		draw_pos_ = pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
		DrawRotaGraph(draw_pos_.x, draw_pos_.y, 0.5, 0, gpc_hdl, true);
	}
};