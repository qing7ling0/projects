#include "AttackData.h"
#include "Skill.h"


AttackData::AttackData(void)
	: _skills(new Vector<Skill*>())
{
}


AttackData::~AttackData(void)
{
	CC_SAFE_DELETE(_skills);
}

bool AttackData::init()
{
	return true;
}

void AttackData::addSkill(Skill *skill)
{
	_skills->pushBack(skill);
}