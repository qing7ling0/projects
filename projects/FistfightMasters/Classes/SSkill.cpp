#include "SSkill.h"
#include "BattleRole.h"
#include "BattleRoles.h"
#include "Skill.h"

SSkill::SSkill(void)
	: _stepDatas(new Vector<SkillStepData*>())
	, _attackRole(nullptr)
	, _skillAttackType(SkillAttackType::attackFront1)
{
}


SSkill::~SSkill(void)
{
	CC_SAFE_DELETE(_stepDatas);
	CC_SAFE_RELEASE(_attackRole);
}

bool SSkill::init(SkillAttackType skillAttackType, BattleRole *attackRole, Vector<SkillStepData*> &stepDatas)
{
	_targetRoles.reserve(5);
	_skillAttackType = skillAttackType;
	_attackRole = attackRole;
	CC_SAFE_RETAIN(_attackRole);
	_stepDatas->reserve(3);

	for(auto &step : stepDatas)
	{
		_stepDatas->pushBack(step);
	}

	return true;
}

std::vector<Point> SSkill::getCanAttackGrids(SkillAttackType skillAttackType, BattleRole *attackRole)
{
	std::vector<Point> grids;
	
	if (!attackRole) return grids;

	grids.reserve(5);

	Point srcGrid = attackRole->getGridIndex();
	Point point = Point::ZERO;
	bool isLeft = attackRole->isLeft();

	int _doFlag = -1;
	int count = 0;

	switch (skillAttackType)
	{
	case attackFront1:
		_doFlag = 1;
		count = 1;
		break;
	case attackFront2:
		_doFlag = 1;
		count = 2;
		break;
	case attackFront3:
		_doFlag = 1;
		count = 3;
		break;
	case attackFront4:
		_doFlag = 1;
		count = 4;
		break;
	case attackFront5:
		_doFlag = 1;
		count = 5;
		break;
	default:
		break;
	}

	if (_doFlag == 1)
	{
		for(int i=0; i<count; i++)
		{
			point.x = srcGrid.x - i;
			point.y = srcGrid.y;
			bool bounds = CHECK_GRID_BOUNDS(point.x, point.y);
			if (!bounds) grids.push_back(Point(point));
		}
	}

	return grids;
}

void SSkill::getCanAttackRoles(SkillAttackType skillAttackType, BattleRole *attackRole, Vector<BattleRole*> targetRoles)
{
	std::vector<Point> grids = getCanAttackGrids(skillAttackType, attackRole);

	for (Point grid : grids)
    {
		BattleRole* role = BattleRoles::getInstance()->getRoleByGrid(grid);
		if (role) targetRoles.pushBack(role);
    }
}

SSkill* SSkill::createSSKill(SkillType skillType, SkillAttackType skillAttackType, BattleRole *attackRole, Vector<SkillStepData*> &stepDatas)
{
	switch(skillType)
	{
	case SkillType::SkillRemote:
		return SRemoteSkill::create(skillAttackType, attackRole, stepDatas);
	}

	return nullptr;
}

SRemoteSkill::SRemoteSkill(void)
{
}


SRemoteSkill::~SRemoteSkill(void)
{
}

Skill* SRemoteSkill::doSkill(void)
{
	if (!_attackRole) return nullptr;

	SSkill::getCanAttackRoles(_skillAttackType, _attackRole, _targetRoles);

	auto step1 = SkillHeroStep::create(_stepDatas->at(0));
	auto step2 = SkillNormalBombStep::create(_stepDatas->at(1));

	return Skill::create(SequenceSkillStep::createWithTwoSteps(step1, step2));
}