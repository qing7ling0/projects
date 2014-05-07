#pragma once
#include "RPGHead.h"
#include "RoleData.h"
#include "SkillData.h"

class BattleRole;
class Skill;

class SSkill : public Ref
{
public:
	SSkill(void);
	~SSkill(void);

	virtual bool init(SkillAttackType skillAttackType, BattleRole *attackRole, Vector<SkillStepData*> &stepDatas);

	virtual Skill* doSkill(void) { return nullptr; };

	static void getCanAttackRoles(SkillAttackType skillAttackType, BattleRole *attackRole, Vector<BattleRole*> &targetRoles);

	static std::vector<Point> getCanAttackGrids(SkillAttackType skillAttackType, BattleRole *attackRole);

	static SSkill* createSSKill(SkillType skillType, SkillAttackType skillAttackType, BattleRole *attackRole, Vector<SkillStepData*> &stepDatas);

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

	F_CREATE_FUNC_ARGS_3(SRemoteSkill, SkillAttackType, skillAttackType, BattleRole*, attackRole, Vector<SkillStepData*>, stepDatas);
};