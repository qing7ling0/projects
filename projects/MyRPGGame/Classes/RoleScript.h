#pragma once
#include "RPGHead.h"
#include "Role.h"
#include "HeroRole.h"
#include "TouchControl.h"
#include "HeroControl.h"
#include "HeroAnimi.h"

class RoleScript : public Ref
{
public:
	RoleScript(void);
	~RoleScript(void);

	virtual void init(HeroRole *role){}

	virtual void doScript(float dt){}

	virtual void update(float dt){}
	
	/**
	* 执行一些动作，这些动作通过虚拟摇杆获得
	*/
	virtual void doTouchActions(std::vector<DirectionFlag> directionFlags){}

	virtual Node* createRoleNode(){ return nullptr; }

	virtual CommandType parseRoleAction(std::vector<DirectionFlag> directionFlags);
	
	/**
	* 创建角色脚本
	*/
	static RoleScript* createScript(ScriptType scriptType);

	/**
	* 根据角色动作获取角色动画相应的动作序列
	*/
	virtual int getRoleAnimiFlag(RoleActionBase action);
	
	/**
	* 获得走路速度
	*/
	virtual float getMoveSpeed() { return 50; }
	
	/**
	* 获得跑步速度
	*/
	virtual float getRunSpeed() { return getMoveSpeed() * 2; }
	
	/**
	* 获得跳速度
	*/
	virtual float getJumpSpeed() { return 30; }
	
	/**
	* 获得下落速度
	*/
	virtual float getDropSpeed() { return getJumpSpeed(); }

protected:
	HeroRole *_hero;
};

