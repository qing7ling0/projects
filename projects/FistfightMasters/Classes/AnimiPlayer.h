#pragma once
#include "RPGHead.h"

class AnimiPlayer : public Layer
{
public:
	AnimiPlayer(void);
	~AnimiPlayer(void);

	virtual bool init(Vector<SpriteFrame*> frames, float delay=0);

	virtual Animation* getAnimation() { return _animi; }

	virtual void start(bool loop=true, bool visible=false);

	virtual void resume();

	virtual void pause();

	virtual void stop(bool visible=false);

	static AnimiPlayer* create(Vector<SpriteFrame*> frames, float delay=0);

protected:
	Animation *_animi;
	Sprite *_animiSprite;
};

