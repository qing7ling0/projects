#pragma once

//
// 角色方向
//
typedef enum RoleDirect
{
	roleLeft,
	roleRight
};

//
// 角色动作类型
//
typedef enum RoleAction
{
	// 攻击
	actionAttack,
	// 被攻击
	actionHurt,
	// 待机
	actionWait,
	// 移动
	actionMove,
	// 跑
	actionRun,
	// 防御
	actionDefense
};


typedef enum ScriptType
{
	scriptRobot
};

struct RoleData
{
	int roleId;
	float px;
	float py;
	ScriptType scriptType;
	RoleData()
	{
		this->roleId = 0;
		this->px = 0;
		this->py = 0;

	}

	RoleData(const int roleId, const float px, const float py, const ScriptType scriptType)
	{
		this->roleId = roleId;
		this->px = px;
		this->py = py;
		this->scriptType = scriptType;
	}
};


