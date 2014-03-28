#include "HeroRole.h"
#include "RoleScript.h"
#include "HeroControl.h"
#include "MapControl.h"

HeroRole::HeroRole(void) 
	: b_enemy(false)
	, b_self(false)
	, _heroControl (nullptr)
	, _camera(nullptr)
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

		_heroControl = new HeroControl();
		_heroControl->init(this);

		_camera = new HeroCamera();
		_camera->init(Size(D_display.w, D_display.h), MapControl::getInstance()->getMapSize());
		_camera->setHero(this);
		_camera->setCamera(data.px, data.py);

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


void HeroRole::setCamera(const float x, const float y)
{
	_position.x = x;
	_position.y = y;
}

void HeroRole::setPosition(const float px, const float py)
{
	if (_camera)
	{
		_camera->setCamera(px, py);
	}
}

void HeroRole::setPosition(const Point &point)
{
	if (_camera)
	{
		_camera->setCamera(point);
	}
}