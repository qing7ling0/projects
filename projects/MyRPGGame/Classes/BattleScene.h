#pragma once
#include "RPGHead.h"
#include "TouchPad.h"

USING_NS_CC;

class BattleScene : public Layer
{
public:
	BattleScene(void);
	~BattleScene(void);

	virtual bool init();  

	CREATE_SECNE_FUNC(BattleScene);
};

