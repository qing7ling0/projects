#include "BattleRole.h"
#include "BattleController.h"


BattleRole::BattleRole(void)
	: _enemy(false)
	, _roleData(nullptr)
	, _gridIndex(Point::ZERO)
	, _left(false)
	, _currentAnimiActionIndex(0)
	, _currentPlayer(nullptr)
	, _currenSelectSkill(nullptr)
{
}


BattleRole::~BattleRole(void)
{
	if(_roleData)
	{
		const char* animiPath = String::createWithFormat("%s.plist", _roleData->_roleAnimiName)->getCString();
		SpriteFrameCache::getInstance()->removeSpriteFrameByName(animiPath);
	}

	CC_SAFE_RELEASE(_roleData);

	_animiPlayers.clear();
}

void BattleRole::setEnemy(bool enemy)
{
	_enemy = enemy;
}

bool BattleRole::init(RoleData *data)
{
	if (!Role::init()) return false;

	_roleData = data;
	CC_SAFE_RETAIN(_roleData);

	if (_roleData)
	{
		_enemy = _roleData->_enemy;
		setLeft(!_roleData->_enemy);
	}

	BattleController::getInstance()->addChild(_node, ZORDER_BATTLE_ROLE);

	initRoleAnimiPlayers();

	setDefaultAction();
	
	_currenSelectSkill = _roleData->_skillDatas.at(0);

	return true;
}

void BattleRole::setDefaultAction()
{
	setCurrentAnimiActionIndex(HERO_ANIMI_ACTION_STAND, 0);
}

void BattleRole::initRoleAnimiPlayers()
{
	if (!_roleData) return;

	const char* animiPath = String::createWithFormat("%s%s.plist", _roleData->_roleAnimiPath, _roleData->_roleAnimiName)->getCString();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(animiPath);
	if (_roleData->_roleAnimiActions)
	{
		for(auto &actionData : *_roleData->_roleAnimiActions)
		{
			Vector<SpriteFrame*> frames;
			for(int j=actionData->_actionIndexs[0]; j<=actionData->_actionIndexs[1]; j++)
			{
				const char* imgName = String::createWithFormat("%s_%03d.png", _roleData->_roleAnimiName, j)->getCString();
				frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName));
			}
			auto player = AnimiPlayer::create(frames, 0.2f);
			player->setAnchorPoint(Point(0, 0));
			player->setScale(0.65f);
			//player->start();
			if (!_roleData->_enemy) player->setPositionY(35);
			else player->setPositionY(-15);
			_node->addChild(player);

			_animiPlayers.insert(actionData->_actionType, player);
		}
	}

	setGirdIndex(_roleData->_grid);
}

void BattleRole::setGirdIndex(const Point &grid, bool updatePosition)
{
	_gridIndex = Point(grid);
	if (updatePosition)
	{
		bool bounds = CHECK_GRID_BOUNDS(_gridIndex.x, _gridIndex.y);
		_node->setVisible(!bounds);
		if(!bounds)
			_node->setPosition(GRID_CONVER_TO_PIXEL(_gridIndex.x, _gridIndex.y));
	}
}

void BattleRole::setLeft(bool left)
{
	_left = left;
}

void BattleRole::setCurrentAnimiActionIndex(int index, int loop, bool resume)
{
	if (index != _currentAnimiActionIndex)
	{
		auto player = _animiPlayers.at(index);
		if (!player) return;

		if (_currentPlayer ) _currentPlayer->stop(false);
		_currentPlayer = player;
		_currentPlayer->start(loop);

		_currentAnimiActionIndex = index;
	}
	else
	{
		if (resume && _currentPlayer)
		{
			_currentPlayer->stop();
			_currentPlayer->start(_currentPlayer->getLoops(), _currentPlayer->getOverVisible());
		}
	}
}