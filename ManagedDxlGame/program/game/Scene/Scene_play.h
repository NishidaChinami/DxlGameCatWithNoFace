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
//Scene�̎q�N���X
// 
// �v���C��ʂ̃N���X
//-------------------------------------------------------------------------------------------------//
class ScenePlay final : public SceneBase, public std::enable_shared_from_this<ScenePlay> {
public:
	//�X�e�[�W�^�C�v
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
	void Update(float delta_time)override;//�v���C�V�[���̍X�V�֐�
	void Draw()override {};			//�v���C�V�[���̕`��֐�
	void ChangeStage();				//�X�e�[�W�X�V�̔��������֐�
	void NewStage(int stage_id);	//�V�����X�e�[�W��ǂݍ��ފ֐�

	int GetStageType() {return static_cast<int>(stage_id_);}//�X�e�[�WID��int�^�ŕԂ��֐�
	bool &GetTitleFlug() {return title_back;}//�^�C�g���̖߂邩�̃t���O��n���֐�
	int GetSoundHdl()const {return play_bgm_sound_hdl;}//BGM�n���h����n���֐�
private:
	tnl::Sequence<ScenePlay> sequence_ = tnl::Sequence<ScenePlay>(this, &ScenePlay::seqResult);//�V�[���J�ڗp�̃e���v���[�g
	bool seqResult(float delta_time);
	bool title_back = false;//�^�C�g���̖߂邩�ǂ����̃t���O
	bool seqfadeout(const float delta_time);				//�t�F�[�h�A�E�g�֐�


	std::list<std::shared_ptr<GameObjectManager>>object;
	std::shared_ptr<Camera>camera = nullptr;
	std::shared_ptr<SaveLoad>save = nullptr;
	std::shared_ptr<Stage>stage = nullptr;
	//�e�}�l�[�W���[�N���X���Ǘ�����N���X�|�C���^
	std::shared_ptr<PlayerManager>playermanager = nullptr;	
	std::shared_ptr<EnemyManager>enemymanage = nullptr;
	std::shared_ptr<GimmickManager>gimmickmanager = nullptr;
	std::shared_ptr<MobManager>mobmanager = nullptr;
	//UIManager��Manegerobject�ɂ͊܂܂�Ȃ�
	//UI�̓����N���X�̃|�C���^
	std::shared_ptr<UIManager>uimanager = nullptr;

	//�X�e�[�W���A�b�v�f�[�g�ň�x�������[�h���邽�߂̃t���O
	bool initStage1 = false;//�X�e�[�W�P
	bool initStage2 = false;//�X�e�[�W2
	bool initStage3 = false;//�X�e�[�W3
	bool initStage4 = false;//�X�e�[�W4

	STAGETYPE stage_id_ = STAGETYPE::STAGE_1;//�X�e�[�WID�̏����l
	int play_bgm_sound_hdl;//�v���C��ʂ�BGM�n���h��
};