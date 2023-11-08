#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include"Enemy.h"
class Player;
//-------------------------------------------------------------------------------------------------//
//エネミー子クラス②　追尾型
//-------------------------------------------------------------------------------------------------//
class EnemyTrack final:public Enemy
{
public:
	EnemyTrack(const tnl::Vector3& pos, float size);
	~EnemyTrack();
	void Move(float delta_time,const std::shared_ptr<Player>player)override;//追尾型の挙動の関数
};
