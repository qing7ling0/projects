#pragma once

#include "RPGHead.h"

class MainMenu : public Layer
{
public:
	MainMenu(void);
	~MainMenu(void);

	bool init(void);

	/*void onEnter(void);

	void onExit(void);*/

    void gotoBattleScene();

	void endGame();

    void touchEvent(Ref *pSender, TouchEventType type);    

	CREATE_SECNE_FUNC(MainMenu);

private:
	Layer *_uiLayer;
};

