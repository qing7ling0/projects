#pragma once
#include "RPGHead.h"
#include "TouchPad.h"
#include "HeroRole.h"
#include "TouchControl.h"

USING_NS_CC;

class BattleScene : public Layer
{
public:
	BattleScene(void);
	~BattleScene(void);

	virtual bool init();  
	virtual void update(float dt);  

	CREATE_SECNE_FUNC(BattleScene);

private:
	int getHeroAnimiIndexByActionFlag(DirectionFlag flag);


private:
	Armature *_hero;
	Vector<TouchAction*> _actions;
	void touchPadCallback(Object *touchPad);
};
