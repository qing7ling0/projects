#pragma once
#include "RPGHead.h"
#include "Role.h"
#include "RoleData.h"
#include "AnimiPlayer.h"


class BattleRole : public Role
{
public:
	BattleRole();
	~BattleRole(void);

	virtual bool isEnemy() const { return _enemy; }

	virtual void setEnemy(bool enemy);

	virtual bool init(RoleData *_roleData);

	virtual void setGirdIndex(const Point &grid, bool updatePosition=true);

	virtual bool isLeft() const { return _left; }

	virtual void setLeft(bool left);

	virtual Point getGridIndex() const { return _gridIndex; }

	static BattleRole* create(RoleData *roleData)
	{
		auto role = new BattleRole();
		if (role->init(roleData))
		{
			role->autorelease();

			return role;
		}
		else
		{
			delete role;
			role = nullptr;
		}

		return nullptr;
	}

protected:
	void initRoleAnimiPlayers();

protected:
	Point _gridIndex;

	bool _enemy;

	RoleData *_roleData;

	bool _left;

	Map<int, AnimiPlayer*> _animiPlayers;
};

