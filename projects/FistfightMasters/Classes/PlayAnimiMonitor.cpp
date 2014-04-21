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
	if (_attackData && _attackData->_skill)
	{
		_attackData->_skill->update(dt);
		if (_attackData->_skill->isOver())
		{
			BattleController::getInstance()->setMonitor(WaitNewRound::create());
		}
	}
}