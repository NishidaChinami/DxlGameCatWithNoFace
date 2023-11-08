#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class Player;
class Camera;
class Mapchip;
//-------------------------------------------------------------------------------------------------//
//ギミックの親クラス
//-------------------------------------------------------------------------------------------------//
class Gimmick{
public:
	Gimmick(int type, tnl::Vector3& pos, float width, float hight)
		:gimmick_type_(type), gimmick_pos_(pos), gimmick_width_(width), gimmick_hight_(hight){}
	virtual ~Gimmick() {};
	void Update(float delta_time) {};//ギミックの更新
	virtual void Draw(const std::shared_ptr<Camera>camera){}//各ギミックの描画関数
	virtual void Move(float delta_time, const std::shared_ptr<Player>player) {};//各ギミックの動きの関数
	virtual void Hit(const std::list<std::shared_ptr<Mapchip>>& mapchip, const std::shared_ptr<Player>player) {}//ギミックとの当たり判定更新の関数

	tnl::Vector3 GetGimmickPos() { return gimmick_pos_; }		//ギミックのゲーム内座標を返す関数
	tnl::Vector3 GetGimmickDrawPos() { return draw_pos_; }		//ギミックの描画座標を返す関数
	float GetGimmickWidth() const { return gimmick_width_; }	//ギミックの横幅を返す関数
	float GetGimmickHight() const { return gimmick_hight_; }	//ギミックの縦幅を返す関数
	int GetGimmickType() const { return gimmick_type_; }		//ギミックのタイプを返す関数
protected:
	tnl::Vector3 gimmick_pos_;	//ギミックのゲーム内座標
	tnl::Vector3 draw_pos_;		//ギミックの描画座標
	float gimmick_width_;		//ギミックの横サイズ
	float gimmick_hight_;		//ギミックの縦サイズ
private:
	int gimmick_type_ = 0;		//ギミックタイプを判別する変数
};




