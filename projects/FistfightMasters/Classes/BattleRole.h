#pragma once
#include "RPGHead.h"
#include "Role.h"


class BattleRole : public Role
{
public:
	BattleRole(void);
	~BattleRole(void);
protected:
	Point _gridIndex;
};

