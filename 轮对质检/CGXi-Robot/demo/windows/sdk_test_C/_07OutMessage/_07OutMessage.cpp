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
		const char  *programfile = "function mainFuncProgram()\n"
		"--start robotConfig\n"
		"TCP_1 = { 0,0,0,0,0,0 }\n"
		"Payload_1= { 0,{0,0,0} }\n"
		"set_tcp_payload(Payload_1[1], Payload_1[2])\n"
		"--end robotConfig\n"
		"function RobotProgram()\n"
		"while (true)\n"
		"do\n"
		"--popup_out:text\n"
		"popup_message(\"hello\", \"message\", false, false, true)\n"
		"wait(1)  --sync\n"
		"end\n"
		"end\n"
		"RobotProgram_Result = task_create(RobotProgram)\n"
		"function PauseFuncProgram()\n"
		"while (true)\n"
		"do\n"
		"wait(100)  --sync\n"
		"end\n"
		"end\n"
		"PauseFuncProgram_Result = task_create(PauseFuncProgram)\n"
		"end\n"
		"mainFuncProgram_Result = task_create(mainFuncProgram)";
		result = cr_downloadProgram(robotHandle, programfile);  //加载程序
		if (result == sucess)
		{
			result = cr_play(robotHandle);  //运行程序
			if (result == sucess)
			{
				BOOL hasPopup;
				result = cr_script_popup_exist(robotHandle, &hasPopup);  //是否存在弹窗：1-是，0-否
				if (result == sucess)
				{
					if (hasPopup == TRUE)
					{
						PopUpMsg popupMsg;
						result = cr_script_popup_msg_get(robotHandle, &popupMsg);  //读取弹窗信息
						if (result == sucess)
						{
							printf("%d:%d\n", __LINE__, popupMsg.popupType);
							result = cr_stop(robotHandle);  //停止程序运行
						}
						else
						{
							printf("%d:%d\n", __LINE__, result);
						}
					}
					else
					{
						printf("%d:%s\n", __LINE__, "没有弹窗信息");
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


