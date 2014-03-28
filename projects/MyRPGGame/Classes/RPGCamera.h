#pragma once
#include "RPGHead.h"

class RPGCamera : public Object
{
public:
	RPGCamera(void);
	~RPGCamera(void);

	virtual bool init(Size size, Size sceneSize);

	//virtual void update(float dt);

	/**
	* 检测镜头有没有出界
	* return true 出界；return false 没有出界
	*/
	virtual bool checkBound(const Point off);

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
	
};

