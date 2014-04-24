#include "Skill.h"
#include "BattleRoles.h"


Skill::Skill(void)
	: _skillStep(nullptr)
	, _srcRole(nullptr)
	, _skillAttackType(SkillAttackType::attackFront1)
	, _skillType(SkillType::SkillClose)
{
}


Skill::~Skill(void)
{
	CC_SAFE_RELEASE(_skillStep);

	CC_SAFE_RELEASE(_srcRole);
}

bool Skill::init(SkillStep *skillStep)
{
	_targetRoles.reserve(5);

	_skillStep = skillStep;
	CC_SAFE_RETAIN(_skillStep);

	return true;
}

void Skill::start()
{
	//getCanAttackRoles();
	if (_skillStep) _skillStep->start();
}

void Skill::stop()
{
	if (_skillStep) _skillStep->stop();
}

void Skill::doDamage()
{


}

const int Skill::getDamage() const
{
	return 100;
}

