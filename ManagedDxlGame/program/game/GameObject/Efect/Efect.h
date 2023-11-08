#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Camera;

//-------------------------------------------------------------------------------------------------//
//�G�t�F�N�g�Đ��p�N���X
//-------------------------------------------------------------------------------------------------//
class Efect {
public:
	// arg1...�G�t�F�N�g�A�j���[�V�����̉摜URL�̕�����
	// arg2...�A�j���[�V�����Đ��ʒu
	// arg3...�t���[���̍s��
	// arg4...�t���[���̗�
	// arg5...�t���[���̉��T�C�Y
	// arg5...�t���[���̏c�T�C�Y
	// arg6...�t���[���̑���
	// arg7...�t���[���̃C���^�[�o��
	Efect(const std::string& gh_pass, const tnl::Vector3& pos, 
		int w_num, int h_num, int w_size, int h_size, int frame_count, int delay);
	~Efect();

enum class EfectState {
	PLAYING,//�Đ�
	PAUSE,//�ꎞ��~
	STOP,//��~
};

	void PlayEfect();//�G�t�F�N�g���Đ�����֐�
	void StopEfect();//�G�t�F�N�g���~����֐�
	void PauseEfect();//�G�t�F�N�g���ꎞ��~����֐�
	void Update(const float delta_time);//�G�t�F�N�g�̍X�V������֐�
	void Draw(const std::shared_ptr<Camera>camera);//�G�t�F�N�g�̕`�悷��֐�

private:
	int graph_handle;//�O���t�B�b�N�n���h��
	int width_num_;//�t���[���̍s��
	int height_num_;//�t���[���̗�
	int width_size_;//���̃T�C�Y
	int height_size_;//�c�̃T�C�Y
	int frame_num_;//�t���[���̑���
	int current_frame_;//���݂̃t���[��
	int frame_interval_;//�t���[���Ԃ̃C���^�[�o��
	int timer_;//�^�C�}�[
	int* efect_gpc_hdl;//�O���t�B�b�N�n���h���̔z��
	tnl::Vector3 draw_pos_;//�`����W
	tnl::Vector3 effect_pos_;//�G�t�F�N�g�̃Q�[�������W

	EfectState state;//�G�t�F�N�g�̏��

};