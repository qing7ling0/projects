#include "MainMenu.h"
#include "BattleController.h"

MainMenu::MainMenu(void)
{
}


MainMenu::~MainMenu(void)
{
}

bool MainMenu::init(void)
{
    if ( !Layer::init() )
    {
        return false;
    }

	_uiLayer = Layer::create();
	_uiLayer->setPosition(Point(D_display.getLeftBottom()));
	addChild(_uiLayer);

	auto spBg = Sprite::create("images/mainmenu_bg.jpg");
	spBg->setPosition(D_display.getCenterPoint());
	_uiLayer->addChild(spBg);


	auto btnStart = Button::create();
    btnStart->setTouchEnabled(true);
    btnStart->loadTextures("images/btn_start.png", "", "");
	btnStart->setPosition(Point(D_display.cx, D_display.cy+43));
	btnStart->setTag(1);
    btnStart->addTouchEventListener(this, toucheventselector(MainMenu::touchEvent));
    _uiLayer->addChild(btnStart);

	auto btnExit = Button::create();
    btnExit->setTouchEnabled(true);
    btnExit->loadTextures("images/btn_exit.png", "", "");
	btnExit->setPosition(Point(D_display.cx, D_display.cy-43));
    btnExit->addTouchEventListener(this, toucheventselector(MainMenu::touchEvent));
	btnExit->setTag(2);
    _uiLayer->addChild(btnExit); 

	return true;
}

void MainMenu::touchEvent(Ref *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:

			if (pSender)
			{
				Node *node = static_cast<Node*>(pSender);
				if (node)
				{
					switch (node->getTag())
					{
					case 1:
						gotoBattleScene();
						break;
					case 2:
						endGame();
						break;
					default:
						break;
					}
				}
			}

            break;
            
        default:
            break;
    }
}


void MainMenu::gotoBattleScene()
{
	auto *sc = BattleController::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, sc));
}

void MainMenu::endGame()
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}