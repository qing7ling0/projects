#pragma once
#include "RPGHead.h"
#include "SkillData.h"

class BattleRole;

#define STE_SKILL_STEP_DATA(varType, varName)    \
protected: varType varName; \
public: virtual void setSkillStepData(varType var)   \
{ \
    if (varName != var) \
    { \
        CC_SAFE_RELEASE(varName); \
		varName = nullptr; \
		if (var) { \
			varName = var;\
			CC_SAFE_RETAIN(varName); \
		} \
    } \
}

class SkillStep : public Ref
{
public:
	SkillStep(void);
	~SkillStep(void);

	virtual void loadRes(void) {}

	virtual bool init();
	
	virtual void start(void);

	virtual void stop(void);

	virtual void unloadRes(void) {}

	virtual void update(float dt) {}

	virtual bool isOver(void) { return _over; } const

	virtual void setOver(const bool over) { _over = over; }

	virtual bool isStart(void) { return _start; } const

	virtual void setStart(const bool start) { _start = start; }

	virtual SkillStepData* getSkillStepData(void) const { return nullptr; }

	virtual void setSkillStepData(SkillStepData* skillStepData){}

protected:
	bool _over;

	bool _start;

	int _step;
};



class SequenceSkillStep : public SkillStep
{
public:
	SequenceSkillStep(void);
	~SequenceSkillStep(void);

	virtual bool initWithTwoSteps(SkillStep *stepOne, SkillStep *stepTwo);
	
	virtual void loadRes(void);

	virtual void unloadRes(void);

	virtual void start(void);

	virtual void stop(void);

	virtual void update(float dt);

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

	virtual bool init(SkillStepHeroData* stepData, BattleRole* targetRole);

	F_CREATE_FUNC_ARGS_2(SkillHeroStep, SkillStepHeroData*, stepData, BattleRole*, targetRole);

	STE_SKILL_STEP_DATA(SkillStepHeroData*, _stepData);

protected:
	BattleRole *_targetRole;
};

class SkillNormalBombStep : public SkillStep
{
public:
	SkillNormalBombStep(void);
	~SkillNormalBombStep(void);
	
	virtual void loadRes();

	virtual void unloadRes();

	virtual void start(void);

	virtual void stop(void);

	virtual void update(float dt);

	virtual bool init(SkillStepNormalBombData* stepData);

	virtual void addTargetRole(BattleRole* targetRole);

	F_CREATE_FUNC_ARGS_1(SkillNormalBombStep, SkillStepNormalBombData*, stepData);

	STE_SKILL_STEP_DATA(SkillStepNormalBombData*, _stepData);

protected:
	Vector<SpriteFrame*> _frames;
	Vector<BattleRole*> _targetRoles;
};

