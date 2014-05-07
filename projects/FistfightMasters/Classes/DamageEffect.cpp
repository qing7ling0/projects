#include "DamageEffect.h"


DamageEffect::DamageEffect(void)
{
}

DamageEffect::~DamageEffect(void)
{
}

bool DamageEffect::init(int damageNum)
{
	Layer::init();

	_damageNum = damageNum;
	if (_damageNum == 0)
	{
		return false;
	}
	else
	{
		auto _text = Text::create();
		const char* animiPath = String::createWithFormat("%d", _damageNum)->getCString();
		_text->setText(animiPath);
		_text->setFontSize(20);

		if (_damageNum < 0)
			_text->setColor(Color3B(0xff, 0, 0));
		else
			_text->setColor(Color3B(0, 0xff, 0));

		_text->setOpacityModifyRGB(false);
		_text->runAction(

			Sequence::create(
				EaseIn::create(MoveBy::create(0.6f, Point(0, -6)), 5),
				DelayTime::create(0.2f),
				Spawn::create(
					EaseOut::create(MoveBy::create(0.7f, Point(0, 40)), 0.2f),
					EaseOut::create(FadeTo::create(0.7f, 20), 0.2f),
					EaseOut::create(ScaleTo::create(0.7f, 1.3f), 0.2f),
					nullptr
				),
				CallFunc::create([this](){
					this->removeFromParent();
				}),
				nullptr
			)
		);
		this->addChild(_text);
	}


	return true;
}