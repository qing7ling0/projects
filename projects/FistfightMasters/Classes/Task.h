#pragma once
#include "RPGHead.h"
#include "RoleData.h"
#include "BattleConfig.h"
#include "AttackData.h"


class Task : public Ref
{
public:
	Task(void);
	~Task(void);

	virtual bool init(MonitorType monitorType=MonitorType::MonitorAll) { _monitorType=monitorType; return true; };

	virtual void doTask(MonitorType monitorType) {};

	virtual bool isFinish() { return _finish; }

	virtual void setFinish(bool finish) { _finish = finish; }

protected:
	bool _finish;
	MonitorType _monitorType;
};


class Tasks : public Ref
{
public:
	Tasks(void);
	~Tasks(void);

	bool init(void);

	void addTask(Task *task);

	void doTasks(MonitorType monitorType);

	//void do

	CREATE_FUNC(Tasks);

	EXTERN_CREATE_INSTANCE_FUNC(Tasks);

protected:
	Vector<Task*> _tasks;
};

class AttackTask : public Task
{
public:
	AttackTask(void);
	~AttackTask(void);

	virtual bool init(AttackData *attackData, MonitorType monitorType);

	virtual void doTask(MonitorType monitorType);

	F_CREATE_FUNC_ARGS_2(AttackTask, AttackData*, attackData, MonitorType, monitorType);

protected:
	AttackData *_attackData;
};

class GameStartTask : public Task
{
public:
	virtual void doTask(MonitorType monitorType);

	F_CREATE_FUNC_ARGS_1(GameStartTask, MonitorType, monitorType);

};

class GameOverTask : public Task
{
public:
	virtual void doTask(MonitorType monitorType);

	F_CREATE_FUNC_ARGS_1(GameOverTask, MonitorType, monitorType);

};

class NewRoundTask : public Task
{
public:
	NewRoundTask(void);
	~NewRoundTask(void);

	bool init(MonitorType monitorType, RoundInfo* roundInfo);

	virtual void doTask(MonitorType monitorType);

	F_CREATE_FUNC_ARGS_2(NewRoundTask, MonitorType, monitorType, RoundInfo*, roundInfo);

protected:
	RoundInfo* _roundInfo;
};


class MoveTask : public Task
{
public:
	MoveTask(void);
	~MoveTask(void);

	bool init(MonitorType monitorType);

	void addRole(BattleRole *role) { _roles.pushBack(role); };

	virtual void doTask(MonitorType monitorType);

	F_CREATE_FUNC_ARGS_1(MoveTask, MonitorType, monitorType);
	
protected:
	Vector<BattleRole*> _roles;
	int _finishCount;
};