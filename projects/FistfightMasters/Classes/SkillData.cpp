#include "SkillData.h"


SkillStepData::SkillStepData(void)
	: _stepType(SkillStepType::SKILL_STEP_NONE)
{
}

SkillStepData::~SkillStepData(void)
{
}


SkillStepHeroData::SkillStepHeroData(void)
{
	_stepType = SkillStepType::SKILL_STEP_HERO;
}

SkillStepHeroData::~SkillStepHeroData(void)
{
}

SkillStepNormalBombData::SkillStepNormalBombData(void)
{
	_stepType = SkillStepType::SKILL_STEP_NORMAL_BOMB;
}

SkillStepNormalBombData::~SkillStepNormalBombData(void)
{
}


SkillData::SkillData(void)
	: _stepDatas(new Vector<SkillStepData*>())
	, _skillType(SkillType::SkillClose)
	, _skillAttackType(SkillAttackType::attackFront1)
{
}

SkillData::~SkillData(void)
{
	CC_SAFE_DELETE(_stepDatas);
}

bool SkillData::init(void)
{
	return true;
}
