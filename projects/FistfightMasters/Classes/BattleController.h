#pragma once
#include "RPGHead.h"
#include "BattleConfig.h"
#include "RoleData.h"

class BattleMap;
class BattleRoles;
class Monitor;
class GameServer;
class Tasks;

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

	BattleMap* getMap() { return _map; }

	void setMonitor(Monitor *monitor);

	Monitor* getMonitor() { return _monitor; }

	void initNewRound() {}

	CC_SYNTHESIZE_RETAIN(RoundInfo*, _roundInfo, RoundInfo);

	CREATE_SECNE_FUNC(BattleController);

	static BattleController* getInstance();

private:
	BattleMap *_map;

	BattleRoles *_battleRoles;

	Monitor *_monitor;

	GameServer *_gameServer;

	Tasks *_tasks;
};

