#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Scene_Base.h"

//-------------------------------------------------------------------------------------------------//
//Scene�̎q�N���X
// 
// �Q�[���N���A��̃X�g�[���[�`��N���X
//-------------------------------------------------------------------------------------------------//
class SceneEnd final: public SceneBase
{
public:
	SceneEnd();
	~SceneEnd()override;
	void Update(float delta_time)override;//�G���f�B���O�̍X�V�֐�
	void Draw()override;//�G���f�B���O�̕`��֐�
	bool EndingDraw(const float delta_time);//�G���f�B���O�̃R���[�`���p�`��֐�
	
	TNL_CO_SEQUENCE(SceneEnd, &SceneEnd::EndingDraw);
	tnl::Sequence<SceneEnd> seq_ = tnl::Sequence<SceneEnd>(this, &SceneEnd::EndingDraw);	//�G���f�B���O�X�g�[���̕��͂̃R���[�`��
private:
	tnl::Sequence<SceneEnd> sequence_ = tnl::Sequence<SceneEnd>(this, &SceneEnd::seqTitle);//�V�[���J�ڂ̊֐�
	bool seqTitle(float delta_time);
	
	int end_gpc_hdl = 0;																//�G���f�B���O�̔w�i�̃O���t�B�b�N�n���h��
	int end_cat_gpc_hdl = 0;															//�G���f�B���O�̃v���C���[�摜�n���h��
	int end_movie_hdl;																	//����ۑ��p�n���h��
	int end_screen_hdl;																	//����Đ��̕`��n���h��
	int end_bgm_sound_hdl;																//�G���f�B���O��BGM�n���h��
	int end_effect_sound_hdl;															//�G���f�B���O�̌��ʉ��̃n���h��
	std::vector<std::vector<tnl::CsvCell>> end_story_csv;								//�G���f�B���O�X�g�[���[���i�[����CSV
	std::vector<std::string> endingstory;												//�G���f�B���O�̕��̕ϐ�
	const tnl::Vector3 ENDING_POS = { DXE_WINDOW_WIDTH >> 1 ,DXE_WINDOW_HEIGHT>>1,0 };	//�����̕`����W
	bool title_return_ = false;															//ending�I���̃t���O
	const int ENDING_FONT_SIZE = 50;													//�G���f�B���O�����T�C�Y(��)
	const int HORROR_FONST_SIZE = 150;													//�G���f�B���O�����T�C�Y(��)
};

