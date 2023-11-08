#pragma once
#include "../dxlib_ext/dxlib_ext.h"

 
class Player;
class Camera;
class Mapchip;

//-------------------------------------------------------------------------------------------------//
//�G�l�~�[�̐e�N���X
// 
//�� ���삾�����N���X�ɕ������X�g���e�W�[�p�^�[������������������
//-------------------------------------------------------------------------------------------------//
class Enemy{
public:
	// arg1...�G�l�~�[�̃X�|�[�����W
	// arg2...�G�l�~�[�̃T�C�Y�i���a�j
	Enemy(const tnl::Vector3& pos, float size);
	virtual~Enemy();
	virtual void Hit(const std::list<std::shared_ptr<Mapchip>>& mapchip, const std::shared_ptr<Player>player) {}	//�e�G�ƃ}�b�v�̓����蔻��̊֐�
	virtual void Draw(const std::shared_ptr<Camera>camera);										//�e�G�̕`��֐�
	virtual void Move(float delta_time,const std::shared_ptr<Player>player) {}						//�e�^�C�v�̓G�̓����̊֐�
	
	tnl::Vector3 GetEnemyPos() const { return enemy_pos_; }							//�G�̍��W��n���֐�
	void SetEnemyPos(tnl::Vector3 pos) { enemy_pos_ = pos; }						//�G�̍��W��ύX����֐�
	tnl::Vector3 GetStartPos() const { return enemy_init_pos_; }					//�G�̏����ʒu��Ԃ��֐�
	tnl::Vector3 GetEnemyDrawPos() const { return draw_pos_; }						//�G�̕`����W��Ԃ��֐�
	float GetEnemySize() const { return enemy_size_; }								//�G�̃T�C�Y��Ԃ��֐�
	int GetBossHP()const { return boss_hp_; }											//�G��HP��Ԃ��֐�
	void SetBossHP(int hp) { boss_hp_ = hp; }										//�G��HP��ύX����֐�
	bool& GetBossAttack(){ return boss_attack_; }									//�G�̍U���ɂ����������𔻒肷��t���O��Ԃ��֐�

protected:
	tnl::Vector3 enemy_pos_;					//�G�̃Q�[�������W
	tnl::Vector3 draw_pos_ = { 2000,2000,0 };	//�G�̕`����W
	float enemy_size_ = 0;						//�G�̃T�C�Y
	int boss_hp_;								//HP�̂���G��HP�ϐ�
	bool boss_attack_ = false;					//�U���������������ǂ����̃t���O
	int enemy_gpc_hdl_ = 0;						//�G�摜�n���h��
	int enemy_voice_sound_hdl = 0;				//�G�T�E���h�n���h��
	tnl::Vector3 enemy_init_pos_;				//�G�̏����n��ۑ�����ϐ�

};
