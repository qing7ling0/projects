#include "BattleMap.h"


BattleMap::BattleMap(void)
	: _battleLayer(nullptr)
{
}


BattleMap::~BattleMap(void)
{
}

bool BattleMap::init(void)
{
	auto spBg = Sprite::create("images/map_01.jpg");
	spBg->setPosition(D_display.getCenterPoint());
	
	Size battleSize = Size(MAP_GRID_WIDTH*10, MAP_GRID_HEIGHT*5);

	_battleLayer = Layer::create();
	_battleLayer->setContentSize(battleSize);
	_battleLayer->setAnchorPoint(Point(0.5f, 0));
	_battleLayer->ignoreAnchorPointForPosition(false);
	_battleLayer->setPosition(Point(spBg->getContentSize().width/2, 15));
	spBg->addChild(_battleLayer);

	auto centerLine = LayerColor::create(Color4B(255, 0, 0, 155), 2, battleSize.height);
	centerLine->setAnchorPoint(Point(0.5f, 0.5f));
	centerLine->ignoreAnchorPointForPosition(false);
	centerLine->setPosition(Point(battleSize.width/2, battleSize.height/2));
	_battleLayer->addChild(centerLine);

    auto batch = SpriteBatchNode::create("images/grid_bg.png", 50);
	_battleLayer->addChild(batch);

	for(int i=0; i<10; i++)
	{
		for(int j=0; j<5; j++)
		{
			auto gridBg = Sprite::createWithTexture(batch->getTexture());
			Point point = getGameMapGirdPosition(Point(i,j))+Point(MAP_GRID_WIDTH/2, MAP_GRID_HEIGHT/2);
			gridBg->setPosition(point);
			batch->addChild(gridBg);
		}
	}
	
	BattleController::getInstance()->addChild(spBg);

	return true;
}

Point BattleMap::getGameMapGirdPosition(Point grid)
{
	return Point(grid.x*MAP_GRID_WIDTH, grid.y*MAP_GRID_HEIGHT);
}