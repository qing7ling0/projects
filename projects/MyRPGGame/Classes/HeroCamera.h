#pragma once
#include "MapCamera.h"

class HeroRole;

class HeroCamera : public MapCamera
{
public:
	HeroCamera(void);
	~HeroCamera(void);

	virtual void setHero(HeroRole *hero);

	virtual HeroRole* getHero() { return _hero; }

protected:
	virtual void updateCamera(const float x, const float y);

private:
	HeroRole *_hero;
};

