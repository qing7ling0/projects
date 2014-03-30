#pragma once
#include "RPGHead.h"
#include "Role.h"

class HeroControl;

class HeroRole : public Role
{
public:
	HeroRole(void);
	~HeroRole(void);

	bool init(RoleData data);

	virtual bool isSelf() { return b_self; }

	virtual void setSelf(const bool self) { this->b_self = self; }

	virtual bool isEnemy() { return b_enemy; }

	virtual void setEnemy(const bool enemy) { this->b_self = enemy; }
	
	virtual void setPosition(const float px, const float py);

	virtual void setPosition(const Point &point);

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

	virtual RoleAnimi *getRoleAnimi() { return _roleAnimi; }

	virtual void setRoleAnimi(RoleAnimi *animi);

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
	bool b_enemy;

	bool b_self;

	HeroControl *_heroControl;

	RoleScript *_script;

	RoleAnimi *_roleAnimi;

	/** 角色现在移动方向 */
	RoleDirect _direct;

	RoleData _data;

	/** 角色的朝向, 是否是朝左 */
	bool _isDirectLeft;
};

