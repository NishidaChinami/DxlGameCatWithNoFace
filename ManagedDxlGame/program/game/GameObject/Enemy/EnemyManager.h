#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy.h"
#include"../GameObjectManager.h"


class Stage;
class Camera;
class Gimmick;
class Player;
class Mapchip;
class Enemy;


//-------------------------------------------------------------------------------------------------//
//エネミー作成クラス
// 
//※Factoryのように実装したかった
//-------------------------------------------------------------------------------------------------//
class EnemyManager final:public GameObjectManager
{
public:
	EnemyManager(int stage_id);
	~EnemyManager()override;
	void NewObject();
	void Update(float delta_time, const std::shared_ptr<Player>player)override;//敵の更新
	void Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player)override;//敵の描画関数
	void Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player, 
		const std::list<std::shared_ptr<Gimmick>>&gimmick, const std::list<std::shared_ptr<Enemy>>&enemy,std::shared_ptr<Camera>camera)override;//敵の当たり判定更新の関数
	
	const std::list<std::shared_ptr<Enemy>>& GetEnemylist()const { return m_enemys_move; }//Enemyクラスにアクセスする用のGetter
private:
	std::vector<std::vector<tnl::CsvCell>> enemy_csv;	//enemy情報のcsvハンドル
	std::list<std::shared_ptr<Enemy>> m_enemys;		//待機中の敵のリストポインタ
	std::list<std::shared_ptr<Enemy>> m_enemys_move;	//実行中の敵のリストポインタ
	int enemy_move_type_ = 0;							//敵の種類を判別する変数
};

