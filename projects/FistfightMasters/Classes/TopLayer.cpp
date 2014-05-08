#include "TopLayer.h"


TopLayer::TopLayer(void)
{
}


TopLayer::~TopLayer(void)
{
}

bool TopLayer::init(void)
{
	if (!Layer::init()) return false;

	return true;
}

void TopLayer::gameStart()
{
	auto sp = Sprite::create("images/img_battle_start.png");
	sp->setAnchorPoint(Point(1,0.5f));
	sp->setPosition(Point(0, _contentSize.height/2));
	sp->runAction(
		Sequence::create(
		EaseIn::create(MoveTo::create(1,Point(_contentSize.width/2,0)), 2),
			DelayTime::create(0.5f),
			EaseOut::create(MoveBy::create(1,Point(_contentSize.width/2+sp->getContentSize().width,0)), 2),
			CallFuncN::create([&](Node* node){
				node->removeFromParent();
			}),
			nullptr
	));
	addChild(sp);
}

void TopLayer::yourTurn()
{
	auto sp = Sprite::create("images/battle_your_turn.png");
	sp->setAnchorPoint(Point(1,0.5f));
	sp->setPosition(Point(0, _contentSize.height/2));
	sp->runAction(
		Sequence::create(
		EaseIn::create(MoveTo::create(1,Point(_contentSize.width/2,0)), 2),
			DelayTime::create(0.5f),
			EaseOut::create(MoveBy::create(1,Point(_contentSize.width/2+sp->getContentSize().width,0)), 2),
			CallFuncN::create([&](Node* node){
				node->removeFromParent();
			}),
			nullptr
	));
	addChild(sp);
}
