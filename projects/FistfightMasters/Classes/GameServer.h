#pragma once
#include "RPGHead.h"
#include "ServerConfig.h"
#include "ServerData.h"

class GameServer : public Object
{
public:
	GameServer(void);
	~GameServer(void);

	bool init(void);

	void gameStart(void);

	void gameEnd(void);

	void attack(void);

	CREATE_FUNC(GameServer);

	EXTERN_CREATE_INSTANCE_FUNC(GameServer);

protected:
	void nextRound();

protected:
	SRoundInfo *_roundInfo;
};

