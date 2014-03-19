#pragma once
#include "RPGHead.h"

class RoleScript;

class Role : public Object
{
public:
	Role(void);

	~Role(void);

	virtual bool init(RoleData data);

	virtual Node* getNode() { return _node; }

	virtual RoleDirect getDirect() { return _direct; }

	virtual void doTouchActions(std::vector<DirectionFlag> directionFlags);

	virtual void attack();

	virtual void hurt();

	virtual void move();

	virtual void run();

	virtual void update(float dt);

protected:
	Node *_node;
	RoleDirect _direct;
	RoleData _data;
	RoleScript *_script;
};

