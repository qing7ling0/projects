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

#define F_CREATE_FUNC_ARGS_1(__TYPE__, _VARTYPE_, _VARNAME_) \
static __TYPE__* create(_VARTYPE_ _VARNAME_) \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init(_VARNAME_)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

#define F_CREATE_FUNC_ARGS_2(__TYPE__, _VARTYPE1_, _VARNAME1_, _VARTYPE2_, _VARNAME2_) \
static __TYPE__* create(_VARTYPE1_ _VARNAME1_, _VARTYPE2_ _VARNAME2_) \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init(_VARNAME1_, _VARNAME2_)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

#define F_CREATE_FUNC_ARGS_3(__TYPE__, _VARTYPE1_, _VARNAME1_, _VARTYPE2_, _VARNAME2_, _VARTYPE3_, _VARNAME3_) \
static __TYPE__* create(_VARTYPE1_ _VARNAME1_, _VARTYPE2_ _VARNAME2_, _VARTYPE3_ _VARNAME3_) \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init(_VARNAME1_, _VARNAME2_, _VARNAME3_)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

#define NEW_ROLE_SCRIPT(__TYPE__) new __TYPE__(); 

#define EXTERN_CREATE_INSTANCE_FUNC(__TYPE__) static __TYPE__* getInstance();

#define DEFINE_CREATE_INSTANCE_FUNC(__TYPE__) \
static __TYPE__ *_instance = nullptr; \
__TYPE__* __TYPE__::getInstance() \
{ \
	return _instance; \
}

/**
* 添加帧动画帧缓存
*/
#define ADD_ANIMIPLAYER_SPRITE_FRAME_CACHE_PLIST(path, name, formatStr) \
const char* animiPath = String::createWithFormat("%s%s.plist", path, name)->getCString(); \
SpriteFrameCache::getInstance()->addSpriteFramesWithFile(animiPath);

/**
* 删除帧动画帧缓存
*/
#define REMOVE_ANIMIPLAYER_SPRITE_FRAME_CACHE_PLIST(path, name) \
const char* animiPath = String::createWithFormat("%s%s.plist", path, name)->getCString(); \
SpriteFrameCache::getInstance()->removeSpriteFrameByName(animiPath); 

/**
* 创建帧动画所有的帧
*/
#define CREATE_ANIMIPLAYER_FRAMES(name, formatStr, frames, actionStart, actionEnd) \
for(int ___actionIndex___=actionStart; ___actionIndex___<=actionEnd; ___actionIndex___++) \
{ \
	const char* imgName = String::createWithFormat(formatStr, name, ___actionIndex___)->getCString(); \
	frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName)); \
}

extern Display D_display;