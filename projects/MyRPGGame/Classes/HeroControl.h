#pragma once
#include "RPGHead.h"
#include "HeroRole.h"
#include "RoleHelper.h"

class HeroControl : public Object
{
public:
	HeroControl(void);
	~HeroControl(void);

	virtual void init(HeroRole *role);

	/**
	* 控制角色移动
	* speedx speedy 角色移动速度
	* direct 移动方向：是方向的组合值，如左上
	* fast 是否是超速移动
	*/
	virtual void doMove(float speedx, float speedy, RoleDirect direct, bool fast=false);

	virtual void update(float dt);

	virtual void stop();

protected:
	HeroRole *_hero;

	/** 移动速度 */
	Point _speed;

	/** 是否超速移动 */
	bool _fastMove;

	RoleDirect _roleDirect;

};

