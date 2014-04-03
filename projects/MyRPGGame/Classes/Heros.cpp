#include "Heros.h"
#include "HeroRole.h"
#include "BattleController.h"
#include "RoleScript.h"
#include "FollowRoles.h"
#include "MapControl.h"

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
	for(auto &role : _heros)
	{
		role->update(dt);
	}
}

void Heros::initHeros(RoleData *datas, int size)
{
	for(int i=0; i<size; i++)
	{
		HeroRole *_role = HeroRole::create(datas[i]);

		FollowRoles::getInstance()->add(FollowRole::create(_role, MapControl::getInstance()));

		if (datas[i].roleId == 1) _role->setSelf(true);

		_heros.pushBack(_role);
		BattleController::getInstance()->addChild(_role->getNode());

		if (i == 1)
		{
			_role->setEnemy(_heros.at(0));
			_heros.at(0)->setEnemy(_role);
		}
	}

}

void Heros::doTouchActions(const std::vector<DirectionFlag> directionFlags)
{
	for(HeroRole* hero : _heros)
	{
		if (hero && hero->isSelf())
			hero->getRoleScript()->doTouchActions(directionFlags);
	}
}