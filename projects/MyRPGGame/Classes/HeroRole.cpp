#include "HeroRole.h"
#include "RoleScript.h"
#include "HeroControl.h"
#include "MapControl.h"
#include "HeroAnimi.h"

HeroRole::HeroRole(void) 
	: b_self(false)
	, _heroControl (nullptr)
	, _direct(RoleDirect::roleLeft)
	, _script(nullptr)
	, _roleAnimi(nullptr)
	, _data()
	, _isDirectLeft (false)
	, _enemy (nullptr)
	, _flag (RoleFlag::flagStand)
{
}


HeroRole::~HeroRole(void)
{
	CC_SAFE_RELEASE(_heroControl);
	CC_SAFE_RELEASE(_script);
	CC_SAFE_RELEASE(_roleAnimi);
	CC_SAFE_RELEASE(_enemy);
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

		setPosition(data.px, data.py);

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

	if (_enemy) faceRole(_enemy);

	if (_script)
	{
		_script->update(dt);
		_heroControl->update(dt);
	}
}

void HeroRole::setRoleAnimi(HeroAnimi *animi)
{
	_roleAnimi = animi;
	setDirectLeft(_isDirectLeft);
	CC_SAFE_RETAIN(_roleAnimi);
}

void HeroRole::setDirectLeft(bool left)
{
	_isDirectLeft = left;
	/*if (_roleAnimi && _roleAnimi->getArmature())
	{
		float scalex = _roleAnimi->getArmature()->getScaleX();
		_roleAnimi->getArmature()->setScaleX(abs(scalex) * (left?-1:1));
	}*/
}

void HeroRole::doTouchActions(std::vector<DirectionFlag> directionFlags)
{
	
}

void HeroRole::face(const Point &position)
{
	setDirectLeft(_position.x > position.x);
}

void HeroRole::faceRole(Role* role)
{
	face(role->getPosition());
}

void HeroRole::setEnemy(HeroRole* enemy)
{
	_enemy = enemy;
	CC_SAFE_RETAIN(_enemy);
}

void HeroRole::setFlag(RoleFlag flag)
{
	_flag = flag;
}
