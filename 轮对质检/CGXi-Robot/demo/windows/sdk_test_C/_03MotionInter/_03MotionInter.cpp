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
		double jointpos[6] = { 0, 0, 90, 0, -90, 0 };  //目标点示例数据
		double pose[6] = { 0, 0, 0, 0, 0, 0 };  //在MoveJ中无影响
		PointControlPara  pointControlPara;
		for (int index = 0; index < ROB_AXIS_NUM; index++)
		{
			pointControlPara.pose[index] = pose[index];
			pointControlPara.jointpos[index] = jointpos[index];
			pointControlPara.tcpOffset[index] = 0;
			pointControlPara.coordinatePose[index] = 0;
			pointControlPara.speed[index] = 30;
			pointControlPara.acc[index] = 30;
			pointControlPara.jerk[index] = 60;
		}
		pointControlPara.tcpID = -1;
		pointControlPara.coordinateType = jointCoordinate;
		pointControlPara.pointTransType = pointTransStop;
		pointControlPara.pointTransRadius = 0;
		pointControlPara.poseTranType = poseTranMoveToTargetPose;
		pointControlPara.motiontriggerMode = MovetriggerbyOnlyRpc;
		result = cr_moveJ(robotHandle, pointControlPara);  //轴空间运动
		if (result == sucess)
		{
			Sleep(50);
			BOOL isRobotMoving;
			while (result == sucess)
			{
				result = cr_get_robotMoveStatus(robotHandle, &isRobotMoving);  //读机械臂运动状态,如果运动已经停止，代表上一次运动已经结束，则跳出循环进行下一次运动
				if (!isRobotMoving)
				{
					break;
				}
			}
			result = cr_get_tcpActualPose(robotHandle, pose);  //读实际TCP位置
			pose[2] = pose[2] - 150;                           //Z方向向下运动150mm
			if (result == sucess)
			{
				pointControlPara.coordinateType = baseCoordinate;
				for (int index = 0; index < ROB_AXIS_NUM; index++)
				{
					pointControlPara.pose[index] = pose[index];
					pointControlPara.jointpos[index] = jointpos[index];
				}
				result = cr_moveL(robotHandle, pointControlPara);  //直线运动
				if (result == sucess)
				{
					Sleep(50);
					while (result == sucess)
					{
						result = cr_get_robotMoveStatus(robotHandle, &isRobotMoving);  //读机械臂运动状态,如果运动已经停止，代表上一次运动已经结束，则跳出循环进行下一次运动
						if (!isRobotMoving)
						{
							break;
						}
					}
					pose[2] = pose[2] + 150;
					PointControlParaSimple  pointControlParaSimple;
					for (int index = 0; index < ROB_AXIS_NUM; index++)
					{
						pointControlParaSimple.pose[index] = pose[index];
						pointControlParaSimple.jointpos[index] = jointpos[index];
						pointControlParaSimple.tcpOffset[index] = 0;
						pointControlParaSimple.coordinatePose[index] = 0;
						pointControlParaSimple.speed[index] = 30;
						pointControlParaSimple.acc[index] = 30;
					}
					pointControlParaSimple.coordinateType = baseCoordinate;
					pointControlParaSimple.pointTransType = pointTransStop;
					pointControlParaSimple.motiontriggerMode = MovetriggerbyOnlyRpc;
					result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple, &pointControlPara);  //PointControlParaSimple数据转换为PointControlPara
					result = cr_move_line(robotHandle, pointControlPara, TRUE);  //阻塞式的直线运动，由于是阻塞的直线运动，则运动会在运动到位后在进行后续的程序运行，因此不用像之前做判断
					if (result == sucess)
					{
						double jointpos2[6] = { 90, 0, 90, 0, -90, 0 };
						pointControlParaSimple.coordinateType = jointCoordinate;
						for (int index = 0; index < ROB_AXIS_NUM; index++)
						{
							pointControlParaSimple.pose[index] = pose[index];
							pointControlParaSimple.jointpos[index] = jointpos2[index];
						}
						result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple, &pointControlPara);  //PointControlParaSimple数据转换为PointControlPara
						result = cr_move_joint(robotHandle, pointControlPara, TRUE);  //阻塞式的轴空间运动，由于是阻塞的轴空间运动，则运动会在运动到位后在进行后续的程序运行，因此不用像之前做判断
						if (result == sucess)
						{
							pointControlPara.coordinateType = baseCoordinate;
							result = cr_get_tcpActualPose(robotHandle, pose);  //读实际TCP位置
							pose[2] = pose[2] - 150;
							for (int index = 0; index < ROB_AXIS_NUM; index++)
							{
								pointControlParaSimple.pose[index] = pose[index];
								pointControlParaSimple.jointpos[index] = jointpos2[index];
							}
							result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple, &pointControlPara);  //PointControlParaSimple数据转换为PointControlPara
							result = cr_moveL(robotHandle, pointControlPara);  //直线运动
							if (result == sucess)
							{
								Sleep(50);
								while (result == sucess)
								{
									result = cr_get_robotMoveStatus(robotHandle, &isRobotMoving);  //读机械臂运动状态,如果运动已经停止，代表上一次运动已经结束，则跳出循环进行下一次运动
									if (!isRobotMoving)
									{
										break;
									}
								}
								pose[2] = pose[2] + 150;
								for (int index = 0; index < ROB_AXIS_NUM; index++)
								{
									pointControlParaSimple.pose[index] = pose[index];
									pointControlParaSimple.jointpos[index] = jointpos2[index];
								}
								result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple, &pointControlPara);  //PointControlParaSimple数据转换为PointControlPara
								result = cr_move_line(robotHandle, pointControlPara, FALSE);  //非阻塞式直线运动，下发运动后会马上执行下一条指令
								if (result == sucess)
								{
									printf("%d:%s\n", __LINE__, "运动已完成");
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