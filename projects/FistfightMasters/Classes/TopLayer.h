#pragma once
#include "RPGHead.h"

/**
战斗最上层
放置战斗按钮
战斗提示等UI

*/

class TopLayer : public Layer
{
public:
	TopLayer(void);
	~TopLayer(void);

	bool init(void);

	void gameStart();

	void yourTurn();

	void showImageEffect(const std::string &imageName);

	CREATE_FUNC(TopLayer);
};

