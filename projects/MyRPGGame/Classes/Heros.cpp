#include "Heros.h"

static Heros *_heros = nullptr;

Heros::Heros(void)
{
}


Heros::~Heros(void)
{
}

void Heros::init()
{
	_heros.reserve(2);
}

Heros* Heros::create()
{
	auto hero = new Heros();
	
	if (hero) hero->init();


	return hero;
}

void Heros::update(float dt)
{
}

void Heros::initHeros(RoleData *datas, int size)
{
	for(int i=0; i<size; i++)
	{
		HeroRole *_role = HeroRole::create(datas[i]);

		if (datas[i].roleId == 1) _role->setSelf(true);
		else _role->setEnemy(true);

		_heros.pushBack(_role);
		BattleController::getInstance()->addChild(_role->getNode());
	}
}

void Heros::doTouchActions(std::vector<DirectionFlag> directionFlags)
{
	for(HeroRole* hero : _heros)
	{
		if (hero && hero->isSelf())
			hero->doTouchActions(directionFlags);
	}
}