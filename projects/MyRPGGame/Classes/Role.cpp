#include "Role.h"


Role::Role(void):
	_node(nullptr),
	_direct(RoleDirect::roleLeft),
	_script(nullptr),
	_data()
{
}

Role::~Role(void)
{
	CC_SAFE_RELEASE(_node);
}

bool Role::init(RoleData data)
{
	this->_data = data;

	return true;
}



void Role::attack()
{
}

void Role::hurt()
{
}

void Role::move()
{
}

void Role::run()
{
}

void Role::doTouchActions(std::vector<DirectionFlag> directionFlags)
{
	_sc
}