#pragma once
#include "../dxlib_ext/dxlib_ext.h"


//-------------------------------------------------------------------------------------------------//
//Mobキャラクターが持つストーリーの描画クラス
//-------------------------------------------------------------------------------------------------//
class Story {
public:
	// arg1...キャラクターがプレイヤーかMobかを判別する
	// arg2...ストーリーの文字列
	// arg3...その会話の最後の文かを判別するフラグ
	Story(int side, const std::string& letter, bool active_) 
		:chara_side_(side), story_sentence(letter), active_(active_) {};
	~Story(){}
	void Draw();								//セリフの描画関数
	bool Getactive_() const { return active_; }//最後のセリフか判別するフラグのGetter
	void SetLetterCount(int count) { letter_count_ = count; }//描画した文字をリセットするためのSetter
private:
	int chara_side_;							//文字がプレイヤーかモブかの判別をする変数
	std::string story_sentence;					//csvから読み込んだ文章を保存する変数
	std::string text;							//表示したい文字の変数
	int letter_count_ = 0;						//何文字表示したか数える変数
	const int full_width_ = 2;					//全角の１文字の大きさ
	bool active_;								//最後のセリフか判別するフラグ

	const tnl::Vector3 MOB_SERIF = { 500,180,0 };	//モブのセリフの描画の座標
	const tnl::Vector3 PLAYER_SERIF = { 400,540,0 };//プレイヤーのセリフの描画座標
};