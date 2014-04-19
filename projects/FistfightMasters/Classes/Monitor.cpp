#include "Monitor.h"


Monitor::Monitor(void)
	: _over(false)
	, step(0)
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