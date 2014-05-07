#pragma once

#include "RPGHead.h"

typedef enum tagPadState 
{
    kPadStateGrabbed,
    kPadStateUngrabbed
} tagPadState;

struct Location
{
	int x;
	int y;
	Location(int x, int y){this->x=x; this->y=y;};
};

// ´¥Ãþ°æ
class TouchPad : public cocos2d::__LayerRGBA
{
public:
	TouchPad(void);
	~TouchPad(void);

	virtual bool init();
    virtual void onEnter();
    virtual void onExit();
	
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

    CREATE_FUNC(TouchPad);

	void setTouchOverCall(const std::function<void(Ref*)> &func)
	{
		_TouchOverCall = func;
	}

private:
	void updateThroughPoint(const Point &point);
	bool checkTouch(const Location &location, const Point &touchPoint);
	void addLocation(const Location &location, const Point &touchPoint);
	DirectionFlag getDirection(const Location &fromLocation, const Location &toLocation);

public:
	std::vector<DirectionFlag> _directionLists;

private:
	int _state;
	int _gridWidth;
	std::vector<Location> _touchPoints;
	Point _startPoint;
	Point _headPoint;
	Point _endPoint;

	Location _currentTouchIndex;

	__LayerRGBA *_padLayer;

	std::function<void(Ref*)> _TouchOverCall;
};


