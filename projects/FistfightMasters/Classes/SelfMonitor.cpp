#include "SelfMonitor.h"
#include "BattleController.h"
#include "GameServer.h"
#include "BattleRoles.h"
#include "TopLayer.h"


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
	Monitor::onEnter();
	//MessageServer::getInstance()->addMessage(MessageItem::create("ÂÖµ½Äã¹¥»÷À²£¡"));
	BattleController::getInstance()->getTopLayer()->yourTurn();
}

void SelfMonitor::onExit()
{
	Monitor::onExit();
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
		if (f_time > 1)
		{
			_step++;
		}
	}
	else if (_step == 2)
	{
		setOver(true);
		_step++;
		GameServer::getInstance()->attack();
		GameServer::getInstance()->nextRound();
		BattleController::getInstance()->setMonitor(WaitingNext::create());
	}
}


