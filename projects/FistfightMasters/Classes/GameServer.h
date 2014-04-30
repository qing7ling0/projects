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

	void update(float dt);

	void nextRound();

	CREATE_FUNC(GameServer);

	EXTERN_CREATE_INSTANCE_FUNC(GameServer);

protected:

protected:
	SRoundInfo *_roundInfo;
};

