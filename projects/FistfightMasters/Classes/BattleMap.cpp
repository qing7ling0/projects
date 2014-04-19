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
	
	_battleLayer = Layer::create();
	_battleLayer->setAnchorPoint(Point(0.5f, 0));
	_battleLayer->ignoreAnchorPointForPosition(false);
	_battleLayer->setPosition(Point(spBg->getContentSize().width/2, 0));
	spBg->addChild(_battleLayer);

	auto centerLine = LayerColor::create(Color4B(255, 0, 0, 155), 2, MAP_GRID_HEIGHT*5);
	centerLine->setAnchorPoint(Point(0.5f, 0.5f));
	centerLine->ignoreAnchorPointForPosition(false);
	centerLine->setPosition(Point(D_display.cx, 15+MAP_GRID_HEIGHT*2.5f));
	_battleLayer->addChild(centerLine);

    auto batch = SpriteBatchNode::create("images/grid_bg.png", 50);
	_battleLayer->addChild(batch);

	for(int i=0; i<10; i++)
	{
		for(int j=0; j<5; j++)
		{
			auto gridBg = Sprite::createWithTexture(batch->getTexture());
			gridBg->setPosition(GRID_CONVER_TO_PIXEL(i,j));
			batch->addChild(gridBg);
		}
	}

	BattleController::getInstance()->addChild(spBg);

	return true;
}