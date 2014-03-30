#pragma once
#include "RPGHead.h"
#include "Role.h"

#define MAX_MOVE_X			 50

// 移动一屏距离所需时间
#define MAX_MOVE_TIME		 1


typedef enum CameraType
{
	// 镜头可以任意控制
	camera_none,

	// 镜头由英雄控制
	camera_hero,
};

class MapControl : public Role
{
public:
	MapControl(void);
	~MapControl(void);

	bool init();

	void load();

	void update(float dt);

	Point getRoleCenterPoint() const;

	bool cameraTo(const Point point, float delayTime=0.5f, bool force=false);

	void cameraToRole();
	
	void cameraOver();

	bool cameraMoving();

	void setCameraType(CameraType type);

	static MapControl* getInstance();

	Size getMapSize();

private:

	Size _size;
	
	Point _off;

	CameraType _cameraType;

	bool _cameraMoving;
};

