#include "FollowRole.h"


FollowRole::FollowRole(void)
	: _followRole (nullptr)
	, _targetRole (nullptr)
{
}


FollowRole::~FollowRole(void)
{
}

bool FollowRole::init(Role *followRole, Role *targetRole)
{
	_followRole = followRole;
	_targetRole = targetRole;

	return true;
}

void FollowRole::update(float dt)
{
	if (_followRole && _targetRole)
	{
		Point f_position = _followRole->getPosition();
		Point t_position = _targetRole->getPosition();
		_followRole->toScreen(t_position.x+f_position.x, t_position.y+f_position.y);
	}
}

FollowRole* FollowRole::create(Role *followRole, Role *targetRole)
{
	FollowRole *_fr = new FollowRole();
	if (_fr->init(followRole, targetRole))
	{
		_fr->autorelease();
		return _fr;
	}
	else
	{
		delete _fr;
		_fr = nullptr;
		return nullptr;
	}
}