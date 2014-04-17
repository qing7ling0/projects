#pragma once
#include "BattleController.h"

class BattleMap : public Object
{
public:
	BattleMap(void);
	~BattleMap(void);

	bool init(void);

	CREATE_FUNC(BattleMap);

	static Point getGameMapGirdPosition(Point grid);

private:



	Layer *_battleLayer;

	bool grids[50];
};

