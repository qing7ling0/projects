#pragma once
#include "RPGHead.h"
#include "ServerData.h"

class GameServer : public Ref
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

