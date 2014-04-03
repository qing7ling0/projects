#include "MapControl.h"
#include "BattleController.h"
#include "Heros.h"
#include "HeroRole.h"

static MapControl *_instance = nullptr;

MapControl::MapControl(void)
	: _cameraType (CameraType::camera_none)
	, _cameraMoving (false)
{
}


MapControl::~MapControl(void)
{
}

MapControl* MapControl::getInstance()
{
	if (!_instance)
	{
		_instance = new MapControl();
		_instance->init();
	}

	return _instance;
}

bool MapControl::init()
{
	if (Role::init())
	{
		auto map = TMXTiledMap::create("map/town.tmx");
		if (map)
		{
			_node = map;
			_node->retain();
			_size = Size(map->getContentSize());
			BattleController::getInstance()->addChild(map, -1, 1);
		}
		return true;
	}

	return false;
}

bool MapControl::cameraTo(const Point point, float delayTime, bool force, CameraType type)
{
	if (force || !_cameraMoving)
	{
		setCameraType(type);
		_cameraMoving = true;

		Point offTo = correctCamera(point);

		Point curPosition = _node->getPosition();
	
		float gapX = offTo.x - curPosition.x;
		float gapY = offTo.y - curPosition.y;
		float timex = abs( gapX / D_display.w * MAX_MOVE_TIME );
		float timey = abs( gapY / D_display.h * MAX_MOVE_TIME );

		auto action1 = Spawn::create(
			EaseOut::create(MoveBy::create(timex, Point(gapX, 0)), 2),
			EaseOut::create(MoveBy::create(timey, Point(0, gapY)), 2),
			NULL
			);
		auto action2 = Sequence::create(
			action1,
			DelayTime::create(delayTime),
			CallFunc::create( std::bind(&MapControl::cameraOver, this) ),
			NULL
			);

		_node->runAction(action2);

		return true;
	}

	return false;
}

/**
* 检测镜头有没有出界
* 如果出界了会纠正off成正确的偏移
* return true 出界；return false 没有出界
*/
bool MapControl::checkBound(Role *role)
{
	if (!role) return false;

	Rect roleR = role->getBounds();
	Point correctOff = Point(roleR.getMinX(), roleR.getMinY());
	float hw = roleR.size.width/2.0f;
	float hh = roleR.size.height/2.0f;

	bool bounds = false;

	if (correctOff.x < 0)
	{
		correctOff.x = hw;
		bounds = true;
	}
	else if (roleR.getMaxX() > _size.width)
	{
		correctOff.x = _size.width - hw;
		bounds = true;
	}
	if (correctOff.y < 150)
	{
		correctOff.y = hh+150;
		bounds = true;
	}
	else if (roleR.getMaxY() > _size.height)
	{
		correctOff.y = _size.height - hh;
		bounds = true;
	}

	if (bounds) role->setPosition(correctOff);

	return bounds;
}

/**
* 纠正镜头偏移,不能出界
* 并转化成Map的实际偏移量
**/
Point MapControl::correctCamera(const Point off)
{
	Point offTo = Point(off);
	offTo.x -= (D_display.w/2.0f);

	if (offTo.x < 0)
		offTo.x = 0;
	else
	{
		float maxOffx = _size.width - D_display.w;
		if (offTo.x > maxOffx) offTo.x = maxOffx;
	}
	
	if (offTo.y < 0)
		offTo.y = 0;
	else
	{
		float maxOffy = _size.height - D_display.h;
		if (offTo.y > maxOffy) offTo.y = maxOffy;
	}

	return -offTo;
}

void MapControl::setCameraType(CameraType type)
{
	_cameraType = type;
}

void MapControl::cameraOver()
{
	_cameraMoving = false;
}

void MapControl::update(float dt)
{
	Role::update(dt);

	if (_position != _node->getPosition())
	{
		_position = Point(_node->getPosition());
	}

	if (!_cameraMoving)
	{
		Point roleCenter = getRoleCenterPoint();
		if (_cameraType != CameraType::camera_hero)
		{
			cameraTo(roleCenter, 0, true, CameraType::camera_hero);
		}
		else
		{
			//setPosition(roleCenter);

			Point mapOff = _node->getPosition();
			Point screenOff = mapOff-roleCenter;
			if (screenOff.x < D_display.w/3)
			{
			}
			roleCenter = correctCamera(roleCenter);
			_node->setPosition(roleCenter);
		}
	}
}

Point MapControl::getRoleCenterPoint() const
{
	Heros *heros = BattleController::getInstance()->getHeros();
	if (heros)
	{
		Vector<HeroRole*> _roles = heros->getHeros();
		Point leftp = Point::ZERO;
		Point rightp = Point::ZERO;

		int _index = 0;
		for(auto &role : _roles)
		{
			if (_index > 0)
			{
				const float x = role->getPX();
				if (x < leftp.x) leftp.x = x;
				else if (x > rightp.x) rightp.x = x;
			}
			else if (_index == 0)
			{
				leftp = Point(role->getPX(), role->getPY());
				rightp = Point(leftp);
			}
			_index ++;
		}

		return Point(leftp+rightp)/2;
	}

	return Point::ZERO;
}
