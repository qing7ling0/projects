#include "GameServer.h"
#include "BattleRoles.h"

DEFINE_CREATE_INSTANCE_FUNC(GameServer);

GameServer::GameServer(void)
	: _roundInfo(nullptr)
{
}


GameServer::~GameServer(void)
{
	CC_SAFE_RELEASE(_roundInfo);
}

bool GameServer::init(void)
{
	_instance = this;
	_roundInfo = new SRoundInfo();
	_roundInfo->_currentRound = 0;
	_roundInfo->_selfRound = true;
	return true;
}

void GameServer::gameStart(void)
{
	nextRound();	
}

void GameServer::gameEnd(void)
{
}

void GameServer::attack(void)
{
	Vector<BattleRole*> roles = _roundInfo->_selfRound ? BattleRoles::getInstance()->getSelfRoles():BattleRoles::getInstance()->getEnemyRoles();

}

void GameServer::nextRound(void)
{
	_roundInfo->_currentRound++;
	_roundInfo->_selfRound = !_roundInfo->_selfRound;
}
