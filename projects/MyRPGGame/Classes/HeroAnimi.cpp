#include "HeroAnimi.h"


HeroAnimi::HeroAnimi(void)
	: _animation(nullptr)
	, _animiFlag(-1)
{
}


HeroAnimi::~HeroAnimi(void)
{
	CC_SAFE_RELEASE(_animation);
	_animiFlag = -1;
}

void HeroAnimi::setAnimation(Animation *animation)
{
	if (_animation)
	{
		//_animation->removeFromParentAndCleanup(true);
	}

	_animation = animation;
	CC_SAFE_RETAIN(_animation);
}

void HeroAnimi::setAnimiFlag(int flag, bool doForce)
{
	if (flag < 0) return;

	if (doForce || _animiFlag != flag)
	{
		if (_animation)
		{
			/*ArmatureAnimation *animi = _armature->getAnimation();
			if (animi && flag < animi->getMovementCount())
				animi->playWithIndex(flag);*/
		}
	}

	this->_animiFlag = flag;
}
