#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy.h"
#include"../GameObjectManager.h"


class Stage;
class Camera;
class Gimmick;
class Player;
class Mapchip;
class Enemy;


//-------------------------------------------------------------------------------------------------//
//�G�l�~�[�쐬�N���X
// 
//��Factory�̂悤�Ɏ�������������
//-------------------------------------------------------------------------------------------------//
class EnemyManager final:public GameObjectManager
{
public:
	EnemyManager(int stage_id);
	~EnemyManager()override;
	void NewObject();
	void Update(float delta_time, const std::shared_ptr<Player>player)override;//�G�̍X�V
	void Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player)override;//�G�̕`��֐�
	void Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player, 
		const std::list<std::shared_ptr<Gimmick>>&gimmick, const std::list<std::shared_ptr<Enemy>>&enemy,std::shared_ptr<Camera>camera)override;//�G�̓����蔻��X�V�̊֐�
	
	const std::list<std::shared_ptr<Enemy>>& GetEnemylist()const { return m_enemys_move; }//Enemy�N���X�ɃA�N�Z�X����p��Getter
private:
	std::vector<std::vector<tnl::CsvCell>> enemy_csv;	//enemy����csv�n���h��
	std::list<std::shared_ptr<Enemy>> m_enemys;		//�ҋ@���̓G�̃��X�g�|�C���^
	std::list<std::shared_ptr<Enemy>> m_enemys_move;	//���s���̓G�̃��X�g�|�C���^
	int enemy_move_type_ = 0;							//�G�̎�ނ𔻕ʂ���ϐ�
};

