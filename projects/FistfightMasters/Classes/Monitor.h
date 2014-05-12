#pragma once
#include "RPGHead.h"
#include "BattleConfig.h"
#include "RoleData.h"

class Monitor : public Ref
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

	virtual bool canBreak() { return true; }

	virtual MonitorType getMonitorType() { return MonitorType::MonitorAll; }

protected:
	bool _over;
	int _step;
	float f_time;
};

class WaitingNext : public Monitor
{
public:

	virtual void update(float dt);

	MonitorType getMonitorType() { return MonitorType::MonitorWaitNext; }

	CREATE_FUNC(WaitingNext);
};

class NewRoundMonitor : public Monitor
{
public:
	NewRoundMonitor(void);
	~NewRoundMonitor(void);

	virtual bool init(RoundInfo* roundInfo);
	
	virtual void onEnter(void);

	virtual void update(float dt);

	MonitorType getMonitorType() { return MonitorType::MonitorNewRound; }

	F_CREATE_FUNC_ARGS_1(NewRoundMonitor, RoundInfo*, roundInfo);

private:
	RoundInfo* _roundInfo;
};

class GameStartMonitor : public Monitor
{
public:
	virtual void onEnter(void);

	virtual void update(float dt);

	MonitorType getMonitorType() { return MonitorType::MonitorGameStart; }

	CREATE_FUNC(GameStartMonitor);
};

class GameOverMonitor : public Monitor
{
public:
	virtual void onEnter(void);

	virtual void update(float dt);

	MonitorType getMonitorType() { return MonitorType::MonitorGameOver; }

	CREATE_FUNC(GameOverMonitor);
};

class OtherMonitor : public Monitor
{
public:

	void update(float dt);

	CREATE_FUNC(OtherMonitor);

protected:

};
