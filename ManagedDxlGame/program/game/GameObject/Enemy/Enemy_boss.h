#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy.h"
#include"../Camera/Camera.h"

class Player;
class Attack;
class Item;
class Camera;
class Efect;

class EnemyBoss final:public Enemy
{
public:
	EnemyBoss(const tnl::Vector3& pos, float size);
	~EnemyBoss()override;
	//�{�X�̍U���̃R���[�`��
	TNL_CO_SEQUENCE(EnemyBoss, &EnemyBoss::Magic);
	tnl::Sequence<EnemyBoss> seq_ = tnl::Sequence<EnemyBoss>(this, &EnemyBoss::Magic);
	
	bool Magic(const float delta_time);//�{�X�̍U���R���[�`���p�t���O
	void Move(float delta_time, const std::shared_ptr<Player>player)override;//�{�X�̋����֐�
	void Draw(const std::shared_ptr<Camera>camera)override;//�{�X�̕`��֐�
	int GetBossHP(){ return boss_hp_; }		//�{�X��HP��Ԃ��֐�
private:

	std::list<std::shared_ptr<Attack>>attack;								//�܍U���̃��X�g
	std::shared_ptr<Item>item = nullptr;									//�U���A�C�e���̃N���X�|�C���^
	std::shared_ptr<Efect>fire_anim = nullptr;							//�G�t�F�N�g�N���X�̃|�C���^
	const tnl::Vector3 EFECT_POS = { 7360,200,0 };			//�G�t�F�N�g���W
	float enemyspeed = 3.0f;									//�U���̉��ړ��̑��x
	tnl::Vector3 attack_pos = { 6720,DXE_WINDOW_HEIGHT >> 1,0 };//�U�����o����W	
	const int ATTACKSIZE = 250;									//�U���T�C�Y
	bool player_attack = false;									//�v���C���[�̍U���t���O
	int attack_sound_hdl;										//�U���T�E���h�̃n���h��
	int death_sound_hdl;										//�{�X�̎��ʃT�E���h�n���h��


};



