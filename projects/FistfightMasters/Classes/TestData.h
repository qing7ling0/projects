#pragma once
#include "RoleData.h"

class TestData : public Object
{
public:
	TestData(void);
	~TestData(void);

public:
	Vector<RoleData*> _roleDatas;
};

