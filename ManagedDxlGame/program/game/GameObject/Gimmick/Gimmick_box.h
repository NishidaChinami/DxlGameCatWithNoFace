#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Gimmick.h"

class Player;
class Camera;
//-------------------------------------------------------------------------------------------------//
//ギミックの子クラス①　押せる箱
//-------------------------------------------------------------------------------------------------//
class GimmickBox: public Gimmick
{
public:
	GimmickBox(int type, tnl::Vector3& pos, float width, float hight)
		:Gimmick(type, pos, width, hight) {}
	~GimmickBox()override {}
	void Move(float delta_time, const std::shared_ptr<Player>player)override;//動く箱の挙動関数
	void Draw(const std::shared_ptr<Camera>camera)override;//動く箱の描画関数
	void Hit(const std::list<std::shared_ptr<Mapchip>>&mapchip, const std::shared_ptr<Player>player)override;//動く箱との当たり判定更新の関数
	int Getfacenum() { return surface_num_; }//動く箱とプレイヤーがどの面で接するかを返す関数
private:
	int surface_num_ = 0;//箱のどの面に触れたかを示す変数
	tnl::Vector3 prev_pos_;//箱の補正前座標
};

