#pragma once
#include "RoleScript.h"

class RobotScript : virtual public RoleScript
{
public:
	RobotScript(void);
	~RobotScript(void);
	
	virtual void init(Role *role);
	virtual Node* createRoleNode();
	virtual void doScript(float dt);
	virtual void doTouchActions(std::vector<DirectionFlag> directionFlags);
};
