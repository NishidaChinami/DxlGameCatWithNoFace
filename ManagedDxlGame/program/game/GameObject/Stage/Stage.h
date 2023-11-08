#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Camera;
class Mapchip;
class Player;

//-------------------------------------------------------------------------------------------------//
//�X�e�[�W�`��N���X
//-------------------------------------------------------------------------------------------------//
class Stage {
public:
	Stage(int stage_id);
	~Stage();
	void MapDraw(const std::shared_ptr<Camera>camera);//�}�b�v�w�i�ƃ}�b�v�`�b�v�̕`��֐�
	const std::list<std::shared_ptr<Mapchip>>& Getlist() const{ return Collitions; }//�}�b�v�̓����蔻���n���֐�

private:
	tnl::Vector3 map_pos_;//�}�b�v�w�i�̃Q�[�������W
	int stage_gpc_hdl_ = 0;//�X�e�[�W�w�i�̃O���t�B�b�N�n���h��
	int chip_hdl[256];//�}�b�v�̒n�`�摜�n���h�����i�[����z��
	int chip_second_hdl_[767];//�}�b�v�̒u���摜�n���h�����i�[����z��
	float cam_weight_ = 0.1f;//�J�����ňڂ���䗦

	std::vector<std::vector<int>> map_csv;	//�}�b�v�̒n�`��csv�n���h��
	std::vector<std::vector<int>> map_or_csv;//�}�b�v�̏����csv�n���h��
	std::vector<std::vector<tnl::CsvCell>> stage_csv;//�e�X�e�[�W�̏���csv�n���h��
	std::vector<std::vector<int>> Collition_csv;//�����蔻���csv�n���h��

	std::list<std::shared_ptr<Mapchip>>Collitions;//�}�b�v�`�b�v�̓����蔻��̃��X�g�|�C���^
	std::list<std::shared_ptr<Mapchip>> blocks;//�}�b�v�`�b�v�̃��X�g�|�C���^
	std::string stage_date;//�w�i�摜��ID�ꗗ
	std::string csv_date;//�X�e�[�W�̃}�b�v�`�b�v��ID�ꗗ
	std::string ornament_data;//�u���̃}�b�v�`�b�v��ID�ꗗ
	std::string Collition_date;//�����蔻��ꗗ
};


