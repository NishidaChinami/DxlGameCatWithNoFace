#include "../dxlib_ext/dxlib_ext.h"
#include"Scene_title.h"
#include"Scene_play.h"
#include"Scene_Base.h"
#include"../Manager.h"
#include"../Etc/Save.h"
#include"../GameObject/UI/UI_operation.h"


SceneTitle::SceneTitle() {
	//画像ハンドルの読み込み
	title_gpc_hdl = LoadGraph("graphics/title.jpg");
	//タイトル動画読み込み
	title_movie_hdl = LoadGraph("movies/nc283871.mp4");
	//動画の画像サイズを取得
	int size_x = 0;
	int size_y = 0;
	GetGraphSize(title_movie_hdl, &size_x, &size_y);
	//動画と同サイズのスクリーンを作成(透明なピクセルを扱うため三つ目の引数はTRUE)
	title_screen_hdl = MakeScreen(size_x, size_y, TRUE);
	PlayMovieToGraph(title_movie_hdl, DX_MOVIEPLAYTYPE_NORMAL);
	//タイトルサウンド読み込み
	title_bgm_sound_hdl = LoadSoundMem("sound/title.mp3");
	title_effect_sound_hdl = LoadSoundMem("sound/enter.mp3");
	title_select_sound_hdl = LoadSoundMem("sound/enter.mp3");
	//タイトルBGMのループ再生
	PlaySoundMem(title_bgm_sound_hdl, DX_PLAYTYPE_LOOP);
	load = std::make_shared<SaveLoad>();
}

SceneTitle::~SceneTitle() {
	//各画像、サウンドのハンドルの消去
	DeleteGraph(title_gpc_hdl);
	DeleteGraph(title_movie_hdl);
	DeleteGraph(title_screen_hdl);
	DeleteSoundMem(title_bgm_sound_hdl);
	DeleteSoundMem(title_effect_sound_hdl);
	DeleteSoundMem(title_select_sound_hdl);
}

void SceneTitle::Update(float delta_time) {
	sequence_.Update(delta_time);
}
void SceneTitle::Draw() {
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1,1,0,title_gpc_hdl,true);
	// 動画再生
	GraphFilterBlt(title_movie_hdl, title_screen_hdl, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 50, true, GetColor(0, 0, 0), 0);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, title_screen_hdl, TRUE);
	//選択の描画
	SetFontSize(TITLE_FONT_SIZE);
	ChangeFont("g_コミックホラー恐怖-教漢", DX_CHARSET_DEFAULT);
	for (int i = 0; i < 3; i++) {
		//中央揃え
		int width = GetDrawStringWidth(start_button[i].c_str(), start_button[i].length()) / 2;
		DrawStringEx(START_BUTTON_POS.x -width, START_BUTTON_POS.y + i * 50, -1, "%s", start_button[i].c_str());
	}
	int width = GetDrawStringWidth(chose_box.c_str(), chose_box.length()) / 2;
	DrawStringEx(START_BUTTON_POS.x - width, START_BUTTON_POS.y + chose_start_button_ * 50, -1, "%s", chose_box.c_str());
	//遊び方が選択されたとき
	if (op) {
		op->Draw();
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)||
			(tnl::Input::IsPadDownTrigger(ePad::KEY_5))) {
			op = nullptr;
		}
	}
}

bool SceneTitle::seqIdle(float delta_time) {
	//タイトルの選択項目
	if (chose_start_button_ < 2) { 
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_S)||
			(tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN))) {
			chose_start_button_++;
			PlaySoundMem(title_effect_sound_hdl, DX_PLAYTYPE_BACK);
		}
	}
	if (chose_start_button_ > 0) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W)|| (tnl::Input::IsPadDownTrigger(ePad::KEY_UP))) {
			chose_start_button_--;
			PlaySoundMem(title_effect_sound_hdl, DX_PLAYTYPE_BACK);
		}
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)|| (tnl::Input::IsPadDownTrigger(ePad::KEY_0))) {
		//新しいゲーム
		if (0 == chose_start_button_) {
			load->NewGame();
			auto mgr = GameManager::GetInstance();
			mgr->ChangeScene(std::make_shared<ScenePlay>());
		}
		//ゲームの続きから
		if (1 == chose_start_button_) {
			auto mgr = GameManager::GetInstance();
			mgr->ChangeScene(std::make_shared<ScenePlay>());
		}
		if (2 == chose_start_button_) {
			if (!op)op = std::make_shared<UIOperation>();
		}
		//選択音
		PlaySoundMem(title_select_sound_hdl, DX_PLAYTYPE_BACK);
	}
	return true;
}

