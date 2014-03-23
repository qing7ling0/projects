#include "HeroRole.h"
#include "RoleScript.h"
#include "HeroControl.h"

HeroRole::HeroRole(void) 
	: b_enemy(false)
	, b_self(false)
	, _heroControl (nullptr)
{
}


HeroRole::~HeroRole(void)
{
	CC_SAFE_RELEASE(_heroControl);
}

bool HeroRole::init(RoleData data)
{
	if (Role::init(data))
	{
		_script = RoleScript::createScript(data.scriptType);
		if (_script) _script->retain();
		_script->init(this);
		_node = _script->createRoleNode();
		_position.x = data.px;
		_position.y = data.py;
		_node->setPosition(_position);

		_heroControl = new HeroControl();
		_heroControl->init(this);

		return true;
	}

	return false;
}

void HeroRole::attack()
{
}

void HeroRole::hurt()
{
}

void HeroRole::move()
{
}

void HeroRole::run()
{
}

void HeroRole::update(float dt)
{
	Role::update(dt);
	if (_script)
	{
		_script->update(dt);
		_heroControl->update(dt);
	}
}
