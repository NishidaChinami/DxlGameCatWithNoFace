#pragma once
class Camera;
class Player;
class Enemy;
class Gimmick;
class Stage;


//-------------------------------------------------------------------------------------------------//
//GameObjectのポリモフィズム用抽象クラス
//-------------------------------------------------------------------------------------------------//
class GameObjectManager {
public:
	GameObjectManager(){}
	GameObjectManager(int type) { actorType_ = type; }
	virtual~GameObjectManager() {};
	virtual void Update(float delta_time, const std::shared_ptr<Player>player) {};//オブジェクトの更新
	virtual void Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player) {};//オブジェクトの描画関数

	//当たり判定を取る関数
	
	
	// arg1...ステージ座標を読み取り
	// arg2...プレイヤーの座標、サイズの読み取り
	// arg3...マップチップの座標、サイズの読み取り
	// arg4...エネミーの座標、サイズの読み取り
	// arg5...カメラ座標の読み取り
	virtual void Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player,
		const std::list<std::shared_ptr<Gimmick>>&gimmick, const std::list<std::shared_ptr<Enemy>>&enemy,std::shared_ptr<Camera>camera) {};//オブジャクトの当たり判定
	
	int GetActType()const { return actorType_; }//オブジェクトの判別をするGetter
protected:
	int stage_id_ = 0;//ステージID
private:
	int actorType_ = 0;//オブジャクトが何かを判別する変数(0:player,1:enemy 2:gimmick3:mob) 

};