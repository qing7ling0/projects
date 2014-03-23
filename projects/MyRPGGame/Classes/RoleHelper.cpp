#include "RoleHelper.h"


RoleHelper::RoleHelper(void)
{
}


RoleHelper::~RoleHelper(void)
{
}


bool RoleHelper::checkRoleDirect(const int value, RoleDirect direct)
{
	return (value&direct) > 0;
}
