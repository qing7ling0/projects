#include "SkillStep.h"
#include "BattleRole.h"
#include "BattleRoles.h"
#include "BattleController.h"
#include "DamageEffect.h"


/*--------------  SkillStep BEGAN ----------------*/
SkillStep::SkillStep(void)
	: _over(false)
	, _step(0)
{
	setSkillStepData(nullptr);
}

SkillStep::~SkillStep(void)
{
	CC_SAFE_RELEASE(getSkillStepData());
}

void SkillStep::start(void)
{
	setOver(false);
	setStart(true);
	_step = 0;
}

void SkillStep::stop(void)
{
	setOver(true);
	setStart(false);
}

bool SkillStep::init(void)
{
	return true;
}
/*--------------  SkillHeroStep END ----------------*/

/*--------------  SequenceSkillStep BEGAN ----------------*/
SequenceSkillStep::SequenceSkillStep(void)
	: _stepOne(nullptr)
	, _stepTwo(nullptr)
	, _lastStep(nullptr)
{
}

SequenceSkillStep::~SequenceSkillStep(void)
{
	CC_SAFE_RELEASE(_stepOne);
	CC_SAFE_RELEASE(_stepTwo);
}

void SequenceSkillStep::loadRes(void)
{
	if (_stepOne) _stepOne->loadRes();
	if (_stepTwo) _stepTwo->loadRes();
}

void SequenceSkillStep::unloadRes(void)
{
	if (_stepOne) _stepOne->unloadRes();
	if (_stepTwo) _stepTwo->unloadRes();
}

void SequenceSkillStep::start(void)
{
	SkillStep::start();
	_lastStep = _stepOne;
	if (_stepOne) _stepOne->start();
}

void SequenceSkillStep::stop(void)
{
	SkillStep::stop();
	if (_lastStep) _lastStep->stop();
}

void SequenceSkillStep::update(float dt)
{
	if (!_start) return;

	if (_lastStep)
	{
		_lastStep->update(dt);

		if (_lastStep->isOver())
		{
			if (_lastStep == _stepOne)
			{
				_lastStep = _stepTwo;
				if (_lastStep) _lastStep->start();
			}
			else if (_lastStep == _stepTwo)
			{
				_lastStep = nullptr;
			}
		}
	}

	if (!_lastStep) stop();
}

SequenceSkillStep* SequenceSkillStep::create(SkillStep *step, ...)
{
    va_list params;
    va_start(params, step);

    SequenceSkillStep *ret = SequenceSkillStep::createWithVariableList(step, params);

    va_end(params);
    
    return ret;
}

SequenceSkillStep* SequenceSkillStep::createWithVariableList(SkillStep *step1, va_list args)
{
    SkillStep *now;
    SkillStep *prev = step1;
    bool bOneAction = true;

    while (step1)
    {
        now = va_arg(args, SkillStep*);
        if (now)
        {
            prev = createWithTwoSteps(prev, now);
            bOneAction = false;
        }
        else
        {
            // If only one action is added to Sequence, make up a Sequence by adding a simplest finite time action.
            if (bOneAction)
            {
				prev = createWithTwoSteps(prev, nullptr);
            }
            break;
        }
    }
    
    return ((SequenceSkillStep*)prev);
}

SequenceSkillStep* SequenceSkillStep::create(const Vector<SkillStep*>& arrayOfSteps)
{
    SequenceSkillStep* ret = nullptr;
    do 
    {
        auto count = arrayOfSteps.size();
        CC_BREAK_IF(count == 0);

        auto prev = arrayOfSteps.at(0);

        if (count > 1)
        {
            for (int i = 1; i < count; ++i)
            {
                prev = createWithTwoSteps(prev, arrayOfSteps.at(i));
            }
        }
        else
        {
            // If only one action is added to Sequence, make up a Sequence by adding a simplest finite time action.
            prev = createWithTwoSteps(prev, nullptr);
        }
        ret = static_cast<SequenceSkillStep*>(prev);
    }while (0);

    return ret;
}

SequenceSkillStep* SequenceSkillStep::createWithTwoSteps(SkillStep *stepOne, SkillStep *stepTwo)
{
	auto step = new SequenceSkillStep();
	if (step->initWithTwoSteps(stepOne, stepTwo))
	{
		step->autorelease();
		return step;
	}
	else
	{
		delete step;
		step = nullptr;
	}

	return nullptr;
}

