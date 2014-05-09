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

typedef enum{
	MonitorAll,
	MonitorGameStart,
	MonitorAttack,
	MonitorPlayAnimi,
	MonitorNewRound,
	MonitorWaitNext
} MonitorType;

class SkillData;

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
	float _duraction;
	int _actionIndexs[2];
};

class RoleData : public Ref
{
public:
	RoleData(void);

	~RoleData(void);

	bool init(void);

	void initDatas(Vector<SkillData*> skillDatas, char *_roleAnimiName);

	CREATE_FUNC(RoleData);

public:
	const char *_roleAnimiName;
	const char *_roleAnimiPath;

	Vector<SkillData*> _skillDatas;

	/** 角色的所有动作 */
	std::vector<AnimiAction*> *_roleAnimiActions;

	int _animiCount;

	bool _enemy;

	Point _grid;
};


class RoundInfo : public Ref
{
public:
	RoundInfo(void);

	~RoundInfo(void);

	bool init() { return true; }

	CREATE_FUNC(RoundInfo);

public:
	int _currentRound;
	bool _selfRound;
};
