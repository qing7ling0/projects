#pragma once
#include "RPGHead.h"
#include "BattleConfig.h"

// 攻击动作
const int HERO_ANIMI_ACTION_ATTACK = 1;

// 站立动作
const int HERO_ANIMI_ACTION_STAND = 2;

// 被攻击动作
const int HERO_ANIMI_ACTION_HITTED = 3;

// 移动动作
const int HERO_ANIMI_ACTION_MOVE = 4;

enum SkillType
{
	// 近身攻击
	SkillClose,

	// 远程攻击
	SkillRemote,
};

enum SkillAttackType
{
	// 攻击正前方1个格子
	attackFront1,
	// 攻击正前方2个格子
	attackFront2,
	// 攻击正前方3个格子
	attackFront3,
	// 攻击正前方4个格子
	attackFront4,
	// 攻击正前方5个格子
	attackFront5,
};

struct AnimiAction
{
	int _actionType;
	int _actionIndexs[2];
};

class SkillData : public Object
{
public:
	SkillData(void);

	~SkillData(void);

	bool init(void);

	CREATE_FUNC(SkillData);

public:
	char *_animiName;
	int _animiIndex[2];
};

class RoleData : public Object
{
public:
	RoleData(void);

	~RoleData(void);

	bool init(void);

	void initDatas(Vector<SkillData*> skillDatas, char *_roleAnimiName);

	CREATE_FUNC(RoleData);

public:
	char *_roleAnimiName;

	Vector<SkillData*> _skillDatas;

	/** 角色的所有动作 */
	AnimiAction *_roleAnimiActions;

	int _animiCount;
};

