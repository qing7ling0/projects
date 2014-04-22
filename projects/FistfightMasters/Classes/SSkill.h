#pragma once
#include "RPGHead.h"
#include "RoleData.h"
#include "SkillData.h"

class BattleRole;
class Skill;

class SSkill : public Object
{
public:
	SSkill(void);
	~SSkill(void);

	virtual bool init(Vector<SkillStepData*> stepDatas, BattleRole *attackRole, SkillAttackType skillAttackType);

	virtual Skill* doSkill(void) { return nullptr; };

	static void getCanAttackRoles(SkillAttackType skillAttackType, BattleRole *attackRole, Vector<BattleRole*> targetRoles);

	static std::vector<Point> getCanAttackGrids(SkillAttackType skillAttackType, BattleRole *attackRole);

protected:
	Vector<SkillStepData*> *_stepDatas;

	BattleRole *_attackRole;

	SkillAttackType _skillAttackType;

	/** ¹¥»÷µÄÄ¿±ê */
	Vector<BattleRole*> _targetRoles;
};


class SRemoteSkill : public SSkill
{
public:
	SRemoteSkill(void);
	~SRemoteSkill(void);

	Skill* doSkill(void);
};