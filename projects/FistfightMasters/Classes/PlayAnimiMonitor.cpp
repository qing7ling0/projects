#include "PlayAnimiMonitor.h"
#include "BattleController.h"
#include "Skill.h"


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

}

void PlayAnimiMonitor::onExit()
{
}

void PlayAnimiMonitor::update(float dt)
{
	if (_attackData && _attackData->_skills)
	{
		bool over = true;

		for(auto skill : *_attackData->_skills)
		{
			if (!skill->isStart() && !skill->isOver()) skill->start();
			skill->update(dt);
			if (!skill->isOver())
			{
				over = false;
			}
		}

		if (over) BattleController::getInstance()->setMonitor(WaitingNext::create());
	}
}