#include "../dxlib_ext/dxlib_ext.h"
#include"Save.h"
#include"../GameObject/Player/Player.h"
#include"../GameObject/Camera/Camera.h"
#include"../Scene/Scene_play.h"
SaveLoad::SaveLoad()
{
	player_save_pos_ = START_POS;
}
//ゲームセーブ
void SaveLoad::Save(std::shared_ptr<Player>player, const std::shared_ptr<Camera>camera,std::shared_ptr<ScenePlay>stage) {
	player_save_pos_ = player->GetSavePlayerPos();
	camera_save_pos_ = player->Getsavepos();
	save_stage_ = stage->GetStageType();
	
	FILE* fp = nullptr;
	fopen_s(&fp, "save.bin", "wb");
	if (fp) {
		fwrite(&player_save_pos_, sizeof(tnl::Vector3), 1, fp);
		fwrite(&camera_save_pos_, sizeof(tnl::Vector3), 1, fp);
		fwrite(&save_stage_, sizeof(int), 1, fp);
		fclose(fp);
	}
}
//ゲームのロード
void SaveLoad::Load() {
	FILE* fp = nullptr;
	fopen_s(&fp, "save.bin", "rb");
	if (fp) {
		fread(&player_save_pos_, sizeof(tnl::Vector3), 1, fp);
		fread(&camera_save_pos_, sizeof(tnl::Vector3), 1, fp);
		fread(&save_stage_, sizeof(int), 1, fp);
		fclose(fp);
	}
}
//セーブデータリセット
void SaveLoad::NewGame() {
	player_save_pos_ = START_POS;
	camera_save_pos_ = {0,0,0};
	save_stage_ =1;
	FILE* fp = nullptr;
	fopen_s(&fp, "save.bin", "wb");
	if (fp) {
		fwrite(&player_save_pos_, sizeof(tnl::Vector3), 1, fp);
		fwrite(&camera_save_pos_, sizeof(tnl::Vector3), 1, fp);
		fwrite(&save_stage_, sizeof(int), 1, fp);
		fclose(fp);
	}
}