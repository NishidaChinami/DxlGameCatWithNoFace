#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Mapchip;
class Player;
class SaveLoad;
//-------------------------------------------------------------------------------------------------//
//���ۂ̕`��ʒu�����߂�J�����N���X
//-------------------------------------------------------------------------------------------------//
class Camera {
public:
	Camera(const std::shared_ptr<SaveLoad>save);
	~Camera() {};
	void DrawRange();						//�J�������f���͈͂����߂�֐�
	void Scroll(const std::shared_ptr<Player>player);		//�J�������v���C���[�ɍ��킹�ē����֐�
	void CameRareset(const std::shared_ptr<Player>player);	//�v���C���[���S���ɃJ�����𒆊ԃ|�C���g�܂Ŗ߂��֐�
		
	tnl::Vector3 GetCameraPos() const{ return target_; }	//�J�������W��Ԃ��֐�
	void SetCameraPos(tnl::Vector3 &pos) {target_ = pos;}	//�J�������W��ݒ肷��֐�
private:
	tnl::Vector3 target_ = { 0,0,0 };						//�J�����̍��W
	bool m_is_active_ = false;								//�J�������v���C���[��ǂ������邩�Œ肩�̃t���O
	const int MAXCHIP = 8000;								//�}�b�v�̉��̃T�C�Y
	const int MAXSTAGE = 7360;								//�J�������v���C���[��ǂ������Ȃ��Ȃ�ʒu
};

