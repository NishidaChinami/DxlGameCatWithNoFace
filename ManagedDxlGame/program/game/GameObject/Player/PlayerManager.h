#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../GameObjectManager.h"

class Stage;
class Camera;
class Gimmick;
class Player;
class Enemy;
class SaveLoad;

//-------------------------------------------------------------------------------------------------//
//�v���C���[�����N���X
// 
//-------------------------------------------------------------------------------------------------//
class PlayerManager final: public GameObjectManager{
public:
	PlayerManager(const std::shared_ptr<SaveLoad>save);
	~PlayerManager()override;
	void Update(float delta_time, const std::shared_ptr<Player>player)override;//�v���C���[�X�V�֐�
	void Draw(const std::shared_ptr<Camera>camera, const std::shared_ptr<Player>player)override;//�v���C���[�`��֐�
	void Collition(std::shared_ptr<Stage>stage, const std::shared_ptr<Player>player,
		const std::list<std::shared_ptr<Gimmick>>&gimmick, const std::list<std::shared_ptr<Enemy>>&enemy,std::shared_ptr<Camera>camera)override;//�v���C���[�Ƃ̓����蔻����X�V����֐�

	std::shared_ptr<Player>GetPlayer() { return m_player; }//�v���C���[�N���X�|�C���^�̃A�N�Z�X������n���֐�
private:
	std::shared_ptr<Player>m_player = nullptr;//�v���C���[�̃N���X�|�C���^
};
