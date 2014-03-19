#include "RoleScript.h"
#include "RobotScript.h"


RoleScript::RoleScript(void):
	_role(nullptr)
{
}


RoleScript::~RoleScript(void)
{
	CC_SAFE_RELEASE(_role);
}

RoleScript* RoleScript::createScript(ScriptType scriptType)
{
	RoleScript* script = nullptr;

	switch(scriptType)
	{
	case ScriptType::scriptRobot:

		script = new RobotScript();
		break;
	}
	if (script) script->autorelease();

	return script;
}

RoleAction parseRoleAction(std::vector<DirectionFlag> directionFlags)
{
}
