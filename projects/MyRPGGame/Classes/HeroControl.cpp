#include "HeroControl.h"
#include "RoleScript.h"


HeroControl::HeroControl(void) 
	: _hero(nullptr)
	, _speed (Point::ZERO)
	, _fastMove (false)
	, _roleDirect (RoleDirect::roleNone)
{
}


HeroControl::~HeroControl(void)
{
	CC_SAFE_RELEASE(_hero);
}

void HeroControl::init(HeroRole *role)
{
	_hero = role;
	CC_SAFE_RETAIN(_hero);
}

void HeroControl::doMove(float speedx, float speedy, RoleDirect direct, bool fast)
{
	if (_hero)
	{
		_speed.x = speedx;
		_speed.y = speedy;
		_fastMove = fast;

		if (direct != RoleDirect::roleNone)
		{
			int animiFlag = -1;
			switch(direct)
			{
			case RoleDirect::roleDown:
				//animiFlag 
				break;
			case RoleDirect::roleUp:
				break;
			case RoleDirect::roleLeft:
				animiFlag = _hero->getRoleScript()->getRoleAnimiFlag(RoleActionBase::actionMove);
				break;
			case RoleDirect::roleRight:
				break;
			case RoleDirect::roleDownLeft:
				animiFlag = _hero->getRoleScript()->getRoleAnimiFlag(RoleActionBase::actionMove);
				break;
			case RoleDirect::roleDownRight:
				break;
			case RoleDirect::roleUpLeft:
				break;
			case RoleDirect::roleUpRight:
				break;
			}

			if (animiFlag > -1)
			{
				_hero->getRoleAnimi()->setAnimiFlag(animiFlag);
			}
		}
		_roleDirect = direct;
	}
}

void HeroControl::update(float dt)
{
	if (_speed.x != 0  || _speed.y != 0)
	{
		Point position = Point(_hero->getPosition());
		position.x += dt * _speed.x;
		position.y += dt * _speed.y;
		_hero->setPosition(position);
	}

}

void HeroControl::stop()
{
	_fastMove = false;
	_speed.x = 0;
	_speed.y = 0;
	_roleDirect = RoleDirect::roleNone;
}