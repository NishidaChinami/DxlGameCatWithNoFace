#include "../dxlib_ext/dxlib_ext.h"
#include"Stage.h"
#include"../Camera/Camera.h"
#include"Mapchip.h"

Stage::Stage(int stage_id) {
	//�X�e�[�W�S���̃n���h��
	stage_csv = tnl::LoadCsv("csvfile/stage.csv");
	//�`�b�v�̉摜��256���ǂݍ���
	LoadDivGraph("graphics/TX Tileset Ground.png", 256, 16, 16, 32, 32, chip_hdl);
	LoadDivGraph("graphics/TX Village Props.png", 767,32, 24, 32, 32, chip_second_hdl_);
	for (int i = 1; i < stage_csv.size(); i++) {
		if (stage_id == stage_csv[i][0].getInt()) {
			csv_date = stage_csv[i][1].getString().c_str();//csv�}�b�v�`�b�v�P
			ornament_data = stage_csv[i][2].getString().c_str();//csv�}�b�v�`�b�v2
			Collition_date = stage_csv[i][3].getString().c_str();//csv�����蔻��
			stage_date = stage_csv[i][4].getString().c_str();//�摜��hdl
		}
	}
	//�e�n���h���ɓǂݍ���
	map_csv = tnl::LoadCsv<int>(csv_date.c_str());
	map_or_csv = tnl::LoadCsv<int>(ornament_data.c_str());
	Collition_csv = tnl::LoadCsv<int>(Collition_date.c_str());
	stage_gpc_hdl_ = LoadGraph(stage_date.c_str());

	//�}�b�v�`�b�v���̓ǂݎ���č��W������
	for (int i = 0; i < map_csv.size(); ++i) {
		for (int k = 0; k < map_csv[i].size(); ++k) {
			if (-1 == map_csv[i][k]) continue;
			if (256 < map_csv[i][k]) continue;

			tnl::Vector3 pos;
			int gpc_hdl;
			pos.x = { 16.0f + k * Mapchip::CHIP_SIZE };
			pos.y = { 100.0f + i * Mapchip::CHIP_SIZE };
			gpc_hdl = chip_hdl[map_csv[i][k]];
			blocks.emplace_back(new Mapchip(pos, gpc_hdl, 0));
		}
	}
	//��Ԗڂ̃`�b�v�摜�̃f�[�^
	for (int i = 0; i < map_or_csv.size(); ++i) {
		for (int k = 0; k < map_or_csv[i].size(); ++k) {
			if (-1 == map_or_csv[i][k]) continue;
			tnl::Vector3 pos;
			int gpc_hdl;
			pos.x = { 16.0f +k * Mapchip::CHIP_SIZE };
			pos.y = { 100.0f + i * Mapchip::CHIP_SIZE };
			gpc_hdl = chip_second_hdl_[map_or_csv[i][k]];
			blocks.emplace_back(std::make_shared<Mapchip>(pos, gpc_hdl, 0));
		}
	}
	//�}�b�v�`�b�v�̓����蔻��̓ǂݍ���
	for (int i = 0; i < Collition_csv.size(); ++i) {
		for (int k = 0; k < Collition_csv[i].size(); ++k) {
			if (0 == Collition_csv[i][k]) continue;
			tnl::Vector3 pos;
			int type;
			pos.x = { 16.0f + k * Mapchip::CHIP_SIZE };
			pos.y = { 100.0f + i * Mapchip::CHIP_SIZE };
			type = Collition_csv[i][k];
			Collitions.emplace_back(std::make_shared<Mapchip>(pos, 0, type));
		}
	}
}

Stage::~Stage() {

	DeleteGraph(stage_gpc_hdl_);
	for(int i = 0; i < 256; i++){
		DeleteGraph(chip_hdl[i]);
	}
	for (int i = 0; i < 767; i++) {
		DeleteGraph(chip_second_hdl_[i]);
	}
}


//�w�i�`�揈��
void Stage::MapDraw(const std::shared_ptr<Camera>camera) {
	tnl::Vector3 draw_pos_ = map_pos_ - (camera->GetCameraPos() * cam_weight_) + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	DrawRotaGraph(draw_pos_.x, draw_pos_.y, 1.0f, 0,stage_gpc_hdl_, true);
	for (auto chip : blocks) {
		chip->Mapchipdraw(camera);
	}
}

