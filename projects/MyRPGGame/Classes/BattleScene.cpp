#include "BattleScene.h"

BattleScene::BattleScene(void)
{
}


BattleScene::~BattleScene(void)
{
}

bool BattleScene::init(void)
{
	if (Layer::init())
	{
		ArmatureDataManager::getInstance()->addArmatureFileInfo("animi/robot.png",
			"animi/robot.plist",
			"animi/robot.xml");

		auto map = TMXTiledMap::create("map/town.tmx");
		addChild(map, 0, 1);

		Armature *armature = Armature::create("robot");
		armature->getAnimation()->playWithIndex(0);
		armature->setPosition(Point(D_display.cx, D_display.cy));
		armature->setScale(0.6f);
		armature->getAnimation()->setSpeedScale(0.5f);
		addChild(armature);
		_hero = armature;
		
		ParticleSystem *p1 = CCParticleSystemQuad::create("Particles/SmallSun.plist");
		ParticleSystem *p2 = CCParticleSystemQuad::create("Particles/SmallSun.plist");

		Bone *bone  = Bone::create("p1");
		bone->addDisplay(p1, 0);
		bone->changeDisplayWithIndex(0, true);
		bone->setIgnoreMovementBoneData(true);
		bone->setLocalZOrder(100);
		bone->setScale(1.2f);
		armature->addBone(bone, "bady-a3");

		bone  = Bone::create("p2");
		bone->addDisplay(p2, 0);
		bone->changeDisplayWithIndex(0, true);
		bone->setIgnoreMovementBoneData(true);
		bone->setLocalZOrder(100);
		bone->setScale(1.2f);
		armature->addBone(bone, "bady-a30");

		TouchPad *_pad = TouchPad::create();
		_pad->setTouchOverCall(CC_CALLBACK_1(BattleScene::touchPadCallback, this));
		addChild(_pad, 1);

		_actions.reserve(10);

		scheduleUpdate();

		return true;
	}

	return false;
}


void BattleScene::update(float dt)
{
	//_hero->is

	if (_actions.size() > 0)
	{
		float _per = _hero->getAnimation()->getCurrentPercent();
		RoleAction *ac = _actions.at(0);
		if (ac&&_per>=1)
		{
			_hero->getAnimation()->playWithIndex(getHeroAnimiIndexByActionFlag(ac->actionFlag));
			_actions.erase(0);
		}
	}
}
int BattleScene::getHeroAnimiIndexByActionFlag(DirectionFlag flag)
{
	switch(flag)
	{
	case DirectionFlag::down:
			return 0;
	case DirectionFlag::left:
			return 1;
	case DirectionFlag::leftDown:
			return 2;
	case DirectionFlag::leftUp:
			return 3;
	case DirectionFlag::right:
			return 4;
	case DirectionFlag::rightDown:
			return 5;
	case DirectionFlag::rightUp:
			return 6;
	case DirectionFlag::up:
			return 7;
	}

	return 0;
}

void BattleScene::touchPadCallback(Object *touchPad)
{
	TouchPad *pad = static_cast<TouchPad*>(touchPad);

	for ( std::vector<DirectionFlag>::iterator iter = pad->_directionLists.begin() ; iter != pad->_directionLists.end() ; iter++ )
	{
		//CCLOG("direction = %d", *iter);
		auto ac = new RoleAction();
		ac->actionFlag = *iter;
		ac->autorelease();

		_actions.pushBack(ac);
	};
}