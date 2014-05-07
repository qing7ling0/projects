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

	virtual void toScreen(const float sx, const float sy);

	virtual void setPosition(const float px, const float py);

	virtual void setPosition(const Point &point);
	
	virtual Point getPosition() const { return _position; }

	virtual float getPX() const { return _position.x; }

	virtual float getPY() const { return _position.y; }

	virtual void setSize(const Size size);

	virtual Size getSize() const { return _size; };

	virtual Rect getBounds() { return Rect(_position.x-_size.width/2, _position.y, _size.width, _size.height); }

protected:

	Node *_node;

	Point _position;

	Size _size;
};

