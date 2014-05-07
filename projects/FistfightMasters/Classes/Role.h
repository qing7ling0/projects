#pragma once
#include "RPGHead.h"

class Role : public Ref
{
public:
	Role(void);

	~Role(void);

	virtual bool init();

	virtual Node* getNode() { return _node; }

	virtual void update(float dt);

	virtual void setPosition(const float px, const float py);

	virtual void setPosition(const Point &point);
	
	virtual Point getPosition() const { return _position; }

	virtual float getPX() const { return _position.x; }

	virtual float getPY() const { return _position.y; }

protected:

	Node *_node;

	Point _position;
};

