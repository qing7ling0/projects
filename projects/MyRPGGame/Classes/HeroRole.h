#pragma once
#include "RPGHead.h"
#include "Role.h"

class HeroControl;
class HeroAnimi;
class RoleScript;

class HeroRole : public Role
{
public:
	HeroRole(void);
	~HeroRole(void);

	bool init(RoleData data);

	virtual bool isSelf() { return b_self; }

	virtual void setSelf(const bool self) { this->b_self = self; }

	virtual void attack();

	virtual void hurt();

	virtual void move();

	virtual void run();

	virtual void update(float dt);

	virtual RoleDirect getDirect() { return _direct; }

	virtual RoleScript* getRoleScript() { return _script; }

	virtual void doTouchActions(std::vector<DirectionFlag> directionFlags);

	virtual HeroControl* getHeroControl() { return _heroControl; }

	virtual bool isDirectLeft() { return _isDirectLeft; }

	virtual void setDirectLeft(bool left);

	virtual HeroAnimi *getRoleAnimi() { return _roleAnimi; }

	virtual void setRoleAnimi(HeroAnimi *animi);

	virtual RoleData getRoleData() { return _data; }

	virtual void face(const Point &position);

	virtual void faceRole(Role* role);

	virtual HeroRole* getEnemy() { return _enemy; }

	virtual void setEnemy(HeroRole* enemy);

	virtual void setFlag(RoleFlag flag);

	virtual RoleFlag getFlag() { return _flag; }

	static HeroRole* create(RoleData data)
	{
		HeroRole *role = new HeroRole();
		if (role && role->init(data))
		{
			role->autorelease();
			return role;
		}
		else
		{
			delete role;
			role = NULL;
			return NULL;
		}
	};

protected:

private:
	bool b_self;

	HeroControl *_heroControl;

	RoleScript *_script;

	HeroAnimi *_roleAnimi;

	/** 角色现在移动方向 */
	RoleDirect _direct;

	RoleData _data;

	/** 角色的朝向, 是否是朝左 */
	bool _isDirectLeft;

	HeroRole *_enemy;

	/** 角色状态：下蹲、上跳、下落、站立 */
	RoleFlag _flag;
};

