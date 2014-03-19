#include "HeroRole.h"
#include "RoleScript.h"

HeroRole::HeroRole(void)
{
}


HeroRole::~HeroRole(void)
{
}

bool HeroRole::init(RoleData data)
{
	if (Role::init(data))
	{
		_script = RoleScript::createScript(data.scriptType);
		if (_script) _script->retain();
		_node = _script->createRoleNode();
		_node->setPosition(Point(data.px, data.py));

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
