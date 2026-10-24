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
		int index;
		result = cr_cfg_tcp_active_get(robotHandle, &index);  //读取当前激活的TCP索引
		if (result == sucess)
		{
			TCPMsg tcpMsg;
			index = 0;
			result = cr_cfg_tcp_get(robotHandle, index, &tcpMsg);  //需要先存在索引号为0的TCP
			if (result == sucess)
			{
				double offset[6] = { 3,10,9,90,80,70 };
				for (int i = 0; i < 6; i++)
				{
					tcpMsg.tcpOffset[i] = offset[i];
				}
				result = cr_cfg_tcp_set(robotHandle, index, tcpMsg);  //编辑索引号为0的TCP数据
				if (result == sucess)
				{
					TCPMsg tcpMsg2;
					int i;
					char name[20] = { "TCP" };
					strcpy_s(tcpMsg2.tcpName, sizeof(name), name);
					double offset2[6] = { 5,10,15,10,20,30 };
					for (i = 0; i < 6; i++)
					{
						tcpMsg2.tcpOffset[i] = offset2[i];
					}
					result = cr_cfg_tcp_add(robotHandle, tcpMsg2);  //增加TCP
					if (result == sucess)
					{
						index = 1;
						result = cr_cfg_tcp_active_set(robotHandle, index);  //激活索引号为1的TCP
						if (result == sucess)
						{
							result = cr_cfg_tcp_active_get(robotHandle, &index);
							if (result == sucess)
							{
								printf("%d:当前激活的TCP为%d\n", __LINE__, index);
								index = 0;
								result = cr_cfg_tcp_delete(robotHandle, index);  //删除索引号为0的TCP
								if (result == sucess)
								{
									printf("%d:已成功删除索引号为0的TCP", __LINE__);
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


