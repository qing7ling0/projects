#include "Role.h"
#include "RoleScript.h"


Role::Role(void)
	: _node(nullptr)
	, _direct(RoleDirect::roleLeft)
	, _script(nullptr)
	, _position(Point::ZERO)
	, _data()
{
}

Role::~Role(void)
{
	CC_SAFE_RELEASE(_node);
	CC_SAFE_RELEASE(_script);
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