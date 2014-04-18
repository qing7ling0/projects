#pragma once
#include "RPGHead.h"

class BattleRole;

class BattleRoles : public Object
{
public:
	BattleRoles(void);
	~BattleRoles(void);

	bool init();

	void addTestData();

	BattleRole* getRoleByGrid(Point grid);

	EXTERN_CREATE_INSTANCE_FUNC(BattleRoles);
	
	CREATE_FUNC(BattleRoles);

private:
	Vector<BattleRole*> _roles;
};

