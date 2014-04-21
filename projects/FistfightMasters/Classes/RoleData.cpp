#include "RoleData.h"

RoleData::RoleData(void)
	: _roleAnimiActions(nullptr)
	, _ememy(false)
	, _animiCount(0)
	, _grid(Point::ZERO)
{
}


RoleData::~RoleData(void)
{
	if (_roleAnimiActions)
	{
		for(auto &action : *_roleAnimiActions)
		{
			if (action) delete action;
			action = nullptr;
		}
	}
	CC_SAFE_DELETE(_roleAnimiActions);
}

bool RoleData::init(void)
{
	_skillDatas.reserve(3);
	_roleAnimiActions = new std::vector<AnimiAction*>();
	return true;
}
