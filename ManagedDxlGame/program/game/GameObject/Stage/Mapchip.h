#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Camera;

//-------------------------------------------------------------------------------------------------//
//�}�b�v�`�b�v�N���X
//-------------------------------------------------------------------------------------------------//
class Mapchip {
public:

	// arg1...�}�b�v�`�b�v�̍��W
	// arg2...�}�b�v�`�b�v�̃O���t�B�b�N�n���h��
	// arg3...�����蔻��̎��
	Mapchip(const tnl::Vector3& pos, int gfx_hdl, int type);
	~Mapchip();
	void Mapchipdraw(const std::shared_ptr<Camera>camera);//�}�b�v�`�b�v�ꖇ�ɑ΂���`��֐�
	static constexpr float CHIP_SIZE = 32;//�`�b�v�̑傫��
	tnl::Vector3 GetChipPos()const { return chip_pos_; }//�}�b�v�`�b�v�̍��W��n���֐�
	int GetCollitionType()const { return collition_type_; }//�}�b�v�`�b�v�̓����蔻��^�C�v��n���֐�
private:
	int chip_gpc_hdl_ = 0;//�X�e�[�W�w�i�̃O���t�B�b�N�n���h��
	tnl::Vector3 chip_pos_ = { 0, 0, 0 };//�}�b�v�`�b�v�̃Q�[�������W
	tnl::Vector3 draw_pos_ = { 0,0,0 };//�}�b�v�`�b�v�̕`����W
	int collition_type_ = 0;//�`�b�v�̓����蔻��^�C�v�̔��ʕϐ�
};