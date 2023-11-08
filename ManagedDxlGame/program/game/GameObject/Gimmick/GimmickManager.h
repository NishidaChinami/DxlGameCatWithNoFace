#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../GameObjectManager.h"

class Stage;
class Camera;
class Gimmick;
class Player;
class Enemy;

//-------------------------------------------------------------------------------------------------//
//ギミック生成クラス
// ※Factoryクラスのようにしたかった
//-------------------------------------------------------------------------------------------------//
class GimmickManager:public GameObjectManager
{
public:
	GimmickManager(int stage_id);
	~GimmickManager()override;
	void NewObject();
	void Update(float delta_time, const std::shared_ptr<Player>player)override;//ギミックの更新関数
	void Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player)override;//ギミックの描画関数
	void Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player, 
		const std::list<std::shared_ptr<Gimmick>>&gimmick, const std::list<std::shared_ptr<Enemy>>&enemy,std::shared_ptr<Camera>camera)override;//ギミックとの当たり判定更新の関数

	const std::list<std::shared_ptr<Gimmick>>& GetGimmickList()const { return m_gimmicks_move; }//ギミックの実行中リストポインタを返す関数
private:
	std::vector<std::vector<tnl::CsvCell>> gimmick_csv;	//ギミックのスポーン位置などのcsvハンドル
	int gimmick_move_type_ = 0;							//ギミックタイプを判別する変数
	std::list<std::shared_ptr<Gimmick>> m_gimmicks;						//待機中のギミッククラスのリストポインタ
	std::list<std::shared_ptr<Gimmick>> m_gimmicks_move;				//実行中のギミッククラスのリストポインタ
};	



