#pragma once
//-------------------------------------------------------------------------------------------------//
//Scene�̐e�N���X
//-------------------------------------------------------------------------------------------------//
class SceneBase {
public:
	SceneBase() {};
	virtual~SceneBase() {};
	virtual void Update(float delta_time) {};//�V�[���̍X�V
	virtual void Draw() {};//�V�[���̕`��֐�
};