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
		PointCSNode pointCSNode;
		char name[32] = { "point3" };
		strcpy_s(pointCSNode.name, sizeof(name), name);
		double toolAxisAngle[6] = { 30,30,30,30,30,30 };
		double toolPosition[6];
		int count;
		for (int i = 0; i < 6; i++)
		{
			pointCSNode.point.toolAxisAngle[i] = toolAxisAngle[i];
		}
		result = cr_kineForward(robotHandle, toolAxisAngle, toolPosition); //正解求点的位姿
		if (result == sucess)
		{
			for (int i = 0; i < 6; i++)
			{
				pointCSNode.point.toolPosition[i] = toolPosition[i];
			}
			result = cr_cfg_cs_point_count(robotHandle, &count);  //读取点坐标系个数
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
			}
			else
			{
				printf("%d:%d\n", __LINE__, result);
			}
			if (result == sucess)
			{
				double pose[ROB_AXIS_NUM];
				result = cr_get_tcpActualPose(robotHandle, pose);  //读实际TCP位置
				if (result == sucess)
				{
					int basePoseLen = 6;
					int userPoseLen = 6;
					int poseInUserLen = 6;
					double basePose[6];
					double userPose[6];
					for (int i = 0; i < ROB_AXIS_NUM; i++)
					{
						basePose[i] = pose[i];
						userPose[i] = pointCSNode.point.toolPosition[i];//将点坐标系设置为用户坐标系
					}
					double poseInUser[6];
					result = cr_compute_pose_base_to_user(basePose, basePoseLen, userPose, userPoseLen, poseInUser, poseInUserLen);  //基坐标系下位姿转移到用户坐标系下
					if (result == sucess)
					{
						for (int i = 0; i < 6; i++)
						{
							printf("%d:%f\n", __LINE__, poseInUser[i]);  
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


