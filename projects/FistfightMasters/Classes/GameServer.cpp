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
#include "BattleController.h"

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
	_roundInfo->autorelease();
	CC_SAFE_RETAIN(_roundInfo);
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

void GameServer::move(void)
{
	if (!_roundInfo->_selfRound)
	{
		Vector<BattleRole*> roles = BattleRoles::getInstance()->getEnemyRoles();
		MoveTask *task = nullptr;

		for(auto role : roles)
		{
			Point grid = role->getGridIndex();
			grid.x += 1;
			if (!BattleRoles::getInstance()->getRoleByGrid(grid))
			{
				if (!task)
				{
					task = MoveTask::create(MonitorType::MonitorAll);
					CC_SAFE_RETAIN(task);
				}
				role->setGirdIndex(grid, false);
				task->addRole(role);
			}
		}
		if (task) Tasks::getInstance()->addTask(task);
		CC_SAFE_RELEASE(task);
	}
}

void GameServer::attack(void)
{
	move();

	AttackData *attackData = AttackData::create();

	Vector<BattleRole*> roles = _roundInfo->_selfRound ? BattleRoles::getInstance()->getSelfRoles():BattleRoles::getInstance()->getEnemyRoles();
	
	for(BattleRole *role : roles)
	{
		if (!role->isDeadth())
		{
			auto skillData = role->getCurrentSelectSkill();
			if (skillData)
			{
				auto sskill = SSkill::createSSKill(skillData->_skillType, skillData->_skillAttackType, role, *skillData->_stepDatas);
				auto skill = sskill->doSkill();
				if (skill) attackData->addSkill(skill);
			}
		}
	}
	Tasks::getInstance()->addTask(AttackTask::create(attackData, MonitorType::MonitorWaitNext));
}

void GameServer::nextRound(void)
{
	bool over = checkGameOver();
	if (over)
	{
		Tasks::getInstance()->addTask(GameOverTask::create(MonitorType::MonitorWaitNext));
	}
	else
	{
		_roundInfo->_currentRound++;
		_roundInfo->_selfRound = !_roundInfo->_selfRound;

		RoundInfo* round = RoundInfo::create();
		round->_currentRound = _roundInfo->_currentRound;
		round->_selfRound = _roundInfo->_selfRound;

		Tasks::getInstance()->addTask(NewRoundTask::create(MonitorType::MonitorWaitNext, round));
	}
}

bool GameServer::checkGameOver()
{

	Vector<BattleRole*> roles = BattleRoles::getInstance()->getSelfRoles();

	bool over = true;
	for (auto &role : roles)
	{
		if(!role->isDeadth())
		{
			over = false;
			break;
		}
	}
	if (over)
	{
		BattleController::getInstance()->setGameWin(false);
		return true;
	}

	over = true;
	roles = BattleRoles::getInstance()->getEnemyRoles();
	for (auto &role : roles)
	{
		if(!role->isDeadth())
		{
			over = false;
			break;
		}
	}
	if (over)
	{
		BattleController::getInstance()->setGameWin(true);
		return true;
	}

	return over;
}
