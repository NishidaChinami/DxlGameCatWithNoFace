#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"../game/GameObject/Camera/Camera.h"
//-------------------------------------------------------------------------------------------------//
//�v���C���[�̍U���A�C�e���N���X
//-------------------------------------------------------------------------------------------------//
class Item {
public:
	tnl::Vector3 pos_;  //�Q�[�������W
	tnl::Vector3 draw_pos_;//�`����W
	int gpc_hdl = 0;//�A�C�e���̃O���t�B�b�N�n���h��
	const float ITEMSIZE = 32;//�A�C�e���̃T�C�Y
	float random_pos_ = (rand() % 1280) + 6720;//�A�C�e�����X�|�[������ʒu�������_���Ɍ��߂�
	Item() {
		pos_ = { random_pos_,600,0 };
		gpc_hdl = LoadGraph("graphics/sword.png");
	}
	~Item() {
		DeleteGraph(gpc_hdl);
	}
	void Draw(const std::shared_ptr<Camera>camera) {
		draw_pos_ = pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
		DrawRotaGraph(draw_pos_.x, draw_pos_.y, 0.5, 0, gpc_hdl, true);
	}
};