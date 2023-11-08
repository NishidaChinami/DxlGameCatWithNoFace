#include "../dxlib_ext/dxlib_ext.h"
#include"GimmickManager.h"
#include"Gimmick.h"
#include"../GameObjectManager.h"
#include"../Player/Player.h"
#include"../Camera/Camera.h"
#include"../Stage/Stage.h"
#include"Gimmick_box.h"
#include"Gimmick_floor.h"
#include"Gimmick_rope.h"

GimmickManager::GimmickManager(int stage_id):GameObjectManager(2)
{
	stage_id_ = stage_id;
	gimmick_csv = tnl::LoadCsv("csvfile/map_gimmick.csv");
	NewObject();
}

GimmickManager::~GimmickManager()
{
}
void GimmickManager::NewObject() {
	//csv‚©‚çŠe—v‘f‚ð‘ã“ü
	for (int i = 1; i < gimmick_csv.size(); ++i) {
		if (stage_id_ == gimmick_csv[i][0].getInt()) {
			tnl::Vector3 pos;
			float w_size;
			float h_size;
			gimmick_move_type_ = gimmick_csv[i][1].getInt();
			pos.x = gimmick_csv[i][2].getFloat();
			pos.y = gimmick_csv[i][3].getFloat();
			w_size = gimmick_csv[i][4].getFloat();
			h_size = gimmick_csv[i][5].getFloat();
			//“®‚©‚¹‚é” 
			if (0 == gimmick_move_type_) {
				m_gimmicks.emplace_back(new GimmickBox(gimmick_move_type_,pos, w_size, h_size));
			}
			//“®‚­°
			if (1 == gimmick_move_type_) {
				m_gimmicks.emplace_back(new GimmickFloor(gimmick_move_type_, pos, w_size, h_size));
			}
			//U‚èŽq
			if (2 == gimmick_move_type_) {
				m_gimmicks.emplace_back(new GimmickRope(gimmick_move_type_, pos, w_size, h_size));
			}
		}
			
	}
	
}
void GimmickManager::Update(float delta_time, const std::shared_ptr<Player>player) {
	//•`‰æ”ÍˆÍ‚Ì‚Q”{æ‚É“ü‚Á‚½‚ç‘Ò‹@’†ƒŠƒXƒg‚©‚çŽÀs’†ƒŠƒXƒg‚Ö
	auto it = m_gimmicks.begin();
	while (it != m_gimmicks.end()) {
		if ((*it)->GetGimmickDrawPos().x < DXE_WINDOW_WIDTH * 2) {
			m_gimmicks_move.emplace_back(*it);
			it = m_gimmicks.erase(it);
			break;
		}
		it++;
	}

	for (auto mv : m_gimmicks_move) {
		mv->Move(delta_time, player);
	}
}
void GimmickManager::Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player) {
	for (auto mv : m_gimmicks_move) {
		mv->Draw(camera);
	}
}
void GimmickManager::Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player, const std::list<std::shared_ptr<Gimmick>> &gimmick, const std::list<std::shared_ptr<Enemy>>&enemy, std::shared_ptr<Camera>camera) {
	for (auto mv : m_gimmicks_move) {
		mv->Hit(stage->Getlist(), player);
	}
}