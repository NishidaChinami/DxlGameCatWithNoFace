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
	//�Z�[�u�A���h���[�h
	save = std::make_shared<SaveLoad>();
	if (save) {
		//�Z�[�u�f�[�^�����[�h
		save->Load();
		//�X�e�[�W�f�[�^�����[�h
		stage_id_ = static_cast<STAGETYPE>(save->GetLoadStage());
	}
	//�J����
	camera = std::make_shared<Camera>(save);
	//UI
	uimanager = std::make_shared<UIManager>();
	//�L�����N�^�[�̂܂Ƃ�
	playermanager = std::make_shared<PlayerManager>(save);
	object.emplace_back(playermanager);
	play_bgm_sound_hdl = LoadSoundMem("sound/playbgm.mp3");
	//�v���CBGM�̃��[�v�Đ�
	PlaySoundMem(play_bgm_sound_hdl, DX_PLAYTYPE_LOOP);
}

ScenePlay::~ScenePlay() {
	DeleteSoundMem(play_bgm_sound_hdl);
}

void ScenePlay::Update(float delta_time) {
	//�V�[���J�ڂ̃A�b�v�f�[�g
	sequence_.Update(delta_time);
	//�v���C���[����X�e�[�W�̐؂�ւ����擾StageID�֑��
	if (playermanager) {
		stage_id_ = static_cast<STAGETYPE>(playermanager->GetPlayer()->Getstagepass());
	}
	//�X�e�[�W�X�V
	ChangeStage();
	//�X�e�[�W�`��
	if (stage) stage->MapDraw(camera);
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�Ń|�����t�B�Y�����ĉ�
	auto it = object.begin();
	while (it != object.end()) {
		if (*it) {
			(*it)->Update(delta_time, playermanager->GetPlayer());
			(*it)->Collition(stage, playermanager->GetPlayer(),
				gimmickmanager->GetGimmickList(), enemymanage->GetEnemylist(), camera);
		}
		it++;
	}
	//UI�̍X�V
	uimanager->Update(delta_time, mobmanager->Getlist());

	//�J�����̃X�N���[��
	camera->Scroll(playermanager->GetPlayer());
	//�J�����̕`��͈�
	camera->DrawRange();
	//�I�u�W���N�g�̕`��
	it = object.begin();
	while (it != object.end()) {
		if (*it) {
			(*it)->Draw(camera, playermanager->GetPlayer());
			DrawStringEx(100, 100, -1, "% d", (*it).use_count());
		}
		it++;
	}
	//UI�̕`��
	uimanager->Draw(save,playermanager->GetPlayer(),camera, shared_from_this());
	
}

//�X�e�[�W�X�V�̔��������֐�
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
//�V�����X�e�[�W�����̉�����֐�
void ScenePlay::NewStage(int stage_id) {
	//�X�e�[�W�̃f���[�g
	stage = nullptr;
	//�V�����X�e�[�W�w�i�����̉�
	if (!stage) stage = std::make_shared<Stage>(stage_id);
	//�J�����ʒu������
	tnl::Vector3 zero = { 0,0,0 };
	if (camera) camera->SetCameraPos(zero);
	//�I�u�W���N�g����
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
	//�e�|�C���^null�|�C���^����
	enemymanage = nullptr;
	gimmickmanager = nullptr;
	mobmanager = nullptr;
	//�I�u�W�F�N�g�N���X�ɍđ��
	if (!enemymanage)enemymanage = std::make_shared<EnemyManager>(stage_id);
	if(enemymanage)object.emplace_back(enemymanage);
	if (!gimmickmanager)gimmickmanager = std::make_shared<GimmickManager>(stage_id);
	if (gimmickmanager)object.emplace_back(gimmickmanager);
	if (!mobmanager) mobmanager = std::make_shared<MobManager>(stage_id);
	if (mobmanager)object.emplace_back(mobmanager);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////s

bool ScenePlay::seqResult(float delta_time) {
	//ending�ֈڍs
	if (enemymanage) {
		auto enm = enemymanage->GetEnemylist().begin();
		while (enm != enemymanage->GetEnemylist().end()) {
			//�{�X�̗̑͂Ŕ���
			if ((*enm)->GetBossHP() <= 0) {
				auto mgr = GameManager::GetInstance();
				mgr->ChangeScene(std::make_shared<SceneEnd>());
				(*enm)->SetBossHP(100);
				break;
			}
			enm++;
		}
	}
	//�ݒ肩��^�C�g����ʂ�
	if (title_back) {
		auto mgr = GameManager::GetInstance();
		mgr->ChangeScene(std::make_shared<SceneTitle>());
		//�ڍs�t���O��false
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
