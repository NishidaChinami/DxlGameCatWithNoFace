
#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Scene_Base.h"


class SaveLoad;
class UIOperation;

//-------------------------------------------------------------------------------------------------//
//Sceneの子クラス
// 
// タイトル画面のクラス
//-------------------------------------------------------------------------------------------------//
class SceneTitle final: public SceneBase {
public:
	SceneTitle();
	~SceneTitle()override;
	void Update(float delta_time)override;//タイトルシーンの更新関数
	void Draw()override;//タイトルシーンの描画関数

private:
	tnl::Sequence<SceneTitle> sequence_ = tnl::Sequence<SceneTitle>(this, &SceneTitle::seqIdle);//シーン遷移のテンプレート
	bool seqIdle(float delta_time);

	std::shared_ptr<SaveLoad>load = nullptr;
	std::shared_ptr<UIOperation>op = nullptr;
	//SaveLoad* load = nullptr;									//セーブクラスのポインタ
	//UIOperation* op = nullptr;									//UIの遊び方用のクラスポインタ
	
	int title_gpc_hdl = 0;										//タイトルの背景のグラフィックハンドル
	int title_movie_hdl;										//動画読み込みの描画ハンドル
	int title_screen_hdl;										//動画再生用の画像ハンドル
	int title_bgm_sound_hdl;									//タイトルBGMのサウンドハンドル
	int title_effect_sound_hdl;									//タイトルの選択音のサウンドハンドル
	int title_select_sound_hdl;									//タイトルの決定音のサウンドハンドル
	
	const tnl::Vector3 START_BUTTON_POS = {DXE_WINDOW_WIDTH>>1,500,0};	//タイトルの文字の基準位置
	const float TITLE_FONT_SIZE = 40;									//タイトルの文字のサイズ
	const static int BUTTON_NUM = 3;									//タイトルの文字の配列数
	const std::string start_button[BUTTON_NUM] = { "START","セーブから始める","遊び方" };//タイトルの選択項目
	const std::string chose_box = {"[＿＿＿＿＿＿＿＿]"};								//選択しているものを示す文字
	int chose_start_button_ = 0;															//タイトルボタンの選択を表す変数
	
};

