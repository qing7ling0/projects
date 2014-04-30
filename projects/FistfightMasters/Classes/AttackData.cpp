#include "AttackData.h"
#include "Skill.h"


AttackData::AttackData(void)
{
}


AttackData::~AttackData(void)
{
}

bool AttackData::init()
{
	_skills.reserve(1);
	return true;
}

void AttackData::addSkill(Skill *skill)
{
	_skills.pushBack(skill);
}
