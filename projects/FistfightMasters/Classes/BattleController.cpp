#include "BattleController.h"
#include "BattleMap.h"
#include "BattleRoles.h"
#include "BattleRole.h"
#include "Monitor.h"
#include "MessageServer.h"
#include "Task.h"
#include "GameServer.h"
#include "TopLayer.h"

static BattleController *_instance = nullptr;

BattleController::BattleController(void)
	: _map(nullptr)
	, _battleRoles(nullptr)
	, _monitor(nullptr)
	, _roundInfo(nullptr)
	, _gameServer(nullptr)
	, _tasks(nullptr)
	, _loadRes(false)
	, _topLayer(nullptr)
{
}

BattleController::~BattleController(void)
{
	CC_SAFE_RELEASE(_map);
	CC_SAFE_RELEASE(_battleRoles);
	CC_SAFE_RELEASE(_monitor);
	CC_SAFE_RELEASE(_roundInfo);
	CC_SAFE_RELEASE(_gameServer);
	CC_SAFE_RELEASE(_tasks);
	CC_SAFE_RELEASE(_topLayer);
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

	_tasks = Tasks::create();
	CC_SAFE_RETAIN(_tasks);

	_gameServer = GameServer::create();
	CC_SAFE_RETAIN(_gameServer);

	MessageServer::create();
	addChild(MessageServer::getInstance());

	_topLayer = TopLayer::create();
	addChild(_topLayer);

	setMonitor(WaitingNext::create());

	return true;
}

void BattleController::loadRes(void)
{
	Director::getInstance()->getTextureCache()->addImage("images/battle_hurt_boji_num.png");
	Director::getInstance()->getTextureCache()->addImage("images/battle_hurt_add_num.png");
	Director::getInstance()->getTextureCache()->addImage("images/battle_hurt_add.png");
	Director::getInstance()->getTextureCache()->addImage("images/battle_hurt_boji_reduce.png");
	Director::getInstance()->getTextureCache()->addImage("images/battle_blood_01.png");
	Director::getInstance()->getTextureCache()->addImage("images/battle_blood_bg.png");
	Director::getInstance()->getTextureCache()->addImage("images/battle_your_turn.png");
	Director::getInstance()->getTextureCache()->addImage("images/img_battle_start.png");
}

void BattleController::unloadRes(void)
{
	Director::getInstance()->getTextureCache()->removeTextureForKey("images/battle_hurt_boji_num.png");
	Director::getInstance()->getTextureCache()->removeTextureForKey("images/battle_hurt_add_num.png");
	Director::getInstance()->getTextureCache()->removeTextureForKey("images/battle_hurt_add.png");
	Director::getInstance()->getTextureCache()->removeTextureForKey("images/battle_hurt_boji_reduce.png");
	Director::getInstance()->getTextureCache()->removeTextureForKey("images/battle_blood_01.png");
	Director::getInstance()->getTextureCache()->removeTextureForKey("images/battle_blood_bg.png");
	Director::getInstance()->getTextureCache()->removeTextureForKey("images/battle_your_turn.png");
	Director::getInstance()->getTextureCache()->removeTextureForKey("images/img_battle_start.png");
}

void BattleController::onEnter(void)
{
	Layer::onEnter();
	loadRes();
	scheduleUpdate();
	gameStart();
}

void BattleController::onExit(void)
{
	Layer::onExit();
	unloadRes();
	unscheduleUpdate();
}

void BattleController::gameStart()
{
	GameServer::getInstance()->gameStart();
}

void BattleController::setMonitor(Monitor *monitor)
{
	if (_monitor == monitor) return;

	if (_monitor)
	{
		_monitor->setOver(true);
		_monitor->onExit();
		CC_SAFE_RELEASE(_monitor);
		_monitor = nullptr;
	}
	if (monitor)
	{
		_monitor = monitor;
		if (_monitor) monitor->onEnter();
		CC_SAFE_RETAIN(_monitor);
	}
}

void BattleController::update(float dt)
{
	if (_monitor) _monitor->update(dt);
	if (_monitor) Tasks::getInstance()->doTasks(_monitor->getMonitorType());

	GameServer::getInstance()->update(dt);
}