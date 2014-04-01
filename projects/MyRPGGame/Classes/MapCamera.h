#pragma once
#include "RPGHead.h"
#include "Role.h"
#include "MapControl.h"

typedef enum CameraType
{
	// 镜头可以任意控制
	camera_none,

	// 镜头由英雄控制
	camera_hero,
};

class MapCamera : public Object
{
public:
	MapCamera(void);
	~MapCamera(void);

	virtual bool init(Size size, Size sceneSize);

	virtual void addObserved(Role *role);

	virtual void setMap(MapControl *map);

	virtual void setCameraType(CameraType type);

	//virtual void update(float dt);

	/**
	* 检测镜头有没有出界
	* return true 出界；return false 没有出界
	*/
	virtual bool checkBound(Point off);

	/**
	* 设置镜头观察点
	*/
	virtual void setCamera(const Point viewPosition);
	
	/**
	* 设置镜头观察点
	*/
	virtual void setCamera(float x, float y);

	/**
	* 纠正镜头观察点,不能出界
	*/
	virtual Point correctCamera(const Point viewPosition);

	virtual void update(float dt);

protected:

	/**
	* 镜头发生移动
	*/
	virtual void updateCamera(const float x, const float y);

protected:
	// 镜头大小
	Size _size;

	// 镜头场景大小
	Size _sceneSize;

	// 镜头偏移量
	Point _off;
	
	Vector<Role*> _observedRoles;

	MapControl* _map;

	CameraType _cameraType;

	bool _cameraUpdate;
};

