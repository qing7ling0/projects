#pragma once
#include "RPGHead.h"
#include "FollowRole.h"

class FollowRoles : public Ref
{
public:
	FollowRoles(void);
	~FollowRoles(void);

	bool init();

	void update(float dt);

	void add(FollowRole *role);

	void remove(FollowRole *role);

	static FollowRoles* getInstance();

	CREATE_FUNC(FollowRoles);

private:
	Vector<FollowRole*> _followRoles; 
};

