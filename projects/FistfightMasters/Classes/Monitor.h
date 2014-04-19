#pragma once
#include "RPGHead.h"

class Monitor : public Object
{
public:
	Monitor(void);
	~Monitor(void);

	virtual bool init(void);

	virtual void update(float dt);

	virtual void onEnter(void);

	virtual void onExit(void);

	virtual bool isOver() { return _over; }

	virtual void setOver(bool over) { _over = over; }

protected:
	bool _over;
	int step;
	float f_time;
};

