#pragma once
#include "RPGHead.h"


class DamageEffect : public Layer
{
public:
	DamageEffect(void);
	~DamageEffect(void);

	virtual bool init(int damageNum);

	F_CREATE_FUNC_ARGS_1(DamageEffect, int, damageNum)

private:

	int _damageNum;
};


