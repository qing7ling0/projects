#pragma once

#include "cocos2d.h"

USING_NS_CC;

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
class TouchPad : public cocos2d::LayerRGBA
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

private:
	void updateThroughPoint(const Point &point);
	bool checkTouch(const Location &location, const Point &touchPoint);
	void addLocation(const Location &location, const Point &touchPoint);

private:
	int _state;
	int _gridWidth;
	std::vector<Location> _touchPoints;
	Point _startPoint;
	Point _headPoint;
	Point _endPoint;

	Location _currentTouchIndex;

	LayerRGBA *_padLayer;
};

