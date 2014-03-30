#include "HeroRole.h"
#include "RoleScript.h"
#include "HeroControl.h"
#include "MapControl.h"
#include "RoleAnimi.h"

HeroRole::HeroRole(void) 
	: b_enemy(false)
	, b_self(false)
	, _heroControl (nullptr)
	, _direct(RoleDirect::roleLeft)
	, _script(nullptr)
	, _roleAnimi(nullptr)
	, _data()
	, _isDirectLeft (false)
{
}


HeroRole::~HeroRole(void)
{
	CC_SAFE_RELEASE(_heroControl);
	CC_SAFE_RELEASE(_script);
	CC_SAFE_RELEASE(_roleAnimi);
}

bool HeroRole::init(RoleData data)
{
	if (Role::init())
	{
		this->_data = data;

		_script = RoleScript::createScript(data.scriptType);
		if (_script) _script->retain();
		_script->init(this);
		_node = _script->createRoleNode();

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

void HeroRole::setRoleAnimi(RoleAnimi *animi)
{
	_roleAnimi = animi;
	setDirectLeft(_isDirectLeft);
	CC_SAFE_RETAIN(_roleAnimi);
}

void HeroRole::setDirectLeft(bool left)
{
	_isDirectLeft = left;
	if (_roleAnimi && _roleAnimi->getArmature())
	{
		float scalex = _roleAnimi->getArmature()->getScaleX();
		_roleAnimi->getArmature()->setScaleX(abs(scalex) * (left?1:-1));
	}
}

void HeroRole::doTouchActions(std::vector<DirectionFlag> directionFlags)
{
	
}
