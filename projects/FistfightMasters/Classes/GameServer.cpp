#include "GameServer.h"
#include "BattleRole.h"
#include "BattleRoles.h"
#include "SkillStep.h"
#include "SkillData.h"
#include "SSkill.h"
#include "AttackData.h"
#include "Task.h"
#include "RoleData.h"

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
	Tasks::getInstance()->addTask(GameStartTask::create(MonitorType::MonitorWaitNext));
	nextRound();	
}

void GameServer::gameEnd(void)
{
}

void GameServer::attack(void)
{
	AttackData *attackData = AttackData::create();

	Vector<BattleRole*> roles = _roundInfo->_selfRound ? BattleRoles::getInstance()->getSelfRoles():BattleRoles::getInstance()->getEnemyRoles();
	
	for(BattleRole *role : roles)
	{
		auto skill = role->getCurrentSelectSkill();
		if (skill)
		{
			auto sskill = SSkill::createSSKill(skill->_skillType, skill->_skillAttackType, role, *skill->_stepDatas);
			attackData->addSkill(sskill->doSkill());
		}
	}

	Tasks::getInstance()->addTask(AttackTask::create(attackData, MonitorType::MonitorWaitNext));
}

void GameServer::nextRound(void)
{
	_roundInfo->_currentRound++;
	_roundInfo->_selfRound = !_roundInfo->_selfRound;

	RoundInfo* round = RoundInfo::create();
	round->_currentRound = _roundInfo->_currentRound;
	round->_selfRound = _roundInfo->_selfRound;

	Tasks::getInstance()->addTask(NewRoundTask::create(MonitorType::MonitorWaitNext, round));
}
