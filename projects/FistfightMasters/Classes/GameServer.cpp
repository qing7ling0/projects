#include "GameServer.h"
#include "BattleRole.h"
#include "BattleRoles.h"
#include "SkillStep.h"
#include "SkillData.h"
#include "SSkill.h"
#include "AttackData.h"
#include "Task.h"
#include "RoleData.h"
#include "SelfMonitor.h"

DEFINE_CREATE_INSTANCE_FUNC(GameServer);

GameServer::GameServer(void)
	: _roundInfo(nullptr)
{
}


GameServer::~GameServer(void)
{
	CC_SAFE_RELEASE(_roundInfo);
	_instance = nullptr;
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

void GameServer::update(float dt)
{
}

void GameServer::attack(void)
{
	AttackData *attackData = AttackData::create();

	Vector<BattleRole*> roles = _roundInfo->_selfRound ? BattleRoles::getInstance()->getSelfRoles():BattleRoles::getInstance()->getEnemyRoles();
	
	for(BattleRole *role : roles)
	{
		auto skillData = role->getCurrentSelectSkill();
		if (skillData)
		{
			auto sskill = SSkill::createSSKill(skillData->_skillType, skillData->_skillAttackType, role, *skillData->_stepDatas);
			auto skill = sskill->doSkill();
			if (skill) attackData->addSkill(skill);
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

	if (!round->_selfRound)
	{
		attack();
		nextRound();
	}
}
