#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Player;
class Camera;


//-------------------------------------------------------------------------------------------------//
//ストーリーをもつ登キャラクター
//-------------------------------------------------------------------------------------------------//
class Mob
{
public:
	// arg1...Mobが持つストーリが何話めか
	// arg2...キャラクターの位置
	// arg3...キャラクターサイズ
	// arg4...Mobキャラクターの画像ハンドル
	Mob(int chapter, const tnl::Vector3& pos, float size, int gpc_hdl);
	~Mob();
	void Update(float delta_time);//Mobキャラクターを更新する関数	
	void Draw(const std::shared_ptr<Camera>camera);//Mobの描画関数
	void Collition(const std::shared_ptr<Player>player);//Mobとプレイヤーとの当たり判定の取得の関数

	tnl::Vector3 GetMobDrawPos()const { return draw_pos_; }	//Mobの描画座標を返す関数
	bool Getmob() const{ return mob_collition_; }			//Mobに当たったかを判定するフラグを返す関数
	int Getchapter() const { return mob_chapter_; }			//Mobがチャプターいくつのストーリーを持つか返す関数

private:
	tnl::Vector3 mob_pos_;				//Mobゲーム内座標
	tnl::Vector3 draw_pos_;				//Mobの描画座標
	int mob_gpc_hdl;					//Mobの画像ハンドル
	float mob_size_ ;					//Mobのサイズ
	bool mob_collition_ = false;		//プレイヤーとの当たり判定のフラグ
	int mob_chapter_;					//何のストーリーをもつMobかを判別する変数
};
