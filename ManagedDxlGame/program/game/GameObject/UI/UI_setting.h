#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"UI.h"

class SaveLoad;
class Player;
class Camera;
class ScenePlay;

//-------------------------------------------------------------------------------------------------//
//UIの子クラス
// 
// プレイ画面の設定UI描画、入力クラス
//-------------------------------------------------------------------------------------------------//
class UISetting final: public UI
{
public:
	UISetting();
	~UISetting()override;
	void Draw()override;//設定画面の描画関数

	//設定画面の入力関数
	// arg1...Save関数呼び出し
	// arg2...使用なし
	// arg3...使用なし
	// arg4...タイトルに戻るフラグ
	void Input(std::shared_ptr<SaveLoad>save, std::shared_ptr<Player>player, const std::shared_ptr<Camera>camera, std::shared_ptr<ScenePlay>stage)override;
private:
	//設定に使う画像

	int setting_bg_hdl = 0;			//背景画像のハンドル
	int bar_gpc_hdl = 0;			//バーの画像ハンドル
	int progress_gpc_hdl = 0;		//動くピンの画像ハンドル
	int option_gpc_hdl = 0;			//カーソルの画像ハンドル
	
	int volume_progress_ = 255;		//音量の初期値
	int brightness_progress_ = 255;	//明るさの初期値
	int volume_unit = 20;			//音量の一メモリの単位
	int brightness_unit_ = 20;		//明るさの一メモリの単位
	
	const std::string setting_item[4] = { "音量","画面の明るさ","セーブしてゲームを終わる","ESCでゲームにもどる"};//選択項目
	const tnl::Vector3 OPTION_POS = {300,180,0};								//選択しているものを示すが画像の初期位置
	const tnl::Vector3 BAR_POS = { 800,180,0 };									//バーの画像の位置
	const tnl::Vector3 PROGRESS_POS = { 680,180,0 };							//プログレスの画像の位置
	const tnl::Vector3 ITEM_POS = {320,180,0};									//設定の選択項目の基準位置
	const int SETTING_FONT_SIZE = 30;											//設定の文字のサイズ
	int chose_item_button_ = 0;													//設定項目を選択する変数
	int select_sound_hdl;														//選択するときのサウンドハンドル

};

