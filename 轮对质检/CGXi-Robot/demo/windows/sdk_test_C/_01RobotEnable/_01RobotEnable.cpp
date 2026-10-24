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
		enum RobotModes robotMode;
		result = cr_get_robotMode(robotHandle, &robotMode);  //读机械臂当前状态
		if (result == sucess &&robotMode == 6)	//判断状态,robotMode为6时是本体未上电状态才可以进行上电
		{
			result = cr_poweron(robotHandle); //机械臂上电 
			if (result == sucess)
			{
				while (result == sucess)
				{
					result = cr_get_robotMode(robotHandle, &robotMode);
					Sleep(50);
					if (robotMode == 8)      //判断状态,robotMode为8时是机器人上电完成后再进行使能
						break;
				}
				result = cr_enable(robotHandle);  //机械臂使能
				if (result == sucess )
				{				
					while (result == sucess)
					{
						result = cr_get_robotMode(robotHandle, &robotMode);
						Sleep(50);
						if (robotMode == 103)  //判断状态,robotMode为103时机器人使能完成
							break;
					}
					printf("%d:%s\n", __LINE__, "使能完成");
				}
				else
				{
					printf("%d:%d\n",__LINE__,result);
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