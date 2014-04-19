#pragma once
#include "RPGHead.h"
#include "Monitor.h"

class BattleRole;

class AttackMonitor : public Monitor
{
public:
	AttackMonitor(void);
	~AttackMonitor(void);

	bool init(Vector<BattleRole*> attackRoles);

	void onEnter(void);

	void onExit(void);

	void update(float dt);

	void attack();

	F_CREATE_FUNC_ARGS_1(AttackMonitor, Vector<BattleRole*>, attackRoles);

protected:
	Vector<BattleRole*> _attackRoles;
};

