#include "DamageEffect.h"
#include "NumberLabel.h"


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
		Texture2D *texture = nullptr;
		Sprite *sp = nullptr;

		if (damageNum>0)
		{
			texture = Director::getInstance()->getTextureCache()->getTextureForKey("images/battle_hurt_add_num.png");
			sp = Sprite::create("images/battle_hurt_add.png");
		}
		else
		{
			Director::getInstance()->getTextureCache()->getTextureForKey("images/battle_hurt_boji_num.png");
			sp = Sprite::create("images/battle_hurt_boji_reduce.png");
			damageNum = -damageNum;
		}

		auto label = NumberLabel::create(texture, damageNum);
		label->setScale(0.8f);
		label->runAction(
			Sequence::create(
				EaseIn::create(MoveBy::create(0.6f, Point(0, -6)), 5),
				DelayTime::create(0.2f),
				Spawn::create(
					EaseOut::create(MoveBy::create(0.7f, Point(0, 40)), 0.2f),
					EaseOut::create(FadeTo::create(0.7f, 20), 0.2f),
					EaseOut::create(ScaleTo::create(0.7f, 0.85f), 0.2f),
					nullptr
				),
				CallFunc::create([this](){
					this->removeFromParent();
				}),
				nullptr
			)
		);

		if (sp)
		{
			sp->setAnchorPoint(Point(1, 0.5f));
			sp->setPosition(Point(-5,label->getContentSize().height/2));
			label->addChild(sp);
		}

		this->addChild(label);
	}


	return true;
}