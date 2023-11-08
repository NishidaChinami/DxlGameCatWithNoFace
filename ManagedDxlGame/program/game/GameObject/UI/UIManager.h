#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class UI;
class UIStory;
class UISetting;
class Mob;
class Camera;
class Player;
class SaveLoad;
class ScenePlay;



//-------------------------------------------------------------------------------------------------//
//UI生成クラス
// 
// ※Factoryクラスを実装したかった
//-------------------------------------------------------------------------------------------------//
class UIManager
{
public:
	UIManager();
	~UIManager();
	void Update(float delta_time, const std::list<std::shared_ptr<Mob>> &mob);	//UI更新の関数
	void Draw(std::shared_ptr<SaveLoad>save, std::shared_ptr<Player>player, const std::shared_ptr<Camera>camera, std::shared_ptr<ScenePlay>stage);//UI表示の関数
	void NewStory(int chapter);//ストーリーを実体化する関数
private:
	//UIクラスポインタ
	std::list<std::shared_ptr<UI>> m_ui;//UIのリストポインタ
	bool initStory = false;//ストーリーを一度だけ読み取るフラグ
	std::shared_ptr<UIStory>story = nullptr;//ストーリーのUIクラスのポインタ
	std::shared_ptr<UISetting>setting = nullptr;//設定のUIクラスのポインタ
	int chapter_ = 0;//ストーリのエピソード数の変数
	int select_sound_hdl;//選択サウンドのハンドル

};
