#include "AttackData.h"
#include "Skill.h"


AttackData::AttackData(void)
	: _skill(nullptr)
{
}


AttackData::~AttackData(void)
{
	CC_SAFE_DELETE(_skill);
}

bool AttackData::init(Skill *skill)
{
	_skill = skill;
	CC_SAFE_RETAIN(_skill);
}