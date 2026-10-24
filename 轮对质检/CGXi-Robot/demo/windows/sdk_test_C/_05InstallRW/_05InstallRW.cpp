#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "robotapi.h"
#include "basestruct.h"
#include <windows.h>
#include <string.h>

int main()
{
	RobotHandle robotHandle;
	CRresult result = cr_create_robot(&robotHandle, "192.168.6.6", 2323, "123");  // 机械臂连接
	char name[CR6_ISTALL_VAR_NAME_LENGTH] = { "i_var_1" };
	VariableMsg variablemsg;
	strcpy_s(variablemsg.variableName, sizeof(name), name);
	variablemsg.variableType = LUA_TBOOLEAN;
	variablemsg.boolValue = TRUE;
	variablemsg.variableID = 3;
	if (result == sucess)
	{
		int count =-1;
		result = cr_cfg_var_install_count(robotHandle, &count);  //读取安装变量个数
		if (result == sucess)
		{
			if (count > 0)
			{
				for (int i = 0; i < count; i++)
				{
					VariableMsg variableMsg;
					result = cr_cfg_var_install_get(robotHandle, i, &variableMsg);
					if (strcmp(name, variableMsg.variableName) == 0) //判断是否已存在名为i_var_1的安装变量，如果有就修改，没有就增加
					{
						result = cr_cfg_var_install_set(robotHandle, i, &variablemsg);
						if (result == sucess)
						{
							printf("%s\n", "已成功修改安装变量");
						}
						else
						{
							printf("%d:%d\n", __LINE__, result);
						}
						break;
					}
					if (i == (count - 1))
					{
						result = cr_cfg_var_install_add(robotHandle, &variablemsg);  //增加安装变量
						if (result == sucess)
						{
							printf("%s\n", "已成功增加安装变量");
						}
						else
						{
							printf("%d:%d\n", __LINE__, result);
						}
					}
				}
			}
			else  //如果不存在安装变量，则添加安装变量
			{
				result = cr_cfg_var_install_add(robotHandle, &variablemsg);  //增加安装变量
				if (result == sucess)
				{
					printf("%d:%s\n", __LINE__,"已成功增加安装变量");
				}
				else
				{
					printf("%d:%d\n", __LINE__, result);
				}
			}
			
		}
		else
		{
			printf("%d:%d\n", __LINE__, result);
		}
	}
	else
	{
		printf("%d:%d\n", __LINE__, result);
	}
	result = cr_destroy_robot(robotHandle);  //机器人断开连接，释放句柄
	if (result == sucess)
	{
		printf("%d:机器人已成功断开连接", __LINE__);
	}
	else
	{
		printf("%d:%d\n", __LINE__, result);
		printf("%d:机器人断开连接失败", __LINE__);
	}
	system("pause");
}


