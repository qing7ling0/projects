#pragma once
#include "RPGHead.h"
#include "RoleData.h"

class BattleRole;

typedef enum 
{
	SKILL_STEP_NONE = 1,
	SKILL_STEP_HERO,
	SKILL_STEP_NORMAL_BOMB,

} SkillStepType;

class SkillStepData : public Ref
{
public:
	SkillStepData(void);
	~SkillStepData(void);

protected:
	SkillStepType _stepType;
};


class SkillStepHeroData : public SkillStepData
{
public:
	SkillStepHeroData(void);
	~SkillStepHeroData(void);
public:
	int _roleAnimiActionIndex;
};

class SkillStepNormalBombData : public SkillStepData
{
public:
	SkillStepNormalBombData(void);
	~SkillStepNormalBombData(void);
public:
	const char *_animiName;
	const char *_animiPath;
	float frameDt;
	int _hurtHP;
};

class SkillData : public Ref
{
public:
	SkillData(void);

	~SkillData(void);

	bool init(void);

	CREATE_FUNC(SkillData);

public:
	Vector<SkillStepData*>* _stepDatas;
	SkillType _skillType;
	SkillAttackType _skillAttackType;
};

