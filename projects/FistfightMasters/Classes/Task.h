#pragma once
#include "RPGHead.h"
#include "RoleData.h"
#include "BattleConfig.h"

class AttackData;

class Task : public Object
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


class Tasks : public Object
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