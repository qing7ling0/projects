#include "CommonRes.h"


void CommonRes::load(void)
{
	totalCount = 1;
	loadCount = 0;

	Director::getInstance()->getTextureCache()->addImageAsync(s_pathloadingbg, CC_CALLBACK_1(CommonRes::loadCallback, this));
}

void CommonRes::loadCallback(Object *obj)
{
	loadCount++;
}

float CommonRes::loadProgress()
{
	return loadCount *1.0f / totalCount;
}

