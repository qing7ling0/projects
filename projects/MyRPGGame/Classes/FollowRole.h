#pragma once
#include "RPGHead.h"
#include "Role.h"


class FollowRole : public Ref
{
public:
	FollowRole(void);
	~FollowRole(void);

	virtual bool init(Role *followRole, Role *targetRole);

	virtual void update(float dt);

	static FollowRole* create(Role *followRole, Role *targetRole);

protected:

	Role *_followRole;
	Role *_targetRole;
};

