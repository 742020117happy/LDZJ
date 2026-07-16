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
		pointControlParaSimple.coordinateType = jointCoordinate;
		pointControlParaSimple.pointTransType = pointTransStop;
		pointControlParaSimple.motiontriggerMode = MovetriggerbyOnlyRpc;
		PointControlPara  pointControlPara;
		result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple, &pointControlPara);  //PointControlParaSimple数据转换为PointControlPara
		result = cr_move_joint(robotHandle, pointControlPara, TRUE);  //轴空间运动
		RecordPathPara recordPathPara;
		recordPathPara.sampleTime = 2;
		recordPathPara.recordControl = 1;
		result = cr_path_recordPara_set(robotHandle, recordPathPara);  //设置轨迹记录参数，开启轨迹记录
		Sleep(500);
		double jointpos2[6] = { 90, 0, 90, 0, -90, 0 };  //目标点示例数据
		for (int index = 0; index < ROB_AXIS_NUM; index++)
		{
			pointControlParaSimple.jointpos[index] = jointpos2[index];
		}
		result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple, &pointControlPara);  //PointControlParaSimple数据转换为PointControlPara		
		if (result == sucess)
		{
			result = cr_move_joint(robotHandle, pointControlPara, TRUE);  //阻塞式轴空间运动
			if (result == sucess)
			{
				recordPathPara.recordControl = 0;
				result = cr_path_recordPara_set(robotHandle, recordPathPara);  //设置轨迹记录参数，结束轨迹记录
				if (result == sucess)
				{
					int index = -1;
					PathData pathData;
					pathData.pathPoints = new PathPoint[10000];
					result = cr_path_upload(robotHandle, index, &pathData);
					if (result == sucess)
					{
						int allPathIndex[11];
						int pathIndexLen;
						result = cr_path_all_index_get(robotHandle, allPathIndex, &pathIndexLen);
						//读取控制柜当前存在的轨迹索引
						for (int i = 0; i < pathIndexLen; i++)
						{
							if (allPathIndex[i] == 2)  //将下载的轨迹索引设置为2，故需要判断其是否已经存在
							{
								printf("%d:%s\n", __LINE__, "存在轨迹索引为2的轨迹");
								PathDownloadData pathDownloadData;
								pathDownloadData.pathData = pathData;
								pathDownloadData.pathPara.index = 2;
								pathDownloadData.pathPara.moveType = 1;
								result = cr_path_download(robotHandle, pathDownloadData);  //下载轨迹到索引2
								if (result == sucess)
								{
									printf("%d:%s\n", __LINE__, "已成功下载索引为2的轨迹");
								}
								else
								{
									printf("%d:%d\n", __LINE__, result);
								}
								break;
							}
							if (i == (pathIndexLen - 1))
							{
								PathDownloadData pathDownloadData;
								pathDownloadData.pathData = pathData;
								pathDownloadData.pathPara.index = 2;
								pathDownloadData.pathPara.moveType = 1;
								result = cr_path_download(robotHandle, pathDownloadData);  //下载轨迹到索引2
								if (result == sucess)
								{
									printf("%d:%s\n", __LINE__, "已成功下载索引为2的轨迹");
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



