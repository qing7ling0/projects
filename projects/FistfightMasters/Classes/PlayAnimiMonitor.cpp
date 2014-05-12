#include "PlayAnimiMonitor.h"
#include "BattleController.h"
#include "Skill.h"
#include "GameServer.h"


PlayAnimiMonitor::PlayAnimiMonitor(void)
	: _attackData(nullptr)
{
}


PlayAnimiMonitor::~PlayAnimiMonitor(void)
{
	CC_SAFE_RELEASE(_attackData);
}


bool PlayAnimiMonitor::init(AttackData *attackData)
{
	if (!Monitor::init()) return false;
	_attackData = attackData;
	CC_SAFE_RETAIN(_attackData);

	return true;
}

void PlayAnimiMonitor::onEnter()
{
	if (_attackData && _attackData->_skills.size() > 0)
	{
		for(auto skill : _attackData->_skills)
		{
			if (skill) skill->loadRes();
		}
	}
}

void PlayAnimiMonitor::onExit()
{
	if (_attackData && _attackData->_skills.size() > 0)
	{
		for(auto skill : _attackData->_skills)
		{
			if (skill) skill->unloadRes();
		}
	}
}

void PlayAnimiMonitor::update(float dt)
{
	bool over = true;
	if (_attackData && _attackData->_skills.size() > 0)
	{
		for(auto skill : _attackData->_skills)
		{
			if (!skill->isStart() && !skill->isOver()) skill->start();
			skill->update(dt);
			if (!skill->isOver())
			{
				over = false;
			}
		}
	}

	if (over)
	{
		GameServer::getInstance()->nextRound();
		BattleController::getInstance()->setMonitor(WaitingNext::create());
	}
}