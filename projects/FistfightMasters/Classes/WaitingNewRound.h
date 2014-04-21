#pragma once
#include "RPGHead.h"
#include "Monitor.h"

class WaitingNewRound : public Monitor
{
public:

	virtual void update(float dt)

	CREATE_FUNC(WaitingNewRound);
};

