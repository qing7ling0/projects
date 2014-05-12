#pragma once
#include "RPGHead.h"
#include "BattleConfig.h"
#include "RoleData.h"

class BattleMap;
class BattleRoles;
class Monitor;
class GameServer;
class Tasks;
class TopLayer;

class BattleController : public Layer
{
public:
	BattleController(void);
	~BattleController(void);

	bool init(void);

	void onEnter(void);

	void onExit(void);

	void update(float dt);

	void gameStart();

	void gameEnd();

	void loadRes();

	void unloadRes();

	BattleMap* getMap() { return _map; }

	void setMonitor(Monitor *monitor);

	Monitor* getMonitor() { return _monitor; }

	void initNewRound() {}

	TopLayer* getTopLayer() { return _topLayer; }

	//static Scene* BattleController::createScene()
	//{
	//	// 'scene' is an autorelease object
	//	auto scene = Scene::create();
 //   
	//	// 'layer' is an autorelease object
	//	auto layer = BattleController::create();

	//	// add layer as a child to scene
	//	scene->addChild(layer);

	//	// return the scene
	//	return scene;
	//}

	CC_SYNTHESIZE_RETAIN(RoundInfo*, _roundInfo, RoundInfo);

	CREATE_SECNE_FUNC(BattleController);

	static BattleController* getInstance();

	CC_SYNTHESIZE(bool, _gameWin, GameWin);

private:
	BattleMap *_map;

	BattleRoles *_battleRoles;

	Monitor *_monitor;

	GameServer *_gameServer;

	Tasks *_tasks;

	TopLayer *_topLayer;

	bool _loadRes;
};

