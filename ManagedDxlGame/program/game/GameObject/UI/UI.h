#pragma once
#include "../dxlib_ext/dxlib_ext.h"


class SaveLoad;
class Player;
class Camera;
class ScenePlay;

//-------------------------------------------------------------------------------------------------//
//UIの親クラス
//-------------------------------------------------------------------------------------------------//
class UI
{
public:
	UI() {};
	virtual~UI() { };
	virtual void Draw() {};	//UIの描画関数
	virtual void Input(std::shared_ptr<SaveLoad>save, std::shared_ptr<Player>player, const std::shared_ptr<Camera>camera, std::shared_ptr<ScenePlay>stage) {};//UIの入力関数
	bool invisible_ = false;//UIの表示終了のフラグ
};

