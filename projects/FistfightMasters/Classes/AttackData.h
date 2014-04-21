#pragma once
#include "RPGHead.h"

class Skill;

class AttackData : public Object
{
public:
	AttackData(void);
	~AttackData(void);

	bool init(Skill *skill);

	F_CREATE_FUNC_ARGS_1(AttackData, Skill*, skill);

public:
	Skill *_skill;
};

