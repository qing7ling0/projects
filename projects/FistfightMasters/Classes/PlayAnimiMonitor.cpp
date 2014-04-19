#include "PlayAnimiMonitor.h"


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
}