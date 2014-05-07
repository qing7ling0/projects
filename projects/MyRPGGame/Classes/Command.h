#pragma once
#include "RPGHead.h"
#include "HeroRole.h"

class Command : public Ref
{
public:
	Command(void);

	~Command(void);

	virtual void init(HeroRole *role, CommandType command);

	virtual void doCommand(float dt);

	virtual bool canBreakCommand(Command command);

	virtual void over();

	virtual bool isOver() { return _over; }

	virtual void clean();

protected:
	bool _over;
	CommandType _commandType;
	HeroRole *_hero;
};

