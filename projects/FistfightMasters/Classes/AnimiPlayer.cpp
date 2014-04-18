#include "AnimiPlayer.h"

AnimiPlayer::AnimiPlayer(void)
	: _animi (nullptr)
	, _animiSprite (nullptr)
{
}

AnimiPlayer::~AnimiPlayer(void)
{
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

	_animi = Animation::createWithSpriteFrames(frames);
	_animi->setRestoreOriginalFrame(true);

	_animiSprite = Sprite::create();
	addChild(_animiSprite);

	return true;
}

/**
开始播放动画
@loop 是否循环播放
@visible 如果是非循环播放，播放玩是否隐藏
*/
void AnimiPlayer::start(bool loop, bool visible)
{
	_animi->setLoops(loop);
	_animiSprite->setVisible(true);
	ActionInterval *action = nullptr;
	if (loop)
		action = CCRepeatForever::create(CCAnimate::create(_animi));
	else
		action = Sequence::create(
			CCAnimate::create(_animi),
			CallFunc::create(
				[&](){
					stop(visible);
				}),
			NULL);
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