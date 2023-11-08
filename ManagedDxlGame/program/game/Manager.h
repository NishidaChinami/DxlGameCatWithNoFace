#pragma once
#include "../library/tnl_sequence.h"

class SceneBase;
//-------------------------------------------------------------------------------------------------//
//マネージャークラス

//-------------------------------------------------------------------------------------------------//
class GameManager {
public:
	static GameManager* GetInstance(std::shared_ptr<SceneBase>start_scene = nullptr);//マネージャーのインスタンス取得
	static void Destroy();//デストラクタ関数
	void ChangeScene(std::shared_ptr<SceneBase>next_scene, float trans_time = 0.5f);//シーン切り替え用の関数
	void Update(float delta_time);//マネージャーの更新関数

private:
	GameManager(std::shared_ptr<SceneBase>start_scene);
	//シーン切り替え用のポインタ変数
	std::shared_ptr<SceneBase>now_scene_ = nullptr;
	std::shared_ptr<SceneBase>next_scene_ = nullptr;

	int tansition_graph_hdl = 0;//フェードアウト用の黒画像のハンドル
	float trans_time_ = 0.5f;//フェードの速度変数

	tnl::Sequence<GameManager> sequence_ = tnl::Sequence<GameManager>(this, &GameManager::seqTransIn);//フェードインフェードアウト用
	bool seqTransIn(const float delta_time);//フェードイン
	bool seqTransOut(const float delta_time);//フェードアウト
	bool seqRunScene(const float delta_time);//待機状態

};