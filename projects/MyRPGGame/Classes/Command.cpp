#include "Command.h"


Command::Command(void):_over(false)
	, _hero(nullptr)
	, _commandType(CommandType::noneCommand)
{

}


Command::~Command(void)
{
	CC_SAFE_RELEASE(_hero);
}

void Command::init(HeroRole *role, CommandType command)
{ 
	_hero = role;
	_hero->retain();
	_commandType = command;
}

void Command::doCommand(float dt) {}

bool Command::canBreakCommand(Command command) { return true; }

void Command::over() { _over = true; }

void Command::clean() {}
