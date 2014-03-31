#include "MapControl.h"
#include "BattleController.h"
#include "Heros.h"
#include "HeroRole.h"

static MapControl *_instance = nullptr;

MapControl::MapControl(void)
	: _size (Size::ZERO)
	, _cameraType (CameraType::camera_none)
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

Size MapControl::getMapSize()
{
	return _size;
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
* 纠正镜头偏移,不能出界
* 并转化成Map的实际偏移量
**/
Point MapControl::correctCamera(const Point off)
{
	Point offTo = Point(off);

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
		}

		return (rightp + leftp) / 2;
	}

	return Point::ZERO;
}
