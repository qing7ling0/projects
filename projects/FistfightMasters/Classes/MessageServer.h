#pragma once
#include "RPGHead.h"


class MessageItem : public Ref
{
public:
	MessageItem(void);
	~MessageItem(void);

	virtual bool init(const std::string msg);

	virtual Node* getNode();

	virtual bool isOver() { return _over; }

	virtual void over() { _over = true; }

	F_CREATE_FUNC_ARGS_1(MessageItem, std::string, msg);

protected:
	std::string _msg;

	bool _over;

	Node* _node;
};

class MessageServer : public Layer
{
public:
	MessageServer(void);
	~MessageServer(void);
	
	virtual bool init(void);

	virtual void onEnter(void);

	virtual void onExit(void);

	virtual void update(float dt);

	void addMessage(MessageItem* item);

	CREATE_FUNC(MessageServer);

	EXTERN_CREATE_INSTANCE_FUNC(MessageServer);

private:
	Node* _node;

	Vector<MessageItem*> _messageItems;

	MessageItem* _curItem;
};

