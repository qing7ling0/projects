#include "MapCamera.h"


MapCamera::MapCamera(void)
	: _size ( Size::ZERO )
	, _sceneSize ( Size::ZERO )
	, _off ( Point::ZERO )
	, _map ( nullptr)
	, _cameraType (CameraType::camera_none)
	, _cameraUpdate (false)
{
	_observedRoles.reserve(2);
}


MapCamera::~MapCamera(void)
{
	_observedRoles.clear();
	CC_SAFE_RELEASE(_map);
}

bool MapCamera::init(Size size, Size sceneSize)
{
	_size = Size(size);
	_sceneSize = Size(sceneSize);

	return true;
}

void MapCamera::setMap(MapControl *map)
{
	_map = map;
	CC_SAFE_RETAIN(_map);
}
void MapCamera::setCameraType(CameraType type)
{
	_cameraType = type;
}

void MapCamera::addObserved(Role *role)
{
	_observedRoles.pushBack(role);
}

bool MapCamera::checkBound(const Point off)
{
	if (off.x < 0) return true;
	else if (off.x > (_sceneSize.width-_size.width)) return true;

	if (off.y < 0) return true;
	else if (off.y > (_sceneSize.height - _size.height)) return true;

	return false;
}

void MapCamera::setCamera(const Point viewPosition)
{
	Point position = correctCamera(viewPosition);
	if (position != _off)
	{
		_off.x = position.x;
		_off.y = position.y;
		updateCamera(_off.x, _off.y);
	}
}
	
void MapCamera::setCamera(const float x, const float y)
{
	setCamera(Point(x, y));
}

Point MapCamera::correctCamera(const Point viewPosition)
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

void MapCamera::updateCamera(const float x, const float y)
{

}

void MapCamera::update(float dt)
{
	
}