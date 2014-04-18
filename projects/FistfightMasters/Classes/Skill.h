#pragma once
#include "RPGHead.h"
#include "RoleData.h"
#include "BattleRole.h"

class Skill : public Object
{
public:
	Skill(void);
	~Skill(void);

	virtual bool init(SkillData *_skillData);

	virtual void start(BattleRole* srcRole);

	virtual void doDamage();

	virtual const int getDamage() const;

	virtual void getCanAttackRoles();

	virtual Vector<Point> getCanAttackGrids();

protected:
	/** 技能类型 */
	SkillType _skillType;

	/** 攻击范围的类型 */
	SkillAttackType _skillAttackType;

	/** 攻击的目标 */
	Vector<BattleRole*> _targetRoles;

	/** 攻击者 */
	BattleRole *_srcRole;

	/** 技能数据 */
	SkillData *_skillData;
};

