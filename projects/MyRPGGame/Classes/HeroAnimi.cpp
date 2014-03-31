#include "HeroAnimi.h"


HeroAnimi::HeroAnimi(void)
	: _armature(nullptr)
	, _animiFlag(-1)
{
}


HeroAnimi::~HeroAnimi(void)
{
	CC_SAFE_RELEASE(_armature);
	_animiFlag = -1;
}

void HeroAnimi::setArmature(Armature *armature)
{
	if (_armature)
	{
		_armature->removeFromParentAndCleanup(true);
	}

	_armature = armature;
	CC_SAFE_RETAIN(_armature);
}

void HeroAnimi::setAnimiFlag(int flag, bool doForce)
{
	if (flag < 0) return;

	if (doForce || _animiFlag != flag)
	{
		if (_armature)
		{
			ArmatureAnimation *animi = _armature->getAnimation();
			if (animi && flag < animi->getMovementCount())
				animi->playWithIndex(flag);
		}
	}

	this->_animiFlag = flag;
}
