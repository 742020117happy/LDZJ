#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "robotapi.h"
#include "basestruct.h"
#include<windows.h>

int main()
{
	RobotHandle robotHandle;
	CRresult result = cr_create_robot(&robotHandle, "192.168.6.6", 2323, "123");  // 机械臂连接
	if (result == sucess)
	{
		Lua_ScriptStatus scriptstatus;
		result = cr_get_lua_scriptstatus(robotHandle, &scriptstatus);  //读脚本运行状态
		if (result == sucess&&scriptstatus == lua_Script_stop) //当脚本运行状态处于脚本程序停止时才可进行程序下载
		{
			char crpFilepathname[100] = ".././program/demo.crp";
			//.crp文件路径
			char crscriptFilepathname[100] = ".././program/demo.crscript";
			//脚本程序路径
			result = cr_downloadProject(robotHandle, crpFilepathname, crscriptFilepathname); //下载工程
			if (result == sucess)
			{
				result = cr_play(robotHandle);  //运行工程
				if (result == sucess)
				{
					while (result == sucess)
					{
						enum RobotModes robotMode;
						result = cr_get_robotMode(robotHandle, &robotMode);  
						if (robotMode == 103)                                //读机械臂当前状态,程序停止状态下才可以上传程序
							break;
					}
					if (result == sucess)	//判断状态
					{
						char FilePath[100] = ".././program/"; //文件保存路径
						char filename[100] = "demo";  //.crp和脚本程序的文件名
						result = cr_uploadProject(robotHandle, FilePath, filename);  //工程文件上传
						if (result == sucess)
						{
							printf("%d:%s\n", __LINE__, "已成功上传工程文件");
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
		}
		else
		{
			printf("%d:%d\n", __LINE__, scriptstatus);
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







