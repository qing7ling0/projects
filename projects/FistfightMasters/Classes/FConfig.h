#pragma once

#define SCREEN_WIDTH			960
#define SCREEN_HEIGHT			640
#define FPS_SHOW				true
#define FPS						60

struct Display
{
	float x;
	float y;
	float w;
	float h;
	float cx;
	float cy;
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

extern Display D_display;


typedef enum DirectionFlag 
{
	none,
    left,
    right,
	up,
	down,
	leftDown,
	leftUp,
	rightDown,
	rightUp
};