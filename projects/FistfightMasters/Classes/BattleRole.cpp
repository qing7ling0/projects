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
	, _hpBar(nullptr)
	, _death(false)
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
	CC_SAFE_RELEASE(_hpBar);

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
		_roleHP = _roleData->_HP;
	}


	auto sp = Sprite::create("images/battle_blood_bg.png");
	//sp->setAnchorPoint(Point(0, 0.5f));
	sp->setPosition(Point(0,-28));
	sp->setScale(0.6f);

	_hpBar = Sprite::create("images/battle_blood_01.png");
	_hpBar->ignoreAnchorPointForPosition(true);
	sp->addChild(_hpBar);
	CC_SAFE_RETAIN(_hpBar);

	_node->addChild(sp, 20);
	_node->setCascadeOpacityEnabled(true);

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
			player->setCascadeOpacityEnabled(true);

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

void BattleRole::setHP(int hp)
{
	_roleHP = hp;

	if (_hpBar)
	{
		float per = MAX (0, MIN(1, (hp*1.0f) / MAX(getMaxHP(), FLT_EPSILON)));
		Size size = _hpBar->getTexture()->getContentSize();
		_hpBar->setTextureRect(Rect(0, 0, size.width*per, size.height));
	}

	if (!_death)
	{
		_death = _roleHP<=0;
		if (_death)
		{
			if (_node) _node->runAction(FadeOut::create(2));
		}
	}
}

int BattleRole::getMaxHP()
{
	return _roleData->_maxHP;
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

void BattleRole::moveTo(const Point &grid)
{
	int sx = MAX(abs(_gridIndex.x - grid.x), abs(_gridIndex.y - grid.y));


	setGirdIndex(grid, false);
	if (sx > 0)
	{
		auto action = MoveTo::create(0.5f, GRID_CONVER_TO_PIXEL(_gridIndex.x, _gridIndex.y));
		_node->runAction(action);
	}
}