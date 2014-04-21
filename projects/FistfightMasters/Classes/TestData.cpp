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
	skill->_animiIndexs[0] = 1;
	skill->_animiIndexs[1] = 5;
	skill->_animiName = "e_longjuan";
	skill->_animiPath = "animi/skill/";
	skill->_skillType = SkillType::SkillRemote;
	roleData->_skillDatas.pushBack(skill);

	roleData->_ememy = true;
	roleData->_grid = Point(2, 2);
	_roleDatas.pushBack(roleData);


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
	skill->_animiIndexs[0] = 1;
	skill->_animiIndexs[1] = 10;
	skill->_animiName = "e_tabomb";
	skill->_animiPath = "animi/skill/";
	skill->_skillType = SkillType::SkillRemote;
	roleData->_skillDatas.pushBack(skill);

	roleData->_ememy = false;
	roleData->_grid = Point(7, 2);
	_roleDatas.pushBack(roleData);
}


TestData::~TestData(void)
{
}
