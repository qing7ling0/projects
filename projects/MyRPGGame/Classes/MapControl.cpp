#include "MapControl.h"
#include "BattleController.h"

static MapControl *_instance = nullptr;

MapControl::MapControl(void)
	: _mapLayer(nullptr)
	, _size(Size::ZERO)
{
}


MapControl::~MapControl(void)
{
	CC_SAFE_RELEASE(_mapLayer);
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

void MapControl::init()
{
	auto map = TMXTiledMap::create("map/town.tmx");
	if (map)
	{
		_mapLayer = map;
		_mapLayer->retain();
		_size = Size(map->getContentSize());
		BattleController::getInstance()->addChild(map, -1, 1);
	}
}

Size MapControl::getMapSize()
{
	return _size;
}
