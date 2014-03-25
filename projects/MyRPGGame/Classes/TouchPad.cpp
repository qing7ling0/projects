#include "TouchPad.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;


TouchPad::TouchPad(void):_state(kPadStateUngrabbed)
	, _gridWidth(90)
	, _padLayer(nullptr)
	, _headPoint(Point::ZERO)
	, _endPoint(Point::ZERO)
	, _startPoint(Point::ZERO)
	, _currentTouchIndex(Location(0,0))
	, _TouchOverCall(nullptr)
{
}


TouchPad::~TouchPad(void)
{
}

bool TouchPad::init()
{
	if (LayerRGBA::init())
	{
		_touchPoints.reserve(9);
		_directionLists.reserve(9);

		_padLayer = LayerRGBA::create();
		_padLayer->setAnchorPoint(Point(0.5f, 0.5f));
		_padLayer->setContentSize(Size(_gridWidth*3, _gridWidth*3));
		_padLayer->ignoreAnchorPointForPosition(false);

		addChild(_padLayer);

		for(int i=0; i<9; i++)
		{
			int row = i / 3;
			int cols = i % 3;
			Sprite *_sp = Sprite::create("images/pad_ico_01.png");
			_sp->setPosition(Point(row*_gridWidth + _gridWidth/2, cols*_gridWidth + _gridWidth/2));
			_sp->setTag(i*2);
			_sp->setScale(0.4f);
			_padLayer->addChild(_sp);

			_sp = Sprite::create("images/pad_ico_02.png");
			_sp->setPosition(Point(row*_gridWidth + _gridWidth/2, cols*_gridWidth + _gridWidth/2));
			_sp->setTag(i*2+1);
			_sp->setScale(0.4f);
			_sp->setVisible(false);
			_padLayer->addChild(_sp);
		}

		return true;
	}

	return false;
}

void TouchPad::onEnter()
{
	LayerRGBA::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
    
	listener->onTouchBegan = CC_CALLBACK_2(TouchPad::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TouchPad::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TouchPad::onTouchEnded, this);
    
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void TouchPad::onExit()
{
	LayerRGBA::onExit();
}

bool TouchPad::onTouchBegan(Touch* touch, Event* event)
{
    if (_state != kPadStateUngrabbed) return false;
    
    _state = kPadStateGrabbed;
    auto touchPoint = touch->getLocation();
	_startPoint.x = touchPoint.x;
	_startPoint.y = touchPoint.y;

	_padLayer->setPosition(Point(_startPoint.x, _startPoint.y));

	_directionLists.clear();
	_touchPoints.clear();
	_currentTouchIndex = Location(-1, -1);
	addLocation(Location(1,1), touchPoint);

    return true;
}

void TouchPad::onTouchMoved(Touch* touch, Event* event)
{
    CCASSERT(_state == kPadStateGrabbed, "TouchPad - Unexpected state!");    
	updateThroughPoint(touch->getLocation());
}

void TouchPad::onTouchEnded(Touch* touch, Event* event)
{
    CCASSERT(_state == kPadStateGrabbed, "TouchPad - Unexpected state!");    
    

	updateThroughPoint(touch->getLocation());

	for(unsigned int i=1; i<_touchPoints.size(); i++)
	{
		_padLayer->removeChildByTag(10000+i);
	}
    _state = kPadStateUngrabbed;


	_TouchOverCall(this);
}

void TouchPad::updateThroughPoint(const Point &touchPoint)
{
	Point point = touchPoint -_startPoint+Point(_gridWidth*3/2, _gridWidth*3/2);
	bool ok = false;
	do
	{
		for(int i=0; i<9; i++)
		{
			Location temp = Location(i/3, i%3);
			bool touched = checkTouch(temp, Point(point.x, point.y));
			if (touched)
			{
				ok = temp.x > -1 && (temp.x!=_currentTouchIndex.x || temp.y!=_currentTouchIndex.y);
				if (ok)
				{
					addLocation(temp, point);
					break;
				}
			}
		}
	} while (ok);
}

bool TouchPad::checkTouch(const Location &location, const Point &touchPoint)
{
	Point _pcp = Point(location.x*_gridWidth+_gridWidth/2, location.y*_gridWidth+_gridWidth/2);
	const float dx = _pcp.x-touchPoint.x;
	const float dy = _pcp.y-touchPoint.y;
	float _dis = dx*dx + dy*dy;
	// CCLOG("addLocation _dis=%f, x = %d, y = %d", _dis, location.x, location.y);
	return _dis < 1600;
}

void TouchPad::addLocation(const Location &location, const Point &touchPoint)
{
    //CCLOG("addLocation x = %d, y = %d,   curx=%d, cury=%d", location.x, location.y, _currentTouchIndex.x, _currentTouchIndex.y);
	if (_currentTouchIndex.x > -1 && _currentTouchIndex.y>-1)
	{
		auto batchNode = SpriteBatchNode::create("images/pad_line_01.png");
		auto blocks = Scale9Sprite::create();
    
		blocks->updateWithBatchNode(batchNode, Rect(0, 0, 50, 26), false, Rect(17, 9, 17, 9));
		blocks->setAnchorPoint(Point(0, 0.5f));
		blocks->setPosition(Point(_currentTouchIndex.x*_gridWidth+_gridWidth/2, _currentTouchIndex.y*_gridWidth+_gridWidth/2));
		
		float sx = (location.x - _currentTouchIndex.x) * _gridWidth;
		float sy = (location.y - _currentTouchIndex.y) * _gridWidth;
		float angle = -atan2f(sy, sx) / M_PI * 180;

		float length = hypotf(sx, sy);

		blocks->setRotation(angle);


		blocks->setContentSize(Size(length, 15));
		blocks->setTag(10000+_touchPoints.size());
		_padLayer->addChild(blocks, -1);
	}

	_touchPoints.push_back(location);
	int size = _touchPoints.size();
	if (size > 1)
	{
		DirectionFlag dir = getDirection(_currentTouchIndex, location);
		if (dir != DirectionFlag::none) _directionLists.push_back(dir);
	}
	_currentTouchIndex.x = location.x;
	_currentTouchIndex.y = location.y;

	_padLayer->getChildByTag(location.x*6+location.y*2+1)->setVisible(true);
}

DirectionFlag TouchPad::getDirection(const Location &fromLocation, const Location &toLocation)
{
	if (fromLocation.x==toLocation.x && fromLocation.y==toLocation.y)
	{
		return DirectionFlag::none;
	}
	
	int sx = fromLocation.x - toLocation.x;
	int sy = fromLocation.y - toLocation.y;

	if (sx==0)
	{
		return sy<0?DirectionFlag::up:DirectionFlag::down;
	}
	else if (sy == 0)
	{
		return sx<0?DirectionFlag::right:DirectionFlag::left;
	}
	else if (sx < 0)
	{
		return sy<0?DirectionFlag::leftUp:DirectionFlag::leftDown;
	}
	else if (sx > 0)
	{
		return sy<0?DirectionFlag::rightUp:DirectionFlag::rightDown;
	}

	return DirectionFlag::none;
}