#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mapchip;
class Player;
class SaveLoad;
//-------------------------------------------------------------------------------------------------//
//実際の描画位置を決めるカメラクラス
//-------------------------------------------------------------------------------------------------//
class Camera {
public:
	Camera(const std::shared_ptr<SaveLoad>save);
	~Camera() {};
	void DrawRange();						//カメラが映す範囲を決める関数
	void Scroll(const std::shared_ptr<Player>player);		//カメラがプレイヤーに合わせて動く関数
	void CameRareset(const std::shared_ptr<Player>player);	//プレイヤー死亡時にカメラを中間ポイントまで戻す関数
		
	tnl::Vector3 GetCameraPos() const{ return target_; }	//カメラ座標を返す関数
	void SetCameraPos(tnl::Vector3 &pos) {target_ = pos;}	//カメラ座標を設定する関数
private:
	tnl::Vector3 target_ = { 0,0,0 };						//カメラの座標
	bool m_is_active_ = false;								//カメラがプレイヤーを追いかけるか固定かのフラグ
	const int MAXCHIP = 8000;								//マップの横のサイズ
	const int MAXSTAGE = 7360;								//カメラがプレイヤーを追いかけなくなる位置
};

