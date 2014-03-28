#pragma once
#include "RPGHead.h"
#include "Role.h"
#include "HeroCamera.h"

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

	virtual void setCamera(const float x, const float y);
	
	virtual void setPosition(const float px, const float py);

	virtual void setPosition(const Point &point);

	virtual void attack();

	virtual void hurt();

	virtual void move();

	virtual void run();

	virtual void update(float dt);

	virtual HeroControl* getHeroControl() { return _heroControl; }

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
	HeroCamera *_camera;
	HeroControl *_heroControl;
};

