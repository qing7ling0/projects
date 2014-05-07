#pragma once
#include "RPGHead.h"

#include "Skill.h"

class AttackData : public Ref
{
public:
	AttackData(void);
	~AttackData(void);

	bool init();
	void addSkill(Skill *skill);

	CREATE_FUNC(AttackData);

public:
	Vector<Skill*> _skills;
};

