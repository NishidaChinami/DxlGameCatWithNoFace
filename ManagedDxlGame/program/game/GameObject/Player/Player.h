#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../Camera/Camera.h"

class Mapchip;
class Camera;
class Gimmick;
class Enemy;
class SaveLoad;


//-------------------------------------------------------------------------------------------------//
//�v���C����L�����N�^�[�N���X
//-------------------------------------------------------------------------------------------------//
class Player: public std::enable_shared_from_this<Player> {
public:
	Player(const std::shared_ptr<SaveLoad>save);
	~Player();
	void Update(float delta_time);									//�v���C���[�̍X�V����֐�
	void Draw(const std::shared_ptr<Camera>camera);								//�v���C���[�̕`��
	void Hit(const std::list<std::shared_ptr<Mapchip>>&mapchip,std::shared_ptr<Camera>camera);	//�v���C���[�ƃ}�b�v�̓����蔻��
	void GimmickHit(const std::list<std::shared_ptr<Gimmick>>&gimmick);			//�v���C���[�ƃM�~�b�N�̓����蔻��
	void EnemyHit(const std::list<std::shared_ptr<Enemy>>&enemy, std::shared_ptr<Camera>camera);	//�v���C���[�ƓG�̓����蔻��
	void Death(std::shared_ptr<Camera>camera);										//���S�E���ԃZ�[�u�̊֐�
	//�A�j���[�V�����^�C�v
	enum class ANIMTYPE {
		DIR_LEFT,		//���֕���
		DIR_RIGHT,		//�E�֕���
		DIR_IDEL,		//���͑҂����
		DIR_JUMP_LEFT,	//�������ɃW�����v
		DIR_JUMP_RIGHT, //�E�����ɃW�����v
		DIR_ROPE,		//���[�v�ɂ��܂铮��
		DIR_LADDER,		//��q�ɏ��
		DIR_MAX
	};


	
	const static int PLAYER_SIZE = 30;								//�v���C���[�T�C�Y

	tnl::Vector3 GetPlayerPos() const { return player_pos_; }		//�v���C���[���W��Getter
	tnl::Vector3 GetPlayerPrevPos() const { return prev_pos_; }		//�v���C���[�̕␳�O���W��Getter
	tnl::Vector3 Getsavepos() const { return intermediate_save_; }	//���ԃZ�[�u�̃J�������W��Getter
	tnl::Vector3 GetSavePlayerPos() const { return save_pos_; }		//���ԃZ�[�u�̃v���C���[���W��Getter
	int Getstagepass(){ return stage_pass_; }						//�X�e�[�W�ۑ��p�̕ϐ���Getter
	bool Getbattle() const { return start_battle_; }					//�{�X��J�n�̃t���O��Getter
	bool GetPlayerDeath() const{ return player_death_; }				//�v���C���[�����񂾂��ǂ����̃t���O��Getter
private:
	tnl::Vector3 player_pos_;										//�v���C���[�̃Q�[�������W
	tnl::Vector3 draw_pos_ = { 0,0,0 };								//�v���C���[�`����W
	float gravity_ = 0;												//�v���C���[�ɂ�����d��
	tnl::Vector3 force = {0,0,0};									//�ړ��̊����p�ϐ�
	const tnl::Vector3 INITIAL_POS = { PLAYER_SIZE / 2, 200, 0 };	//�v���C���[�����l
	tnl::Vector3 prev_pos_ = { 0,0,0 };								//�v���C���[�̕␳�O�̍��W
	tnl::Vector3 intermediate_save_;								//�J�������X�|�[���l��ۑ�
	tnl::Vector3 save_pos_;											//�v���C���[���X�|�[���l��ۑ�
	int stage_pass_;												//���̃X�e�[�W�ɍs�����߂̉��Z�p�̃X�e�[�W�ۑ��ϐ�
	//�v���C���[�̈ړ���Ԃ��Ǘ�����V�[�N�G���X
	tnl::Sequence<Player> sequence_ = tnl::Sequence<Player>(this, &Player::seqIdle);
	//�e�ړ����
	bool seqIdle(const float delta_time);				//�A�C�h��
	bool seqdeath(const float delta_time);				//���S
	bool seqRun(const float delta_time);				//�ʏ�ړ�
	bool seqclimb(const float delta_time);				//�㉺�ړ�
	bool seqstop(const float delta_time);				//��~���
	bool seqpendulum(const float delta_time);			//��ɕ߂܂��Ă�����
	bool seqmovefloor(const float delta_time);			//�������ɏ���Ă�����


	ANIMTYPE anim_ctrl_dir = ANIMTYPE::DIR_IDEL;//�A�j���[�V�����^�C�v��ID

	//�S�A�j���[�V�����摜
	std::string files[static_cast<int>(ANIMTYPE::DIR_MAX)] = {
		"graphics/AnimWalkL.png",
		"graphics/AnimWalkR.png",
		"graphics/AnimIdleR.png",
		"graphics/AnimJumpL.png",
		"graphics/AnimJumpR.png",
		"graphics/AnimFuriko.png",
		"graphics/AnimLadder.png"
	};

	const int frame_count_ = 4;								// ���t���[����
	const int frame_width_ = 4;								// ���t���[����
	const int frame_hight_ = 1;								// �c�t���[����
	const int size_width_ = 300;							// �������� 1�t���[��������̕�
	const int size_hight_ = 300;							// �c������ 1�t���[��������̕�

	int player_death_sound_hdl;							//�v���C���[���S���̃T�E���h�n���h��
	int death_gpc_hdl;										//���S���̉摜�n���h��

	int anim_hdls[static_cast<int>(ANIMTYPE::DIR_MAX)][4];	//�A�j���[�V�����摜�̓񎟌��z��
	int anim_ctrl_frame_ = 0;								//�A�j���̃t���[����
	int body_side_ = 0;										//�v���C���[�̑̂̌���
	bool rope_active_ = false;								//�U��q�Ƃ̓����蔻��t���O
	bool start_battle_ = false;								//�{�X��J�n�̃t���O
	bool damege_ = true;									//�v���C���[�Ƀ_���[�W��^�����邩�̃t���O
	bool player_death_ = false;								//���S�������̃t���O

	
};
