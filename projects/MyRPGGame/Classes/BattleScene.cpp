#include "BattleScene.h"


BattleScene::BattleScene(void)
{
}


BattleScene::~BattleScene(void)
{
}

bool BattleScene::init(void)
{
	if (Layer::init())
	{
		auto map = TMXTiledMap::create("map/town.tmx");
		addChild(map, 0, 1);

		TouchPad *_pad = TouchPad::create();
		addChild(_pad, 1);

		return true;
	}

	return false;
}