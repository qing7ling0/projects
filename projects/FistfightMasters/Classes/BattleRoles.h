#pragma once
#include "RPGHead.h"

#include "BattleRole.h"

class BattleRoles : public Ref
{
public:
	BattleRoles(void);
	~BattleRoles(void);

	bool init();

	void addTestData();

	BattleRole* getRoleByGrid(const Point &grid);

	Vector<BattleRole*> getSelfRoles() { return _selfRoles; }

	Vector<BattleRole*> getEnemyRoles() { return _enemyRoles; }

	EXTERN_CREATE_INSTANCE_FUNC(BattleRoles);
	
	CREATE_FUNC(BattleRoles);

private:
	Vector<BattleRole*> _selfRoles;
	Vector<BattleRole*> _enemyRoles;
};

