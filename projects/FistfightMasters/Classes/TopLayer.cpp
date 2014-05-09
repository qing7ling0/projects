#include "TopLayer.h"
#include "BattleConfig.h"


TopLayer::TopLayer(void)
{
}


TopLayer::~TopLayer(void)
{
}

bool TopLayer::init(void)
{
	if (!Layer::init()) return false;
	setLocalZOrder(ZORDER_BATTLE_EFFECT);
	return true;
}

void TopLayer::gameStart()
{
	showImageEffect("images/img_battle_start.png");
}

void TopLayer::yourTurn()
{
	showImageEffect("images/battle_your_turn.png");
}


void TopLayer::showImageEffect(const std::string &imageName)
{
	auto sp = Sprite::create(imageName);
	sp->setPosition(Point(-sp->getContentSize().width/2, _contentSize.height/2));
	sp->setScale(0.7f);
	sp->runAction(
		Sequence::create(
			EaseIn::create(MoveTo::create(1,Point(_contentSize.width/2,_contentSize.height/2)), 2),
			DelayTime::create(1.5f),
			EaseOut::create(MoveTo::create(1,Point(_contentSize.width+sp->getContentSize().width/2,_contentSize.height/2)), 2),
			CallFuncN::create([&](Node* node){
				node->removeFromParent();
			}),
			nullptr
		));
	addChild(sp);
}