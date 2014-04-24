#pragma once
#include "RPGHead.h"
#include "BattleConfig.h"
#include "RoleData.h"

class Monitor : public Object
{
public:
	Monitor(void);
	~Monitor(void);

	virtual bool init(void);

	virtual void update(float dt);

	virtual void onEnter(void);

	virtual void onExit(void);

	virtual bool isOver() { return _over; }

	virtual void setOver(bool over) { _over = over; }

	virtual MonitorType getMonitorType() { return MonitorType::MonitorAll; }

protected:
	bool _over;
	int step;
	float f_time;
};

class WaitingNext : public Monitor
{
public:

	virtual void update(float dt);

	MonitorType getMonitorType() { return MonitorType::MonitorWaitNext; }

	CREATE_FUNC(WaitingNext);
};

class GameStartMonitor : public Monitor
{
};
