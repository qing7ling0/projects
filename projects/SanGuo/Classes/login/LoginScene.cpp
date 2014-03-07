#include "LoginScene.h"
#include "battle\BattleScene.h"


LoginScene::~LoginScene(void)
{
}


bool LoginScene::init(void)
{
	if (Layer::init())
	{
		Layer *loginUI =Layer::create(); 
		//将UILayer层加入到当前的场景 
		this->addChild(loginUI); 
		Layout *m_pWidget = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("main/main.ExportJson"));
		loginUI->addChild(m_pWidget);
		
		Button *startBtn = dynamic_cast<Button*> (m_pWidget->getChildByName("btn_battle"));

		startBtn->setPressedActionEnabled(true);
		startBtn->setBright(true);

		startBtn->addTouchEventListener(this, toucheventselector(LoginScene::startGameTouchListener));

		return true;
	}

	return false;
}

void LoginScene::startGameTouchListener(Object* pSender, int eventType)
{
	if (eventType == TOUCH_EVENT_ENDED)
	{
		Scene *sc = BattleScene::createScene();
        Director::getInstance()->replaceScene(
		TransitionFade::create(0.5f, sc));
		
	}
}
