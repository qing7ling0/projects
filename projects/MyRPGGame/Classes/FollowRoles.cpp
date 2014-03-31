#include "FollowRoles.h"

static FollowRoles* _instance;

FollowRoles::FollowRoles(void)
{
	_instance = this;
	CC_SAFE_RETAIN(_instance);
}


FollowRoles::~FollowRoles(void)
{
	_followRoles.clear();
	CC_SAFE_RELEASE(_instance);
}

bool FollowRoles::init()
{
	_followRoles.reserve(4);

	return true;
}

void FollowRoles::update(float dt)
{
	for(auto &role : _followRoles)
	{
		role->update(dt);
	}
}

void FollowRoles::add(FollowRole *role)
{
	_followRoles.pushBack(role);
}

void FollowRoles::remove(FollowRole *role)
{
	_followRoles.eraseObject(role, true);
}

FollowRoles* FollowRoles::getInstance()
{
	if (!_instance)
	{
		FollowRoles::create();
	}

	return _instance;
}