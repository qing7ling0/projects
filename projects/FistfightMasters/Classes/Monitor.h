#pragma once
#include "RPGHead.h"
#include "BattleConfig.h"

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

class WaitNewRound : public Monitor
{
public:

	virtual void update(float dt);

	MonitorType getMonitorType() { return MonitorType::MonitorWaitNewRound; }

	CREATE_FUNC(WaitNewRound);

};
