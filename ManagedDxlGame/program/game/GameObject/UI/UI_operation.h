#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"UI.h"

//-------------------------------------------------------------------------------------------------//
//UIの子クラス
// 
// スタート画面の遊び方の描画
//-------------------------------------------------------------------------------------------------//
class UIOperation final:public UI 
{
public:
	UIOperation();
	~UIOperation();
	void Draw();//遊び方説明の描画関数
private:
	int operation_gpc_hdl = 0;//操作説明のグラフィックハンドル
};


