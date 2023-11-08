#include <time.h>
#include <string>
#include <numbers>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include"Manager.h"
#include"../game/Scene/Scene_Base.h"
#include"../game/Scene/Scene_end.h"
#include"../game/Scene/Scene_play.h"
#include"../game/Scene/Scene_title.h"

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart(){
	srand(time(0));
	GameManager::GetInstance(std::make_shared<SceneTitle>());
	SetWindowText("顔のない猫");
	//フォントの読み込み
	tnl::AddFontTTF("font/g_comichorrorR_freeR.ttf");
	tnl::AddFontTTF("onryou.TTF");
}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {
	GameManager::GetInstance()->Update(delta_time);

}


//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
//ゲームマネージャーのデリート
	GameManager::Destroy();
}

