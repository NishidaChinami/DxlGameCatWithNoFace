#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../GameObjectManager.h"

class Stage;
class Camera;
class Gimmick;
class Player;
class Enemy;
class SaveLoad;

//-------------------------------------------------------------------------------------------------//
//プレイヤー生成クラス
// 
//-------------------------------------------------------------------------------------------------//
class PlayerManager final: public GameObjectManager{
public:
	PlayerManager(const std::shared_ptr<SaveLoad>save);
	~PlayerManager()override;
	void Update(float delta_time, const std::shared_ptr<Player>player)override;//プレイヤー更新関数
	void Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player)override;//プレイヤー描画関数
	void Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player,
		const std::list<std::shared_ptr<Gimmick>>&gimmick, const std::list<std::shared_ptr<Enemy>>&enemy,std::shared_ptr<Camera>camera)override;//プレイヤーとの当たり判定を更新する関数

	std::shared_ptr<Player>GetPlayer() { return m_player; }//プレイヤークラスポインタのアクセス権限を渡す関数
private:
	std::shared_ptr<Player>m_player = nullptr;//プレイヤーのクラスポインタ
};
