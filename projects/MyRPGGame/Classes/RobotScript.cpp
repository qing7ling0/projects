#include "RobotScript.h"

unsigned short roleAnimiActions[7][2] = {
	{RoleActionBase::actionAttack, 1}, {RoleActionBase::actionDefense, 1},
	{RoleActionBase::actionHurt, 1}, {RoleActionBase::actionJump, 1},
	{RoleActionBase::actionMove, 1}, {RoleActionBase::actionRun, 1},
	{RoleActionBase::actionWait, 1}
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
	ArmatureDataManager::getInstance()->addArmatureFileInfo("animi/robot.png",
			"animi/robot.plist",
			"animi/robot.xml");
	Armature *armature = Armature::create("robot");
	armature->getAnimation()->playWithIndex(0);
	armature->setScale(0.6f);
	armature->getAnimation()->setSpeedScale(0.5f);
		
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

	HeroAnimi *_animi = new HeroAnimi();
	_animi->autorelease();
	_animi->setArmature(armature);
	_hero->setRoleAnimi(_animi);

	__LayerRGBA *layer = __LayerRGBA::create();
	layer->addChild(armature);
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
			_hero->getHeroControl()->doMove(speedx, 0, RoleDirect::roleLeft);
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
