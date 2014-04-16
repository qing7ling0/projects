#include "RobotScript.h"

unsigned short roleAnimiActions[7][2] = {
	{RoleActionBase::actionAttack, 1}, {RoleActionBase::actionDefense, 2},
	{RoleActionBase::actionHurt, 1}, {RoleActionBase::actionAttack, 1},
	{RoleActionBase::actionMove, 1}, {RoleActionBase::actionRun, 1},
	{RoleActionBase::actionAttack, 1}
	};


RobotScript::RobotScript(void)
{
}


RobotScript::~RobotScript(void)
{
}


void RobotScript::init(HeroRole *role)
{
	this->_hero = role;
	if (_hero) _hero->retain();
}

Node* RobotScript::createRoleNode()
{

	/*ArmatureDataManager::getInstance()->addArmatureFileInfo(
		"niutouguai.png",
		"niutouguai.plist",
		"niutouguai.xml");
	Armature *armature = Armature::create("niutouguai");
	armature->getAnimation()->playWithIndex(0);
	armature->setScale(0.5f);
	armature->getAnimation()->setSpeedScale(0.75f);
		
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
	armature->addBone(bone, "bady-a30");*/
	
	Vector<SpriteFrame*> frames;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animi/benimaru.plist");
	for(int i=1; i<9; i++)
	{
		const char* imgName = String::createWithFormat("benimaru_%02d.png", i)->getCString();
		frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName));
	}

	auto animi = Animation::createWithSpriteFrames(frames, 1.0f/10);
	animi->setRestoreOriginalFrame(true);
	animi->setLoops(true);

	HeroAnimi *_animi = new HeroAnimi();
	_animi->autorelease();
	_animi->setAnimation(animi);
	_hero->setRoleAnimi(_animi);


	auto sp = Sprite::create();
	sp->runAction(CCRepeatForever::create(CCAnimate::create(animi)));
	__LayerRGBA *layer = __LayerRGBA::create();
	layer->addChild(sp);
	//armature->setColor(Color3B::RED);
	layer->setCascadeColorEnabled(true);

	if (_hero->getRoleData().roleId == 1) layer->setColor(Color3B::BLUE);

	return layer;
}

void RobotScript::doScript(float dt)
{
}

void RobotScript::doTouchActions(std::vector<DirectionFlag> directionFlags)
{
	CommandType _command = parseRoleAction(directionFlags);

	if (_command == CommandType::attackCommand)
	{
		float speedx = getMoveSpeed();
		if (_hero->isDirectLeft()) speedx = -speedx;
			_hero->getHeroControl()->doMove(speedx, 0, RoleDirect::roleLeft);
	}
	else if (_command == CommandType::moveBackCommand)
	{
		float speedx = getMoveSpeed();
		if (!_hero->isDirectLeft()) speedx = -speedx;
		_hero->getHeroControl()->doMove(speedx, 0, RoleDirect::roleRight);
	}
}

CommandType RobotScript::parseRoleAction(std::vector<DirectionFlag> directionFlags)
{
	if (directionFlags.size() > 0)
	{
		switch(directionFlags[0])
		{
		case DirectionFlag::left:
			if (_hero->isDirectLeft())
				return CommandType::attackCommand;
			else
				return CommandType::moveBackCommand;
		case DirectionFlag::right:
			if (!_hero->isDirectLeft())
				return CommandType::attackCommand;
			else
				return CommandType::moveBackCommand;
		case DirectionFlag::down:
			if (_hero->isDirectLeft())
				return CommandType::attackCommand;
			else
				return CommandType::moveBackCommand;
		}
	}

	return CommandType::noneCommand;
}

int RobotScript::getRoleAnimiFlag(RoleActionBase action)
{
	for(int i=0; i<7; i++)
	{
		if (roleAnimiActions[i][0] == action)
		{
			return roleAnimiActions[i][1];
		}
	}

	return -1;
}
