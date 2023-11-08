#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class Player;
class Camera;
class ScenePlay;

//-------------------------------------------------------------------------------------------------//
//セーブ＆ロードまたは新しいゲームを始めるのを管理するクラス
//-------------------------------------------------------------------------------------------------//
class SaveLoad
{
public:
	SaveLoad();
	~SaveLoad() {};
	void Save(std::shared_ptr<Player>player,const std::shared_ptr<Camera>camera,std::shared_ptr<ScenePlay>stage);//セーブしたときの関数
	void Load();//続きから始めたときの関数
	void NewGame();//新しいゲームを始めたときの関数

	tnl::Vector3 GetLoadPos()const { return player_save_pos_; }			//セーブしたプレイヤー位置をロードする関数
	tnl::Vector3 GetLoadCameraPos() const { return camera_save_pos_; }	//セーブしたカメラ座標をロードする関数
	int GetLoadStage() const { return save_stage_; }						//セーブしたステージをロードする関数
private:
	tnl::Vector3 player_save_pos_;										//プレイヤーが最後に通った中間セーブの地点
	tnl::Vector3 camera_save_pos_ = {0,0,0};								//プレイヤーが最後に通った中間セーブのカメラ座標
	const tnl::Vector3 START_POS = { 15,200,0 };						//プレイヤーの初期値
	int save_stage_;														//ステージを保存する変数

};

