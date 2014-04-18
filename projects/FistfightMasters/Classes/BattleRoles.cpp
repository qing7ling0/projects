#include "BattleRoles.h"
#include "BattleRole.h"

DEFINE_CREATE_INSTANCE_FUNC(BattleRoles);

BattleRoles::BattleRoles(void)
{
}


BattleRoles::~BattleRoles(void)
{
	_instance = nullptr;
}

bool BattleRoles::init(void)
{
	_instance = this;
	_roles.reserve(10);
}

void BattleRoles::addTestData(void)
{
	//Role
}

BattleRole* BattleRoles::getRoleByGrid(const Point &grid)
{
	for(auto &role : _roles)
	{
		if (role->getGridIndex() == grid) return role;
	}

	return nullptr;
}
