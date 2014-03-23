#pragma once
#include "RPGHead.h"

class RoleScript;
class Command;

class Role : public Object
{
public:
	Role(void);

	~Role(void);

	virtual bool init(RoleData data);

	virtual Node* getNode() { return _node; }

	virtual RoleDirect getDirect() { return _direct; }

	virtual RoleScript* getRoleScript() { return _script; }

	virtual void doTouchActions(std::vector<DirectionFlag> directionFlags);

	virtual void attack();

	virtual void hurt();

	virtual void move();

	virtual void run();

	virtual void update(float dt);
	
	virtual void setPosition(const float px, const float py);
	virtual void setPosition(const Point &point);
	
	virtual Point getPositon() const { return _position; }
	virtual float getPositonX() const { return _position.x; }
	virtual float getPositonY() const { return _position.y; }

protected:
	Node *_node;
	RoleScript *_script;
	Command *_command;

	RoleDirect _direct;
	RoleData _data;
	Point _position;
};

