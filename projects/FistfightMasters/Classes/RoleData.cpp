#include "RoleData.h"

SkillData::SkillData(void)
{
}


SkillData::~SkillData(void)
{
}

bool SkillData::init(void)
{

	return true;
}

RoleData::RoleData(void)
	:_roleAnimiActions(nullptr)
{
}


RoleData::~RoleData(void)
{
	CC_SAFE_DELETE(_roleAnimiActions);
}

bool RoleData::init(void)
{
	_skillDatas.reserve(3);
	return true;
}
