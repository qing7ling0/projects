#include "Role.h"

Role::Role(void)
	: _node (nullptr)
	, _position (Point::ZERO)
	, _size (Size::ZERO)
{
}

Role::~Role(void)
{
	CC_SAFE_RELEASE(_node);
}

bool Role::init()
{
	return true;
}

void Role::update(float dt)
{
}

void Role::toScreen(const float sx, const float sy)
{
	if (_node)
	{
		Point screen = Point(sx, sy);
		if ( screen != _node->getPosition())
		{
			_node->setPosition(screen);
		}
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

void Role::setSize(const Size size)
{
	_size = Size(size);
}