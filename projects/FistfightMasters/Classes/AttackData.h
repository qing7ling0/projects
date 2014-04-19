#pragma once
#include "RPGHead.h"

class Skill;

class AttackData : public Object
{
public:
	AttackData(void);
	~AttackData(void);

	void addSkill(const Skill* skill);

public:
	Vector<Skill*>* _skills;
};

