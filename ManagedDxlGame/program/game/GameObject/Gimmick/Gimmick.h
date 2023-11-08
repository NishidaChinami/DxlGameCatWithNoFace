#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class Player;
class Camera;
class Mapchip;
//-------------------------------------------------------------------------------------------------//
//�M�~�b�N�̐e�N���X
//-------------------------------------------------------------------------------------------------//
class Gimmick{
public:
	Gimmick(int type, tnl::Vector3& pos, float width, float hight)
		:gimmick_type_(type), gimmick_pos_(pos), gimmick_width_(width), gimmick_hight_(hight){}
	virtual ~Gimmick() {};
	void Update(float delta_time) {};//�M�~�b�N�̍X�V
	virtual void Draw(const std::shared_ptr<Camera>camera){}//�e�M�~�b�N�̕`��֐�
	virtual void Move(float delta_time, const std::shared_ptr<Player>player) {};//�e�M�~�b�N�̓����̊֐�
	virtual void Hit(const std::list<std::shared_ptr<Mapchip>>& mapchip, const std::shared_ptr<Player>player) {}//�M�~�b�N�Ƃ̓����蔻��X�V�̊֐�

	tnl::Vector3 GetGimmickPos() { return gimmick_pos_; }		//�M�~�b�N�̃Q�[�������W��Ԃ��֐�
	tnl::Vector3 GetGimmickDrawPos() { return draw_pos_; }		//�M�~�b�N�̕`����W��Ԃ��֐�
	float GetGimmickWidth() const { return gimmick_width_; }	//�M�~�b�N�̉�����Ԃ��֐�
	float GetGimmickHight() const { return gimmick_hight_; }	//�M�~�b�N�̏c����Ԃ��֐�
	int GetGimmickType() const { return gimmick_type_; }		//�M�~�b�N�̃^�C�v��Ԃ��֐�
protected:
	tnl::Vector3 gimmick_pos_;	//�M�~�b�N�̃Q�[�������W
	tnl::Vector3 draw_pos_;		//�M�~�b�N�̕`����W
	float gimmick_width_;		//�M�~�b�N�̉��T�C�Y
	float gimmick_hight_;		//�M�~�b�N�̏c�T�C�Y
private:
	int gimmick_type_ = 0;		//�M�~�b�N�^�C�v�𔻕ʂ���ϐ�
};




