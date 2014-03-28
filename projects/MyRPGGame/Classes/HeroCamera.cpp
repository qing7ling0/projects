#include "HeroCamera.h"
#include "HeroRole.h"

HeroCamera::HeroCamera(void)
	: _hero (nullptr)
{
}


HeroCamera::~HeroCamera(void)
{
	CC_SAFE_RELEASE(_hero);
}

void HeroCamera::setHero(HeroRole *hero)
{
	_hero = hero;
	CC_SAFE_RETAIN(_hero);
}

void HeroCamera::updateCamera(const float x, const float y)
{
	_hero->setCamera(x, y);
}