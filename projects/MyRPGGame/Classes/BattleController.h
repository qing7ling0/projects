#pragma once
#include "RPGHead.h"
#include "TouchControl.h"

USING_NS_CC;

class Heros;
class HeroRole;
class TouchPad;

class BattleController : public Layer
{
public:
	BattleController(void);
	~BattleController(void);

	static BattleController* getInstance();

	virtual bool init();

	virtual void update(float dt);

	virtual void cleanup();

	TouchPad* getTouchPad() { return _touchPad; }

	Heros* getHeros() { return _heros; }

	static Scene* createScene();

    CREATE_FUNC(BattleController);

private:
	int getHeroAnimiIndexByActionFlag(DirectionFlag flag);
	void touchPadCallback(Ref *touchPad);

private:
	Heros* _heros;
	TouchPad *_touchPad;
};
