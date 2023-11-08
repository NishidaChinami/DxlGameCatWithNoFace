#include "../dxlib_ext/dxlib_ext.h"
#include"EnemyManager.h"
#include"../GameObjectManager.h"
#include"../Player/Player.h"
#include"../Camera/Camera.h"
#include"../Stage/Stage.h"
#include"../Gimmick/Gimmick.h"
#include "Enemy_track.h"
#include"Enemy_Daruma.h"
#include"Enemy_Patrol.h"
#include"Enemy_boss.h"
#include"../Stage/Mapchip.h"

EnemyManager::EnemyManager(int stage_id) :GameObjectManager(1) {
	stage_id_ = stage_id;
	enemy_csv = tnl::LoadCsv("csvfile/map_enemy.csv");
	NewObject();
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::NewObject() {
	for (int i = 1; i < enemy_csv.size(); ++i) {
		if (stage_id_ == enemy_csv[i][0].getInt()) {
			tnl::Vector3 pos;
			float size;
			std::string gpc_hdl;
			enemy_move_type_ = enemy_csv[i][1].getInt();
			pos.x = enemy_csv[i][2].getFloat();
			pos.y = enemy_csv[i][3].getFloat();
			size = enemy_csv[i][4].getFloat();
			//追跡型
			if (0 == enemy_move_type_) {
				m_enemys.emplace_back(std::make_shared<EnemyTrack>(pos, size));
			}
			//巡回型
			if (1 == enemy_move_type_) {
				m_enemys.emplace_back(std::make_shared<EnemyPatrol>(pos, size));
			}
			//だるまさん型
			if (2 == enemy_move_type_) {
				m_enemys.emplace_back(std::make_shared<EnemyDaruma>(pos, size));
			}
			//ボス
			if (3 == enemy_move_type_) {
				m_enemys.emplace_back(std::make_shared<EnemyBoss>(pos, size));
			}
		}

	}
}


void EnemyManager::Update(float delta_time, const std::shared_ptr<Player>player) {
	//画面内に入ったら待機中リストから実行中リストへ
	auto it = m_enemys.begin();
	while (it != m_enemys.end()) {
		if ((*it)->GetEnemyDrawPos().x < DXE_WINDOW_WIDTH) {
			m_enemys_move.emplace_back(*it);
			it = m_enemys.erase(it);
			break;
		}
		it++;
	}

	for (auto mv : m_enemys_move) {
		mv->GetBossAttack() = false;
		mv->Move(delta_time,player);
	}
}
void EnemyManager::Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player) {
	for (auto m : m_enemys) {
		m->Draw(camera);
	}
	for (auto mv : m_enemys_move) {
		mv->Draw(camera);
	}
}
void EnemyManager::Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player, 
	const std::list<std::shared_ptr<Gimmick>> &gimmick, const std::list<std::shared_ptr<Enemy>>&enemy, std::shared_ptr<Camera>camera) {
	auto mv = m_enemys_move.begin();
	while (mv != m_enemys_move.end()) {
		//床と当たり判定が必要な子に限り
		(*mv)->Hit(stage->Getlist(), player);
		//死んだら待機中へ
		if (player->GetPlayerDeath()) {
			(*mv)->SetEnemyPos((*mv)->GetStartPos());
			m_enemys.emplace_back(*mv);
			mv = m_enemys_move.erase(mv);
			break;
		}
		mv++;
	}
}
