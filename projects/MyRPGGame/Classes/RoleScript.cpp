#include "RoleScript.h"
#include "RobotScript.h"


RoleScript::RoleScript(void)
	: _hero(nullptr)
{
}


RoleScript::~RoleScript(void)
{
	CC_SAFE_RELEASE(_hero);
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

CommandType RoleScript::parseRoleAction(std::vector<DirectionFlag> directionFlags)
{

	return CommandType::noneCommand;
}

int RoleScript::getRoleAnimiFlag(RoleActionBase action)
{
	return -1;
}