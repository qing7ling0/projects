#pragma once
#include "RPGHead.h"
#include "HeroRole.h"

class HeroControl : public Ref
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

	virtual void move(float speedx, float speedy, float accx, float accy, bool fast=false);

	virtual void update(float dt);

	virtual void stop();

protected:
	HeroRole *_hero;

	/** 移动速度 */
	Point _speed;

	/** 加速度 */
	Point _acc;

	/** 是否超速移动 */
	bool _fastMove;

	/** 移动方向 */
	RoleDirect _roleDirect;

	RoleActionBase _roleActionFlag;
};

