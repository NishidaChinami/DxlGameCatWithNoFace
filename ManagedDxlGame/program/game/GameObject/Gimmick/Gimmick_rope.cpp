#include "../dxlib_ext/dxlib_ext.h"
#include"Gimmick_rope.h"
#include"../Player/Player.h"
#include"../Camera/Camera.h"

GimmickRope::GimmickRope(int type,tnl::Vector3& pos, float width, float hight)
	:Gimmick(type, pos, width, hight) {
	s_ = { gimmick_pos_.x, gimmick_pos_.y - (gimmick_hight_ / 2),0 };
	e_ = { gimmick_pos_.x, gimmick_pos_.y + (gimmick_hight_ / 2),0 };
}

void GimmickRope::Move(float delta_time, const std::shared_ptr<Player>player) {
	//始点から終点の単位ベクトル
	tnl::Vector3 cpn = tnl::Vector3::Normalize(e_ - s_);
	//始点から終点の単位ベクトルと奥行Z軸との外積を求める
	tnl::Vector3 cpz_cr = cpn.cross(tnl::Vector3(0, 0, -1));
	//振り子の真上のベクトルとcpz_crの内積を求めと振り子に直角なベクトルを求める
	//振り子が９０度の時内積は０になる速度が止まり
	//振り子が０度の時内積は１になる符号が入れ替わる
	float gr = cpz_cr.dot(tnl::Vector3(0, 1, 0));

	float pw = 0.98f * 0.5f * gr;
	
	//力を加える
	rot_vel_ += pw;
	//力を加えると同時に、終点に重りがついているときの回転の制御の計算をする
	rot_vel_ *= 1.0f - (0.01f * (1.0f - (e_ - s_).length() / max_length_));
	//角度を計算
	float angle = tnl::ToRadian(rot_vel_);
	//終点がどの弧を描くかを計算する
	e_ = s_ + tnl::Vector3::TransformCoord(
		cpn * (e_ - s_).length(),
		tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, 1), angle));

}

void GimmickRope::Draw(const std::shared_ptr<Camera>camera) {
	draw_pos_ = gimmick_pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	tnl::Vector3 s1 = s_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	tnl::Vector3 e1 = e_ -camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	//振り子の紐の描画
	DrawLine(s1.x, s1.y, e1.x, e1.y, 0xFF734E30,5);

}