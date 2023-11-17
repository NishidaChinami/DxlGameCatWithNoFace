#include "../dxlib_ext/dxlib_ext.h"
#include"UIManager.h"
#include"UI.h"
#include"UI_setting.h"
#include"UI_story.h"
#include"../Mob/Mob.h"
#include"../Camera/Camera.h"
#include"../Player/Player.h"
#include"../game/Scene/Scene_play.h"
#include"../game/Etc/Save.h"

UIManager::UIManager()
{
	//�T�E���h�̓ǂݍ���
	select_sound_hdl = LoadSoundMem("sound/enter.mp3");
}

UIManager::~UIManager()
{
	DeleteSoundMem(select_sound_hdl);
}

void UIManager::Update(float delta_time, const std::list<std::shared_ptr<Mob>>&mob) {
	//�X�g�[���[�L�����N�^�[�ɓ��������Ƃ���ui�ɑ��
	if (!initStory) {
		if (!setting) {
			for (auto m : mob) {
				if (m->Getmob()) {
					NewStory(m->Getchapter());
					initStory = true;
				}
			}
		}
		
	}
	//��\���̃t���O���I���ɂȂ�����\������UI������
	auto u =m_ui.begin();
	while (u != m_ui.end()) {
		if (*u) {
			if ((*u)->invisible_) {
				(*u) = nullptr;
				initStory = false;

			}
		}
		u++;
	}
	//Esc�Őݒ��ʂ��J���AEsc�ŕ���
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)||(tnl::Input::IsPadDownTrigger(ePad::KEY_5))) {
		if (setting) {
			auto u = m_ui.begin();
			while (u != m_ui.end()) {
				if ((*u)) {
					(*u)=nullptr;
					setting = nullptr;
					story = nullptr;
				}
				u++;
			}
		}
		else if (!setting) {
			setting = std::make_shared<UISetting>();
			m_ui.emplace_back(setting);
		}
	
		PlaySoundMem(select_sound_hdl, DX_PLAYTYPE_BACK);
	}
	
}

void UIManager::Draw(std::shared_ptr<SaveLoad>save, std::shared_ptr<Player>player, const std::shared_ptr<Camera>camera, std::shared_ptr<ScenePlay>stage){
	//ui���X�g�ɓ����Ă���̂�`��܂��͓��͂��󂯕t��
	auto it = m_ui.begin();
	while (it != m_ui.end()) {
		if (*it) {
			(*it)->Input(save, player, camera, stage);
			(*it)->Draw();
		}
		it++;
	}
}
void UIManager::NewStory(int chapter) {
	if (!story) m_ui.emplace_back(std::make_shared<UIStory>(chapter));
}