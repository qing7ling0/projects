#pragma once
#include "RPGHead.h"
#include "TouchPad.h"

USING_NS_CC;

class RoleAction : public Object
{
public:
	DirectionFlag actionFlag;
};

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
	Vector<RoleAction*> _actions;
	void touchPadCallback(Object *touchPad);
};
