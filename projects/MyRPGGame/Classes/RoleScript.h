#pragma once
#include "RPGHead.h"
#include "Role.h"
#include "HeroRole.h"
#include "TouchControl.h"
#include "HeroControl.h"

class RoleScript : public Object
{
public:
	RoleScript(void);
	~RoleScript(void);

	virtual void init(HeroRole *role){}

	virtual void doScript(float dt){}

	virtual void doTouchActions(std::vector<DirectionFlag> directionFlags){}

	virtual Node* createRoleNode(){ return nullptr; }

	virtual CommandType parseRoleAction(std::vector<DirectionFlag> directionFlags);

	static RoleScript* createScript(ScriptType scriptType);

protected:
	HeroRole *_hero;
};

