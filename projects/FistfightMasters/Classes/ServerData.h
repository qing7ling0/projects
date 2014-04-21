#pragma once
#include "RPGHead.h"
#include "ServerConfig.h"


class SRoundInfo : public Object
{
public:
	SRoundInfo(void);
	~SRoundInfo(void);

public:
	int _currentRound;
	bool _selfRound;
};

class ServerData : public Object
{
public:
	ServerData(void);
	~ServerData(void);
};

