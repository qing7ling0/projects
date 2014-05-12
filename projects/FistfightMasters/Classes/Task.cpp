#include "Task.h"
#include "BattleController.h"
#include "PlayAnimiMonitor.h"
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
	_instance = nullptr;
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
	if (task->isFinish()) 
		_tasks.eraseObject(task);
}

AttackTask::AttackTask(void)
	: _attackData(nullptr)
{
}


AttackTask::~AttackTask(void)
{
	_monitorType = MonitorType::MonitorAll;
	CC_SAFE_RELEASE(_attackData);
}

bool AttackTask::init(AttackData *attackData, MonitorType monitorType)
{
	if (!Task::init(monitorType)) return false;

	_attackData = attackData;
	CC_SAFE_RETAIN(_attackData);

	return true;
}

void AttackTask::doTask(MonitorType monitorType)
{
	if (_monitorType == monitorType)
	{
		setFinish(true);
		BattleController::getInstance()->setMonitor(PlayAnimiMonitor::create(_attackData));
	}
}

void GameStartTask::doTask(MonitorType monitorType)
{
	if (_monitorType == monitorType)
	{
		setFinish(true);
		BattleController::getInstance()->setMonitor(GameStartMonitor::create());
	}
}

void GameOverTask::doTask(MonitorType monitorType)
{
	if (_monitorType == monitorType)
	{
		setFinish(true);
		BattleController::getInstance()->setMonitor(GameOverMonitor::create());
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
		setFinish(true);
		BattleController::getInstance()->setMonitor(NewRoundMonitor::create(_roundInfo));
	}
}

MoveTask::MoveTask(void)
	: _finishCount(-1)
{
	_roles.reserve(5);
}

MoveTask::~MoveTask(void)
{
}

bool MoveTask::init( MonitorType monitorType)
{
	if (!Task::init(monitorType)) return false;

	return true;
}



void MoveTask::doTask(MonitorType monitorType)
{
	if (_monitorType == monitorType || _monitorType==MonitorType::MonitorAll)
	{
		if (_finishCount < 0)
		{
			_finishCount = 0;
			for(auto role : _roles)
			{
				role->getNode()->runAction(
				Sequence::create(
				JumpTo::create(0.7f, GRID_CONVER_TO_PIXEL(role->getGridIndex().x, role->getGridIndex().y), 45, 1),
					CallFunc::create([&](){
						_finishCount++;
						if (_finishCount >= _roles.size())
						{
							this->setFinish(true);
						}
					}),
					nullptr
				));
			}
		}
	}
}
