#pragma once
#include "RPGHead.h"
#include "HeroRole.h"
#include "BattleController.h"


class Heros : public Object
{
public:
	Heros(void);
	~Heros(void);

	static Heros* create();

	void init();

	void update(float dt);

	Vector<HeroRole*> getHeros() { return _heros; }

	void initHeros(RoleData *datas, int size);

	void doTouchActions(std::vector<DirectionFlag> directionFlags);
	
private:
	Vector<HeroRole*> _heros;
};

