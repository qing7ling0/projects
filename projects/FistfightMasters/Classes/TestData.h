#pragma once
#include "RoleData.h"
#include "SkillData.h"



class TestData : public Ref
{
public:
	TestData(void);
	~TestData(void);

	void createAnimi(std::vector<AnimiAction*> *roleAnimiActions, int roleType);

public:
	Vector<RoleData*> _roleDatas;
};

