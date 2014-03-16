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
		ArmatureDataManager::getInstance()->addArmatureFileInfo("animi/robot.png",
			"animi/robot.plist",
			"animi/robot.xml");

		

		auto map = TMXTiledMap::create("map/town.tmx");
		addChild(map, 0, 1);

		HeroRole *_role = HeroRole::create(RoleData(1, D_display.cx-200, D_display.cy-100, ScriptType::scriptRobot));
		addChild(_role->getNode());

		TouchPad *_pad = TouchPad::create();
		_pad->setTouchOverCall(CC_CALLBACK_1(BattleScene::touchPadCallback, this));
		addChild(_pad, 1);

		_actions.reserve(10);

		scheduleUpdate();

		return true;
	}

	return false;
}


void BattleScene::update(float dt)
{
	//_hero->is

	if (_actions.size() > 0)
	{
		float _per = _hero->getAnimation()->getCurrentPercent();
		TouchAction *ac = _actions.at(0);
		if (ac&&_per>=1)
		{
			_hero->getAnimation()->playWithIndex(getHeroAnimiIndexByActionFlag(ac->actionFlag));
			_actions.erase(0);
		}
	}
}
int BattleScene::getHeroAnimiIndexByActionFlag(DirectionFlag flag)
{
	switch(flag)
	{
	case DirectionFlag::down:
			return 0;
	case DirectionFlag::left:
			return 1;
	case DirectionFlag::leftDown:
			return 2;
	case DirectionFlag::leftUp:
			return 3;
	case DirectionFlag::right:
			return 4;
	case DirectionFlag::rightDown:
			return 5;
	case DirectionFlag::rightUp:
			return 6;
	case DirectionFlag::up:
			return 7;
	}

	return 0;
}

void BattleScene::touchPadCallback(Object *touchPad)
{
	TouchPad *pad = static_cast<TouchPad*>(touchPad);

	for ( std::vector<DirectionFlag>::iterator iter = pad->_directionLists.begin() ; iter != pad->_directionLists.end() ; iter++ )
	{
		//CCLOG("direction = %d", *iter);
		auto ac = new TouchAction();
		ac->actionFlag = *iter;
		ac->autorelease();

		//_actions.pushBack(ac);
	};
}