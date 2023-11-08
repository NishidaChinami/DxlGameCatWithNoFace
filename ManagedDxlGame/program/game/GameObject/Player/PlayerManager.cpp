#include "../dxlib_ext/dxlib_ext.h"
#include"PlayerManager.h"
#include"../GameObjectManager.h"
#include"../game/Scene/Scene_play.h"
#include"../Enemy/Enemy.h"
#include"../Camera/Camera.h"
#include"../Stage/Stage.h"
#include"../Player/Player.h"


PlayerManager::PlayerManager(const std::shared_ptr<SaveLoad>save):GameObjectManager(0)
{
	if (!m_player)m_player = std::make_shared<Player>(save);
}

PlayerManager::~PlayerManager()
{

}
void PlayerManager::Update(float delta_time, const std::shared_ptr<Player>player) {
	if(m_player)m_player->Update(delta_time);
}
void PlayerManager::Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player) {
	if (m_player)m_player->Draw(camera);
}
void PlayerManager::Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player, const std::list<std::shared_ptr<Gimmick>> &gimmick, const std::list<std::shared_ptr<Enemy>>&enemy,std::shared_ptr<Camera>camera) {
	if (m_player) {
		m_player->Hit(stage->Getlist(),camera);
		m_player->GimmickHit(gimmick);
		m_player->EnemyHit(enemy,camera);
	}
}