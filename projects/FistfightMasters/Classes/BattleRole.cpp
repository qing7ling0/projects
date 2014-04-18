#include "BattleRole.h"
#include "BattleController.h"


BattleRole::BattleRole(void)
	: _enemy(false)
	, _roleData(nullptr)
	, _gridIndex(Point::ZERO)
	, _left(false)
{
}


BattleRole::~BattleRole(void)
{
	if(_roleData)
	{
		const char* animiPath = String::createWithFormat("animi/%s.plist", _roleData->_roleAnimiName)->getCString();
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
	_roleData = data;
	CC_SAFE_RETAIN(_roleData);

	BattleController::getInstance()->addChild(_node);

	initRoleAnimiPlayers();

	return true;
}

void BattleRole::initRoleAnimiPlayers()
{
	if (!_roleData) return;

	const char* animiPath = String::createWithFormat("animi/%s.plist", _roleData->_roleAnimiName)->getCString();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(animiPath);

	for(int i=0; i<_roleData->_animiCount; i++)
	{
		if (_roleData->_roleAnimiActions)
		{
			auto actionData = _roleData->_roleAnimiActions;
			if (actionData)
			{
				Vector<SpriteFrame*> frames;
				for(int j=actionData->_actionIndexs[0]; j<=actionData->_actionIndexs[1]; j++)
				{
					const char* imgName = String::createWithFormat("%s_%03d.png", _roleData->_roleAnimiName, j)->getCString();
					frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName));
				}
				auto player = AnimiPlayer::create(frames);
				_node->addChild(player);

				_animiPlayers.insert(actionData->_actionType, player);
			}

			_roleData->_roleAnimiActions++;
		}
	}
}

void BattleRole::setGirdIndex(const Point &grid, bool updatePosition)
{
	_gridIndex = Point(grid);
	if (updatePosition)
	{
		bool bounds = CHECK_GRID_BOUNDS(_gridIndex.x, _gridIndex.y);
		_node->setVisible(bounds);
		if(!bounds)
			_node->setPosition(GRID_CONVER_TO_PIXEL(_gridIndex.x, _gridIndex.y));
	}
}

void BattleRole::setLeft(bool left)
{
	_left = left;
}
