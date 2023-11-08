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
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart(){
	srand(time(0));
	GameManager::GetInstance(std::make_shared<SceneTitle>());
	SetWindowText("��̂Ȃ��L");
	//�t�H���g�̓ǂݍ���
	tnl::AddFontTTF("font/g_comichorrorR_freeR.ttf");
	tnl::AddFontTTF("onryou.TTF");
}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {
	GameManager::GetInstance()->Update(delta_time);

}


//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
//�Q�[���}�l�[�W���[�̃f���[�g
	GameManager::Destroy();
}

