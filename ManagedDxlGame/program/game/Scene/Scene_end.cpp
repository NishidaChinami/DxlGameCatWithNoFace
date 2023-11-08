#include"Scene_end.h"
#include "../dxlib_ext/dxlib_ext.h"
#include"Scene_title.h"
#include"Scene_Base.h"
#include"../Manager.h"

SceneEnd::SceneEnd()
{
	//画像ハンドルの読み込み
	end_gpc_hdl = LoadGraph("graphics/end.jpg");
	//猫の画像ハンドル読み込み
	end_cat_gpc_hdl = LoadGraph("graphics/endingneko.png");
	//タイトル動画読み込み
	end_movie_hdl = LoadGraph("movies/ending.mp4");
	//動画の画像サイズを取得
	int size_x = 0;
	int size_y = 0;
	GetGraphSize(end_movie_hdl, &size_x, &size_y);
	//動画と同サイズのスクリーンを作成(透明なピクセルを扱うため三つ目の引数はTRUE)
	end_screen_hdl = MakeScreen(size_x, size_y, TRUE);
	PlayMovieToGraph(end_movie_hdl, DX_MOVIEPLAYTYPE_NORMAL);
	//エンディングサウンド読み込み
	end_bgm_sound_hdl = LoadSoundMem("sound/ending.mp3");
	end_effect_sound_hdl = LoadSoundMem("sound/4nyaa.wav");
	//エンディングBGMのループ再生
	PlaySoundMem(end_bgm_sound_hdl, DX_PLAYTYPE_LOOP);

	//ストーリーcsvのハンドル
	end_story_csv = tnl::LoadCsv("csvfile/endingstory.csv");
	for (int i = 1; i < end_story_csv.size(); ++i) {
		std::string story;
		story = end_story_csv[i][0].getString().c_str();
		endingstory.emplace_back(story);
	}
}

SceneEnd::~SceneEnd()
{
	//各画像、サウンドのハンドルの消去
	DeleteGraph(end_gpc_hdl);
	DeleteGraph(end_movie_hdl);
	DeleteGraph(end_screen_hdl);
	DeleteGraph(end_cat_gpc_hdl);
	DeleteSoundMem(end_bgm_sound_hdl);
	DeleteSoundMem(end_effect_sound_hdl);
}

void SceneEnd::Draw() {
	// 動画再生
	GraphFilterBlt(end_movie_hdl, end_screen_hdl, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 50, true, GetColor(0, 0, 0), 0);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_WIDTH, end_screen_hdl, TRUE);
	//選択の描画
	SetFontSize(ENDING_FONT_SIZE);
}
void SceneEnd::Update(float delta_time) {
	//シーン遷移のアップデート
	sequence_.Update(delta_time);
	tnl_sequence_.Update(delta_time);
}
bool SceneEnd::seqTitle(float delta_time) {
	if (title_return_) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)
			||(tnl::Input::IsPadDownTrigger(ePad::KEY_0))) {
			auto mgr = GameManager::GetInstance();
			mgr->ChangeScene(std::make_shared<SceneTitle>());
			title_return_ = false;
		}
	}
	return true;
}

bool SceneEnd::EndingDraw(float delta_time) {
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 1, 0, end_gpc_hdl, true);
	SetFontSize(ENDING_FONT_SIZE);
	//ChangeFont("g_コミックホラー恐怖-教漢", DX_CHARSET_DEFAULT);
	ChangeFont("怨霊", DX_CHARSET_DEFAULT);
	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]() {});
	for (int i = 0; i < (endingstory.size()- 2); ++i) {
		TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]() {
			int width = GetDrawStringWidth(endingstory[i].c_str(), endingstory[i].length()) / 2;
			DrawStringEx(ENDING_POS.x - width, DXE_WINDOW_HEIGHT >> 1, -1, "%s", endingstory[i].c_str());
		});
	}
	TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]() {});
	TNL_SEQ_CO_FRM_YIELD_RETURN(1, delta_time, [&]() {	
		ChangeVolumeSoundMem(150,end_bgm_sound_hdl);
		PlaySoundMem(end_effect_sound_hdl, DX_PLAYTYPE_BACK);
		});
	TNL_SEQ_CO_TIM_YIELD_RETURN(4, delta_time, [&]() {
		DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 1, 0, end_cat_gpc_hdl, true);
		SetFontSize(HORROR_FONST_SIZE);
		ChangeFont("怨霊", DX_CHARSET_DEFAULT);
		int width = GetDrawStringWidth(endingstory[6].c_str(), endingstory[6].length()) / 2;
		DrawStringEx(ENDING_POS.x - width, DXE_WINDOW_HEIGHT >> 1, 0xFFFF0000, "%s", endingstory[6].c_str());
	});
	TNL_SEQ_CO_TIM_YIELD_RETURN(100, delta_time, [&]() {
		SetFontSize(ENDING_FONT_SIZE);
		int width = GetDrawStringWidth(endingstory[7].c_str(), endingstory[7].length()) / 2;
		DrawStringEx(ENDING_POS.x - width, DXE_WINDOW_HEIGHT >> 1, -1, "%s", endingstory[7].c_str());
		title_return_ = true;
	});

	TNL_SEQ_CO_END;
}
