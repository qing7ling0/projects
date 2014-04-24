#include "SelfMonitor.h"
#include "BattleController.h"
#include "GameServer.h"
#include "BattleRoles.h"


SelfMonitor::SelfMonitor(void)
{
}


SelfMonitor::~SelfMonitor(void)
{
}

bool SelfMonitor::init(void)
{
	if (!Monitor::init()) return false;

	return true;
}

void SelfMonitor::onEnter()
{
}

void SelfMonitor::onExit()
{
}

void SelfMonitor::update(float dt)
{
	if (_step == 0)
	{
		f_time = 0;
		_step++;
	}
	else if (_step == 1)
	{
		f_time += dt;
		if (f_time > 2)
		{
			_step++;
		}
	}
	else if (_step == 2)
	{
		setOver(true);
		BattleController::getInstance()->setMonitor(WaitingNext::create());
		GameServer::getInstance()->attack();
		_step++;
	}
}


