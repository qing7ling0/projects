#include "RPGCamera.h"


RPGCamera::RPGCamera(void)
	: _size ( Size::ZERO )
	, _sceneSize ( Size::ZERO )
	, _off ( Point::ZERO )
{
}


RPGCamera::~RPGCamera(void)
{
}

bool RPGCamera::init(Size size, Size sceneSize)
{
	_size = Size(size);
	_sceneSize = Size(sceneSize);

	return true;
}

bool RPGCamera::checkBound(const Point off)
{
	if (off.x < 0) return true;
	else if (off.x > (_sceneSize.width-_size.width)) return true;

	if (off.y < 0) return true;
	else if (off.y > (_sceneSize.height - _size.height)) return true;

	return false;
}

void RPGCamera::setCamera(const Point viewPosition)
{
	Point position = correctCamera(viewPosition);
	if (position != _off)
	{
		_off.x = position.x;
		_off.y = position.y;
		updateCamera(_off.x, _off.y);
	}
}
	
void RPGCamera::setCamera(const float x, const float y)
{
	setCamera(Point(x, y));
}

Point RPGCamera::correctCamera(const Point viewPosition)
{
	Point okPosition = Point(viewPosition);

	if (okPosition.x < 0)
		okPosition.x = 0;
	else
	{
		float maxOffx = _sceneSize.width - _size.width;
		if (okPosition.x > maxOffx) okPosition.x = maxOffx;
	}
	
	if (okPosition.y < 0)
		okPosition.y = 0;
	else
	{
		float maxOffy = _sceneSize.height - _size.height;
		if (okPosition.y > maxOffy) okPosition.y = maxOffy;
	}

	return okPosition;
}

void RPGCamera::updateCamera(const float x, const float y)
{

}