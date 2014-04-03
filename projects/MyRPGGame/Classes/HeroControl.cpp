#include "HeroControl.h"
#include "RoleScript.h"
#include "MapControl.h"


HeroControl::HeroControl(void) 
	: _hero(nullptr)
	, _speed (Point::ZERO)
	, _acc (Point::ZERO)
	, _fastMove (false)
	, _roleDirect (RoleDirect::roleNone)
	, _roleActionFlag (RoleActionBase::actionNone)
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
				animiFlag = _hero->getRoleScript()->getRoleAnimiFlag(RoleActionBase::actionDefense);
				break;
			case RoleDirect::roleDownLeft:
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

void HeroControl::move(float speedx, float speedy, float accx, float accy, bool fast)
{
	if (_hero)
	{
		_speed.x = speedx;
		_speed.y = speedy;
		_acc.x = accx;
		_acc.y = accy;
		_fastMove = fast;
		if (_fastMove)
		{
			_acc = _acc*2;
			_speed = _speed*2;
		}
	}
}

void HeroControl::update(float dt)
{
	if (_speed.x != 0  || _speed.y != 0 || _acc.x != 0 || _acc.y != 0)
	{
		Point position = Point(_hero->getPosition());
		position.x += dt * _speed.x;
		position.y += dt * _speed.y;
		_hero->setPosition(position);
		MapControl::getInstance()->checkBound(_hero);

		if (_speed.y>0 && (_speed.y + _acc.y)<0)
		{
		}

		_speed.x += _acc.x;
		_speed.y += _acc.y;
	}
}

void HeroControl::stop()
{
	_fastMove = false;
	_speed.x = 0;
	_speed.y = 0;
	_roleDirect = RoleDirect::roleNone;
}