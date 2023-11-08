#include "../dxlib_ext/dxlib_ext.h"
#include"../Manager.h"
#include"Scene_play.h"
#include"Scene_title.h"
#include"Scene_end.h"
#include"../GameObject/GameObjectManager.h"
#include"../GameObject/Player/PlayerManager.h"
#include"../GameObject/Gimmick/GimmickManager.h"
#include"../GameObject/Enemy/EnemyManager.h"
#include"../GameObject/Mob/MobManager.h"
#include"../GameObject/UI/UIManager.h"
#include"../GameObject/Camera/Camera.h"
#include"../GameObject/Player/Player.h"
#include"../GameObject/UI/UI.h"
#include"../Etc/Save.h"

ScenePlay::ScenePlay() {
	//セーブアンドロード
	save = std::make_shared<SaveLoad>();
	if (save) {
		//セーブデータをロード
		save->Load();
		//ステージデータをロード
		stage_id_ = static_cast<STAGETYPE>(save->GetLoadStage());
	}
	//カメラ
	camera = std::make_shared<Camera>(save);
	//UI
	uimanager = std::make_shared<UIManager>();
	//キャラクターのまとめ
	playermanager = std::make_shared<PlayerManager>(save);
	object.emplace_back(playermanager);
	play_bgm_sound_hdl = LoadSoundMem("sound/playbgm.mp3");
	//プレイBGMのループ再生
	PlaySoundMem(play_bgm_sound_hdl, DX_PLAYTYPE_LOOP);
}

ScenePlay::~ScenePlay() {
	DeleteSoundMem(play_bgm_sound_hdl);
}

void ScenePlay::Update(float delta_time) {
	//シーン遷移のアップデート
	sequence_.Update(delta_time);
	//プレイヤーからステージの切り替えを取得StageIDへ代入
	if (playermanager) {
		stage_id_ = static_cast<STAGETYPE>(playermanager->GetPlayer()->Getstagepass());
	}
	//ステージ更新
	ChangeStage();
	//ステージ描画
	if (stage) stage->MapDraw(camera);
	//ゲームオブジェクトマネージャーでポリモフィズムして回す
	auto it = object.begin();
	while (it != object.end()) {
		if (*it) {
			(*it)->Update(delta_time, playermanager->GetPlayer());
			(*it)->Collition(stage, playermanager->GetPlayer(),
				gimmickmanager->GetGimmickList(), enemymanage->GetEnemylist(), camera);
		}
		it++;
	}
	//UIの更新
	uimanager->Update(delta_time, mobmanager->Getlist());

	//カメラのスクロール
	camera->Scroll(playermanager->GetPlayer());
	//カメラの描画範囲
	camera->DrawRange();
	//オブジャクトの描画
	it = object.begin();
	while (it != object.end()) {
		if (*it) {
			(*it)->Draw(camera, playermanager->GetPlayer());
			DrawStringEx(100, 100, -1, "% d", (*it).use_count());
		}
		it++;
	}
	//UIの描画
	uimanager->Draw(save,playermanager->GetPlayer(),camera, shared_from_this());
	
}

//ステージ更新の判定をする関数
void ScenePlay::ChangeStage() {
	switch (GetStageType())
		{
		case 1:
			if (!initStage1) {
				NewStage(GetStageType());
				initStage1 = true;
			}
			break;
		case 2:
			if (!initStage2) {
				NewStage(GetStageType());
				sequence_.change(&ScenePlay::seqfadeout);
				initStage2 = true;
			}
			break;
		case 3:
			if (!initStage3) {
				NewStage(GetStageType());
				sequence_.change(&ScenePlay::seqfadeout);
				initStage3 = true;
			}
			break;
		case 4:
			if (!initStage4) {
				NewStage(GetStageType());
				sequence_.change(&ScenePlay::seqfadeout);
				initStage4 = true;
			}
			break;
	}
}
//新しいステージを実体化する関数
void ScenePlay::NewStage(int stage_id) {
	//ステージのデリート
	stage = nullptr;
	//新しいステージ背景を実体化
	if (!stage) stage = std::make_shared<Stage>(stage_id);
	//カメラ位置初期化
	tnl::Vector3 zero = { 0,0,0 };
	if (camera) camera->SetCameraPos(zero);
	//オブジャクト消去
	auto obj = object.begin();
	while (obj != object.end()) {
		if (*obj) {
			if (1 == (*obj)->GetActType()) {
				(*obj) = nullptr;

			}
			else if (2 == (*obj)->GetActType()) {
				(*obj) = nullptr;
			}
			else if (3 == (*obj)->GetActType()) {
				(*obj) = nullptr;
			}
		}
		
		obj++;
	}
	//各ポインタnullポインタを代入
	enemymanage = nullptr;
	gimmickmanager = nullptr;
	mobmanager = nullptr;
	//オブジェクトクラスに再代入
	if (!enemymanage)enemymanage = std::make_shared<EnemyManager>(stage_id);
	if(enemymanage)object.emplace_back(enemymanage);
	if (!gimmickmanager)gimmickmanager = std::make_shared<GimmickManager>(stage_id);
	if (gimmickmanager)object.emplace_back(gimmickmanager);
	if (!mobmanager) mobmanager = std::make_shared<MobManager>(stage_id);
	if (mobmanager)object.emplace_back(mobmanager);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////s

bool ScenePlay::seqResult(float delta_time) {
	//endingへ移行
	if (enemymanage) {
		auto enm = enemymanage->GetEnemylist().begin();
		while (enm != enemymanage->GetEnemylist().end()) {
			//ボスの体力で判定
			if ((*enm)->GetBossHP() <= 0) {
				auto mgr = GameManager::GetInstance();
				mgr->ChangeScene(std::make_shared<SceneEnd>());
				(*enm)->SetBossHP(100);
				break;
			}
			enm++;
		}
	}
	//設定からタイトル画面へ
	if (title_back) {
		auto mgr = GameManager::GetInstance();
		mgr->ChangeScene(std::make_shared<SceneTitle>());
		//移行フラグをfalse
		title_back = false;
	}
	return true;
}
bool ScenePlay::seqfadeout(float delta_time) {
	static float time = 0.5f;
	int alpha = (sequence_.getProgressTime() / time * 255.0f);
	if (alpha >= 255) {
		SetDrawBright(255, 255, 255);
		sequence_.change(&ScenePlay::seqResult);
	}
	SetDrawBright(alpha, alpha, alpha);
	return true;
}
