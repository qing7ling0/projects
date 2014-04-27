#pragma once
#include "RPGHead.h"
#include "Monitor.h"

class SelfMonitor : public Monitor
{
public:
	SelfMonitor(void);
	~SelfMonitor(void);

	bool init(void);

	void onEnter(void);

	void onExit(void);

	void update(float dt);

	CREATE_FUNC(SelfMonitor);

protected:

};

