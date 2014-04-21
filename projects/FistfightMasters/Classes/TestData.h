#pragma once
#include "RoleData.h"
#include "SkillData.h"

class TestData : public Object
{
public:
	TestData(void);
	~TestData(void);

public:
	Vector<RoleData*> _roleDatas;
};

