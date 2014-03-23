#pragma once
#include "RPGHead.h"

class RoleHelper
{
public:
	RoleHelper(void);
	~RoleHelper(void);

	static bool checkRoleDirect(const int value, RoleDirect direct);
};

