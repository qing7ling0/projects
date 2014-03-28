#pragma once
#include "RPGHead.h"

class MapControl : public Object
{
public:
	MapControl(void);
	~MapControl(void);

	void init();

	void load();

	static MapControl* getInstance();

	Size getMapSize();

private:
	Node *_mapLayer;
	Size _size;
};

