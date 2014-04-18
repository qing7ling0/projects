#pragma once

#include "cocos2d.h"

#define SCREEN_WIDTH			960
#define SCREEN_HEIGHT			640
#define FPS_SHOW				true
#define FPS						60

USING_NS_CC;

struct Display
{
	float x;
	float y;
	float w;
	float h;
	float cx;
	float cy;

	Point getLeftBottom()
	{
		return Point(x, y);
	}

	Point getCenterPoint()
	{
		return Point(cx, cy);
	}

	float getRightX()
	{
		return x + w;
	}

	float getTopY()
	{
		return y+h;
	}
};

#define CREATE_SECNE_FUNC(__TYPE__) \
CREATE_FUNC(__TYPE__) \
static cocos2d::Scene* createScene() \
{ \
	auto scene = Scene::create(); \
	auto layer = __TYPE__::create(); \
    scene->addChild(layer); \
    return scene; \
}

#define NEW_ROLE_SCRIPT(__TYPE__) new __TYPE__(); 

#define EXTERN_CREATE_INSTANCE_FUNC(__TYPE__) static __TYPE__* getInstance();

#define DEFINE_CREATE_INSTANCE_FUNC(__TYPE__) \
static __TYPE__ *_instance = nullptr; \
__TYPE__* __TYPE__::getInstance() \
{ \
	return _instance; \
}

extern Display D_display;