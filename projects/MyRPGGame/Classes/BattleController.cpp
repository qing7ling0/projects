#include "BattleController.h"
#include "TouchPad.h"
#include "HeroRole.h"
#include "Heros.h"
#include "MapControl.h"
#include "FollowRoles.h"

static BattleController* _instance = nullptr;

Scene* BattleController::createScene()
{
    auto scene = Scene::create();
    
    auto layer = BattleController::create();

    scene->addChild(layer);

    return scene;
}

BattleController::BattleController(void)
	: _heros (nullptr)
	, _touchPad (nullptr)
{
}


BattleController::~BattleController(void)
{
	_instance = nullptr;
}

BattleController* BattleController::getInstance()
{
	return _instance;
}

bool BattleController::init(void)
{
	if (Layer::init())
	{
		_instance = this;

		RoleData *datas = new RoleData[1];
		datas[0] = RoleData(1, D_display.cx-200, D_display.cy-100, ScriptType::scriptRobot);

		MapControl::getInstance();

		_heros = Heros::create();
		_heros->initHeros(datas, 1);

		//HeroRole *hero = HeroRole::create(RoleData(1, D_display.cx-200, D_display.cy-100, ScriptType::scriptRobot));
		//this->addChild(hero->getNode());


		_touchPad = TouchPad::create();
		_touchPad->setTouchOverCall(CC_CALLBACK_1(BattleController::touchPadCallback, this));
		addChild(_touchPad, 1);

		scheduleUpdate();

		return true;
	}

	return false;
}


void BattleController::update(float dt)
{
	_heros->update(dt);

	MapControl::getInstance()->update(dt);

	FollowRoles::getInstance()->update(dt);
}

int BattleController::getHeroAnimiIndexByActionFlag(DirectionFlag flag)
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

void BattleController::touchPadCallback(Object *touchPad)
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

	_heros->doTouchActions(pad->_directionLists);
}

void BattleController::cleanup()
{
	Layer::cleanup();
	_instance = nullptr;
}