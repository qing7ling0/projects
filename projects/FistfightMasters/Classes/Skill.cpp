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

bool Skill::init(SkillStep *skillStep, BattleRole* srcRole)
{
	_targetRoles.reserve(5);

	_skillStep = skillStep;
	CC_SAFE_RETAIN(_skillStep);

	_srcRole = srcRole;
	CC_SAFE_RETAIN(_srcRole);

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


std::vector<Point> Skill::getCanAttackGrids()
{
	std::vector<Point> grids;
	
	if (!_srcRole) return grids;

	grids.reserve(5);

	Point srcGrid = _srcRole->getGridIndex();
	Point point = Point::ZERO;
	bool isLeft = _srcRole->isLeft();

	int _doFlag = -1;
	int count = 0;

	switch (_skillAttackType)
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

void Skill::getCanAttackRoles()
{
	_targetRoles.clear();

	std::vector<Point> grids = getCanAttackGrids();

	for (Point grid : grids)
    {
		BattleRole* role = BattleRoles::getInstance()->getRoleByGrid(grid);
		if (role) _targetRoles.pushBack(role);
    }
}