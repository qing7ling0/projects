#include "Role.h"
#include "RoleScript.h"
#include "RoleAnimi.h"


Role::Role(void)
	: _node(nullptr)
	, _direct(RoleDirect::roleLeft)
	, _script(nullptr)
	, _roleAnimi(nullptr)
	, _position(Point::ZERO)
	, _data()
	, _isDirectLeft (false)
{
}

Role::~Role(void)
{
	CC_SAFE_RELEASE(_node);
	CC_SAFE_RELEASE(_script);
	CC_SAFE_RELEASE(_roleAnimi);
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
	
}

void Role::update(float dt)
{
	if (_position != _node->getPosition())
	{
		_node->setPosition(_position);
	}

}
	
void Role::setPosition(const float px, const float py)
{
	_position.x = px;
	_position.y = py;
}

void Role::setPosition(const Point &point)
{
	_position.x = point.x;
	_position.y = point.y;
}

void Role::setRoleAnimi(RoleAnimi *animi)
{
	_roleAnimi = animi;
	setDirectLeft(_isDirectLeft);
	CC_SAFE_RETAIN(_roleAnimi);
}

void Role::setDirectLeft(bool left)
{
	_isDirectLeft = left;
	if (_roleAnimi && _roleAnimi->getArmature())
	{
		float scalex = _roleAnimi->getArmature()->getScaleX();
		_roleAnimi->getArmature()->setScaleX(abs(scalex) * (left?1:-1));
	}
}