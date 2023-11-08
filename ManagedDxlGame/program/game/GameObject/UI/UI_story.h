#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"UI.h"

class Story;
class SaveLoad;
class Player;
class Camera;
class ScenePlay;

//-------------------------------------------------------------------------------------------------//
//UIの子クラス
// 
// プレイ画面のストーリーUIの表示、入力のクラス
//-------------------------------------------------------------------------------------------------//
class UIStory final:public UI
{
public:
	UIStory(int chapter);
	~UIStory()override;

	void Draw()override;									//UIの描画関数
	void Input(std::shared_ptr<SaveLoad>save, std::shared_ptr<Player>player, 
		const std::shared_ptr<Camera>camera, std::shared_ptr<ScenePlay>stage)override {};//UIの入力を感知する関数
private:
	
	int chapter_ = 0;		//ストーリーのエピソード変数
	
	std::vector<std::vector<tnl::CsvCell>> story_csv;		//ストーリー格納CSV
	std::vector<std::vector<tnl::CsvCell>> story_gpc_csv;	//描画されるプレイヤーとMobキャラの情報CVS
	std::list<std::shared_ptr<Story>> story_one;							//ストーリーを格納したクラスポインタ
	std::list<std::shared_ptr<Story>>::iterator str;						//ストーリーのイテレーター	

	
	const tnl::Vector3 MOB_POS = { 320,180,0 };		//ストーリーのモブ位置
	const tnl::Vector3 PLAYER_POS = {960,540,0};	//ストーリーのプレイヤー位置
	const tnl::Vector3 BACKGROUND_POS = { 640,360,0 };//ストーリーの背景位置
	const tnl::Vector3 INSTRUCTION_POS = { 250,620,0 };//ボタン指示の座標

	
	int story_gpc_hdl = 0;						//会話画面の背景ハンドル
	int right_chara_gpc_hdl = 0;				//ストーリーのプレイヤー画像ハンドル
	int left_chara_gpc_hdl = 0;					//ストーリーのMOB画像ハンドル
	int select_sound_hdl;						//会話を進めるサウンド
	
	const int STORY_FONT_SIZE = 30;				//文字サイズ
	const float FLASHINTIME = 30.0f;			// 文字の点滅時間
	float flashing_time_cont_ = 0;				// 点滅時間のカウント変数
	bool flash_draw_ = true;						// 描画フラグ

};