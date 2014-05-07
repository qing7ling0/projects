#pragma once
#include "RPGHead.h"
#include "RoleData.h"
#include "SkillData.h"
#include "BattleRole.h"
#include "SkillStep.h"

class Skill : public Ref
{
public:
	Skill(void);
	~Skill(void);

	virtual bool init(SkillStep *skillStep);

	virtual void start();

	virtual void stop();

	virtual void loadRes();

	virtual void unloadRes();

	virtual void doDamage();

	virtual const int getDamage() const;

	virtual bool isOver() { return _over; } const

	virtual void setOver(const bool over) { _over = over; }

	virtual bool isStart(void) { return _start; } const

	virtual void setStart(const bool start) { _start = start; }

	virtual void update(float dt);

	F_CREATE_FUNC_ARGS_1(Skill, SkillStep*, skillStep);

protected:

	bool _over;

	bool _start;

	SkillStep *_skillStep;
};

