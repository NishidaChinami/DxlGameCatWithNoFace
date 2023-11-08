#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Camera;

//-------------------------------------------------------------------------------------------------//
//エフェクト再生用クラス
//-------------------------------------------------------------------------------------------------//
class Efect {
public:
	// arg1...エフェクトアニメーションの画像URLの文字列
	// arg2...アニメーション再生位置
	// arg3...フレームの行数
	// arg4...フレームの列数
	// arg5...フレームの横サイズ
	// arg5...フレームの縦サイズ
	// arg6...フレームの総数
	// arg7...フレームのインターバル
	Efect(const std::string& gh_pass, const tnl::Vector3& pos, 
		int w_num, int h_num, int w_size, int h_size, int frame_count, int delay);
	~Efect();

enum class EfectState {
	PLAYING,//再生
	PAUSE,//一時停止
	STOP,//停止
};

	void PlayEfect();//エフェクトを再生する関数
	void StopEfect();//エフェクトを停止する関数
	void PauseEfect();//エフェクトを一時停止する関数
	void Update(const float delta_time);//エフェクトの更新をする関数
	void Draw(const std::shared_ptr<Camera>camera);//エフェクトの描画する関数

private:
	int graph_handle;//グラフィックハンドル
	int width_num_;//フレームの行数
	int height_num_;//フレームの列数
	int width_size_;//横のサイズ
	int height_size_;//縦のサイズ
	int frame_num_;//フレームの総数
	int current_frame_;//現在のフレーム
	int frame_interval_;//フレーム間のインターバル
	int timer_;//タイマー
	int* efect_gpc_hdl;//グラフィックハンドルの配列
	tnl::Vector3 draw_pos_;//描画座標
	tnl::Vector3 effect_pos_;//エフェクトのゲーム内座標

	EfectState state;//エフェクトの状態

};