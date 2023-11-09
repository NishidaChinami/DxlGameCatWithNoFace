#include "../dxlib_ext/dxlib_ext.h"
#include"UI_setting.h"
#include"../game/Etc/Save.h"
#include"../Camera/Camera.h"
#include"../Player/Player.h"
#include"../game/Scene/Scene_play.h"

UISetting::UISetting()
{
	setting_bg_hdl = LoadGraph("graphics/setting_box.jpg");
	bar_gpc_hdl =  LoadGraph("graphics/bar_sound.png");
	progress_gpc_hdl = LoadGraph("graphics/sound_pin.png");
	option_gpc_hdl = LoadGraph("graphics/item.png");
	select_sound_hdl = LoadSoundMem("sound/enter.mp3");

}

UISetting::~UISetting()
{
	DeleteGraph(setting_bg_hdl);
	DeleteGraph(bar_gpc_hdl);
	DeleteGraph(progress_gpc_hdl);
	DeleteGraph(option_gpc_hdl);
	DeleteSoundMem(select_sound_hdl);
}

void UISetting::Draw() {
	//設定の描画
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0.5, 0, setting_bg_hdl, true);
	DrawRotaGraph(OPTION_POS.x, OPTION_POS.y + 100* chose_item_button_, 0.5, 0, option_gpc_hdl, true);
	DrawRotaGraph(BAR_POS.x, BAR_POS.y, 1, 0, bar_gpc_hdl, true);
	DrawRotaGraph(PROGRESS_POS.x +volume_progress_, PROGRESS_POS.y, 1, 0, progress_gpc_hdl, true);
	DrawRotaGraph(BAR_POS.x, BAR_POS.y+100, 1, 0, bar_gpc_hdl, true);
	DrawRotaGraph(PROGRESS_POS.x +brightness_progress_, PROGRESS_POS.y+100, 1, 0, progress_gpc_hdl, true);
	SetFontSize(SETTING_FONT_SIZE);
	ChangeFont("g_コミックホラー恐怖-教漢", DX_CHARSET_DEFAULT);
	for (int i = 0; i <4 ; i++) {
		DrawStringEx(ITEM_POS.x, ITEM_POS.y + i * 100, -1, "%s", setting_item[i].c_str());
	}
}

void UISetting::Input(std::shared_ptr<SaveLoad>save, std::shared_ptr<Player>player, const std::shared_ptr<Camera>camera, std::shared_ptr<ScenePlay>stage) {
	//設定項目の選択
	if (chose_item_button_ < 3) { 
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_S)||
			(tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN))) {
			chose_item_button_++;
			PlaySoundMem(select_sound_hdl, DX_PLAYTYPE_BACK);
		}
	}
	if (chose_item_button_ > 0) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W)||
			(tnl::Input::IsPadDownTrigger(ePad::KEY_UP))) {
			chose_item_button_--;
			PlaySoundMem(select_sound_hdl, DX_PLAYTYPE_BACK);
		}
	}
	//音量調整
	if (0 == chose_item_button_) {
		if (volume_progress_ < 255) { 
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)||
				(tnl::Input::IsPadDownTrigger(ePad::KEY_RIGHT)))
			volume_progress_ += volume_unit;
		}
		if (volume_progress_ > 0) { if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)||
			(tnl::Input::IsPadDownTrigger(ePad::KEY_LEFT)))volume_progress_ -= volume_unit; }
		ChangeVolumeSoundMem(volume_progress_, stage->GetSoundHdl());
	}
	//明るさ調整
	else if (1 == chose_item_button_) {
		if (brightness_progress_ < 255) { 
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)||
				(tnl::Input::IsPadDownTrigger(ePad::KEY_RIGHT)))
				brightness_progress_+= brightness_unit_; }
		if (brightness_progress_ > 0) { if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)||
			(tnl::Input::IsPadDownTrigger(ePad::KEY_LEFT)))
			brightness_progress_ -= brightness_unit_; }
		SetDrawBright(brightness_progress_, brightness_progress_, brightness_progress_);
	}

	else if (2 == chose_item_button_) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)|| (tnl::Input::IsPadDownTrigger(ePad::KEY_0))) {
			PlaySoundMem(select_sound_hdl, DX_PLAYTYPE_BACK);
			save->Save(player,camera,stage);
			stage->GetTitleFlug() = true;
		}
	}
}