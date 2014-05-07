#pragma once
#include "RPGHead.h"


class SRoundInfo : public Ref
{
public:
	SRoundInfo(void);
	~SRoundInfo(void);

public:
	int _currentRound;
	bool _selfRound;
};

class ServerData : public Ref
{
public:
	ServerData(void);
	~ServerData(void);
};

