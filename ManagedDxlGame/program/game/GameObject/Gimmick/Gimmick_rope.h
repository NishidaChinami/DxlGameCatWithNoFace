#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Gimmick.h"
class Player;
class Camera;
//-------------------------------------------------------------------------------------------------//
//ギミック子クラス③　ロープ
//-------------------------------------------------------------------------------------------------//
class GimmickRope : public Gimmick
{
public:
	GimmickRope(int type,tnl::Vector3& pos, float width, float hight);
	~GimmickRope() override{}
	void Move(float delta_time, const std::shared_ptr<Player>player)override;//ロープの挙動関数
	void Draw(const std::shared_ptr<Camera>camera)override;//ロープの描画関数

	bool &Getactive_() { return rope_active_; }		//ロープにプレイヤーが触れているかを返す関数
	tnl::Vector3 GetLopePos()const { return e_; }	//ロープの終点座標を返す関数
	void SetRotVel(float rot) {rot_vel_ += rot;}	//ロープにかかる力を変更する関数

private:
	float rot_vel_ = 0;			//回転の力の強さ
	tnl::Vector3 s_;			//振り子の始点
	tnl::Vector3 e_;			//振り子の終点
	float max_length_ = 300.0f;	//紐の最大の長さ
	bool rope_active_ = false;	//ロープに触れているかどうかのフラグ(スピードが速すぎると勝手に離れてしまうため)
};


