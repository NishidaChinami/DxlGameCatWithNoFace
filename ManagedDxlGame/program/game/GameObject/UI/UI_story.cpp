#include "../dxlib_ext/dxlib_ext.h"
#include"UI_story.h"
#include"Story.h"

UIStory::UIStory(int chapter)
{
	chapter_ = chapter;
	//ストーリーcsvのハンドル
	story_csv = tnl::LoadCsv("csvfile/story.csv");
	//ストーリーのUI画像
	story_gpc_csv = tnl::LoadCsv("csvfile/UI_gpc.csv");
	//ストーリー背景
	story_gpc_hdl = LoadGraph("graphics/storyBackground.jpg");

	//ストーリーのキャラクターが右の画像ハンドルか左の画像ハンドルに入るかを決定
	for (int i = 1; i < story_gpc_csv.size(); ++i) {
		if (chapter_ == story_gpc_csv[i][0].getInt()) {
			int side = story_gpc_csv[i][1].getInt();
			if (0 == side)right_chara_gpc_hdl = LoadGraph(story_gpc_csv[i][2].getString().c_str());
			if (1 == side)left_chara_gpc_hdl = LoadGraph(story_gpc_csv[i][2].getString().c_str());
		}
	}
	//ストーリークラスのリストポインタに情報を格納
	for (int i = 1; i < story_csv.size(); ++i) {
		if (chapter_ == story_csv[i][0].getInt()) {
			std::string story;
			int side;
			bool active_;
			side = story_csv[i][1].getInt();
			story = story_csv[i][2].getString().c_str();
			active_ = story_csv[i][3].getBool();
			story_one.emplace_back(std::make_shared<Story>(side, story, active_));
		}

	}
	//ストーリーリストの最初のイテレーターを作成
	str = story_one.begin();
	//選択音サウンドの読み込み
	select_sound_hdl = LoadSoundMem("sound/next.mp3");
}

UIStory::~UIStory()
{
	DeleteGraph(story_gpc_hdl);
	DeleteGraph(right_chara_gpc_hdl);
	DeleteGraph(left_chara_gpc_hdl);
	DeleteSoundMem(select_sound_hdl);
	
}
void UIStory::Draw() {
	DrawRotaGraph(BACKGROUND_POS.x, BACKGROUND_POS.y, 1, 0, story_gpc_hdl, true);
	DrawRotaGraph(PLAYER_POS.x, PLAYER_POS.y, 1, 0, right_chara_gpc_hdl, true);
	DrawRotaGraph(MOB_POS.x, MOB_POS.y, 1, 0, left_chara_gpc_hdl, true);
	SetFontSize(STORY_FONT_SIZE);
	ChangeFont("怨霊", DX_CHARSET_DEFAULT);
	flashing_time_cont_++;
	if (flashing_time_cont_ > FLASHINTIME) {
		flash_draw_ = !flash_draw_;
		flashing_time_cont_ = 0;
	}
	if (flash_draw_) {
		if (GetJoypadNum() == 1) { DrawStringEx(INSTRUCTION_POS.x, INSTRUCTION_POS.y, -1, "Xで進む"); }
		else { DrawStringEx(INSTRUCTION_POS.x, INSTRUCTION_POS.y, -1, "Eで進む"); }
	}
	if(str != story_one.end()) {
		(*str)->Draw();
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_E)||
			(tnl::Input::IsPadDownTrigger(ePad::KEY_2))) {
			if ((*str)->Getactive_()) {
				(*str)->SetLetterCount(0);
				str++;	
			}
			else  {
				invisible_ = true;
			}
			PlaySoundMem(select_sound_hdl, DX_PLAYTYPE_BACK);
		}
	}
	
}



