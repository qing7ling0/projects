#include "Role.h"

Role::Role(void)
	: _node (nullptr)
	, _position (Point::ZERO)
{
}

Role::~Role(void)
{
	CC_SAFE_RELEASE(_node);
}

bool Role::init()
{
	_node = Layer::create();
	CC_SAFE_RETAIN(_node);

	return true;
}

void Role::update(float dt)
{
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
