#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../GameObjectManager.h"

class Stage;
class Camera;
class Gimmick;
class Player;
class Enemy;

//-------------------------------------------------------------------------------------------------//
//�M�~�b�N�����N���X
// ��Factory�N���X�̂悤�ɂ���������
//-------------------------------------------------------------------------------------------------//
class GimmickManager:public GameObjectManager
{
public:
	GimmickManager(int stage_id);
	~GimmickManager()override;
	void NewObject();
	void Update(float delta_time, const std::shared_ptr<Player>player)override;//�M�~�b�N�̍X�V�֐�
	void Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player)override;//�M�~�b�N�̕`��֐�
	void Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player, 
		const std::list<std::shared_ptr<Gimmick>>&gimmick, const std::list<std::shared_ptr<Enemy>>&enemy,std::shared_ptr<Camera>camera)override;//�M�~�b�N�Ƃ̓����蔻��X�V�̊֐�

	const std::list<std::shared_ptr<Gimmick>>& GetGimmickList()const { return m_gimmicks_move; }//�M�~�b�N�̎��s�����X�g�|�C���^��Ԃ��֐�
private:
	std::vector<std::vector<tnl::CsvCell>> gimmick_csv;	//�M�~�b�N�̃X�|�[���ʒu�Ȃǂ�csv�n���h��
	int gimmick_move_type_ = 0;							//�M�~�b�N�^�C�v�𔻕ʂ���ϐ�
	std::list<std::shared_ptr<Gimmick>> m_gimmicks;						//�ҋ@���̃M�~�b�N�N���X�̃��X�g�|�C���^
	std::list<std::shared_ptr<Gimmick>> m_gimmicks_move;				//���s���̃M�~�b�N�N���X�̃��X�g�|�C���^
};	



