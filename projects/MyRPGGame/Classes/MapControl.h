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

	bool cameraTo(const Point point, float delayTime=0.5f, bool force=false, CameraType type=CameraType::camera_none);
	
	void cameraOver();
	
	/**
	* 检测角色有没有
	* 如果出界了会纠正off成正确的偏移
	* return true 出界；return false 没有出界
	*/
	virtual bool checkBound(Role *role);

	/**
	* 纠正镜头偏移,不能出界
	* 并转化成Map的实际偏移量
	*/
	virtual Point correctCamera(const Point off);

	void setCameraType(CameraType type);

	static MapControl* getInstance();

private:
	
	Point _off;

	CameraType _cameraType;

	bool _cameraMoving;
};

