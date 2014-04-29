#include "Skill.h"
#include "BattleRoles.h"


Skill::Skill(void)
	: _skillStep(nullptr)
	, _over(false)
	, _start(false)
{
}


Skill::~Skill(void)
{
	CC_SAFE_RELEASE(_skillStep);
}

bool Skill::init(SkillStep *skillStep)
{

	_skillStep = skillStep;
	CC_SAFE_RETAIN(_skillStep);

	return true;
}

void Skill::start()
{
	//getCanAttackRoles();
	setStart(true);
	setOver(false);
	if (_skillStep) _skillStep->start();
}

void Skill::stop()
{
	setStart(false);
	setOver(true);
	if (_skillStep) _skillStep->stop();
}

void Skill::loadRes()
{
	if(_skillStep) _skillStep->loadRes();
}

void Skill::unloadRes()
{
	if(_skillStep) _skillStep->unloadRes();
}

void Skill::update(float dt)
{
	if(_skillStep)
	{
		_skillStep->update(dt);
		if (_skillStep->isOver())
		{
			setOver(true);
		}
	}
}

void Skill::doDamage()
{


}

const int Skill::getDamage() const
{
	return 100;
}

