#pragma once
#include "RPGHead.h"

class SkillData : public Object
{
public:
	SkillData(void);
	~SkillData(void);

	char *_animiName;
	int _animiIndex[2];
};

