#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Camera;
class Mapchip;
class Player;

//-------------------------------------------------------------------------------------------------//
//ステージ描画クラス
//-------------------------------------------------------------------------------------------------//
class Stage {
public:
	Stage(int stage_id);
	~Stage();
	void MapDraw(const std::shared_ptr<Camera>camera);//マップ背景とマップチップの描画関数
	const std::list<std::shared_ptr<Mapchip>>& Getlist() const{ return Collitions; }//マップの当たり判定を渡す関数

private:
	tnl::Vector3 map_pos_;//マップ背景のゲーム内座標
	int stage_gpc_hdl_ = 0;//ステージ背景のグラフィックハンドル
	int chip_hdl[256];//マップの地形画像ハンドルを格納する配列
	int chip_second_hdl_[767];//マップの置物画像ハンドルを格納する配列
	float cam_weight_ = 0.1f;//カメラで移せる比率

	std::vector<std::vector<int>> map_csv;	//マップの地形のcsvハンドル
	std::vector<std::vector<int>> map_or_csv;//マップの飾りのcsvハンドル
	std::vector<std::vector<tnl::CsvCell>> stage_csv;//各ステージの情報のcsvハンドル
	std::vector<std::vector<int>> Collition_csv;//当たり判定のcsvハンドル

	std::list<std::shared_ptr<Mapchip>>Collitions;//マップチップの当たり判定のリストポインタ
	std::list<std::shared_ptr<Mapchip>> blocks;//マップチップのリストポインタ
	std::string stage_date;//背景画像のID一覧
	std::string csv_date;//ステージのマップチップのID一覧
	std::string ornament_data;//置物のマップチップのID一覧
	std::string Collition_date;//当たり判定一覧
};


