#include "MapControl.h"
#include "BattleController.h"
#include "Heros.h"
#include "HeroRole.h"

static MapControl *_instance = nullptr;

MapControl::MapControl(void)
	: _size (Size::ZERO)
	, _cameraType (CameraType::camera_none)
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
	}
}

Size MapControl::getMapSize()
{
	return _size;
}

bool MapControl::cameraTo(const Point point, float delayTime, bool force)
{
	if (force || !_cameraMoving)
	{
		_cameraMoving = true;

		Point offTo = Point(point);
		offTo.x -= D_display.w/2;
		if (offTo.x < 0) offTo.x = 0;
		else if (offTo.x > _size.width) offTo.x = _size.width;

		Point curPosition = _node->getPosition();
	
		float gapX = curPosition.x - offTo.x;
		float gapY = curPosition.y - offTo.y;
		float timex = abs( gapX / D_display.w * MAX_MOVE_TIME );
		float timey = abs( gapY / D_display.h * MAX_MOVE_TIME );

		Point rolePoint = getRoleCenterPoint();

		auto actionToRole =  Spawn::create(
			EaseOut::create(MoveBy::create(timex, Point(gapX, 0)), 2),
			EaseOut::create(MoveBy::create(timey, Point(0, gapY)), 2),
			NULL
			);

		auto action1 = Spawn::create(
			EaseOut::create(MoveBy::create(timex, Point(gapX, 0)), 2),
			EaseOut::create(MoveBy::create(timey, Point(0, gapY)), 2),
			NULL
			);
		auto action2 = Sequence::create(
			action1,
			DelayTime::create(delayTime),
			action1->reverse(),
			CallFunc::create( std::bind(&MapControl::cameraOver) ),
			CallFunc::create( std::bind(&MapControl::setCameraType, CameraType::camera_hero) ),
			NULL
			);

		_node->runAction(action2);

		return true;
	}

	return false;
}

// 当切换到由角色来控制，先把镜头移动到角色上
void MapControl::cameraToRole()
{

}

void MapControl::setCameraType(CameraType type)
{
	// 当切换到由角色来控制，先把镜头移动到角色上
	if (type != _cameraType && type == CameraType::camera_hero)
	{

	}
	_cameraType = type;

}

void MapControl::cameraOver()
{
	_cameraMoving = false;
}

bool MapControl::cameraMoving()
{
	return _cameraMoving;
}

void MapControl::update(float dt)
{
	if (_cameraType == CameraType::camera_hero)
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
					leftp = Point(role->getPX(), role->getPY);
					rightp = Point(leftp);
				}
			}

			Point offTo = (rightp + leftp) / 2;
			offTo.x -= D_display.w/2;
			if (offTo.x < 0) offTo.x = 0;
			else if (offTo.x > _size.width) offTo.x = _size.width;

			Point curPosition = _node->getPosition();
			if (offTo != curPosition)
			{


				_node->runAction(EaseOut::create(MoveBy::create(0.5f, offTo), 2));
			}
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
				leftp = Point(role->getPX(), role->getPY);
				rightp = Point(leftp);
			}
		}

		Point offTo = (rightp + leftp) / 2;
		offTo.x -= D_display.w/2;
		if (offTo.x < 0) offTo.x = 0;
		else if (offTo.x > _size.width) offTo.x = _size.width;

		return offTo;
	}

	return Point::ZERO;
}
