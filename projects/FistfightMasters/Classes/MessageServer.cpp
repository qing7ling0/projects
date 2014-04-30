#include "MessageServer.h"
#include "BattleConfig.h"

DEFINE_CREATE_INSTANCE_FUNC(MessageServer);

MessageItem::MessageItem(void)
	: _msg("")
	, _over(false)
	, _node(nullptr)
{
}

MessageItem::~MessageItem(void)
{
	CC_SAFE_RELEASE(_node);
}

bool MessageItem::init(const std::string msg)
{
	_msg = msg;

	return true;
}

Node* MessageItem::getNode()
{
	if (!_node)
	{
		auto node = Text::create();
		node->setText(_msg);

		auto nodeBg = LayerColor::create(Color4B(0, 0, 0, 155));
		nodeBg->setContentSize(node->getContentSize()+Size(20, 10));

		node->setPosition(Point(nodeBg->getContentSize().width/2, nodeBg->getContentSize().height/2));

		nodeBg->addChild(node);

		nodeBg->setPosition(D_display.getCenterPoint());
		nodeBg->runAction(Sequence::create(
				DelayTime::create(2),
				Spawn::create(
					MoveBy::create(1, Point(0, -30)),
					FadeOut::create(1)
				),
				CallFunc::create(this, callfunc_selector(MessageItem::over)),
				NULL
			));
		_node = nodeBg;
		CC_SAFE_RETAIN(_node);
	}

	return _node;
}


MessageServer::MessageServer(void)
	: _curItem(nullptr)
{
}

MessageServer::~MessageServer(void)
{
}

bool MessageServer::init()
{
	if (!Layer::init()) return false;
	_messageItems.reserve(10);
	setLocalZOrder(ZORDER_MESSAGE);

	_instance = this;

	return true;
}

void MessageServer::onEnter()
{
	Layer::onEnter();
	scheduleUpdate();
}

void MessageServer::onExit()
{
	Layer::onExit();
	unscheduleUpdate();
}

void MessageServer::update(float dt)
{
	if (_curItem && _curItem->isOver())
	{
		removeChild(_curItem->getNode());
		_messageItems.erase(0);
		_curItem = nullptr;
	}
	if (_messageItems.size() > 0 && !_curItem)
	{
		_curItem = _messageItems.at(0);
		if (_curItem) addChild(_curItem->getNode());
	}
}

void MessageServer::addMessage(MessageItem* item)
{
	_messageItems.pushBack(item);
}