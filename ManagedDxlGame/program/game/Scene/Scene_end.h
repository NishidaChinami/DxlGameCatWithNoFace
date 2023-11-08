#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Scene_Base.h"

//-------------------------------------------------------------------------------------------------//
//Sceneの子クラス
// 
// ゲームクリア後のストーリー描画クラス
//-------------------------------------------------------------------------------------------------//
class SceneEnd final: public SceneBase
{
public:
	SceneEnd();
	~SceneEnd()override;
	void Update(float delta_time)override;//エンディングの更新関数
	void Draw()override;//エンディングの描画関数
	bool EndingDraw(const float delta_time);//エンディングのコルーチン用描画関数
	
	TNL_CO_SEQUENCE(SceneEnd, &SceneEnd::EndingDraw);
	tnl::Sequence<SceneEnd> seq_ = tnl::Sequence<SceneEnd>(this, &SceneEnd::EndingDraw);	//エンディングストーリの文章のコルーチン
private:
	tnl::Sequence<SceneEnd> sequence_ = tnl::Sequence<SceneEnd>(this, &SceneEnd::seqTitle);//シーン遷移の関数
	bool seqTitle(float delta_time);
	
	int end_gpc_hdl = 0;																//エンディングの背景のグラフィックハンドル
	int end_cat_gpc_hdl = 0;															//エンディングのプレイヤー画像ハンドル
	int end_movie_hdl;																	//動画保存用ハンドル
	int end_screen_hdl;																	//動画再生の描画ハンドル
	int end_bgm_sound_hdl;																//エンディングのBGMハンドル
	int end_effect_sound_hdl;															//エンディングの効果音のハンドル
	std::vector<std::vector<tnl::CsvCell>> end_story_csv;								//エンディングストーリーを格納したCSV
	std::vector<std::string> endingstory;												//エンディングの文の変数
	const tnl::Vector3 ENDING_POS = { DXE_WINDOW_WIDTH >> 1 ,DXE_WINDOW_HEIGHT>>1,0 };	//文字の描画座標
	bool title_return_ = false;															//ending終わりのフラグ
	const int ENDING_FONT_SIZE = 50;													//エンディング文字サイズ(普)
	const int HORROR_FONST_SIZE = 150;													//エンディング文字サイズ(大)
};

