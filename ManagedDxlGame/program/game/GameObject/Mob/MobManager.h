#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../GameObjectManager.h"

class Stage;
class Camera;
class Gimmick;
class Player;
class Mob;
class Enemy;

//-------------------------------------------------------------------------------------------------//
//ストーリーを持つキャラクターの生成クラス
// ※Factoryクラスを実装したかった
//-------------------------------------------------------------------------------------------------//
class MobManager final:public GameObjectManager
{
public:
	MobManager(int stage_id);
	~MobManager()override;
	void NewObject();
	void Update(float delta_time, const std::shared_ptr<Player>player)override;//Mobの更新関数
	void Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player)override;//Mobの描画関数
	void Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player,
		const std::list<std::shared_ptr<Gimmick>>& gimmick, const std::list<std::shared_ptr<Enemy>>& enemy, std::shared_ptr<Camera>camera)override;//Mobとの当たり判定更新の関数

	const std::list<std::shared_ptr<Mob>> &Getlist()const { return m_mob_move; }
private:
	std::vector<std::vector<tnl::CsvCell>> mob_csv;	//モブの情報のcsvハンドル
	std::list<std::shared_ptr<Mob>> m_mobs;							//待機中のMobのリストのポインタ
	std::list<std::shared_ptr<Mob>> m_mob_move;						//実行中のMobのリストのポインタ
	int mob_type_;									//Mobがチャプターいくつのストーリーを持つかを判定する変数
};