bool SequenceSkillStep::initWithTwoSteps(SkillStep *stepOne, SkillStep *stepTwo)
{
	if (!stepOne) return false;
	_stepOne = stepOne;
	_stepTwo = stepTwo;
	CC_SAFE_RETAIN(_stepOne);
	CC_SAFE_RETAIN(_stepTwo);

    return true;
}
/*--------------  SequenceSkillStep END ----------------*/


/*--------------  SkillHeroStep BEGAN ----------------*/
SkillHeroStep::SkillHeroStep(void)
	: _targetRole(nullptr)
	, _stepData(nullptr)
{
}

SkillHeroStep::~SkillHeroStep(void)
{
	CC_SAFE_RELEASE(_targetRole);
}

void SkillHeroStep::loadRes(void)
{
}

void SkillHeroStep::start(void)
{
	SkillStep::start();
	if (!_stepData) return;
}

void SkillHeroStep::stop(void)
{
	SkillStep::stop();
}

void SkillHeroStep::update(float dt)
{
	if (!_start || !_stepData || !_targetRole) return;

	if (_step == 0)
	{
		_targetRole->setCurrentAnimiActionIndex(_stepData->_roleAnimiActionIndex);
		_step ++;
	}
	else if (_step == 1)
	{
		if (_targetRole->isAnimiPlayerOver())
		{
			_targetRole->setDefaultAction();
			stop();
			_step++;
		}
	}
}

bool SkillHeroStep::init(SkillStepHeroData* stepData, BattleRole* targetRole)
{
	if (!SkillStep::init() || !targetRole) return false;

	setSkillStepData(stepData);
	_targetRole = targetRole;
	CC_SAFE_RETAIN(targetRole);

	return true;
}
/*--------------  SkillHeroStep END ----------------*/


/*--------------  SkillNormalBombStep BEGAN ----------------*/
SkillNormalBombStep::SkillNormalBombStep(void)
	: _stepData(nullptr)
{
}

SkillNormalBombStep::~SkillNormalBombStep(void)
{
}

void SkillNormalBombStep::loadRes()
{
	if (_stepData)
	{
		ADD_ANIMIPLAYER_SPRITE_FRAME_CACHE_PLIST(_stepData->_animiPath, _stepData->_animiName, "%s%s.plist");
		CREATE_ANIMIPLAYER_FRAMES(_stepData->_animiName, "%s_%003d.png", _frames, 1, _frames.size());
	}
}

void SkillNormalBombStep::unloadRes()
{
	if (_stepData)
	{
		REMOVE_ANIMIPLAYER_SPRITE_FRAME_CACHE_PLIST(_stepData->_animiPath, _stepData->_animiName);
	}
}

void SkillNormalBombStep::start(void)
{
	SkillStep::start();
	if (!_stepData) return;
}

void SkillNormalBombStep::stop(void)
{
	SkillStep::stop();
}

void SkillNormalBombStep::update(float dt)
{
	if (!_start || !_stepData || _targetRoles.size()==0) return;

	if (_step == 0)
	{
		for(int i=0; i<_targetRoles.size(); i++)
		{
			auto role = _targetRoles.at(i);
			auto player = AnimiPlayer::create(_frames, _stepData->frameDt);
			player->setTag(1000+i);
			player->start(1);
			player->setUserObject(role);
			player->setStopEvent([&](AnimiPlayer* player)
			{
				auto effect = DamageEffect::create(_stepData->_hurtHP);
				effect->setPosition(Point(CCRANDOM_MINUS1_1()*10, CCRANDOM_MINUS1_1()*10+60));

				auto role = static_cast<Role*>(player->getUserObject());
				role->getNode()->addChild(effect, 10);

				player->removeFromParent();
			});
			player->setPosition(GRID_CONVER_TO_PIXEL(role->getGridIndex().x, role->getGridIndex().y));
			BattleController::getInstance()->addChild(player, ZORDER_BATTLE_EFFECT);
		}
		_step ++;
	}
	else if (_step == 1)
	{
		bool over = true;
		for(int i=0; i<_targetRoles.size(); i++)
		{
			auto node = BattleController::getInstance()->getChildByTag(1000+i);
			if (node)
			{
				over = false;
			}
		}
		if (over)
		{
			setOver(over);
			_step++;
		}
	}
}

bool SkillNormalBombStep::init(SkillStepNormalBombData* stepData)
{
	if (!SkillStep::init()) return false;
	
	setSkillStepData(stepData);
	_targetRoles.reserve(5);

	return true;
}

void SkillNormalBombStep::addTargetRole(BattleRole* targetRole)
{
	if (targetRole)
		_targetRoles.pushBack(targetRole);
}
/*--------------  SkillNormalBombStep END ----------------*/