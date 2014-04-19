#include "AttackMonitor.h"
#include "BattleController.h"
#include "PlayAnimiMonitor.h"


AttackMonitor::AttackMonitor(void)
{
}


AttackMonitor::~AttackMonitor(void)
{
}

bool AttackMonitor::init(Vector<BattleRole*> attackRoles)
{
	if (!Monitor::init()) return false;

	_attackRoles = attackRoles;

	return true;
}

void AttackMonitor::onEnter()
{
}

void AttackMonitor::onExit()
{
}

void AttackMonitor::attack()
{

}

void AttackMonitor::update(float dt)
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
		attack();
		step++;
	}
	else if (step == 3)
	{
		setOver(true);
		BattleController::getInstance()->setMonitor(PlayAnimiMonitor::create());
		step++;
	}
}