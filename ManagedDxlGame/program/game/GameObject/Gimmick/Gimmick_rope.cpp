#include "../dxlib_ext/dxlib_ext.h"
#include"Gimmick_rope.h"
#include"../Player/Player.h"
#include"../Camera/Camera.h"

GimmickRope::GimmickRope(int type,tnl::Vector3& pos, float width, float hight)
	:Gimmick(type, pos, width, hight) {
	s_ = { gimmick_pos_.x, gimmick_pos_.y - (gimmick_hight_ / 2),0 };
	e_ = { gimmick_pos_.x, gimmick_pos_.y + (gimmick_hight_ / 2),0 };
}

void GimmickRope::Move(float delta_time, const std::shared_ptr<Player>player) {
	//�n�_����I�_�̒P�ʃx�N�g��
	tnl::Vector3 cpn = tnl::Vector3::Normalize(e_ - s_);
	//�n�_����I�_�̒P�ʃx�N�g���Ɖ��sZ���Ƃ̊O�ς����߂�
	tnl::Vector3 cpz_cr = cpn.cross(tnl::Vector3(0, 0, -1));
	//�U��q�̐^��̃x�N�g����cpz_cr�̓��ς����߂ƐU��q�ɒ��p�ȃx�N�g�������߂�
	//�U��q���X�O�x�̎����ς͂O�ɂȂ鑬�x���~�܂�
	//�U��q���O�x�̎����ς͂P�ɂȂ镄��������ւ��
	float gr = cpz_cr.dot(tnl::Vector3(0, 1, 0));

	float pw = 0.98f * 0.5f * gr;
	
	//�͂�������
	rot_vel_ += pw;
	//�͂�������Ɠ����ɁA�I�_�ɏd�肪���Ă���Ƃ��̉�]�̐���̌v�Z������
	rot_vel_ *= 1.0f - (0.01f * (1.0f - (e_ - s_).length() / max_length_));
	//�p�x���v�Z
	float angle = tnl::ToRadian(rot_vel_);
	//�I�_���ǂ̌ʂ�`�������v�Z����
	e_ = s_ + tnl::Vector3::TransformCoord(
		cpn * (e_ - s_).length(),
		tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, 1), angle));

}

void GimmickRope::Draw(const std::shared_ptr<Camera>camera) {
	draw_pos_ = gimmick_pos_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	tnl::Vector3 s1 = s_ - camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	tnl::Vector3 e1 = e_ -camera->GetCameraPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	//�U��q�̕R�̕`��
	DrawLine(s1.x, s1.y, e1.x, e1.y, 0xFF734E30,5);

}