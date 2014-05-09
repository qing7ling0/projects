#include "TestData.h"


static const char skill_bomb_03[] = "e_bomb_03";
static const char skill_bomb_04[] = "e_bomb_04";
static const char skill_bomb_06[] = "e_bomb_06";
static const char skill_longjuan[] = "e_longjuan";
static const char skill_tabomb[] = "e_tabomb";

static const char role_tie_shan[] = "tie_shan";
static const char role_mm_01[] = "mm_01";
static const char role_heiwuchang[] = "heiwuchang";
static const char role_houbing[] = "houbing";

static const char npc_path[] = "animi/npc/";
static const char skill_path[] = "animi/skill/";

TestData::TestData(void)
{
	_roleDatas.reserve(3);

	auto roleData = RoleData::create();
	roleData->_roleAnimiName = role_tie_shan;
	roleData->_roleAnimiPath = npc_path;
	createAnimi(roleData->_roleAnimiActions, 0);

	auto skill = SkillData::create();

	auto skillStep = new SkillStepHeroData();
	skillStep->_roleAnimiActionIndex = HERO_ANIMI_ACTION_ATTACK;
	skill->_stepDatas->pushBack(skillStep);

	auto skillStep2 = new SkillStepNormalBombData();
	skillStep2->frameDt=0.01f;
	skillStep2->_animiName = skill_bomb_04;
	skillStep2->_animiPath = skill_path;
	skill->_stepDatas->pushBack(skillStep2);

	skill->_skillType = SkillType::SkillRemote;
	skill->_skillAttackType = SkillAttackType::attackFront5;
	roleData->_skillDatas.pushBack(skill);

	roleData->_enemy = true;
	roleData->_grid = Point(2, 2);
	_roleDatas.pushBack(roleData);


	//-------------------------------------------------
	roleData = RoleData::create();
	roleData->_roleAnimiName = role_mm_01;
	roleData->_roleAnimiPath = npc_path;
	createAnimi(roleData->_roleAnimiActions, 1);

	skill = SkillData::create();

	skillStep = new SkillStepHeroData();
	skillStep->_roleAnimiActionIndex = HERO_ANIMI_ACTION_ATTACK;
	skill->_stepDatas->pushBack(skillStep);

	skillStep2 = new SkillStepNormalBombData();
	skillStep2->frameDt=0.01f;
	skillStep2->_animiName = skill_bomb_06;
	skillStep2->_animiPath = skill_path;
	skill->_stepDatas->pushBack(skillStep2);

	skill->_skillType = SkillType::SkillRemote;
	skill->_skillAttackType = SkillAttackType::attackFront5;
	roleData->_skillDatas.pushBack(skill);

	roleData->_enemy = false;
	roleData->_grid = Point(7, 2);
	_roleDatas.pushBack(roleData);
	//-------------------------------------------------
}


TestData::~TestData(void)
{
}

/**
0：铁扇公主			name:tie_shan
1：M豆				name:mm_01
2：黑无常			name:heiwuchang
3：猴兵				name:houbing
*/
void TestData::createAnimi(std::vector<AnimiAction*> *roleAnimiActions, int roleType)
{
	AnimiAction *action = new AnimiAction();

	switch(roleType)
	{
	case 0: // 铁扇公主
		action->_actionType = HERO_ANIMI_ACTION_ATTACK;
		action->_actionIndexs[0] = 3;
		action->_actionIndexs[1] = 7;
		roleAnimiActions->push_back(action);

		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_STAND;
		action->_actionIndexs[0] = 10;
		action->_actionIndexs[1] = 13;
		roleAnimiActions->push_back(action);

		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_HITTED;
		action->_actionIndexs[0] = 8;
		action->_actionIndexs[1] = 9;
		roleAnimiActions->push_back(action);
		break;

	case 1: // M豆
		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_ATTACK;
		action->_actionIndexs[0] = 1;
		action->_actionIndexs[1] = 4;
		roleAnimiActions->push_back(action);

		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_STAND;
		action->_actionIndexs[0] = 5;
		action->_actionIndexs[1] = 9;
		roleAnimiActions->push_back(action);

		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_HITTED;
		action->_actionIndexs[0] = 10;
		action->_actionIndexs[1] = 13;
		roleAnimiActions->push_back(action);
		break;

	case 2: // 黑无常
		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_ATTACK;
		action->_actionIndexs[0] = 1;
		action->_actionIndexs[1] = 6;
		roleAnimiActions->push_back(action);

		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_STAND;
		action->_actionIndexs[0] = 10;
		action->_actionIndexs[1] = 13;
		roleAnimiActions->push_back(action);

		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_HITTED;
		action->_actionIndexs[0] = 7;
		action->_actionIndexs[1] = 9;
		roleAnimiActions->push_back(action);

		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_MOVE;
		action->_actionIndexs[0] = 14;
		action->_actionIndexs[1] = 19;
		roleAnimiActions->push_back(action);
		break;

	case 3: // 猴兵
		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_ATTACK;
		action->_actionIndexs[0] = 1;
		action->_actionIndexs[1] = 7;
		roleAnimiActions->push_back(action);

		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_STAND;
		action->_actionIndexs[0] = 10;
		action->_actionIndexs[1] = 12;
		roleAnimiActions->push_back(action);

		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_HITTED;
		action->_actionIndexs[0] = 8;
		action->_actionIndexs[1] = 9;
		roleAnimiActions->push_back(action);

		action = new AnimiAction();
		action->_actionType = HERO_ANIMI_ACTION_MOVE;
		action->_actionIndexs[0] = 13;
		action->_actionIndexs[1] = 18;
		roleAnimiActions->push_back(action);
		break;
	}
}
