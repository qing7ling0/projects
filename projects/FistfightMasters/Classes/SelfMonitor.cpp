#include "SelfMonitor.h"
#include "BattleController.h"
#include "AttackMonitor.h"
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
	if (step == 0)
	{
		f_time = 0;
		step++;
	}
	else if (step == 1)
	{
		f_time += dt;
		if (f_time > 2)
		{
			step++;
		}
	}
	else if (step == 2)
	{
		setOver(true);
		BattleController::getInstance()->setMonitor(AttackMonitor::create(BattleRoles::getInstance()->getSelfRoles()));
		step++;
	}
}


