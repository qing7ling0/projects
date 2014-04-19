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


void AttackData::addSkill(const Skill* skill)
{
	if (_skills)
	{
		_skills->pushBack(skill);
	}
}