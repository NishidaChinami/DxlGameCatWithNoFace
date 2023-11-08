#pragma once
#include "../dxlib_ext/dxlib_ext.h"


//-------------------------------------------------------------------------------------------------//
//Mob�L�����N�^�[�����X�g�[���[�̕`��N���X
//-------------------------------------------------------------------------------------------------//
class Story {
public:
	// arg1...�L�����N�^�[���v���C���[��Mob���𔻕ʂ���
	// arg2...�X�g�[���[�̕�����
	// arg3...���̉�b�̍Ō�̕����𔻕ʂ���t���O
	Story(int side, const std::string& letter, bool active_) 
		:chara_side_(side), story_sentence(letter), active_(active_) {};
	~Story(){}
	void Draw();								//�Z���t�̕`��֐�
	bool Getactive_() const { return active_; }//�Ō�̃Z���t�����ʂ���t���O��Getter
	void SetLetterCount(int count) { letter_count_ = count; }//�`�悵�����������Z�b�g���邽�߂�Setter
private:
	int chara_side_;							//�������v���C���[�����u���̔��ʂ�����ϐ�
	std::string story_sentence;					//csv����ǂݍ��񂾕��͂�ۑ�����ϐ�
	std::string text;							//�\�������������̕ϐ�
	int letter_count_ = 0;						//�������\��������������ϐ�
	const int full_width_ = 2;					//�S�p�̂P�����̑傫��
	bool active_;								//�Ō�̃Z���t�����ʂ���t���O

	const tnl::Vector3 MOB_SERIF = { 500,180,0 };	//���u�̃Z���t�̕`��̍��W
	const tnl::Vector3 PLAYER_SERIF = { 400,540,0 };//�v���C���[�̃Z���t�̕`����W
};