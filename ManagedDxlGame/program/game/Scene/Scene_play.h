#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Scene_Base.h"
#include"../GameObject/Stage/Stage.h"

class GameObjectManager;
class PlayerManager;
class GimmickManager;
class MobManager;
class EnemyManager;
class Stage;
class Camera;
class UIManager;
class SaveLoad;
class SceneTitle;
//-------------------------------------------------------------------------------------------------//
//Sceneの子クラス
// 
// プレイ画面のクラス
//-------------------------------------------------------------------------------------------------//
class ScenePlay final : public SceneBase, public std::enable_shared_from_this<ScenePlay> {
public:
	//ステージタイプ
	enum class STAGETYPE {
		STAGE,
		STAGE_1,
		STAGE_2,
		STAGE_3,
		STAGE_4,
		MAX
	};

	ScenePlay();
	~ScenePlay()override;
	void Update(float delta_time)override;//プレイシーンの更新関数
	void Draw()override {};			//プレイシーンの描画関数
	void ChangeStage();				//ステージ更新の判定をする関数
	void NewStage(int stage_id);	//新しいステージを読み込む関数

	int GetStageType() {return static_cast<int>(stage_id_);}//ステージIDをint型で返す関数
	bool &GetTitleFlug() {return title_back;}//タイトルの戻るかのフラグを渡す関数
	int GetSoundHdl()const {return play_bgm_sound_hdl;}//BGMハンドルを渡す関数
private:
	tnl::Sequence<ScenePlay> sequence_ = tnl::Sequence<ScenePlay>(this, &ScenePlay::seqResult);//シーン遷移用のテンプレート
	bool seqResult(float delta_time);
	bool title_back = false;//タイトルの戻るかどうかのフラグ
	bool seqfadeout(const float delta_time);				//フェードアウト関数


	std::list<std::shared_ptr<GameObjectManager>>object;
	std::shared_ptr<Camera>camera = nullptr;
	std::shared_ptr<SaveLoad>save = nullptr;
	std::shared_ptr<Stage>stage = nullptr;
	//各マネージャークラスを管理するクラスポインタ
	std::shared_ptr<PlayerManager>playermanager = nullptr;	
	std::shared_ptr<EnemyManager>enemymanage = nullptr;
	std::shared_ptr<GimmickManager>gimmickmanager = nullptr;
	std::shared_ptr<MobManager>mobmanager = nullptr;
	//UIManagerはManegerobjectには含まれない
	//UIの統括クラスのポインタ
	std::shared_ptr<UIManager>uimanager = nullptr;

	//ステージをアップデートで一度だけロードするためのフラグ
	bool initStage1 = false;//ステージ１
	bool initStage2 = false;//ステージ2
	bool initStage3 = false;//ステージ3
	bool initStage4 = false;//ステージ4

	STAGETYPE stage_id_ = STAGETYPE::STAGE_1;//ステージIDの初期値
	int play_bgm_sound_hdl;//プレイ画面のBGMハンドル
};