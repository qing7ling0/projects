#include "SkillStep.h"
#include "BattleRole.h"
#include "BattleRoles.h"


/*--------------  SkillStep BEGAN ----------------*/
SkillStep::SkillStep(void)
	: _over(false)
	, _step(0)
	, _targetRole(nullptr)
{
	setSkillStepData(nullptr);
}

SkillStep::~SkillStep(void)
{
	CC_SAFE_RELEASE(getSkillStepData());
	CC_SAFE_RELEASE(_targetRole);
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

void SkillStep::setTargetRole(BattleRole* role)
{
	if (_targetRole != role)
	{
		CC_SAFE_RELEASE(_targetRole);
		CC_SAFE_RETAIN(role);
		_targetRole = role;
	}
}

bool SkillStep::init(SkillStepData* stepData)
{
	setSkillStepData(stepData);
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
	if (!start) return;

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
{
}

SkillHeroStep::~SkillHeroStep(void)
{
}

void SkillHeroStep::loadRes(void)
{
}

void SkillHeroStep::start(void)
{
	SkillStep::start();
	if (!_stepData) return;
	setTargetRole(BattleRoles::getInstance()->getRoleByGrid(_stepData->_roleGridIndex));
}

void SkillHeroStep::stop(void)
{
	SkillStep::stop();
}

void SkillHeroStep::update(float dt)
{
	if (!start || !_stepData || _targetRole) return;

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

bool SkillHeroStep::init(SkillStepData* stepData)
{
	if (!SkillStep::init(stepData)) return false;

	return true;
}
/*--------------  SkillHeroStep END ----------------*/


/*--------------  SkillNormalBombStep BEGAN ----------------*/
SkillNormalBombStep::SkillNormalBombStep(void)
	: _animiPlayer(nullptr)
{
}

SkillNormalBombStep::~SkillNormalBombStep(void)
{
}

void SkillNormalBombStep::loadRes()
{

}

void SkillNormalBombStep::start(void)
{
	SkillStep::start();
	if (!_stepData) return;
	setTargetRole(BattleRoles::getInstance()->getRoleByGrid(_stepData->_roleGridIndex));
}

void SkillNormalBombStep::stop(void)
{
	SkillStep::stop();
}

void SkillNormalBombStep::update(float dt)
{
	if (!start || !_stepData || _targetRole) return;

	if (_step == 0)
	{
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

bool SkillNormalBombStep::init(SkillStepData* stepData)
{
	return true;
}
/*--------------  SkillNormalBombStep END ----------------*/