#include "../dxlib_ext/dxlib_ext.h"
#include"MobManager.h"
#include"../GameObjectManager.h"
#include"../Player/Player.h"
#include"../Camera/Camera.h"
#include"../Stage/Stage.h"
#include"../Gimmick/Gimmick.h"
#include"Mob.h"

MobManager::MobManager(int stage_id) :GameObjectManager(3) {
	stage_id_ = stage_id;
	mob_csv = tnl::LoadCsv("csvfile/map_mob.csv");
	NewObject();
}
MobManager::~MobManager()
{

}

void MobManager::NewObject() {
	for (int i = 1; i < mob_csv.size(); ++i) {
		if (stage_id_ == mob_csv[i][0].getInt()) {
			tnl::Vector3 pos;
			float size;
			int gpc_hdl;
			mob_type_ = mob_csv[i][1].getInt();
			pos.x = mob_csv[i][2].getFloat();
			pos.y = mob_csv[i][3].getFloat();
			size = mob_csv[i][4].getFloat();
			gpc_hdl = LoadGraph(mob_csv[i][5].getString().c_str());
			m_mobs.emplace_back(new Mob(mob_type_, pos, size, gpc_hdl));
		}

	}
}

//待機してるリストと動いてるリスト
void MobManager::Update(float delta_time, const std::shared_ptr<Player>player) {
	auto it = m_mobs.begin();
	while (it != m_mobs.end()) {
		if ((*it)->GetMobDrawPos().x < DXE_WINDOW_WIDTH * 2) {
			m_mob_move.emplace_back(*it);
			it = m_mobs.erase(it);
			break;
		}
		it++;
		
	}

	for (auto mv : m_mob_move) {
		mv->Update(delta_time);
		mv->Collition(player);
	}
}
void MobManager::Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player) {

	for (auto mv : m_mob_move) {
		mv->Draw(camera);
	}
}
void MobManager::Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player, 
	const std::list<std::shared_ptr<Gimmick>>&gimmick, const std::list<std::shared_ptr<Enemy>>&enemy, std::shared_ptr<Camera>camera) {
}