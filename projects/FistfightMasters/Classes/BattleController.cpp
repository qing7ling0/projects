#include "BattleController.h"
#include "BattleMap.h"

static BattleController *_instance = nullptr;

BattleController::BattleController(void)
	: _map(nullptr)
{
}

BattleController::~BattleController(void)
{
	CC_SAFE_RELEASE(_map);
}

BattleController* BattleController::getInstance()
{
	return _instance;
}

bool BattleController::init(void)
{
    if ( !Layer::init() )
    {
        return false;
    }

	_instance = this;

	auto _uiLayer = Layer::create();
	_uiLayer->setPosition(Point(D_display.getLeftBottom()));
	addChild(_uiLayer);

	_map = BattleMap::create();

	return true;
}