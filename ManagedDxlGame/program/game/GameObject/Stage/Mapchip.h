#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Camera;

//-------------------------------------------------------------------------------------------------//
//マップチップクラス
//-------------------------------------------------------------------------------------------------//
class Mapchip {
public:

	// arg1...マップチップの座標
	// arg2...マップチップのグラフィックハンドル
	// arg3...当たり判定の種類
	Mapchip(const tnl::Vector3& pos, int gfx_hdl, int type);
	~Mapchip();
	void Mapchipdraw(const std::shared_ptr<Camera>camera);//マップチップ一枚に対する描画関数
	static constexpr float CHIP_SIZE = 32;//チップの大きさ
	tnl::Vector3 GetChipPos()const { return chip_pos_; }//マップチップの座標を渡す関数
	int GetCollitionType()const { return collition_type_; }//マップチップの当たり判定タイプを渡す関数
private:
	int chip_gpc_hdl_ = 0;//ステージ背景のグラフィックハンドル
	tnl::Vector3 chip_pos_ = { 0, 0, 0 };//マップチップのゲーム内座標
	tnl::Vector3 draw_pos_ = { 0,0,0 };//マップチップの描画座標
	int collition_type_ = 0;//チップの当たり判定タイプの判別変数
};