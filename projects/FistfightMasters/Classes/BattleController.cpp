#include "BattleController.h"
#include "BattleMap.h"
#include "BattleRoles.h"
#include "BattleRole.h"
#include "Monitor.h"

static BattleController *_instance = nullptr;

BattleController::BattleController(void)
	: _map(nullptr)
	, _battleRoles(nullptr)
	, _monitor(nullptr)
{
}

BattleController::~BattleController(void)
{
	CC_SAFE_RELEASE(_map);
	CC_SAFE_RELEASE(_battleRoles);
	CC_SAFE_RELEASE(_monitor);
}

BattleController* BattleController::getInstance()
{
	return _instance;
}

bool BattleController::init(void)
{
    if ( !Layer::init() )
    {
        return false;
    }

	_instance = this;

	auto _uiLayer = Layer::create();
	_uiLayer->setPosition(Point(D_display.getLeftBottom()));
	addChild(_uiLayer);

	_map = BattleMap::create();
	CC_SAFE_RETAIN(_map);

	_battleRoles = BattleRoles::create();
	CC_SAFE_RETAIN(_battleRoles);

	return true;
}

void BattleController::onEnter(void)
{
	Layer::onEnter();
	scheduleUpdate();
}

void BattleController::onExit(void)
{
	Layer::onExit();
	unscheduleUpdate();
}

void BattleController::gameStart()
{

}

void BattleController::setMonitor(Monitor *monitor)
{
	if (_monitor)
	{
		_monitor->setOver(true);
		_monitor->onExit();
		CC_SAFE_RELEASE(_monitor);
	}
	_monitor = monitor;
	if (_monitor) monitor->onEnter();
	CC_SAFE_RETAIN(_monitor);
}

void BattleController::update(float dt)
{
	if (_monitor) _monitor->update(dt);
}