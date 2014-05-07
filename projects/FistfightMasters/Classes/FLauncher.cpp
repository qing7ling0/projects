#include "FLauncher.h"
#include "FConfig.h"
#include "HelloWorldScene.h"

USING_NS_CC;

FLauncher::FLauncher(void)
{
}

FLauncher::~FLauncher(void)
{
}

void FLauncher::create(void)
{
	new FLauncher();
}

void FLauncher::onLoad()
{
	GameLauncher::onLoad();

    auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("FistfightMasters");
        director->setOpenGLView(glview);
    }
	
    // turn on display FPS
	director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	glview->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, ResolutionPolicy::SHOW_ALL);

	
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	
	D_display.x = origin.x;
	D_display.y = origin.y;
	D_display.w = visibleSize.width;
	D_display.h = visibleSize.height;
	D_display.cx = D_display.x + D_display.w/2;
	D_display.cy = D_display.y + D_display.h/2;

	Director::getInstance()->runWithScene(HelloWorld::createScene());
}

void FLauncher::onDispose(void)
{
	GameLauncher::onDispose();
}
