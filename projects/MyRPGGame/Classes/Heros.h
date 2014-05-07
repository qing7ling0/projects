#pragma once
#include "RPGHead.h"

class RoleScript;
class HeroRole;
class BattleController;

class Heros : public Ref
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

