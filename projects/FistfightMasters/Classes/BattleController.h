#pragma once
#include "RPGHead.h"
#include "BattleConfig.h"

class BattleMap;

class BattleController : public Layer
{
public:
	BattleController(void);
	~BattleController(void);

	bool init(void);

	BattleMap* getMap() { return _map; }

	CREATE_SECNE_FUNC(BattleController);

	static BattleController* getInstance();

private:
	BattleMap *_map;
};

