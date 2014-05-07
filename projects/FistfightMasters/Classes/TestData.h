#pragma once
#include "RoleData.h"
#include "SkillData.h"

class TestData : public Ref
{
public:
	TestData(void);
	~TestData(void);

public:
	Vector<RoleData*> _roleDatas;
};

