#include "SkillData.h"

SkillData::SkillData(void)
	: _stepDatas(new Vector<SkillStepData*>())
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
