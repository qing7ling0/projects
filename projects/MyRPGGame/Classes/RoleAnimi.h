#pragma once
#include "RPGHead.h"

class RoleAnimi : public Object
{
public:
	RoleAnimi(void);
	~RoleAnimi(void);

	virtual void setArmature(Armature *armature);

	virtual Armature *getArmature() { return _armature; }

	virtual int getAnimiFlag() { return _animiFlag; }

	virtual void setAnimiFlag(int flag, bool doForce = false);

protected:
	Armature *_armature;

	Node *_node;

	int _animiFlag;
};

