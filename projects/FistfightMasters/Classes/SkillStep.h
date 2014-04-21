#pragma once
#include "RPGHead.h"
#include "SkillData.h"

class BattleRole;

#define STE_SKILL_STEP_DATA(varType, varName)    \
protected: varType varName; \
public: virtual void set##funName(const SkillStepData* var)   \
{ \
    if (varName != var) \
    { \
        CC_SAFE_RELEASE(varName); \
		varName = nullptr; \
		if (var) { \
			varName = static_cast<varType>(var);\
			CC_SAFE_RETAIN(varName); \
		} \
    } \
}

class SkillStep : public Object
{
public:
	SkillStep(void);
	~SkillStep(void);

	virtual void loadRes(void) {}

	virtual bool init(SkillStepData* stepData);
	
	virtual void start(void);

	virtual void stop(void);

	virtual void unloadRes(void) {}

	virtual void update(float dt) {}

	virtual bool isOver(void) { return _over; } const

	virtual void setOver(const bool over) { _over = over; }

	virtual bool isStart(void) { return _start; } const

	virtual void setStart(const bool start) { _start = start; }

	virtual SkillStepData* getSkillStepData(void) { return nullptr; } const

	virtual void setSkillStepData(const SkillStepData* skillStepData) {}

	virtual void setTargetRole(BattleRole* role);

protected:
	bool _over;

	bool _start;

	int _step;

	BattleRole *_targetRole;
};



class SequenceSkillStep : public SkillStep
{
public:
	SequenceSkillStep(void);
	~SequenceSkillStep(void);

	virtual bool initWithTwoSteps(SkillStep *stepOne, SkillStep *stepTwo);
	
	virtual void loadRes(void);

	virtual void start(void);

	virtual void stop(void);

	virtual void update(float dt);

	virtual void unloadRes(void);

	static SequenceSkillStep* create(SkillStep *step, ...);

    static SequenceSkillStep* create(const Vector<SkillStep*>& arrayOfSteps);

	static SequenceSkillStep* createWithVariableList(SkillStep *step1, va_list args);

    static SequenceSkillStep* createWithTwoSteps(SkillStep *stepOne, SkillStep *stepTwo);

protected:
	SkillStep* _stepOne;
	SkillStep* _stepTwo;
	SkillStep* _lastStep;
};



class SkillHeroStep : public SkillStep
{
public:
	SkillHeroStep(void);
	~SkillHeroStep(void);

	virtual void loadRes();

	virtual void start(void);

	virtual void stop(void);

	virtual void update(float dt);

	virtual bool init(SkillStepData* stepData);

	F_CREATE_FUNC_ARGS_1(SkillHeroStep, SkillStepData*, stepData);

	STE_SKILL_STEP_DATA(SkillStepHeroData*, _stepData);

protected:

};

class SkillNormalBombStep : public SkillStep
{
public:
	SkillNormalBombStep(void);
	~SkillNormalBombStep(void);

	virtual void loadRes();

	virtual void start(void);

	virtual void stop(void);

	virtual void update(float dt);

	virtual bool init(SkillStepData* stepData);

	F_CREATE_FUNC_ARGS_1(SkillNormalBombStep, SkillStepData*, stepData);

	STE_SKILL_STEP_DATA(SkillStepNormalBombData*, _stepData);

protected:
	AnimiPlayer *_animiPlayer;
};

