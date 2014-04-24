#include "Task.h"
#include "AttackData.h"
#include "BattleController.h"
#include "PlayAnimiMonitor.h"
#include "RoleData.h"
#include "Monitor.h"

DEFINE_CREATE_INSTANCE_FUNC(Tasks);

Task::Task(void)
	: _finish(false)
	, _monitorType(MonitorType::MonitorAll)
{
}


Task::~Task(void)
{
}


Tasks::Tasks(void)
{
}


Tasks::~Tasks(void)
{
}

bool Tasks::init(void)
{
	_instance = this;
	_tasks.reserve(5);
	return true;
}

void Tasks::addTask(Task *task)
{
	_tasks.pushBack(task);
}

void Tasks::doTasks(MonitorType monitorType)
{
	if (_tasks.size() == 0) return;

	Task *task = _tasks.at(0);
	task->doTask(monitorType);
	if (task->isFinish()) _tasks.eraseObject(task);
}

AttackTask::AttackTask(void)
	: _attackData(nullptr)
{
}


AttackTask::~AttackTask(void)
{
	CC_SAFE_RELEASE(_attackData);
}

bool AttackTask::init(AttackData *attackData, MonitorType monitorType)
{
	if (!Task::init(monitorType)) return false;

	_attackData = attackData;
	CC_SAFE_RETAIN(_attackData);
}

void AttackTask::doTask(MonitorType monitorType)
{
	if (_monitorType == monitorType)
	{
		BattleController::getInstance()->setMonitor(PlayAnimiMonitor::create(_attackData));
	}
}

void GameStartTask::doTask(MonitorType monitorType)
{
	if (_monitorType == monitorType)
	{
		BattleController::getInstance()->setMonitor(GameStartMonitor::create());
	}
}

NewRoundTask::NewRoundTask(void)
	: _roundInfo(nullptr)
{
}

NewRoundTask::~NewRoundTask()
{
	CC_SAFE_RELEASE(_roundInfo);
}


bool NewRoundTask::init(MonitorType monitorType, RoundInfo* roundInfo)
{
	if(!Task::init(monitorType)) return false;

	_roundInfo = roundInfo;
	CC_SAFE_RETAIN(_roundInfo);

	return true;
}


void NewRoundTask::doTask(MonitorType monitorType)
{
	if (_monitorType == monitorType)
	{
		BattleController::getInstance()->setMonitor(NewRoundMonitor::create(_roundInfo));
	}
}
