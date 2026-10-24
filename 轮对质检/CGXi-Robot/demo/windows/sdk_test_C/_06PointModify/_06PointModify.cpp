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
	PointCSNode pointCSNode;
	char name[32] = { "point3" };
	strcpy_s(pointCSNode.name, sizeof(name), name);
	double toolAxisAngle[6] = { 30,30,30,30,30,30 };
	double toolPosition[6];
	int count;
	if (result == sucess)
	{
		result = cr_cfg_cs_point_count(robotHandle, &count);  //读取点坐标系个数
		for (int i = 0; i < 6; i++)
		{
			pointCSNode.point.toolAxisAngle[i] = toolAxisAngle[i];
		}
		if (result == sucess)
		{
			if (count > 0)
			{
				for (int i = 0; i < count; i++)
				{
					PointCSNode pointCSnode;
					result = cr_cfg_cs_point_get(robotHandle, i, &pointCSnode);
					if (name == pointCSnode.name)
					{
						result = cr_kineForward(robotHandle, toolAxisAngle, toolPosition); //正解求点的位姿
						if (result == sucess)
						{
							pointCSNode.isValid = TRUE;
							pointCSNode.id = 1;
							result = cr_cfg_cs_point_set(robotHandle, i, pointCSNode);
						}
						else
						{
							printf("%d:%d\n", __LINE__, result);
						}
						break;
					}
					if (i == (count - 1))
					{
						result = cr_kineForward(robotHandle, toolAxisAngle, toolPosition); //正解求点的位姿
						if (result == sucess)
						{
							pointCSNode.isValid = TRUE;
							pointCSNode.id = 1;
							result = cr_cfg_cs_point_add(robotHandle, pointCSNode);//增加点坐标系数据
						}
						else
						{
							printf("%d:%d\n", __LINE__, result);
						}
					}
				}
			}
			else
			{
				pointCSNode.isValid = TRUE;
				pointCSNode.id = 1;
				result = cr_cfg_cs_point_add(robotHandle, pointCSNode);//增加点坐标系数据
			}
			int index = 0;
			result = cr_cfg_cs_point_get(robotHandle, index, &pointCSNode);//读取索引号为0的点坐标系数据
			if (result == sucess)
			{
				printf("%s\n", pointCSNode.name);                      //打印索引号为0的点坐标系名字
				index = 0;
				result = cr_cfg_cs_point_delete(robotHandle, index);  //删除索引号为0的点坐标系
				if (result == sucess)
				{
					printf("%s\n", "已成功删除点坐标系");
				}
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


