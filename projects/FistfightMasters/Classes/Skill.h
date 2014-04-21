#pragma once
#include "RPGHead.h"
#include "RoleData.h"
#include "SkillData.h"
#include "BattleRole.h"
#include "SkillStep.h"

class Skill : public Object
{
public:
	Skill(void);
	~Skill(void);

	virtual bool init(SkillStep *skillStep, BattleRole* srcRole);

	virtual void start();

	virtual void stop();

	virtual void doDamage();

	virtual const int getDamage() const;

	virtual void getCanAttackRoles();

	virtual std::vector<Point> getCanAttackGrids();

	virtual bool isOver() { return _over; }

	virtual void setOver(bool over) { _over = over; }

protected:
	/** 技能类型 */
	SkillType _skillType;

	/** 攻击范围的类型 */
	SkillAttackType _skillAttackType;

	/** 攻击的目标 */
	Vector<BattleRole*> _targetRoles;

	/** 攻击者 */
	BattleRole *_srcRole;

	bool _over;

	SkillStep *_skillStep;
};

