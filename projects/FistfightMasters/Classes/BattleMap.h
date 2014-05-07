#pragma once
#include "BattleController.h"

class BattleMap : public Ref
{
public:
	BattleMap(void);
	~BattleMap(void);

	bool init(void);

	CREATE_FUNC(BattleMap);

private:



	Layer *_battleLayer;

	bool grids[50];
};

