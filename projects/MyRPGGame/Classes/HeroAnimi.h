#pragma once
#include "RPGHead.h"

class HeroAnimi : public Ref
{
public:
	HeroAnimi(void);
	~HeroAnimi(void);

	virtual void setAnimation(Animation *animation);

	virtual Animation *getAnimation() { return _animation; }

	virtual int getAnimiFlag() { return _animiFlag; }

	virtual void setAnimiFlag(int flag, bool doForce = false);

protected:
	Animation *_animation;

	Node *_node;

	int _animiFlag;
};

