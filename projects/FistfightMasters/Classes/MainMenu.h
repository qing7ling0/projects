#pragma once

#include "RPGHead.h"

using namespace gui;

class MainMenu : public Layer
{
public:
	MainMenu(void);
	~MainMenu(void);

	bool init(void);

    void gotoBattleScene();

	void endGame();

    void touchEvent(Object *pSender, TouchEventType type);    

	CREATE_SECNE_FUNC(MainMenu);

private:
	Layer *_uiLayer;
};

