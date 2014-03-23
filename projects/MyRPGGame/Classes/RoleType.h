#pragma once

//
// 角色移动方向
//
typedef enum RoleDirect
{
	roleNone,
	roleLeft,
	roleRight,
	roleUp,
	roleDown,
	roleUpLeft,
	roleUpRight,
	roleDownLeft,
	roleDownRight,
};



//
// 角色动作类型
//
typedef enum RoleActionBase
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
	actionDefense,
	// 跳
	actionJump
};

//
// 角色命令
//
typedef enum CommandType
{
	// 无
	noneCommand,
	// 攻击
	attackCommand,
	// 待机
	waitCommand,
	// 移动
	moveCommand,
	// 跑
	runCommand,
	// 防御
	defenseCommand
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


