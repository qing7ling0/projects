#include "Monitor.h"
#include "BattleController.h"
#include "MessageServer.h"
#include "SelfMonitor.h"
#include "TopLayer.h"
#include "GameServer.h"


Monitor::Monitor(void)
	: _over(false)
	, _step(0)
	, f_time(0)
{
}


Monitor::~Monitor(void)
{
}

bool Monitor::init(void)
{
	return true;
}

void Monitor::update(float dt) { }

void Monitor::onEnter() { }

void Monitor::onExit() { }


void WaitingNext::update(float dt)
{
}

NewRoundMonitor::NewRoundMonitor(void)
	: _roundInfo(nullptr)
{
}


NewRoundMonitor::~NewRoundMonitor(void)
{
	CC_SAFE_RELEASE(_roundInfo);
}

bool NewRoundMonitor::init(RoundInfo* roundInfo)
{
	if (!Monitor::init()) return false;

	_roundInfo = roundInfo;
	CC_SAFE_RETAIN(_roundInfo);
	return true;
}

void NewRoundMonitor::onEnter()
{
	Monitor::onEnter();
	if (_roundInfo) BattleController::getInstance()->setRoundInfo(_roundInfo);
}

void NewRoundMonitor::update(float dt)
{
	if (_step == 0)
	{
		_step++;
		if (_roundInfo->_selfRound)
			BattleController::getInstance()->setMonitor(SelfMonitor::create());
		else
			BattleController::getInstance()->setMonitor(OtherMonitor::create());
	}
}

void GameStartMonitor::onEnter()
{
	BattleController::getInstance()->getTopLayer()->gameStart();
}

void GameStartMonitor::update(float dt)
{
	if (_step == 0)
	{
		f_time += dt;
		if (f_time > 2)
		{
			_step++;
			BattleController::getInstance()->setMonitor(WaitingNext::create());
		}
	}
}

void GameOverMonitor::onEnter()
{
	bool win = BattleController::getInstance()->getGameWin();
	if (win)
		MessageServer::getInstance()->addMessage(MessageItem::create("You Win!"));
	else
		MessageServer::getInstance()->addMessage(MessageItem::create("You Lose!"));
}

void GameOverMonitor::update(float dt)
{
	if (_step == 0)
	{
		f_time += dt;
		if (f_time > 3)
		{
			_step++;
			BattleController::getInstance()->gameEnd();
		}
	}
}

void OtherMonitor::update(float dt)
{
	if (_step == 0)
	{
		f_time = 0;
		_step++;
	}
	else if (_step == 1)
	{
		f_time += dt;
		if (f_time > 3)
		{
			_step++;
		}
	}
	else if (_step == 2)
	{
		setOver(true);
		_step++;
		GameServer::getInstance()->attack();
		BattleController::getInstance()->setMonitor(WaitingNext::create());
	}
}