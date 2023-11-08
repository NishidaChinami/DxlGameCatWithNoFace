#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class SaveLoad;
class Player;
class Camera;
class ScenePlay;

//-------------------------------------------------------------------------------------------------//
//UI�̐e�N���X
//-------------------------------------------------------------------------------------------------//
class UI
{
public:
	UI() {};
	virtual~UI() { };
	virtual void Draw() {};	//UI�̕`��֐�
	virtual void Input(std::shared_ptr<SaveLoad>save, std::shared_ptr<Player>player, const std::shared_ptr<Camera>camera, std::shared_ptr<ScenePlay>stage) {};//UI�̓��͊֐�
	bool invisible_ = false;//UI�̕\���I���̃t���O
};

