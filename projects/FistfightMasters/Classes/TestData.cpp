#include "TestData.h"

TestData::TestData(void)
{
	_roleDatas.reserve(3);

	auto roleData = RoleData::create();
	roleData->_roleAnimiName = "tie_shan";
	roleData->_roleAnimiPath = "animi/npc/";

	AnimiAction *action = new AnimiAction();

	action->_actionType = HERO_ANIMI_ACTION_ATTACK;
	action->_actionIndexs[0] = 3;
	action->_actionIndexs[1] = 7;
	roleData->_roleAnimiActions->push_back(action);

	action = new AnimiAction();
	action->_actionType = HERO_ANIMI_ACTION_STAND;
	action->_actionIndexs[0] = 10;
	action->_actionIndexs[1] = 13;
	roleData->_roleAnimiActions->push_back(action);

	action = new AnimiAction();
	action->_actionType = HERO_ANIMI_ACTION_HITTED;
	action->_actionIndexs[0] = 8;
	action->_actionIndexs[1] = 9;
	roleData->_roleAnimiActions->push_back(action);

	auto skill = SkillData::create();

	auto skillStep = new SkillStepHeroData();
	skillStep->_roleAnimiActionIndex = HERO_ANIMI_ACTION_ATTACK;
	skill->_stepDatas->pushBack(skillStep);

	auto skillStep2 = new SkillStepNormalBombData();
	skillStep2->_animiIndexs[0] = 1;
	skillStep2->_animiIndexs[1] = 5;
	skillStep2->_animiName = "e_longjuan";
	skillStep2->_animiPath = "animi/skill/";
	skill->_stepDatas->pushBack(skillStep2);

	skill->_skillType = SkillType::SkillRemote;
	skill->_skillAttackType = SkillAttackType::attackFront1;
	roleData->_skillDatas.pushBack(skill);

	roleData->_ememy = true;
	roleData->_grid = Point(2, 2);
	_roleDatas.pushBack(roleData);


	//-------------------------------------------------
	roleData = RoleData::create();
	roleData->_roleAnimiName = "mm_01";
	roleData->_roleAnimiPath = "animi/npc/";

	action = new AnimiAction();
	action->_actionType = HERO_ANIMI_ACTION_ATTACK;
	action->_actionIndexs[0] = 1;
	action->_actionIndexs[1] = 4;
	roleData->_roleAnimiActions->push_back(action);

	action = new AnimiAction();
	action->_actionType = HERO_ANIMI_ACTION_STAND;
	action->_actionIndexs[0] = 5;
	action->_actionIndexs[1] = 9;
	roleData->_roleAnimiActions->push_back(action);

	action = new AnimiAction();
	action->_actionType = HERO_ANIMI_ACTION_HITTED;
	action->_actionIndexs[0] = 10;
	action->_actionIndexs[1] = 13;
	roleData->_roleAnimiActions->push_back(action);

	skill = SkillData::create();

	skillStep = new SkillStepHeroData();
	skillStep->_roleAnimiActionIndex = HERO_ANIMI_ACTION_ATTACK;
	skill->_stepDatas->pushBack(skillStep);

	skillStep2 = new SkillStepNormalBombData();
	skillStep2->_animiIndexs[0] = 1;
	skillStep2->_animiIndexs[1] = 5;
	skillStep2->_animiName = "e_tabomb";
	skillStep2->_animiPath = "animi/skill/";
	skill->_stepDatas->pushBack(skillStep2);

	skill->_skillType = SkillType::SkillRemote;
	skill->_skillAttackType = SkillAttackType::attackFront1;
	roleData->_skillDatas.pushBack(skill);

	roleData->_ememy = false;
	roleData->_grid = Point(7, 2);
	_roleDatas.pushBack(roleData);
	//-------------------------------------------------
}


TestData::~TestData(void)
{
}
