#pragma once
#include "RPGHead.h"
#include "Monitor.h"
#include "AttackData.h"

class PlayAnimiMonitor : public Monitor
{
public:
	PlayAnimiMonitor(void);
	~PlayAnimiMonitor(void);

	bool init(AttackData *attackData);

	void onEnter(void);

	void onExit(void);

	void update(float dt);
	
	F_CREATE_FUNC_ARGS_1(PlayAnimiMonitor, AttackData*, attackData );

protected:
	AttackData *_attackData;
};

