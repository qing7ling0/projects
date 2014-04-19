#include "AnimiPlayer.h"

AnimiPlayer::AnimiPlayer(void)
	: _animi (nullptr)
	, _animiSprite (nullptr)
{
}

AnimiPlayer::~AnimiPlayer(void)
{
	CC_SAFE_RELEASE(_animi);
}

AnimiPlayer* AnimiPlayer::create(Vector<SpriteFrame*> frames, float delay)
{
	auto player = new AnimiPlayer();
	if(player->init(frames, delay))
	{
		player->autorelease();
		return player;
	}
	else
	{
		delete player;
		player = nullptr;
	}
	return nullptr;
}

bool AnimiPlayer::init(Vector<SpriteFrame*> frames, float delay)
{
	if (!Layer::init())
	{
		return false;
	}

	_animi = Animation::createWithSpriteFrames(frames, delay);
	CC_SAFE_RETAIN(_animi);
	_animi->setRestoreOriginalFrame(true);

	_animiSprite = Sprite::create();
	addChild(_animiSprite);

	/*auto line1 = LayerColor::create(Color4B(255, 0, 0, 255), 1, 200);
	line1->setPositionY(-100);
	addChild(line1);

	auto line2 = LayerColor::create(Color4B(255, 0, 0, 255), 200, 1);
	line2->setPositionX(-100);
	addChild(line2);*/

	return true;
}

/**
开始播放动画
@loop 循环次数， 0 表示一直循环，
@visible 如果是非循环播放，播放结束是否隐藏
*/
void AnimiPlayer::start(unsigned int loop, bool visible)
{
	_animi->setLoops(true);
	_animiSprite->setVisible(true);
	auto action = CCRepeatForever::create(CCAnimate::create(_animi));;
	/*if (loop==0)
		action = CCRepeatForever::create(CCAnimate::create(_animi));
	else
		action = Sequence::create(
			CCAnimate::create(_animi),
			CallFunc::create(
				[&](){
					stop(visible);
				}),
			NULL);*/
	action->setTag(9999);
	_animiSprite->runAction(action);
}

void AnimiPlayer::resume()
{
	_animiSprite->resume();
}

void AnimiPlayer::pause()
{
	_animiSprite->pause();
}

void AnimiPlayer::stop(bool visible)
{
	_animiSprite->stopActionByTag(9999);
	_animiSprite->setVisible(visible);
}

unsigned int AnimiPlayer::getLoops()
{
	if (_animi) return _animi->getLoops();

	return 0;
}

bool AnimiPlayer::isOver() const
{
	if (_animiSprite)
	{
		auto action = _animiSprite->getActionByTag(9999);
		return (action &&action->isDone()) || !action;
	}

	return true;
}