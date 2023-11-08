#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../GameObjectManager.h"

class Stage;
class Camera;
class Gimmick;
class Player;
class Mob;
class Enemy;

//-------------------------------------------------------------------------------------------------//
//�X�g�[���[�����L�����N�^�[�̐����N���X
// ��Factory�N���X����������������
//-------------------------------------------------------------------------------------------------//
class MobManager final:public GameObjectManager
{
public:
	MobManager(int stage_id);
	~MobManager()override;
	void NewObject();
	void Update(float delta_time, const std::shared_ptr<Player>player)override;//Mob�̍X�V�֐�
	void Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player)override;//Mob�̕`��֐�
	void Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player,
		const std::list<std::shared_ptr<Gimmick>>& gimmick, const std::list<std::shared_ptr<Enemy>>& enemy, std::shared_ptr<Camera>camera)override;//Mob�Ƃ̓����蔻��X�V�̊֐�

	const std::list<std::shared_ptr<Mob>> &Getlist()const { return m_mob_move; }
private:
	std::vector<std::vector<tnl::CsvCell>> mob_csv;	//���u�̏���csv�n���h��
	std::list<std::shared_ptr<Mob>> m_mobs;							//�ҋ@����Mob�̃��X�g�̃|�C���^
	std::list<std::shared_ptr<Mob>> m_mob_move;						//���s����Mob�̃��X�g�̃|�C���^
	int mob_type_;									//Mob���`���v�^�[�����̃X�g�[���[�������𔻒肷��ϐ�
};