#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class UI;
class UIStory;
class UISetting;
class Mob;
class Camera;
class Player;
class SaveLoad;
class ScenePlay;



//-------------------------------------------------------------------------------------------------//
//UI�����N���X
// 
// ��Factory�N���X����������������
//-------------------------------------------------------------------------------------------------//
class UIManager
{
public:
	UIManager();
	~UIManager();
	void Update(float delta_time, const std::list<std::shared_ptr<Mob>> &mob);	//UI�X�V�̊֐�
	void Draw(std::shared_ptr<SaveLoad>save, std::shared_ptr<Player>player, const std::shared_ptr<Camera>camera, std::shared_ptr<ScenePlay>stage);//UI�\���̊֐�
	void NewStory(int chapter);//�X�g�[���[�����̉�����֐�
private:
	//UI�N���X�|�C���^
	std::list<std::shared_ptr<UI>> m_ui;//UI�̃��X�g�|�C���^
	bool initStory = false;//�X�g�[���[����x�����ǂݎ��t���O
	std::shared_ptr<UIStory>story = nullptr;//�X�g�[���[��UI�N���X�̃|�C���^
	std::shared_ptr<UISetting>setting = nullptr;//�ݒ��UI�N���X�̃|�C���^
	int chapter_ = 0;//�X�g�[���̃G�s�\�[�h���̕ϐ�
	int select_sound_hdl;//�I���T�E���h�̃n���h��

};
