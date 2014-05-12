#pragma once
#include "RPGHead.h"
#include "Role.h"
#include "RoleData.h"
#include "AnimiPlayer.h"
#include "SkillData.h"

static const int ROLE_HP_TAG = 100;

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

	virtual void setDefaultAction();

	virtual int getCurrentAnimiActionIndex(void) { return _currentAnimiActionIndex;}

	virtual void setCurrentAnimiActionIndex(int index, int loop=1, bool resume=true);

	virtual AnimiPlayer* getCurrentAnimiPlayer() { return _currentPlayer; }

	virtual bool isAnimiPlayerOver() { if (_currentPlayer) return _currentPlayer->isOver(); return false; }

	virtual SkillData* getCurrentSelectSkill() { return _currenSelectSkill; }

	virtual void setHP(int hp);

	virtual int getHP() { return _roleHP; }

	virtual int getMaxHP();

	virtual void moveTo(const Point &grid);

	virtual bool isDeadth() { return _death; }

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

	int _roleHP;

	bool _death;

	RoleData *_roleData;

	bool _left;

	Map<int, AnimiPlayer*> _animiPlayers;

	int _currentAnimiActionIndex;

	AnimiPlayer* _currentPlayer;

	SkillData *_currenSelectSkill;

	Sprite *_hpBar;
};

