#include "BattleRoles.h"
#include "BattleRole.h"
#include "TestData.h"

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
	_selfRoles.reserve(5);
	_enemyRoles.reserve(10);

	addTestData();

	return true;
}

void BattleRoles::addTestData(void)
{
	//Role

	auto testData = new TestData();
	testData->autorelease();

	for(auto &data : testData->_roleDatas)
	{
		auto role = BattleRole::create(data);
		if (role->isEnemy()) _enemyRoles.pushBack(role);
		else _selfRoles.pushBack(role);
	}

}

BattleRole* BattleRoles::getRoleByGrid(const Point &grid)
{
	for(auto &role : _selfRoles)
	{
		if (role->getGridIndex() == grid) return role;
	}

	for(auto &role : _enemyRoles)
	{
		if (role->getGridIndex() == grid) return role;
	}

	return nullptr;
}
