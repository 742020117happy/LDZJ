#include <QCoreApplication>
#include <iostream>
#include "robotapi.h"
#include "basestruct.h"
#include<assert.h>
using namespace std;
RobotHandle robotHandle;

///机器人关机
void api_demo_cr_shutdown()
{
    CRresult result = cr_shutdown(robotHandle);
    assert(result == sucess);
}

///机械臂上电
void api_demo_cr_poweron()
{
    CRresult result = cr_poweron(robotHandle);
    assert(result == sucess);
}

///机械臂断电
void api_demo_cr_poweroff()
{
    CRresult result = cr_poweroff(robotHandle);
    assert(result == sucess);
}

///机械臂使能
void api_demo_cr_enable()
{
    CRresult result = cr_enable(robotHandle);
    assert(result == sucess);
}

///机械臂关使能
void api_demo_cr_disable()
{
    CRresult result = cr_disable(robotHandle);
    assert(result == sucess);
}

///机械臂故障复位
void api_demo_cr_FaultReset()
{
    CRresult result = cr_FaultReset(robotHandle);
    assert(result == sucess);
}

///获取控制柜状态
void api_demo_cr_get_controlMode()
{
    int controlmode;
    CRresult result = cr_get_controlMode(robotHandle, &controlmode);
    assert(result == sucess);
    printf("%d\n", controlmode); //控制柜状态：0-自动，1-手动
}

///写机械臂速度百分比
void api_demo_cr_set_robotSpeedPercent()
{
    unsigned int speedpercent = 50; //写机械臂速度百分比为50
    CRresult result = cr_set_robotSpeedPercent(robotHandle, speedpercent);
    assert(result == sucess);
    printf("%d\n", speedpercent);
}

///读机械臂速度百分比
void api_demo_cr_get_robotSpeedPercent()
{
    unsigned int speedpercent = 0;
    CRresult result = cr_get_robotSpeedPercent(robotHandle, &speedpercent);
    assert(result == sucess);
    printf("%u\n", speedpercent);
}

///获取SDK版本号
void api_demo_cr_get_sdk_version()
{
    char version[20];
    CRresult result = cr_get_sdk_version(version);
    assert(result == sucess);
    printf("%s", version);
}

///获取机械臂状态数据
void api_demo_cr_get_robotStateData()
{
    RobotStateData robotStateData;
    CRresult result = cr_get_robotStateData(robotHandle, &robotStateData);
    assert(result == sucess);
    printf("实际tcp位置：");
    for (int i = 0; i < 6; i++)
    {
        printf("%f", robotStateData.tcpActualPose[i]);
        if (i < 5)
            printf(",");
    }
    printf("\n");

    printf("实际关节位置：");
    for (int i = 0; i < 6; i++)
    {
        printf("%f", robotStateData.jointActualPos[i]);
        if (i < 5)
            printf(",");
    }
    printf("\n");

    printf("机械臂当前状态：%d\n", robotStateData.robotMode);
    printf("机械臂运动状态：%d\n", robotStateData.robotMoveStatus);
    printf("机械臂速度百分比：%d\n", robotStateData.robotSpeedPercent);

    printf("控制器可配置数字输出：");
    for (int i = 0; i < 8; i++)
    {
        printf("%d", robotStateData.configurableDigitalOutput[i]);
        if (i < 7)
            printf(",");
    }
    printf("\n");
}

///加载程序
void api_demo_cr_downloadProgram()
{
    const char  *programfile = "function mainfuncprogram()\n"
        "--start robotconfig\n"
        "tcp_1 = { 0,0,0,0,0,0 }\n"
        "payload_1= { 0,{0,0,0} }\n"
        "set_tcp_payload(payload_1[1], payload_1[2])\n"
        "--end robotconfig\n"
        "function robotprogram()\n"
        "while (true)\n"
        "do\n"
        "--output: cdo_0 = true\n"
        "set_standard_digital_out(0, true)\n"
        "wait(1)  --sync\n"
        "end\n"
        "end\n"
        "robotprogram_result = task_create(robotprogram)\n"
        "function pausefuncprogram()\n"
        "while (true)\n"
        "do\n"
        "wait(100)  --sync\n"
        "end\n"
        "end\n"
        "pausefuncprogram_result = task_create(pausefuncprogram)\n"
        "end\n"
        "mainfuncprogram_result = task_create(mainfuncprogram)";
    CRresult result = cr_downloadProgram(robotHandle, programfile);
    //程序功能是将DO_0置为true
    assert(result == sucess);
}

///加载程序（加密）
void api_demo_cr_downloadProgram_encryption()
{
    const char  *programfile = "function mainfuncprogram()\n"
        "--start robotconfig\n"
        "tcp_1 = { 0,0,0,0,0,0 }\n"
        "payload_1= { 0,{0,0,0} }\n"
        "set_tcp_payload(payload_1[1], payload_1[2])\n"
        "--end robotconfig\n"
        "function robotprogram()\n"
        "while (true)\n"
        "do\n"
        "--output: cdo_0 = true\n"
        "set_standard_digital_out(0, true)\n"
        "wait(1)  --sync\n"
        "end\n"
        "end\n"
        "robotprogram_result = task_create(robotprogram)\n"
        "function pausefuncprogram()\n"
        "while (true)\n"
        "do\n"
        "wait(100)  --sync\n"
        "end\n"
        "end\n"
        "pausefuncprogram_result = task_create(pausefuncprogram)\n"
        "end\n"
        "mainfuncprogram_result = task_create(mainfuncprogram)";
    CRresult result = cr_downloadProgram_encryption(robotHandle, programfile);
    assert(result == sucess);
    //程序功能是将DO_0置为true
}

///上传程序
void api_demo_cr_uploadProgram()
{
    char *programfile = new char[1024 * 75 * 10];
    CRresult result = cr_uploadProgram(robotHandle, programfile);
    assert(result == sucess);
    for (int i = 0; i < 100; i++)
    {
        cout << programfile[i];
    }
}

///运行程序
void api_demo_cr_play()
{
    CRresult result = cr_play(robotHandle);
    assert(result == sucess);
}

///停止程序运行
void api_demo_cr_stop()
{
    CRresult result = cr_stop(robotHandle);
    assert(result == sucess);
}

///暂停程序运行
void api_demo_cr_pause()
{
    CRresult result = cr_pause(robotHandle);
    assert(result == sucess);
}

///读取脚本当前运行行号
void api_demo_cr_script_current_line_get()
{
    int currentline[50];
    int linelen = 0;
    CRresult result = cr_script_current_line_get(robotHandle, currentline, &linelen);
    assert(result == sucess);
    printf("%d\n", currentline[0]);
    printf("%d\n", linelen);
}

///读脚本运行状态
void api_demo_cr_get_lua_scriptstatus()
{
    Lua_ScriptStatus scriptstatus;
    CRresult result = cr_get_lua_scriptstatus(robotHandle, &scriptstatus);
    assert(result == sucess);
    printf("%d\n", scriptstatus);
}

///工程文件上传
void api_demo_cr_uploadProject()
{
    char FilePath[100] = "../";
    char filename[100] = "test";
    CRresult result = cr_uploadProject(robotHandle, FilePath, filename);
    assert(result == sucess);
}

///工程文件下载
void api_demo_cr_downloadProject()
{
    char crpfilepathname[100] = "../test.crp";
    char crscriptfilepathname[100] = "../test.crscript";
    CRresult result = cr_downloadProject(robotHandle, crpfilepathname, crscriptfilepathname);
    assert(result == sucess);
}

///是否存在弹窗
void api_demo_cr_script_popup_exist()
{
    BOOL hasPopup;
    CRresult result = cr_script_popup_exist(robotHandle, &hasPopup);
	assert(result == sucess);
    printf("%d", hasPopup);
}

///读取弹窗信息
void api_demo_cr_script_popup_msg_get()
{
    PopUpMsg popupMsg;
    CRresult result = cr_script_popup_msg_get(robotHandle, &popupMsg);
	assert(result == sucess);
	#ifdef _WIN32
		system("chcp 65001");
	#elif __linux__
		system("export LANG=C.UTF-8");
	#endif
    printf("%d", popupMsg.popupType);
}

///设置输入弹窗信息
void api_demo_cr_script_popup_msg_set()
{
    VariableMsg invarMsg;
    char name[CR6_ISTALL_VAR_NAME_LENGTH] = { "install" };
    strcpy(invarMsg.variableName, name);
    invarMsg.variableType = LUA_TNUMBER;
    invarMsg.variableID = 3;
    invarMsg.numberValue = 5;
    CRresult result = cr_script_popup_msg_set(robotHandle, &invarMsg);
    assert(result == sucess);
}

///关闭弹窗
void api_demo_cr_script_popup_close()
{
    CRresult result = cr_script_popup_close(robotHandle);
    assert(result == sucess);
}

///轴空间运动
void api_demo_cr_moveJ()
{
    double jointpos[6] = { 60, 60, -60, 60, 60, 60 }; //目标点示例数据
    double pose[6] = { 0, 0, 0, 0, 0, 0 }; //在MoveJ中无影响
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
    CRresult result = cr_moveJ(robotHandle, pointControlPara);
    assert(result == sucess);
}

///轴空间运动
void api_demo_cr_move_joint()
{
    double jointpos[6] = { 60, 60, -60, 60, 60, 60 }; //目标点示例数据
    double pose[6] = { 0, 0, 0, 0, 0, 0 }; //在MoveJ中无影响
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
    CRresult result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple, &pointControlPara);
    assert(result == sucess);
    result = cr_move_joint(robotHandle, pointControlPara, TRUE);
    assert(result == sucess);
}

///直线运动
void api_demo_cr_moveL()
{
    double jointpos[6] = { 60, 60, -60, 60, 60, 60 }; //起始点示例数据
    double pose[6] = { 0, -438, 887, -57.34, 0, -149 }; //目标点示例数据
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
    pointControlPara.coordinateType = baseCoordinate;
    pointControlPara.pointTransType = pointTransStop;
    pointControlPara.pointTransRadius = 0;
    pointControlPara.poseTranType = poseTranMoveToTargetPose;
    pointControlPara.motiontriggerMode = MovetriggerbyOnlyRpc;
    CRresult result = cr_moveL(robotHandle, pointControlPara);//直线运动
    assert(result == sucess);
}

///直线运动
void api_demo_cr_move_line()
{
    double jointpos[6] = { 60, 60, -60, 60, 60, 60 }; //起始点示例数据
    double pose[6] = { 0, -438, 887, -57.34, 0, -149 }; //目标点示例数据
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
    PointControlPara  pointControlPara;
    CRresult result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple, &pointControlPara);
    assert(result == sucess);
    result = cr_move_line(robotHandle, pointControlPara, TRUE);
    assert(result == sucess);
}

///点动运动
void api_demo_cr_moveJog()
{
	double pose[6] = { 0, 5, 0, 0, 0, 0 };  //沿坐标系y轴运动5mm
	double pointSysPose[6] = { 114.3,-390.498,215.347,-180,0,0 }; //点坐标系
	PointControlPara  pointControlPara;
	for (int index = 0; index < ROB_AXIS_NUM; index++)
	{
		pointControlPara.pose[index] = pose[index];
		pointControlPara.jointpos[index] = 0;
		pointControlPara.tcpOffset[index] = 0;
		pointControlPara.coordinatePose[index] = pointSysPose[index];
		pointControlPara.speed[index] = 30;
		pointControlPara.acc[index] = 30;
		pointControlPara.jerk[index] = 60;
	}
	pointControlPara.tcpID = -1;
	pointControlPara.coordinateType = PointCoordinate;  //基于点坐标系进行点动
	pointControlPara.pointTransType = pointTransStop;
	pointControlPara.pointTransRadius = 0;
	pointControlPara.poseTranType = poseTranMoveToTargetPose;
	pointControlPara.motiontriggerMode = MovetriggerbyOnlyRpc;
    CRresult result = cr_moveJog(robotHandle, pointControlPara);
    assert(result == sucess);
}

///圆弧运动
void api_demo_cr_move_circle()
{
    double jointpos0[6] = { 60, 60, -60, 60, 60, 60 }; //目标点示例数据
    double pose0[6] = { 0, 0, 0, 0, 0, 0 }; //在MoveJ中无影响
    PointControlParaSimple  pointControlParaSimple0;
    for (int index = 0; index < ROB_AXIS_NUM; index++)
    {
        pointControlParaSimple0.pose[index] = pose0[index];
        pointControlParaSimple0.jointpos[index] = jointpos0[index];
        pointControlParaSimple0.tcpOffset[index] = 0;
        pointControlParaSimple0.coordinatePose[index] = 0;
        pointControlParaSimple0.speed[index] = 30;
        pointControlParaSimple0.acc[index] = 30;
    }
    pointControlParaSimple0.coordinateType = jointCoordinate;
    pointControlParaSimple0.pointTransType = pointTransStop;
    pointControlParaSimple0.motiontriggerMode = MovetriggerbyOnlyRpc;
    PointControlPara  pointControlPara0;
    CRresult result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple0, &pointControlPara0);
    assert(result == sucess);
    result = cr_move_joint(robotHandle, pointControlPara0, TRUE); //移至初始点
    assert(result == sucess);

    double jointpos1[6] = { 60, 55, -65, 60, 60, 60 }; //中间点关节角
    double pose1[6]; //中间点位姿
    cr_kineForward(robotHandle, jointpos1, pose1);
    double jointpos2[6] = { 60, 50, -70, 60, 60, 60 };//终点关节角
    double pose2[6]; //终点位姿
    cr_kineForward(robotHandle, jointpos2, pose2);
    PointControlParaSimple  pointControlParaSimple1;
    PointControlParaSimple  pointControlParaSimple2;
    for (int index = 0; index < ROB_AXIS_NUM; index++)
    {
        pointControlParaSimple1.pose[index] = pose1[index];
        pointControlParaSimple1.jointpos[index] = jointpos1[index];
        pointControlParaSimple1.tcpOffset[index] = 0;
        pointControlParaSimple1.coordinatePose[index] = 0;
        pointControlParaSimple1.speed[index] = 30;
        pointControlParaSimple1.acc[index] = 30;
        pointControlParaSimple2.pose[index] = pose2[index];
        pointControlParaSimple2.jointpos[index] = jointpos2[index];
        pointControlParaSimple2.tcpOffset[index] = 0;
        pointControlParaSimple2.coordinatePose[index] = 0;
        pointControlParaSimple2.speed[index] = 30;
        pointControlParaSimple2.acc[index] = 30;
    }
    pointControlParaSimple1.coordinateType = baseCoordinate;
    pointControlParaSimple1.pointTransType = pointTransStop;
    pointControlParaSimple1.motiontriggerMode = MovetriggerbyOnlyRpc;
    pointControlParaSimple2.coordinateType = baseCoordinate;
    pointControlParaSimple2.pointTransType = pointTransStop;
    pointControlParaSimple2.motiontriggerMode = MovetriggerbyOnlyRpc;
    PointControlPara  pointControlPara1;
    PointControlPara  pointControlPara2;
    result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple1, &pointControlPara1);
    assert(result == sucess);
    result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple2, &pointControlPara2);
    assert(result == sucess);
    PointControlParaList pointControlParaList;
    pointControlParaList.pointcontrolpara[0] = pointControlPara1;
    pointControlParaList.pointcontrolpara[1] = pointControlPara2;
    pointControlParaList.fixedrot = 0;
    pointControlParaList.centralangle = 0;
    result = cr_move_circle(robotHandle, pointControlParaList, TRUE);
    assert(result == sucess);
}

///运动控制
void api_demo_cr_moveControl()
{
    MoveType moveType = ImdStop; //立即停止
    CRresult result = cr_moveControl(robotHandle, moveType);
    assert(result == sucess);
}

///设置阻塞移动中参数阈值
void api_demo_cr_move_block_threshold_set()
{
    CRresult result = cr_move_block_threshold_set(robotHandle, 0.05, 0.05);
    //将阻塞移动中的位姿阈值设置为0.05，关节阈值设置为0.05
    assert(result == sucess);
}

///PointControlParaSimple数据转换
void api_demo_cr_move_pointControlPara_transfer()
{
    double jointpos[6] = { 60, 60, -60, 60, 60, 60 }; //目标点示例数据
    double pose[6] = { 0, 0, 0, 0, 0, 0 }; //在MoveJ中无影响
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
    CRresult result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple, &pointControlPara);
    assert(result == sucess);
}

///设置软件自由驱动启动
void api_demo_cr_set_softFreeDriveEnabled()
{
    BOOL softFreeDriveEnabled = TRUE; //进入拖拽模式
    CRresult result = cr_set_softFreeDriveEnabled(robotHandle, softFreeDriveEnabled);
    assert(result == sucess);
}

///读机械臂运动状态
void api_demo_cr_get_robotMoveStatus()
{
    BOOL isRobotMoving;
    CRresult result = cr_get_robotMoveStatus(robotHandle, &isRobotMoving);
    assert(result == sucess);
    printf("%d\n", isRobotMoving); ///机械臂当前是否运动：0-停止，1-运动
}

///读取移动缓存区中移动指令的数量
void api_demo_cr_move_cache_num_get()
{
    int cacheNum;
    CRresult result = cr_move_cache_num_get(robotHandle, &cacheNum);
    assert(result == sucess);
    printf("%d\n", cacheNum);
}

///读实际TCP位置
void api_demo_cr_get_tcpActualPose()
{
    double actual_pose[ROB_AXIS_NUM];
    CRresult result = cr_get_tcpActualPose(robotHandle, actual_pose);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", actual_pose[i]);
    }
}

///读目标TCP位置
void api_demo_cr_get_tcpTargetPose()
{
    double target_pose[ROB_AXIS_NUM];
    CRresult result = cr_get_tcpTargetPose(robotHandle, target_pose);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", target_pose[i]);
    }
}

///读实际TCP速度
void api_demo_cr_get_tcpActualSpeed()
{
    double speed[ROB_AXIS_NUM];
    CRresult result = cr_get_tcpActualSpeed(robotHandle, speed);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", speed[i]);
    }
}

///读目标TCP速度
void api_demo_cr_get_tcpTargetSpeed()
{
    double speed[ROB_AXIS_NUM];
    CRresult result = cr_get_tcpTargetSpeed(robotHandle, speed);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", speed[i]);
    }
}

///读实际TCP加速度
void api_demo_cr_get_tcpActualAcceleration()
{
    double acceleration[ROB_AXIS_NUM];
    CRresult result = cr_get_tcpActualAcceleration(robotHandle, acceleration);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", acceleration[i]);
    }
}

///读当前使用的TCP偏移信息
void api_demo_cr_get_currentTCPmsg()
{
    TCPMsg tcpMsgList;
    CRresult result = cr_get_currentTCPmsg(robotHandle, &tcpMsgList);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", tcpMsgList.tcpOffset[i]);
    }
    printf("%s\n", tcpMsgList.tcpName);
}

///读取当前使用负载信息
void api_demo_cr_get_currentPayloadmsg()
{
    PayLoad payloadMsg;
    CRresult result = cr_get_currentPayloadmsg(robotHandle, &payloadMsg);
    assert(result == sucess);
    printf("%f\n", payloadMsg.toolPayload);
    for (int i = 0; i < 3; i++)
    {
        printf("%f\n", payloadMsg.centerOfGravity[i]);
    }
    printf("%s\n", payloadMsg.payloadName);
}

///读所有TCP偏移信息列表
void api_demo_cr_get_allTCPmsg()
{
    int validNumber;
    TCPMsg tcpMsgList[20];
    CRresult result = cr_get_allTCPmsg(robotHandle, tcpMsgList, &validNumber);
    assert(result == sucess);
    for (int j = 0; j < validNumber; j++)
    {
        for (int i = 0; i < ROB_AXIS_NUM; i++)
        {
            printf("%f\n", tcpMsgList[j].tcpOffset[i]);
        }
        printf("%s\n", tcpMsgList[j].tcpName);
    }
}

///读取所有负载信息
void api_demo_cr_get_allPayloadmsg()
{
    int validNumber;
    PayLoad payloadMsg[20];
    CRresult result = cr_get_allPayloadmsg(robotHandle, payloadMsg, &validNumber);
    assert(result == sucess);
    for (int j = 0; j < validNumber; j++)
    {
        printf("%f\n", payloadMsg[j].toolPayload);
        for (int i = 0; i < 3; i++)
        {
            printf("%f\n", payloadMsg[j].centerOfGravity[i]);
        }
        printf("%s\n", payloadMsg[j].payloadName);
    }
}

///获取指定TCPoffset的位姿
void api_demo_cr_get_AssignTCP_Pose()
{
    double dstTCPoffset[ROB_AXIS_NUM] = { 10, 20, 30, 60, 60, 60 };
    double dstPose[ROB_AXIS_NUM];
    CRresult result = cr_get_AssignTCP_Pose(robotHandle, dstTCPoffset, dstPose);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", dstPose[i]);
    }
}

///读实际关节位置
void api_demo_cr_get_jointActualPos()
{
    double actual_joint_pos[ROB_AXIS_NUM];
    CRresult result = cr_get_jointActualPos(robotHandle, actual_joint_pos);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", actual_joint_pos[i]);
    }
    assert(result == sucess);
}

///读目标关节位置
void api_demo_cr_get_jointTargetPos()
{
    double target_joint_pos[ROB_AXIS_NUM];
    CRresult result = cr_get_jointTargetPos(robotHandle, target_joint_pos);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", target_joint_pos[i]);
    }
}

///读实际关节速度
void api_demo_cr_get_jointActualVelocity()
{
    double velocity[ROB_AXIS_NUM];
    CRresult result = cr_get_jointActualVelocity(robotHandle, velocity);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", velocity[i]);
    }
}

///读目标关节速度
void api_demo_cr_get_jointTargetVelocity()
{
    double velocity[ROB_AXIS_NUM];
    CRresult result = cr_get_jointTargetVelocity(robotHandle, velocity);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", velocity[i]);
    }
}

///读实际关节加速度
void api_demo_cr_get_jointActualAcceleration()
{
    double acceleration[ROB_AXIS_NUM];
    CRresult result = cr_get_jointActualAcceleration(robotHandle, acceleration);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", acceleration[i]);
    }
}

///读目标关节加速度
void api_demo_cr_get_jointTargetAcceleration()
{
    double acceleration[ROB_AXIS_NUM];
    CRresult result = cr_get_jointTargetAcceleration(robotHandle, acceleration);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", acceleration[i]);
    }
}

///读实际关节电机电流
void api_demo_cr_get_jointActualCurrent()
{
    double current[ROB_AXIS_NUM];
    CRresult result = cr_get_jointActualCurrent(robotHandle, current);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", current[i]);
    }
}

///读目标关节电机电流
void api_demo_cr_get_jointTargetCurrent()
{
    double current[ROB_AXIS_NUM];
    CRresult result = cr_get_jointTargetCurrent(robotHandle, current);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", current[i]);
    }
}

///读目标关节转矩
void api_demo_cr_get_jointTargetTorque()
{
    double torque[ROB_AXIS_NUM];
    CRresult result = cr_get_jointTargetTorque(robotHandle, torque);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", torque[i]);
    }
}

///读实际关节采集的母线电压
void api_demo_cr_get_jointActualVoltage()
{
    double voltage[ROB_AXIS_NUM];
    CRresult result = cr_get_jointActualVoltage(robotHandle, voltage);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", voltage[i]);
    }
}

///读关节温度
void api_demo_cr_get_jointTemperature()
{
    double temperature[ROB_AXIS_NUM];
    CRresult result = cr_get_jointTemperature(robotHandle, temperature);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", temperature[i]);
    }
}

///读关节模式
void api_demo_cr_get_jointMode()
{
    enum JointModes jointMode[ROB_AXIS_NUM];
    CRresult result = cr_get_jointMode(robotHandle, jointMode);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%d\n", jointMode[i]);
    }
}

///读取控制柜当前存在的轨迹索引
void api_demo_api_demo_cr_path_all_index_get()
{
	int allPathIndex[11];
	int pathIndexLen;
	CRresult result = cr_path_all_index_get(robotHandle, allPathIndex, &pathIndexLen);
	assert(result == sucess);
	for (int i = 0; i < pathIndexLen; i++)
	{
		printf("%d\n", allPathIndex[i]);
	}
}

///上传轨迹
void api_demo_cr_path_upload()
{
	int index = 1;
	PathData pathData;
	pathData.pathPoints = new PathPoint[10000];
	CRresult result = cr_path_upload(robotHandle, index, &pathData);
	//上传索引为1的轨迹，使用前需判断索引为1的轨迹是否存在
	assert(result == sucess);
	printf("%f\n", pathData.pathPoints[0].jointpos[0]);
	printf("%d\n", pathData.pathPointsNum);
	delete[] pathData.pathPoints;  //内存释放
}

///下载轨迹
void api_demo_cr_path_download()
{
    char filePath[100] = "../path.crpath";
	PathData pathData;
	pathData.pathPoints = new PathPoint[10000];
	CRresult result = cr_path_file2pathData(filePath, &pathData);  //轨迹文件转换为轨迹数据
	assert(result == sucess);
	PathDownloadData pathDownloadData;
	pathDownloadData.pathData = pathData;
	pathDownloadData.pathPara.index = 2;
	pathDownloadData.pathPara.moveType = 1;
	result = cr_path_download(robotHandle, pathDownloadData);  //下载轨迹到索引1
	delete[] pathData.pathPoints;  //内存释放
	assert(result == sucess);

}

///轨迹控制
void api_demo_cr_path_action()
{
	int index = 1;
	PathData pathData;
	pathData.pathPoints = new PathPoint[10000];
	CRresult result = cr_path_upload(robotHandle, index, &pathData);
	//上传索引为1的轨迹，使用前需判断索引为1的轨迹是否存在

	PointControlParaSimple  pointControlParaSimple;
	for (int i = 0; i < ROB_AXIS_NUM; i++)
	{
		pointControlParaSimple.pose[i] = pathData.pathPoints[0].pose[i];
		pointControlParaSimple.jointpos[i] = pathData.pathPoints[0].jointpos[i];
		pointControlParaSimple.tcpOffset[i] = 0;
		pointControlParaSimple.coordinatePose[i] = 0;
		pointControlParaSimple.speed[i] = 30;
		pointControlParaSimple.acc[i] = 30;
	}
	pointControlParaSimple.coordinateType = jointCoordinate;
	pointControlParaSimple.pointTransType = pointTransStop;
	pointControlParaSimple.motiontriggerMode = MovetriggerbyOnlyRpc;
	PointControlPara  pointControlPara;
	result = cr_move_pointControlPara_transfer(robotHandle, pointControlParaSimple, &pointControlPara);
	// pointControlParaSimple转化为pointControlPara
	assert(result == sucess);
	result = cr_move_joint(robotHandle, pointControlPara, TRUE);  //移动至第一个点位
	assert(result == sucess);
	result = cr_path_action(robotHandle, index, 1);
	//启动轨迹索引为1的轨迹，使用前需判断索引为1的轨迹是否存在
	assert(result == sucess);
	delete[] pathData.pathPoints;  //释放内存
}

///轨迹数据转换为轨迹文件
void api_demo_cr_path_pathData2file()
{
    char filePath[100] = "../newpath.crpath";
	PathData pathData;
	pathData.pathPoints = new PathPoint[10000];
	CRresult result = cr_path_upload(robotHandle, 1, &pathData);
	//上传索引为1的轨迹，使用前需判断索引为1的轨迹是否存在
	assert(result == sucess);
	result = cr_path_pathData2file(pathData, filePath);  //轨迹数据转换为轨迹文件
	assert(result == sucess);
	delete[] pathData.pathPoints;  //内存释放
}

///轨迹文件转换为轨迹数据
void api_demo_cr_path_file2pathDatae()
{
    char filePath[100] = "../path.crpath";
	PathData pathData;
	pathData.pathPoints = new PathPoint[10000];
	CRresult result = cr_path_file2pathData(filePath, &pathData);
	assert(result == sucess);
	printf("%d\n", pathData.pathPointsNum);
	delete[] pathData.pathPoints;
}

///设置轨迹记录参数
void api_demo_cr_path_recordPara_set()
{
	RecordPathPara recordPathPara;
	recordPathPara.sampleTime = 2;
	recordPathPara.recordControl = 1;
	CRresult result = cr_path_recordPara_set(robotHandle, recordPathPara);
	assert(result == sucess);
}

///获取当前轨迹记录状态
void api_demo_cr_path_recordStatus_get()
{
	PathRecordStatus pathRecordStatus;
	CRresult result = cr_path_recordStatus_get(robotHandle, &pathRecordStatus);
	assert(result == sucess);
	printf("%d\n", pathRecordStatus.recordStatus);
	printf("%d\n", pathRecordStatus.waypointNumber);
}

///获取当前轨迹运行状态
void api_demo_cr_path_currentRunStatus_get()
{
	PathRunMsg pathRunMsg;
	CRresult result = cr_path_currentRunStatus_get(robotHandle, &pathRunMsg);  //获取当前轨迹运行状态
	assert(result == sucess);
	printf("%d\n", pathRunMsg.pathrunstatus);
	printf("%d\n", pathRunMsg.pointIndex);
}

///读取控制器硬件序列号
void api_demo_cr_get_productInfo()
{
    char productSn[24];
    CRresult result = cr_get_productInfo(robotHandle, productSn);
    assert(result == sucess);
    printf("%s\n", productSn);
}

///读取整臂序列号
void api_demo_cr_get_productSn()
{
    char Sn[24];
    CRresult result = cr_get_productSn(robotHandle, Sn);
    assert(result == sucess);
    printf("%s\n", Sn);
}

///获取版本信息
void api_demo_cr_get_sysVersion()
{
    SysVersion version;
    CRresult result = cr_get_sysVersion(robotHandle, &version);
    assert(result == sucess);
    printf("%s\n", version.kzqVersion.hardwareID);
}

///读机械臂DH参数
void api_demo_cr_get_DhParmeter()
{
    double dhPara[DH_PARA_MAX_NUM];
    CRresult result = cr_get_DhParmeter(robotHandle, dhPara);
    assert(result == sucess);
    for (int i = 0; i < DH_PARA_MAX_NUM; i++)
    {
        printf("%f\n", dhPara[i]);
    }
}

///读机械臂标准DH参数
void api_demo_cr_get_stdDhParmeter()
{
    double dhPara[DH_PARA_MAX_NUM];
    CRresult result = cr_get_stdDhParmeter(robotHandle, dhPara);
    assert(result == sucess);
    for (int i = 0; i < DH_PARA_MAX_NUM; i++)
    {
        printf("%f\n", dhPara[i]);
    }
}

///读机械臂动力学参数
void api_demo_cr_get_DynamicParmeter()
{
    double dynamicPara[DY_PARA_MAX_NUM];
    CRresult result = cr_get_DynamicParmeter(robotHandle, dynamicPara);
    assert(result == sucess);
    for (int i = 0; i < DH_PARA_MAX_NUM; i++)
    {
        printf("%f\n", dynamicPara[i]);
    }
}

///读机械臂零位补偿值
void api_demo_cr_get_zeroCompensationOffset()
{
    double zeroCompensationOffset[ROB_AXIS_NUM];
    CRresult result = cr_get_zeroCompensationOffset(robotHandle, zeroCompensationOffset);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", zeroCompensationOffset[i]);
    }
}

///读机械臂减速比
void api_demo_cr_get_reducerRatio()
{
    double reducerRatio[ROB_AXIS_NUM];
    CRresult result = cr_get_reducerRatio(robotHandle, reducerRatio);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", reducerRatio[i]);
    }
}

///读机械臂当前状态
void api_demo_cr_get_robotMode()
{
    enum RobotModes robotMode;
    CRresult result = cr_get_robotMode(robotHandle, &robotMode);
    assert(result == sucess);
    printf("%d\n", robotMode);
}

///获取机械臂日志
void api_demo_cr_get_logMsgs()
{
    RobotLogMsg *logMsgs = new RobotLogMsg[10];
    int logMsgNumber;
    CRresult result = cr_get_logMsgs(robotHandle, logMsgs, &logMsgNumber);
    assert(result == sucess);
	#ifdef _WIN32
		system("chcp 65001");
	#elif __linux__
		system("export LANG=C.UTF-8");
	#endif
	if (logMsgNumber>0)
	{
		printf("%d\n", logMsgs[0].warningLevel);
		printf("%s\n", logMsgs[0].textMessage);
		printf("%d\n", logMsgNumber);
	}
}

///获取机械臂历史所有日志
void api_demo_cr_sys_history_log_get()
{
    int logMsgNumber;
    RobotLogMsg *logMsgs = new RobotLogMsg[3000];
    CRresult result = cr_sys_history_log_get(robotHandle, logMsgs, &logMsgNumber);
    assert(result == sucess);
	#ifdef _WIN32
		system("chcp 65001");
	#elif __linux__
		system("export LANG=C.UTF-8");
	#endif
	if (logMsgNumber>0)
	{
		printf("%d\n", logMsgs[0].warningLevel);
		printf("%s\n", logMsgs[0].textMessage);
		printf("%d\n", logMsgNumber);
	}
    delete[] logMsgs;
}
///日志功能是否开启
void api_demo_cr_log_enable()
{
    BOOL enable = TRUE;
    cr_log_enable(enable);
}

///日志大小设置
void api_demo_cr_log_set_size()
{
    long size = 1024 * 1024;
    int num = 10;
    cr_log_set_size(size, num);
}

///读系统时间
void api_demo_cr_get_SystemDateTime()
{
    char systemDateTime[100];
    CRresult result = cr_get_SystemDateTime(robotHandle, systemDateTime);
    assert(result == sucess);
    printf("%s\n", systemDateTime);
}

void api_demo_cr_get_controllerType()
{
    char controllerType[10];
    CRresult result = cr_get_controllerType(robotHandle, controllerType);  //读控制器型号
    assert(result == sucess);
    printf("%s\n", controllerType);
}

///读取机型型号
void api_demo_cr_sys_robotModel_get()
{
	char robotModel[10];
	CRresult result = cr_sys_robotModel_get(robotHandle, robotModel, 10);  //读机型型号
	assert(result == sucess);
	printf("%s\n", robotModel);
}

///触发黑匣子数据
void api_demo_cr_sys_blackBoxData_trigger()
{
	CRresult result = cr_sys_blackBoxData_trigger(robotHandle);  //触发黑匣子数据
	assert(result == sucess);
}

///读控制器标准数字输出
void api_demo_cr_get_stdDigitalOut()
{
    int index = 1;
    BOOL val;
    CRresult result = cr_get_stdDigitalOut(robotHandle, index, &val);
    assert(result == sucess);
    printf("%d\n", val);
}

///写控制器标准数字输出
void api_demo_cr_set_stdDigitalOut()
{
    int index = 1;
    BOOL val = TRUE;
    CRresult result = cr_set_stdDigitalOut(robotHandle, index, val);
    assert(result == sucess);
}

///读控制器可配置数字输出
void api_demo_cr_get_configDigitalOut()
{
    int index = 1;
    BOOL val;
    CRresult result = cr_get_configDigitalOut(robotHandle, index, &val);
    assert(result == sucess);
    printf("%d\n", val);
}

///写控制器可配置数字输出
void api_demo_cr_set_configDigitalOut()
{
    int index = 1;
    BOOL val = TRUE;
    CRresult result = cr_set_configDigitalOut(robotHandle, index, val);
    assert(result == sucess);
}

///读工具端数字输出
void api_demo_cr_get_toolDigitalOut()
{
    int index = 0;
    BOOL val;
    CRresult result = cr_get_toolDigitalOut(robotHandle, index, &val);
    assert(result == sucess);
    printf("%d\n", val);
}

///写工具端数字输出
void api_demo_cr_set_toolDigitalOut()
{
    int index = 0;
    BOOL val = FALSE;
    CRresult result = cr_set_toolDigitalOut(robotHandle, index, val);
    assert(result == sucess);
}

///读控制器标准数字输入
void api_demo_cr_get_stdDigitalIn()
{
    int index = 0;
    BOOL val;
    CRresult result = cr_get_stdDigitalIn(robotHandle, index, &val);
    assert(result == sucess);
    printf("%d\n", val);
}

///读控制器可配置数字输入
void api_demo_cr_get_configDigitalIn()
{
    int index = 0;
    BOOL val;
    CRresult result = cr_get_configDigitalIn(robotHandle, index, &val);
    assert(result == sucess);
    printf("%d\n", val);
}

///读工具端数字输入
void api_demo_cr_get_toolDigitalIn()
{
    int index = 0;
    BOOL val;
    CRresult result = cr_get_toolDigitalIn(robotHandle, index, &val);
    assert(result == sucess);
    printf("%d\n", val);

}

///读控制器模拟量输出
void api_demo_cr_get_stdAnalogOut()
{
    int index = 0;
    double val;
    CRresult result = cr_get_stdAnalogOut(robotHandle, index, &val);
    assert(result == sucess);
    printf("%f\n", val);
}

///写控制器模拟量输出
void api_demo_cr_set_stdAnalogOut()
{
    int index = 0;
    double val = 3;
    CRresult result = cr_set_stdAnalogOut(robotHandle, index, val);
    assert(result == sucess);
}

///读工具端模拟量输入
void api_demo_cr_get_toolAnalogIn()
{
    int index = 1;
    double val;
    CRresult result = cr_get_toolAnalogIn(robotHandle, index, &val);
    assert(result == sucess);
    printf("%f\n", val);
}

///读控制器模拟量输入
void api_demo_cr_get_stdAnalogIn()
{
    int index = 1;
    double val;
    CRresult result = cr_get_stdAnalogIn(robotHandle, index, &val);
    assert(result == sucess);
    printf("%f\n", val);
}

///读机械臂控制器和工具端上所有输入数字量和模拟量
void api_demo_cr_get_allDAInput()
{
    BOOL controllerDI[CR6_DI_NUM];
    BOOL controllerCI[CR6_CI_NUM];
    double controllerAI[CR6_AI_NUM];
    BOOL toolDI[CR6_TOOL_DI_NUM];
    double toolAI[CR6_TOOL_AI_NUM];
    CRresult result = cr_get_allDAInput(robotHandle, controllerDI, controllerCI, controllerAI, toolDI, toolAI);
    assert(result == sucess);
    for (int i = 0; i < CR6_DI_NUM; i++)
    {
        printf("%d\n", controllerDI[i]);
        printf("%d\n", controllerCI[i]);
    }
    for (int i = 0; i < CR6_AI_NUM; i++)
    {
        printf("%f\n", controllerAI[i]);
    }
    for (int i = 0; i < CR6_TOOL_DI_NUM; i++)
    {
        printf("%d\n", toolDI[i]);
        printf("%f\n", toolAI[i]);
    }

}

///读机械臂控制器和工具端上所有输出数字量和模拟量
void api_demo_cr_get_allDAOutput()
{
    BOOL controllerDO[CR6_DO_NUM];
    BOOL controllerCO[CR6_CO_NUM];
    double controllerAO[CR6_AO_NUM];
    BOOL toolDO[CR6_TOOL_DO_NUM];
    CRresult result = cr_get_allDAOutput(robotHandle, controllerDO, controllerCO, controllerAO, toolDO);
    assert(result == sucess);
    for (int i = 0; i < CR6_DO_NUM; i++)
    {
        printf("%d\n", controllerDO[i]);
        printf("%d\n", controllerCO[i]);
    }
    for (int i = 0; i < CR6_AO_NUM; i++)
    {
        printf("%f\n", controllerAO[i]);
    }
    for (int i = 0; i < CR6_TOOL_DO_NUM; i++)
    {
        printf("%d\n", toolDO[i]);
    }
}

///读bool寄存器
void api_demo_cr_get_boolRegValue()
{
    unsigned int startAddress = 0;
    unsigned int offsetLength = 10;
    BOOL regData[10];
    CRresult result = cr_get_boolRegValue(robotHandle, startAddress, offsetLength, regData); //读第0至9位的bool寄存器
    assert(result == sucess);
    printf("%d\n", regData[9]);
}

///写bool寄存器
void api_demo_cr_set_boolRegValue()
{
    unsigned int startAddress = 0;
    unsigned int offsetLength = 10;
    BOOL regData[10] = { 0,1,0,1,0,1,0,1,0,1 }; //写入数据
    CRresult result = cr_set_boolRegValue(robotHandle, startAddress, offsetLength, regData);//写第0至9位的bool寄存器
    assert(result == sucess);
}

///读int16寄存器
void api_demo_cr_get_int16RegValue()
{
    unsigned int startAddress = 0;
    unsigned int offsetLength = 10;
    int regData[10];
    CRresult result = cr_get_int16RegValue(robotHandle, startAddress, offsetLength, regData); //读第0至9位的int16寄存器
    assert(result == sucess);
    printf("%d\n", regData[1]);
}

///写int16寄存器
void api_demo_cr_set_int16RegValue()
{
    unsigned int startAddress = 0;
    unsigned int offsetLength = 10;
    int regData[10] = { 1,2,3,4,5,6,7,8,9,0 }; //写入数据
    CRresult result = cr_set_int16RegValue(robotHandle, startAddress, offsetLength, regData); //写第0至9位的int16寄存器
    assert(result == sucess);
}

///读int32寄存器
void api_demo_cr_get_int32RegValue()
{
    unsigned int startAddress = 0;
    unsigned int offsetLength = 10;
    int regData[10];
    CRresult result = cr_get_int32RegValue(robotHandle, startAddress, offsetLength, regData); //读第0至9位的int32寄存器
    assert(result == sucess);
    printf("%d\n", regData[1]);
}

///写int32寄存器
void api_demo_cr_set_int32RegValue()
{
    unsigned int startAddress = 0;
    unsigned int offsetLength = 10;
    int regData[10] = { 1,2,3,4,5,6,7,8,9,0 }; //写入数据
    CRresult result = cr_set_int32RegValue(robotHandle, startAddress, offsetLength, regData); //写第0至9位的int32寄存器
    assert(result == sucess);
}

///读float寄存器
void api_demo_cr_get_floatRegValue()
{
    unsigned int startAddress = 0;
    unsigned int offsetLength = 10;
    float regData[10];
    CRresult result = cr_get_floatRegValue(robotHandle, startAddress, offsetLength, regData); //读第0至9位的float寄存器
    assert(result == sucess);
    printf("%f\n", regData[0]);
}

///写float寄存器
void api_demo_cr_set_floatRegValue()
{
    unsigned int startAddress = 0;
    unsigned int offsetLength = CR6_FLOAT_REG_NUM;
    float regData[CR6_INT16_REG_NUM] = { 1,2,3,4,5,6,7,8,9,0 }; //写入数据
    CRresult result = cr_set_floatRegValue(robotHandle, startAddress, offsetLength, regData); //写第0至9位的float寄存器
    assert(result == sucess);
}

///读安装变量
void api_demo_cr_get_intallVarValue()
{
    const char installVarName[CR6_ISTALL_VAR_NAME_LENGTH] = { "i_var_1" };
    VariableMsg *installVar = new VariableMsg;
    CRresult result = cr_get_intallVarValue(robotHandle, installVarName, installVar);
    assert(result == sucess);
    printf("%f\n", installVar->numberValue);
}

///修改安装变量
void api_demo_cr_set_installVarValue()
{
    const char installVarName[CR6_ISTALL_VAR_NAME_LENGTH] = { "i_var_1" };
    VariableMsg installVar;
    installVar.boolValue = true;
    installVar.variableType = LUA_TBOOLEAN;
    char name[CR6_ISTALL_VAR_NAME_LENGTH] = { "i_var_2" };
    strcpy(installVar.variableName, name);
    CRresult result = cr_set_installVarValue(robotHandle, installVarName, &installVar);
    assert(result == sucess);
}

///读取程序变量数据
void api_demo_cr_script_var_get()
{
    char varName[20] = "var_1";
    VariableMsg variableMsg;
    CRresult result = cr_script_var_get(robotHandle, varName, &variableMsg);
    assert(result == sucess);
    printf("%f\n", variableMsg.numberValue);
}

///修改程序变量数据
void api_demo_cr_script_var_set()
{
	VariableMsg variableMsg;
	variableMsg.numberValue = 2;
	variableMsg.variableType = LUA_TNUMBER;
	char name[CR6_ISTALL_VAR_NAME_LENGTH] = { "var_1" };
	strcpy(variableMsg.variableName, name);
	CRresult result = cr_script_var_set(robotHandle, &variableMsg);  //修改名称为var_1的程序变量的数据
	assert(result == sucess);
}

///获取编码器计数数量
void api_demo_cr_get_encoderTickCnt()
{
    int encoderChannel = 0;
    long long encoderTickCount;
    CRresult result = cr_get_encoderTickCnt(robotHandle, encoderChannel, &encoderTickCount);//获取编码器通道0的计数数量
    assert(result == sucess);
    printf("%lld\n", encoderTickCount);
}

///设置监控界面的工具输出电压
void api_demo_cr_set_ToolOutputVoltage()
{
    ToolPower toolPower = Power_on;
    CRresult result = cr_set_ToolOutputVoltage(robotHandle, toolPower);  //设置监控界面的工具输出电压为24v
    assert(result == sucess);
}

///读取监控界面的工具输出电压
void api_demo_cr_get_ToolOutputVoltage()
{
    enum ToolPower toolPower;
    CRresult result = cr_get_ToolOutputVoltage(robotHandle, &toolPower);  //读取监控界面的工具输出电压
    assert(result == sucess);
    printf("%d\n", toolPower);
}

///位姿转换
void api_demo_cr_poseTrans()
{
    double poseFrom[ROB_AXIS_NUM] = { 1,2,3,0,180,0 };
    double poseTrans[ROB_AXIS_NUM] = { 4,4,4,180,0,0 };
    double poseTo[ROB_AXIS_NUM];
    CRresult result = cr_poseTrans(poseFrom, poseTrans, poseTo);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", poseTo[i]);
    }
}

///位姿求逆
void api_demo_cr_compute_pose_inv()
{
    int poseLen = 6;
    int poseInvLen = 6;
    double pose[6] = { -66, -438, 887, -57, 0, -148 };
    double poseInv[6];
    CRresult result = cr_compute_pose_inv(pose, poseLen, poseInv, poseInvLen);
    assert(result == sucess);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", poseInv[i]);
    }
}

///轴角转欧拉角
void api_demo_cr_AxisAngle2Eule()
{
    double axisAnglePose[ROB_AXIS_NUM] = { 50.06,467.28,672.44,19.81,1.07,-66.3 };
    double eulePose[ROB_AXIS_NUM];
    CRresult result = cr_AxisAngle2Eule(axisAnglePose, eulePose);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", eulePose[i]);
    }
}

///欧拉角转轴角
void api_demo_cr_Eule2AxisAngle()
{
    double eulePose[ROB_AXIS_NUM] = { 50.06,467.28,672.44,19.81,1.07,-66.3 };
    double axisAnglePose[ROB_AXIS_NUM];
    CRresult result = cr_Eule2AxisAngle(eulePose, axisAnglePose);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", axisAnglePose[i]);
    }
}

///TCP位姿转法兰位姿
void api_demo_cr_TcpToFlangePose()
{
    double tcpPose[ROB_AXIS_NUM] = { 223,240,550,23,24,55 };
    double toolPose[ROB_AXIS_NUM] = { 22,44,55,66,77,88 };
    double flangePose[ROB_AXIS_NUM];
    CRresult result = cr_TcpToFlangePose(tcpPose, toolPose, flangePose);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", flangePose[i]);
    }
}

///基坐标系下位姿转移到用户坐标系下
void api_demo_cr_compute_pose_base_to_user()
{
    int basePoseLen = 6;
    int userPoseLen = 6;
    int poseInUserLen = 6;
    double basePose[6] = { -66, -438, 887, -57, 0, -148 };
    double userPose[6] = { 10,10, 10, 10, 10, 10 };
    double poseInUser[6];
    CRresult result = cr_compute_pose_base_to_user(basePose, basePoseLen, userPose, userPoseLen, poseInUser, poseInUserLen);
    assert(result == sucess);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", poseInUser[i]);
    }
}

///正解
void api_demo_cr_kineForward()
{
    double srcJointPose[ROB_AXIS_NUM] = { 60,60,60,60,60,60 };
    double tarPose[ROB_AXIS_NUM];
    CRresult result = cr_kineForward(robotHandle, srcJointPose, tarPose);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", tarPose[i]);
    }
}

///逆解
void api_demo_cr_kineInverse()
{
    double srcPose[ROB_AXIS_NUM] = { -66.01,-438.24,887.68,-57.34,0,-148.98 };
    double refJointPose[ROB_AXIS_NUM] = { 0,0,0,0,0,0 };
    double tarJointPose[ROB_AXIS_NUM];
    CRresult result = cr_kineInverse(robotHandle, srcPose, refJointPose, tarJointPose);
    assert(result == sucess);
    for (int i = 0; i < ROB_AXIS_NUM; i++)
    {
        printf("%f\n", tarJointPose[i]);
    }
}

///设置安装角度
void api_demo_cr_cfg_install_angle_set()
{
    InstallAngle installAngle;
    installAngle.baseAngle = 11;
    installAngle.tiltAngle = 11;
    CRresult result = cr_cfg_install_angle_set(robotHandle, installAngle);
    assert(result == sucess);
}

///读取安装角度
void api_demo_cr_cfg_install_angle_get()
{
    InstallAngle installAngle;
    CRresult result = cr_cfg_install_angle_get(robotHandle, &installAngle);
    assert(result == sucess);
    printf("%f\n", installAngle.tiltAngle);
    printf("%f\n", installAngle.baseAngle);
}

///读取TCP个数
void api_demo_cr_cfg_tcp_count()
{
    int count;
    CRresult result = cr_cfg_tcp_count(robotHandle, &count);
    assert(result == sucess);
    printf("%d\n", count);
}

///读取TCP数据
void api_demo_cr_cfg_tcp_get()
{
    TCPMsg tcpMsg;
    int index = 0;
    CRresult result = cr_cfg_tcp_get(robotHandle, index, &tcpMsg);
    assert(result == sucess);
    printf("%s\n", tcpMsg.tcpName);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", tcpMsg.tcpOffset[i]);
    }
}

///增加TCP
void api_demo_cr_cfg_tcp_add()
{
    TCPMsg tcpMsg;
    int i;
    char name[20] = { "TCP1" };
    strcpy(tcpMsg.tcpName, name);
    double offset[6] = { 3,10,9,90,80,70 };
    for (i = 0; i < 6; i++)
    {
        tcpMsg.tcpOffset[i] = offset[i];
    }
    CRresult result = cr_cfg_tcp_add(robotHandle, tcpMsg);
    assert(result == sucess);

}

///删除TCP
void api_demo_cr_cfg_tcp_delete()
{
    int index = 1;
    CRresult result = cr_cfg_tcp_delete(robotHandle, index);
    assert(result == sucess);
}

///编辑TCP数据
void api_demo_cr_cfg_tcp_set()
{
    int index = 1;
    TCPMsg tcpMsg;
    char name[20] = { "TCP" };
    strcpy(tcpMsg.tcpName,  name);
    double offset[6] = { 3,10,9,90,80,70 };
    for (int i = 0; i < 6; i++)
    {
        tcpMsg.tcpOffset[i] = offset[i];
    }
    CRresult result = cr_cfg_tcp_set(robotHandle, index, tcpMsg);
    assert(result == sucess);
}

///读取当前激活的TCP索引
void api_demo_cr_cfg_tcp_active_get()
{
    int index;
    CRresult result = cr_cfg_tcp_active_get(robotHandle, &index);
    assert(result == sucess);
    printf("%d\n", index);
}

///激活TCP
void api_demo_cr_cfg_tcp_active_set()
{
    int index = 3;
    CRresult result = cr_cfg_tcp_active_set(robotHandle, index);
    assert(result == sucess);
}

///计算TCP位置
void api_demo_cr_compute_tcp_position()
{
    double poses[][6] = { {4.31,-66.66,934.53,20.30,-121.50,-73.277},
    {-3.71,-68.75,926.57,12.589,-124.54,-77.42},
    {13.98,-65.98,934.53,20.30,-121.5,-73.27},
    {4.2558,-66.66,934.53,8.77,-107.15,-71.457} };
    int posesLen = 4;
    double position[3];
    int positionLen = 3;
    double err = 0;
    CRresult result = cr_compute_tcp_position(poses, posesLen, position, positionLen, &err);
    assert(result == sucess);
    for (int i = 0; i < 3; i++)
    {
        printf("%f\n", position[i]);
    }
}

///计算TCP角度
void api_demo_cr_compute_tcp_orientation()
{
    double csPose[6] = { 0, 0, 0, 0, 0, 0 };
    int csLen = 6;
    double pointPose[6] = { -36.10, -4.42, 32.62, 13.54, -91.33, 39.52 };
    int pointLen = 6;
    double orientation[3];
    int orientationLen = 3;
    CRresult result = cr_compute_tcp_orientation(csPose, csLen, pointPose, pointLen, orientation, orientationLen);
    assert(result == sucess);
    for (int i = 0; i < 3; i++)
    {
        printf("%f\n", orientation[i]);
    }
}

///读取负载个数
void api_demo_cr_cfg_payload_count()
{
    int count;
    CRresult result = cr_cfg_payload_count(robotHandle, &count);
    assert(result == sucess);
    printf("%d\n", count);
}

///读取负载数据
void api_demo_cr_cfg_payload_get()
{
    PayLoad payLoad;
    int index = 0;
    CRresult result = cr_cfg_payload_get(robotHandle, index, &payLoad);
    assert(result == sucess);
    printf("%s\n", payLoad.payloadName);
    printf("%f\n", payLoad.toolPayload);
    for (int i = 0; i < 3; i++)
    {
        printf("%f\n", payLoad.centerOfGravity[i]);
    }
}

///增加负载
void api_demo_cr_cfg_payload_add()
{
    PayLoad payLoad;
    char name[20] = { "payload" };
    strcpy(payLoad.payloadName, name);
    payLoad.toolPayload = 6;
    double centerOfGravity[3] = { 0,0,30 };
    for (int i = 0; i < 3; i++)
    {
        payLoad.centerOfGravity[i] = centerOfGravity[i];
    }
    CRresult result = cr_cfg_payload_add(robotHandle, payLoad);
    assert(result == sucess);
}

///删除负载
void api_demo_cr_cfg_payload_delete()
{
    int index = 2;
    CRresult result = cr_cfg_payload_delete(robotHandle, index);
    assert(result == sucess);
}

///编辑负载
void api_demo_cr_cfg_payload_set()
{
    PayLoad payLoad;
    int index = 1;
    char name[20] = { "payload" };
    strcpy(payLoad.payloadName, name);
    payLoad.toolPayload = 6;
    double centerOfGravity[3] = { 0,0,30 };
    for (int i = 0; i < 3; i++)
    {
        payLoad.centerOfGravity[i] = centerOfGravity[i];
    }
    CRresult result = cr_cfg_payload_set(robotHandle, index, payLoad);
    assert(result == sucess);
}

///读取当前激活的负载索引
void api_demo_cr_cfg_payload_active_get()
{
    int index;
    CRresult result = cr_cfg_payload_active_get(robotHandle, &index);
    printf("%d\n", index);
    assert(result == sucess);
}

///激活负载
void api_demo_cr_cfg_payload_active_set()
{
    int index = 1;
    CRresult result = cr_cfg_payload_active_set(robotHandle, index);
    assert(result == sucess);
}

///设置初始位
void api_demo_cr_cfg_home_pose_set()
{
    double homePose[6] = { 60,60,60,60,60,60 };
    int len = 6;
    CRresult result = cr_cfg_home_pose_set(robotHandle, homePose, len);
    assert(result == sucess);
}

///读取初始位
void api_demo_cr_cfg_home_pose_get()
{
    double homePose[6];
    int len = 6;
    CRresult result = cr_cfg_home_pose_get(robotHandle, homePose, len);
    assert(result == sucess);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", homePose[i]);
    }
}

///删除初始位
void api_demo_cr_cfg_home_pose_delete()
{
    CRresult result = cr_cfg_home_pose_delete(robotHandle);
    assert(result == sucess);
}

///读取包装位
void api_demo_cr_cfg_pack_pose_get()
{
    double packPose[6];
    int len = 6;
    CRresult result = cr_cfg_pack_pose_get(robotHandle, packPose, len);
    assert(result == sucess);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", packPose[i]);
    }
}

///设置机器人是否自动上电使能
void api_demo_cr_cfg_poweron_auto_set()
{
    BOOL isAuto = TRUE;
    CRresult result = cr_cfg_poweron_auto_set(robotHandle, isAuto);
    assert(result == sucess);
}

///读取机器人自动上电状态
void api_demo_cr_cfg_poweron_auto_get()
{
    BOOL isAuto;
    CRresult result = cr_cfg_poweron_auto_get(robotHandle, &isAuto);
    assert(result == sucess);
    printf("%d\n", isAuto);
}

///设置机器人拖动阻尼
void api_demo_cr_cfg_joint_drag_damping_set()
{
    int jointDargDamping[6] = {50,50,50,50,50,50};
    int arrSize = 6;
    CRresult result = cr_cfg_joint_drag_damping_set(robotHandle, jointDargDamping, arrSize);
    assert(result == sucess);
}

///读取机器人拖动阻尼
void api_demo_cr_cfg_joint_drag_damping_get()
{
    int jointDargDamping[6] = { 0 };
    int arrSize = 6;
    CRresult result = cr_cfg_joint_drag_damping_get(robotHandle, jointDargDamping, arrSize);
    assert(result == sucess);
}

///设置限制模式
void api_demo_cr_cfg_safety_limit_type_set()
{
    SafetyLimitsValuesType safetyLimitsValuesType;
    safetyLimitsValuesType = LimitLevel_4;
    CRresult result = cr_cfg_safety_limit_type_set(robotHandle, safetyLimitsValuesType);
    assert(result == sucess);
}

///读取限制模式
void api_demo_cr_cfg_safety_limit_type_get()
{
    SafetyLimitsValuesType safetyLimitsValuesType;
    CRresult result = cr_cfg_safety_limit_type_get(robotHandle, &safetyLimitsValuesType);
    assert(result == sucess);
    printf("%d\n", safetyLimitsValuesType);
}

///设置自定义模式下参数
void api_demo_cr_cfg_safety_limit_para_set()
{
    SafetyLimitsValues safetyLimitsValues;
    SafetyLimitsMode mode = mode_Reduced;
    safetyLimitsValues.maxPower = 300;
    safetyLimitsValues.maxMomentum = 25;
    safetyLimitsValues.maxStoppingTime = 400;
    safetyLimitsValues.maxStoppingDistance = 500;
    safetyLimitsValues.maxTcpSpeed = 100;
    safetyLimitsValues.maxForce = 0;
    safetyLimitsValues.maxElbowSpeed = 1500;
    safetyLimitsValues.maxElbowForce = 150;
    CRresult result = cr_cfg_safety_limit_para_set(robotHandle, mode, safetyLimitsValues);
    assert(result == sucess);
}

///读取自定义模式下参数
void api_demo_cr_cfg_safety_limit_para_get()
{
    SafetyLimitsValues safetyLimitsValues;
    SafetyLimitsMode mode = mode_Normal;
    CRresult result = cr_cfg_safety_limit_para_get(robotHandle, mode, &safetyLimitsValues);
    assert(result == sucess);
    printf("%f\n", safetyLimitsValues.maxElbowSpeed);
}

///设置碰撞后处理方式
void api_demo_cr_cfg_safety_collihandle_type_set()
{
    SafetyCollisionHandleMode safetyCollisionHandleMode = Collision_EnterReboundMode;
    CRresult result = cr_cfg_safety_collihandle_type_set(robotHandle, safetyCollisionHandleMode);
    //将碰撞后处理方式设置为进入反弹模式
    assert(result == sucess);
}

///读取碰撞后处理方式
void api_demo_cr_cfg_safety_collihandle_type_get()
{
    SafetyCollisionHandleMode safetyCollisionHandleMode;
    CRresult result = cr_cfg_safety_collihandle_type_get(robotHandle, &safetyCollisionHandleMode);
    assert(result == sucess);
    printf("碰撞后处理方式:%d", safetyCollisionHandleMode);
}

///设置关节限值
void api_demo_cr_cfg_safety_joint_limit_set()
{
    int index = 1;
    SafetyLimitsJointAngle safetyLimitJoint;
    safetyLimitJoint.maxJointPosition = 360;
    safetyLimitJoint.minJointPosition = -200;
    safetyLimitJoint.maxJointSpeed = 150;
    SafetyLimitsMode mode = mode_Reduced;
    CRresult result = cr_cfg_safety_joint_limit_set(robotHandle, mode, index, safetyLimitJoint);
    assert(result == sucess);
}

///读取关节限值
void api_demo_cr_cfg_safety_joint_limit_get()
{
    SafetyLimitsJointAngle safetyLimitJoint;
    SafetyLimitsMode mode = mode_Normal;
    int jointIndex = 1;
    CRresult result = cr_cfg_safety_joint_limit_get(robotHandle, mode, jointIndex, &safetyLimitJoint);
    assert(result == sucess);
    printf("%f\n", safetyLimitJoint.maxJointPosition);
}

///读取安全平面个数
void api_demo_cr_cfg_safety_plane_count()
{
    int count;
    CRresult result = cr_cfg_safety_plane_count(robotHandle, &count);
    assert(result == sucess);
    printf("%d\n", count);
}

///读取安全平面信息
void api_demo_cr_cfg_safety_plane_get()
{
    int index = 1 ;
    SafetyLimitsBoundaryPlane safetyLimitsBoundaryPlane;
    CRresult result = cr_cfg_safety_plane_get(robotHandle, index, &safetyLimitsBoundaryPlane);
    assert(result == sucess);
    printf("%s\n", safetyLimitsBoundaryPlane.name);
    printf("%d\n", safetyLimitsBoundaryPlane.id);
    printf("%f\n", safetyLimitsBoundaryPlane.displacement);
}

///增加安全平面
void api_demo_cr_cfg_safety_plane_add()
{
    SafetyLimitsBoundaryPlane safetyLimitsBoundaryPlane;
    safetyLimitsBoundaryPlane.mode = Normal;
    safetyLimitsBoundaryPlane.id = 4;
    safetyLimitsBoundaryPlane.elbowRestricted = 0;
    safetyLimitsBoundaryPlane.sourceGeomFeatureType = baseCoordinate;
    safetyLimitsBoundaryPlane.displacement = 11;
    char name[20] = { "safeplane" };
    strcpy(safetyLimitsBoundaryPlane.name, name);
    CRresult result = cr_cfg_safety_plane_add(robotHandle, safetyLimitsBoundaryPlane);
    assert(result == sucess);
}

///删除安全平面
void api_demo_cr_cfg_safety_plane_delete()
{
    int index = 1;
    CRresult result = cr_cfg_safety_plane_delete(robotHandle, index);
    assert(result == sucess);
}

///修改安全平面数据
void api_demo_cr_cfg_safety_plane_set()
{
    int index = 1;
    SafetyLimitsBoundaryPlane safetyLimitsBoundaryPlane;
    safetyLimitsBoundaryPlane.mode = Normal;
    safetyLimitsBoundaryPlane.id = 4;
    safetyLimitsBoundaryPlane.displacement = 11;
    char name[20] = { "safeplane" };
    strcpy(safetyLimitsBoundaryPlane.name, name);
    CRresult result = cr_cfg_safety_plane_set(robotHandle, index, safetyLimitsBoundaryPlane);
    assert(result == sucess);
}

///设置可配置输入信号
void api_demo_cr_cfg_safety_io_input_set()
{
    SafetyIOInput safetyinput;
    safetyinput = input_invaild;
    int index = 1;
    CRresult result = cr_cfg_safety_io_input_set(robotHandle, index, safetyinput);
    assert(result == sucess);
}

///读取可配置输入信号
void api_demo_cr_cfg_safety_io_input_get()
{
    SafetyIOInput safetyinput;
    int index = 2;
    CRresult result = cr_cfg_safety_io_input_get(robotHandle, index, &safetyinput);
    assert(result == sucess);
    printf("%d\n", safetyinput);
}

///设置可配置输出信号
void api_demo_cr_cfg_safety_io_output_set()
{
    int index = 1;
    SafetyIOOutput safetyoutput = robotNotStopping;
    CRresult result = cr_cfg_safety_io_output_set(robotHandle, index, safetyoutput);
    assert(result == sucess);
}

///读取可配置输出信号
void api_demo_cr_cfg_safety_io_output_get()
{
    int index = 1;
    SafetyIOOutput safetyoutput;
    CRresult result = cr_cfg_safety_io_output_get(robotHandle, index, &safetyoutput);
    assert(result == sucess);
    printf("%d\n", safetyoutput);
}

///设置是否启用示教器
void api_demo_cr_cfg_safety_tp_use_set()
{
    BOOL isUse = FALSE;
    CRresult result = cr_cfg_safety_tp_use_set(robotHandle, isUse);
    assert(result == sucess);
}

///读取当前是否启用示教器
void api_demo_cr_cfg_safety_tp_use_get()
{
    BOOL isUse;
    CRresult result = cr_cfg_safety_tp_use_get(robotHandle, &isUse);
    assert(result == sucess);
    printf("%d\n", isUse);
}

///设置数字输入信号配置
void api_demo_cr_cfg_var_di_set()
{
    VarDigitialIOType type = Digitial;
    int index = 1;
    IOInputConfiguration inputConfiguration;
    inputConfiguration.inputFilteringTime = 1;
    inputConfiguration.inputActions = InputAction_NONE;
    char name[NAMELENTH] = { "digital" };
    for (int i = 0; i < NAMELENTH; i++)
    {
        inputConfiguration.inputName[i] = name[i];
    }
    CRresult result = cr_cfg_var_di_set(robotHandle, type, index, inputConfiguration);
    assert(result == sucess);
}

///读取数字输入信号配置
void api_demo_cr_cfg_var_di_get()
{
    VarDigitialIOType type = Digitial;
    int index = 1;
    IOInputConfiguration inputConfiguration;
    CRresult result = cr_cfg_var_di_get(robotHandle, type, index, &inputConfiguration);
    assert(result == sucess);
    printf("%d\n", type);
    printf("%s\n", inputConfiguration.inputName);
}

///设置数字输出信号配置
void api_demo_cr_cfg_var_do_set()
{
    VarDigitialIOType type = Digitial;
    int index = 1;
    IOOutputConfiguration outputConfiguration;
    outputConfiguration.outputActions = OutputAction_RobotON_LOW;
    char name[NAMELENTH] = { "digital" };
    for (int i = 0; i < NAMELENTH; i++)
    {
        outputConfiguration.outputName[i] = name[i];
    }
    outputConfiguration.outputOptions = OutputOptions_Enable;
    outputConfiguration.outputRule = OutputRule_Disable;
    CRresult result = cr_cfg_var_do_set(robotHandle, type, index, outputConfiguration);
    assert(result == sucess);
}

///读取数字输出信号配置
void api_demo_cr_cfg_var_do_get()
{
    VarDigitialIOType type = Digitial;
    int index = 1;
    IOOutputConfiguration outputConfiguration;
    CRresult result = cr_cfg_var_do_get(robotHandle, type, index, &outputConfiguration);
    assert(result == sucess);
    printf("%s\n", outputConfiguration.outputName);
}

///设置模拟量输入信号类型
void api_demo_cr_cfg_var_ai_set()
{
    AnalogInputConfiguration analogInputConfiguration;
    VarDigitialIOType type = Analog;
    char Name[NAMELENTH] = { "AI0" };
    int index = 1;
    for (int i = 0; i < NAMELENTH; i++)
    {
        analogInputConfiguration.analogInputName[i] = Name[i];
    }
    analogInputConfiguration.analogInputType = Voltage;
    CRresult result = cr_cfg_var_ai_set(robotHandle, type, index, analogInputConfiguration);
    assert(result == sucess);
}

///读取模拟量输入信号类型
void api_demo_cr_cfg_var_ai_get()
{
    AnalogInputConfiguration analogInputConfiguration;
    VarDigitialIOType type = Analog;
    int index = 1;
    CRresult result = cr_cfg_var_ai_get(robotHandle, type, index, &analogInputConfiguration);
    assert(result == sucess);
    printf("%d\n", analogInputConfiguration.analogInputType);
}

///设置模拟量输出信号类型
void api_demo_cr_cfg_var_ao_set()
{
    int index = 0;
    AnalogOutputConfiguration analogOutputConfiguration;
    analogOutputConfiguration.analogOutputType = Current;
    char Name[NAMELENTH] = { "AN0" };
    for (int i = 0; i < NAMELENTH; i++)
    {
        analogOutputConfiguration.analogOutputName[i] = Name[i];
    }
    CRresult result = cr_cfg_var_ao_set(robotHandle, index, analogOutputConfiguration);
    assert(result == sucess);
}

///读取模拟量输出信号类型
void api_demo_cr_cfg_var_ao_get()
{
    int index = 0;
    AnalogOutputConfiguration analogOutputConfiguration;
    analogOutputConfiguration.analogOutputType = Current;
    CRresult result = cr_cfg_var_ao_get(robotHandle, index, &analogOutputConfiguration);
    assert(result == sucess);
    printf("%s\n", analogOutputConfiguration.analogOutputName);
}

///设置工具电压输出值
void api_demo_cr_cfg_var_to_set()
{
    ToolPower toolPower = Power_on;
    CRresult result = cr_cfg_var_to_set(robotHandle, toolPower);
    assert(result == sucess);
    printf("设置值：%d\n", toolPower);
}

///读取工具电压输出值
void api_demo_cr_cfg_var_to_get()
{
    ToolPower toolPower;
    CRresult result = cr_cfg_var_to_get(robotHandle, &toolPower);
    assert(result == sucess);
    printf("读取值：%d\n", toolPower);
}

///设置位寄存器配置
void api_demo_cr_cfg_var_bit_reg_set()
{
    int index = 1;
    BitRegisterConfiguration bitRegisterConfiguration;
    bitRegisterConfiguration.GeneralPurposeBOOLeanRegisterInputActions = InputAction_NONE;
    bitRegisterConfiguration.GeneralPurposeBOOLeanRegisterOutputActions = OutputAction_RobotON_HIGH;
    bitRegisterConfiguration.GeneralPurposeBOOLeanRegisterOutputRule = OutputRule_Disable;
    char Name[NAMELENTH] = { "WEI" };
    strcpy(bitRegisterConfiguration.GeneralPurposeBOOLeanRegisterName, Name);
    CRresult result = cr_cfg_var_bit_reg_set(robotHandle, index, bitRegisterConfiguration);
    assert(result == sucess);
}

///读取位寄存器配置
void api_demo_cr_cfg_var_bit_reg_get()
{
    BitRegisterConfiguration bitRegisterConfiguration;
    int index = 1;
    CRresult result = cr_cfg_var_bit_reg_get(robotHandle, index, &bitRegisterConfiguration);
    printf("%d\n", bitRegisterConfiguration.GeneralPurposeBOOLeanRegisterInputActions);
    assert(result == sucess);
}

///设置16位整数寄存器变量名
void api_demo_cr_cfg_var_int16_reg_name_set()
{
    char Name[NAMELENTH] = { "WEI16" };
    int index = 1;
    int len = 6;
    CRresult result = cr_cfg_var_int16_reg_name_set(robotHandle, index, Name, len);
    assert(result == sucess);
}

///读取16位整数寄存器变量名
void api_demo_cr_cfg_var_int16_reg_name_get()
{
    char name[NAMELENTH];
    int index = 1;
    int len = 6;
    CRresult result = cr_cfg_var_int16_reg_name_get(robotHandle, index, name, 6);
    assert(result == sucess);
    printf("%s\n", name);
}

///设置32位整数寄存器变量名
void api_demo_cr_cfg_var_int32_reg_name_set()
{
    char Name[NAMELENTH] = { "WEI32" };
    int index = 1;
    int len = 6;
    CRresult result = cr_cfg_var_int32_reg_name_set(robotHandle, index, Name, len);
    assert(result == sucess);
}

///读取32位整数寄存器变量名
void api_demo_cr_cfg_var_int32_reg_name_get()
{
    char name[NAMELENTH];
    int index = 1;
    int len = 6;
    CRresult result = cr_cfg_var_int32_reg_name_get(robotHandle, index, name, len);
    assert(result == sucess);
    printf("%s\n", name);
}

///设置浮点寄存器变量名
void api_demo_cr_cfg_var_float_reg_name_set()
{
    char Name[NAMELENTH] = { "FLOAT" };
    int index = 1;
    int len = 6;
    CRresult result = cr_cfg_var_float_reg_name_set(robotHandle, index, Name, len);
    assert(result == sucess);
}

///读取浮点寄存器变量名
void api_demo_cr_cfg_var_float_reg_name_get()
{
    char name[NAMELENTH];
    int index = 1;
    int len = 10;
    CRresult result = cr_cfg_var_float_reg_name_get(robotHandle, index, name, 6);
    assert(result == sucess);
    printf("%s\n", name);
}

///读取安装变量个数
void api_demo_cr_cfg_var_install_count()
{
    int count;
    CRresult result = cr_cfg_var_install_count(robotHandle, &count);
    assert(result == sucess);
    printf("%d\n", count);
}

///读取安装变量数据
void api_demo_cr_cfg_var_install_get()
{
    VariableMsg variableMsg;
    CRresult result = cr_cfg_var_install_get(robotHandle, 1, &variableMsg);
    assert(result == sucess);
    printf("%d\n", variableMsg.boolValue);
}

///增加安装变量
void api_demo_cr_cfg_var_install_add()
{
    VariableMsg variablemsg;
    char name[CR6_ISTALL_VAR_NAME_LENGTH] = { "install" };
    strcpy(variablemsg.variableName, name);
    variablemsg.variableType = LUA_TBOOLEAN;
    variablemsg.boolValue = TRUE;
    variablemsg.variableID = 3;
    CRresult result = cr_cfg_var_install_add(robotHandle, &variablemsg);
    assert(result == sucess);
}

///删除安装变量
void api_demo_cr_cfg_var_install_delete()
{
    int index = 1;
    CRresult result = cr_cfg_var_install_delete(robotHandle, index);
    assert(result == sucess);
}


///修改安装变量
void api_demo_cr_cfg_var_install_set()
{
    int index = 1;
    char name[CR6_ISTALL_VAR_NAME_LENGTH] = { "install" };
    VariableMsg variablemsg;
    strcpy(variablemsg.variableName, name);
    variablemsg.variableType = LUA_TBOOLEAN;
    variablemsg.boolValue = FALSE;
    variablemsg.variableID = 1;
    CRresult result = cr_cfg_var_install_set(robotHandle, index, &variablemsg);
    assert(result == sucess);
}

///读取点坐标系个数
void api_demo_cr_cfg_cs_point_count()
{
    int count;
    CRresult result = cr_cfg_cs_point_count(robotHandle, &count);
    assert(result == sucess);
    printf("%d\n", count);
}

///读取点坐标系数据
void api_demo_cr_cfg_cs_point_get()
{
    PointCSNode pointCSNode;
    int index = 1;
    CRresult result = cr_cfg_cs_point_get(robotHandle, index, &pointCSNode);
    assert(result == sucess);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", pointCSNode.point.toolAxisAngle[i]);
    }
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", pointCSNode.point.toolPosition[i]);
    }
}

///增加点坐标系
void api_demo_cr_cfg_cs_point_add()
{
    PointCSNode pointCSNode;
    char name[32] = { "point3" };
    strcpy(pointCSNode.name, name);
    double toolAxisAngle[6] = { 30,30,30,30,30,30 };
    double toolPosition[6];
    for (int i = 0; i < 6; i++)
    {
        pointCSNode.point.toolAxisAngle[i] = toolAxisAngle[i];
    }
    cr_kineForward(robotHandle, toolAxisAngle, toolPosition); //正解求点的位姿
    for (int i = 0; i < 6; i++)
    {
        pointCSNode.point.toolPosition[i] = toolPosition[i];
    }
    pointCSNode.isValid = TRUE;
    pointCSNode.id = 1;
    CRresult result = cr_cfg_cs_point_add(robotHandle, pointCSNode);
    assert(result == sucess);
}
///删除点坐标系
void api_demo_cr_cfg_cs_point_delete()
{
    int index = 3;
    CRresult result = cr_cfg_cs_point_delete(robotHandle, index);
    assert(result == sucess);
}

///修改点坐标系数据
void api_demo_cr_cfg_cs_point_set()
{
    int index = 1;
    PointCSNode pointCSNode;
    char name[32] = { "point3" };
    strcpy(pointCSNode.name, name);
    double toolAxisAngle[6] = { 30,30,30,30,30,30 };
    double toolPosition[6];
    for (int i = 0; i < 6; i++)
    {
        pointCSNode.point.toolAxisAngle[i] = toolAxisAngle[i];
    }
    cr_kineForward(robotHandle, toolAxisAngle, toolPosition); //正解求点的位姿
    for (int i = 0; i < 6; i++)
    {
        pointCSNode.point.toolPosition[i] = toolPosition[i];
    }
    pointCSNode.isValid = TRUE;
    pointCSNode.id = 1;
    CRresult result = cr_cfg_cs_point_set(robotHandle, index, pointCSNode);
    assert(result == sucess);
}

///读取线坐标系个数
void api_demo_cr_cfg_cs_line_count()
{
    int count;
    CRresult result = cr_cfg_cs_line_count(robotHandle, &count);
    assert(result == sucess);
    printf("%d\n", count);
}

///读取线坐标系数据
void api_demo_cr_cfg_cs_line_get()
{
    LineCSNode lineCSNode;
    int index = 1;
    CRresult result = cr_cfg_cs_line_get(robotHandle, index, &lineCSNode);
    assert(result == sucess);
    printf("%d\n", lineCSNode.firstPoint.id);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", lineCSNode.coordinateJointPos[i]);
    }
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", lineCSNode.coordinatePose[i]);
    }
}

///增加线坐标系
void api_demo_cr_cfg_cs_line_add()
{
    LineCSNode lineCSNode;
    double toolAxisAngle1[6] = { 0,0,90,0,-90,0 };
    double toolAxisAngle2[6] = { 9.29,3.39,86.49,0.08,-89.91,9.29 };
    double toolPosition1[6];
    double toolPosition2[6];
    double coordinatePose[6];
    double coordinateJointPos[6] = { 0,0,0,0,0,0 };
    cr_kineForward(robotHandle, toolAxisAngle1, toolPosition1); //正解求第一个点位姿
    cr_kineForward(robotHandle, toolAxisAngle2, toolPosition2); //正解求第二个点位姿
    cr_compute_cs_line(toolPosition1, 6, toolPosition2, 6, coordinatePose, 6); //计算线坐标系位姿
    CRresult res = cr_kineInverse(robotHandle, coordinatePose, coordinateJointPos, coordinateJointPos); //逆解求线坐标系关节角度
    if (res == 0) //判断逆解是否存在，即坐标系是否有效
    {
        lineCSNode.isValid = 1;
    }
    else
    {
        lineCSNode.isValid = 0;
    }
    char name[32] = { "LINE" };
    char point_name1[32] = { "p1" };
    char point_name2[32] = { "p2" };
    strcpy(lineCSNode.firstPoint.name, point_name1);
    strcpy(lineCSNode.secondPoint.name, point_name2);
    strcpy(lineCSNode.name, name);
    for (int i = 0; i < 6; i++)
    {
        lineCSNode.firstPoint.point.toolAxisAngle[i] = toolAxisAngle1[i];
        lineCSNode.secondPoint.point.toolAxisAngle[i] = toolAxisAngle2[i];
        lineCSNode.firstPoint.point.toolPosition[i] = toolPosition1[i];
        lineCSNode.secondPoint.point.toolPosition[i] = toolPosition2[i];
        lineCSNode.coordinateJointPos[i] = coordinateJointPos[i];
        lineCSNode.coordinatePose[i] = coordinatePose[i];
    }
    lineCSNode.firstPoint.id = 1;
    lineCSNode.firstPoint.isValid = 1;
    lineCSNode.secondPoint.id = 2;
    lineCSNode.secondPoint.isValid = 1;
    lineCSNode.id = 2;
    CRresult result = cr_cfg_cs_line_add(robotHandle, lineCSNode);
    assert(result == sucess);
}

///删除线坐标系
void api_demo_cr_cfg_cs_line_delete()
{
    int index = 1;
    CRresult result = cr_cfg_cs_line_delete(robotHandle, index);
    assert(result == sucess);
}

///修改线坐标系数据
void api_demo_cr_cfg_cs_line_set()
{
    LineCSNode lineCSNode;
    double toolAxisAngle1[6] = { 0,0,90,0,-90,0 };
    double toolAxisAngle2[6] = { 9.29,3.39,86.49,0.08,-89.91,9.29 };
    double toolPosition1[6];
    double toolPosition2[6];
    double coordinatePose[6];
    double coordinateJointPos[6] = { 0,0,0,0,0,0 };
    cr_kineForward(robotHandle, toolAxisAngle1, toolPosition1); //正解求第一个点位姿
    cr_kineForward(robotHandle, toolAxisAngle2, toolPosition2); //正解求第二个点位姿
    cr_compute_cs_line(toolPosition1, 6, toolPosition2, 6, coordinatePose, 6); //计算线坐标系位姿
    CRresult res = cr_kineInverse(robotHandle, coordinatePose, coordinateJointPos, coordinateJointPos); //逆解求线坐标系关节角度
    if (res == 0) //判断逆解是否存在，即坐标系是否有效
    {
        lineCSNode.isValid = 1;
    }
    else
    {
        lineCSNode.isValid = 0;
    }
    char name[32] = { "LINE" };
    char point_name1[32] = { "p1" };
    char point_name2[32] = { "p2" };
    strcpy(lineCSNode.firstPoint.name, point_name1);
    strcpy(lineCSNode.secondPoint.name, point_name2);
    strcpy(lineCSNode.name, name);
    for (int i = 0; i < 6; i++)
    {
        lineCSNode.firstPoint.point.toolAxisAngle[i] = toolAxisAngle1[i];
        lineCSNode.secondPoint.point.toolAxisAngle[i] = toolAxisAngle2[i];
        lineCSNode.firstPoint.point.toolPosition[i] = toolPosition1[i];
        lineCSNode.secondPoint.point.toolPosition[i] = toolPosition2[i];
        lineCSNode.coordinateJointPos[i] = coordinateJointPos[i];
        lineCSNode.coordinatePose[i] = coordinatePose[i];
    }
    lineCSNode.firstPoint.id = 1;
    lineCSNode.firstPoint.isValid = 1;
    lineCSNode.secondPoint.id = 2;
    lineCSNode.secondPoint.isValid = 1;
    lineCSNode.id = 2;
    CRresult result = cr_cfg_cs_line_set(robotHandle, 1, lineCSNode);
    assert(result == sucess);
}

///读取面坐标系个数
void api_demo_cr_cfg_cs_plane_count()
{
    int count;
    CRresult result = cr_cfg_cs_plane_count(robotHandle, &count);
    assert(result == sucess);
    printf("%d\n", count);
}

///读取面坐标系数据
void api_demo_cr_cfg_cs_plane_get()
{
    int index = 1;
    PlaneCSNode planeCSNode;
    CRresult result = cr_cfg_cs_plane_get(robotHandle, index, &planeCSNode);
    assert(result == sucess);
    printf("%d\n", planeCSNode.secondPoint.id);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", planeCSNode.coordinateJointPos[i]);
    }
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", planeCSNode.coordinatePose[i]);
    }
}

///增加面坐标系
void api_demo_cr_cfg_cs_plane_add()
{
    PlaneCSNode planeCSNode;
    double toolAxisAngle1[6] = { 0, 0, 90, 0, -90, 0 };
    double toolAxisAngle2[6] = { 0, 4.84, 84.91, 0.25, -89.99, 0 };
    double toolAxisAngle3[6] = { -8.1, -1.5, 91.48, 0.04, -90.07, -8.1 };
    double toolPosition1[6];
    double toolPosition2[6];
    double toolPosition3[6];
    double coordinatePose[6];
    double coordinateJointPos[6] = { 0,0,0,0,0,0 };
    cr_kineForward(robotHandle, toolAxisAngle1, toolPosition1); //正解求第一个点位姿
    cr_kineForward(robotHandle, toolAxisAngle2, toolPosition2); //正解求第二个点位姿
    cr_kineForward(robotHandle, toolAxisAngle3, toolPosition3); //正解求第三个点位姿
    cr_compute_cs_plane(toolPosition1, 6, toolPosition2, 6, toolPosition3, 6, coordinatePose, 6);
    //计算面坐标系位姿
    CRresult res = cr_kineInverse(robotHandle, coordinatePose, coordinateJointPos, coordinateJointPos); //逆解求面坐标系关节角度
    if (res == 0) //判断逆解是否存在，即坐标系是否有效
    {
        planeCSNode.isValid = 1;
    }
    else
    {
        planeCSNode.isValid = 0;
    }
    char name[32] = { "plane_1" };
    char point_name1[32] = { "firstpoint" };
    char point_name2[32] = { "secondpoint" };
    char point_name3[32] = { "thirdpoint" };
    strcpy(planeCSNode.firstPoint.name, point_name1);
    strcpy(planeCSNode.secondPoint.name, point_name2);
    strcpy(planeCSNode.thirdPoint.name, point_name3);
    strcpy(planeCSNode.name, name);
    for (int i = 0; i < 6; i++)
    {
        planeCSNode.firstPoint.point.toolAxisAngle[i] = toolAxisAngle1[i];
        planeCSNode.secondPoint.point.toolAxisAngle[i] = toolAxisAngle2[i];
        planeCSNode.thirdPoint.point.toolAxisAngle[i] = toolAxisAngle3[i];
        planeCSNode.firstPoint.point.toolPosition[i] = toolPosition1[i];
        planeCSNode.secondPoint.point.toolPosition[i] = toolPosition2[i];
        planeCSNode.thirdPoint.point.toolPosition[i] = toolPosition3[i];
        planeCSNode.coordinatePose[i] = coordinatePose[i];
        planeCSNode.coordinateJointPos[i] = coordinateJointPos[i];
    }
    planeCSNode.firstPoint.id = 1;
    planeCSNode.firstPoint.isValid = 1;
    planeCSNode.secondPoint.id = 2;
    planeCSNode.secondPoint.isValid = 1;
    planeCSNode.thirdPoint.id = 3;
    planeCSNode.thirdPoint.isValid = 1;
    planeCSNode.id = 2;
    CRresult result = cr_cfg_cs_plane_add(robotHandle, planeCSNode);
    assert(result == sucess);
}

///删除面坐标系
void api_demo_cr_cfg_cs_plane_delete()
{
    int index = 1;
    CRresult result = cr_cfg_cs_plane_delete(robotHandle, index);
    assert(result == sucess);
}

///修改面坐标系数据
void api_demo_cr_cfg_cs_plane_set()
{
    PlaneCSNode planeCSNode;
    double toolAxisAngle1[6] = { 0, 0, 90, 0, -90, 0 };
    double toolAxisAngle2[6] = { 0, 4.84, 84.91, 0.25, -89.99, 0 };
    double toolAxisAngle3[6] = { -8.1, -1.5, 91.48, 0.04, -90.07, -8.1 };
    double toolPosition1[6];
    double toolPosition2[6];
    double toolPosition3[6];
    double coordinatePose[6];
    double coordinateJointPos[6] = { 0,0,0,0,0,0 };
    cr_kineForward(robotHandle, toolAxisAngle1, toolPosition1); //正解求第一个点位姿
    cr_kineForward(robotHandle, toolAxisAngle2, toolPosition2); //正解求第二个点位姿
    cr_kineForward(robotHandle, toolAxisAngle3, toolPosition3); //正解求第三个点位姿
    cr_compute_cs_plane(toolPosition1, 6, toolPosition2, 6, toolPosition3, 6, coordinatePose, 6);
    //计算面坐标系位姿
    CRresult res = cr_kineInverse(robotHandle, coordinatePose, coordinateJointPos, coordinateJointPos); //逆解求面坐标系关节角度
    if (res == 0) //判断逆解是否存在，即坐标系是否有效
    {
        planeCSNode.isValid = 1;
    }
    else
    {
        planeCSNode.isValid = 0;
    }
    char name[32] = { "plane_1" };
    char point_name1[32] = { "firstpoint" };
    char point_name2[32] = { "secondpoint" };
    char point_name3[32] = { "thirdpoint" };
    strcpy(planeCSNode.firstPoint.name,  point_name1);
    strcpy(planeCSNode.secondPoint.name, point_name2);
    strcpy(planeCSNode.thirdPoint.name, point_name3);
    strcpy(planeCSNode.name, name);
    for (int i = 0; i < 6; i++)
    {
        planeCSNode.firstPoint.point.toolAxisAngle[i] = toolAxisAngle1[i];
        planeCSNode.secondPoint.point.toolAxisAngle[i] = toolAxisAngle2[i];
        planeCSNode.thirdPoint.point.toolAxisAngle[i] = toolAxisAngle3[i];
        planeCSNode.firstPoint.point.toolPosition[i] = toolPosition1[i];
        planeCSNode.secondPoint.point.toolPosition[i] = toolPosition2[i];
        planeCSNode.thirdPoint.point.toolPosition[i] = toolPosition3[i];
        planeCSNode.coordinatePose[i] = coordinatePose[i];
        planeCSNode.coordinateJointPos[i] = coordinateJointPos[i];
    }
    planeCSNode.firstPoint.id = 1;
    planeCSNode.firstPoint.isValid = 1;
    planeCSNode.secondPoint.id = 2;
    planeCSNode.secondPoint.isValid = 1;
    planeCSNode.thirdPoint.id = 3;
    planeCSNode.thirdPoint.isValid = 1;
    planeCSNode.id = 2;
    CRresult result = cr_cfg_cs_plane_set(robotHandle, 1, planeCSNode);
    assert(result == sucess);
}

///读取基坐标系数据
void api_demo_cr_cfg_cs_base_get()
{
    int len = 6;
    double csPose[6];
    CRresult result = cr_cfg_cs_base_get(robotHandle, csPose, 6);
    assert(result == sucess);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", csPose[i]);
    }
}

///读取工具坐标系数据
void api_demo_cr_cfg_cs_tool_get()
{
    int len = 6;
    double csPose[6];
    CRresult result = cr_cfg_cs_tool_get(robotHandle, csPose, len);
    assert(result == sucess);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", csPose[i]);
    }
}

///计算点坐标系
void api_demo_cr_compute_cs_point()
{
    int pLen = 6;
    int csLen = 6;
    double pointPose[6] = { -66, -438, 887, -57, 0, -148 };
    double pointCS[6];
    CRresult result = cr_compute_cs_point(pointPose, pLen, pointCS, csLen);
    assert(result == sucess);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", pointCS[i]);
    }
}

///计算线坐标系
void api_demo_cr_compute_cs_line()
{
    int p1Len = 6;
    int p2Len = 6;
    int csLen = 6;
    double point1Pose[6] = { -66, -438, 887, -57, 0, -148 };
    double point2Pose[6] = { -76, -438, 887, -57, 0, -148 };
    double lineCS[6];
    CRresult result = cr_compute_cs_line(point1Pose, p1Len, point2Pose, p2Len, lineCS, csLen);
    assert(result == sucess);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", lineCS[i]);
    }
}

///计算面坐标系
void api_demo_cr_compute_cs_plane()
{
    int p1Len = 6;
    int p2Len = 6;
    int p3Len = 6;
    int csLen = 6;
    double point1Pose[6] = { -70, -436.75, 893, 27.15, 22, 150.76 };
    double point2Pose[6] = { -75, -436.75, 893, 27.15, 22, 150.76 };
    double point3Pose[6] = { -75, -440, 893, 27.15, 22, 150.76 };
    double planeCS[6];
    CRresult result = cr_compute_cs_plane(point1Pose, p1Len, point2Pose, p2Len, point3Pose, p3Len, planeCS, csLen);
    assert(result == sucess);
    for (int i = 0; i < 6; i++)
    {
        printf("%f\n", planeCS[i]);
    }
}

///设置串口配置
void api_demo_cr_cfg_comm_serial_setting_set()
{
    SerialType serialType;
    serialType = rs485_1_CommSettings;
    SerialCommSettings serialCommSettings;
    serialCommSettings.parity = odd;
    serialCommSettings.serialCommType = Modbus_ASCII;
    serialCommSettings.baudRate = BaudRate1200000;
    serialCommSettings.dataBits = 8;
    serialCommSettings.modbusSlaveNo = 1;
    serialCommSettings.retryNumber = 3;
    serialCommSettings.stopBits = 1;
    serialCommSettings.timeout = 300;
    CRresult result = cr_cfg_comm_serial_setting_set(robotHandle, serialType, serialCommSettings);
    assert(result == sucess);
}

///读取串口配置
void api_demo_cr_cfg_comm_serial_setting_get()
{
    SerialType serialType;
    serialType = rs485_2_CommSettings;
    SerialCommSettings serialCommSettings;
    CRresult result = cr_cfg_comm_serial_setting_get(robotHandle, serialType, &serialCommSettings);
    assert(result == sucess);
    printf("%d\n", serialCommSettings.baudRate);
}

///设置控制柜网络配置
void api_demo_cr_cfg_comm_ethernet_ip_set()
{
    IPConfig ipconfig;
    ipconfig.ipAddr[0] = 192;
    ipconfig.ipAddr[1] = 168;
    ipconfig.ipAddr[2] = 6;
    ipconfig.ipAddr[3] = 6;
    ipconfig.subnetMask[0] = 255;
    ipconfig.subnetMask[1] = 255;
    ipconfig.subnetMask[2] = 0;
    ipconfig.subnetMask[3] = 0;
    CRresult result = cr_cfg_comm_ethernet_ip_set(robotHandle, ipconfig);
    assert(result == sucess);
}

///读取控制柜网络配置
void api_demo_cr_cfg_comm_ethernet_ip_get()
{
    IPConfig ipconfig;
    CRresult result = cr_cfg_comm_ethernet_ip_get(robotHandle, &ipconfig);
    assert(result == sucess);
    for (int i = 0; i < 9; i++)
    {
        printf("%d\n", ipconfig.ipAddr[i]);
    }
}

///设置控制柜从站配置
void api_demo_cr_cfg_comm_ethernet_modbus_slave_num_set()
{
    int modbusSlaveNo = 1;
    CRresult result = cr_cfg_comm_ethernet_modbus_slave_num_set(robotHandle, modbusSlaveNo);
    assert(result == sucess);
}

///读取控制柜从站配置
void api_demo_cr_cfg_comm_ethernet_modbus_slave_num_get()
{
    int modbusSlaveNo;
    CRresult result = cr_cfg_comm_ethernet_modbus_slave_num_get(robotHandle, &modbusSlaveNo);
    assert(result == sucess);
    printf("%d\n", modbusSlaveNo);
}

///读取从站个数
void api_demo_cr_cfg_comm_modbus_slave_count()
{
    SerialType type = rs485_1_CommSettings;
    int count;
    CRresult result = cr_cfg_comm_modbus_slave_count(robotHandle, type, &count);
    assert(result == sucess);
    printf("%d\n", count);
}

///读取从站数据
void api_demo_cr_cfg_comm_modbus_slave_get()
{
    SerialType type = rs485_1_CommSettings;
    ModbusMasterConfig modbusConfig;
    CRresult result = cr_cfg_comm_modbus_slave_get(robotHandle, type, 1, &modbusConfig);
    assert(result == sucess);
    printf("%d\n", modbusConfig.slaveNo);
}

///添加从站
void api_demo_cr_cfg_comm_modbus_slave_add()
{
    SerialType type = rs485_1_CommSettings;
    ModbusMasterConfig modbusConfig;
    modbusConfig.id = 3;
    modbusConfig.slaveNo = 4;
    modbusConfig.scanTime = 5;
    modbusConfig.autoConnect = 0;
    modbusConfig.modbusMasterOperate = Stop;
    CRresult result = cr_cfg_comm_modbus_slave_add(robotHandle, type, &modbusConfig);
    assert(result == sucess);
}

///删除从站
void api_demo_cr_cfg_comm_modbus_slave_delete()
{
    SerialType type = rs485_1_CommSettings;
    CRresult result = cr_cfg_comm_modbus_slave_delete(robotHandle, type, 1);
    assert(result == sucess);
}

///修改从站数据
void api_demo_cr_cfg_comm_modbus_slave_set()
{
    SerialType type = rs485_1_CommSettings;
    ModbusMasterConfig modbusConfig;
    modbusConfig.id = 3;
    modbusConfig.slaveNo = 4;
    modbusConfig.scanTime = 5;
    modbusConfig.autoConnect = 0;
    modbusConfig.modbusMasterOperate = Stop;
    CRresult result = cr_cfg_comm_modbus_slave_set(robotHandle, type, 2, modbusConfig);
    assert(result == sucess);
}

///从站连接 / 断开
void api_demo_cr_cfg_comm_modbus_slave_operate()
{
    ModbusMasterOperate modbusOperate = Start;
    SerialType type = rs485_1_CommSettings;
    CRresult result = cr_cfg_comm_modbus_slave_operate(robotHandle, type, 1, modbusOperate);
    assert(result == sucess);
}

///读取地址映射数量
void api_demo_cr_cfg_comm_modbus_addr_map_count()
{
    int  count;
    SerialType type = rs485_1_CommSettings;
    CRresult result = cr_cfg_comm_modbus_addr_map_count(robotHandle, type, 1, &count);
    assert(result == sucess);
    printf("%d\n", count);
}

///读取地址映射数据
void api_demo_cr_cfg_comm_modbus_addr_map_get()
{
    SerialType type = rs485_1_CommSettings;
    ModbusAddrMap addrMap;
    CRresult result = cr_cfg_comm_modbus_addr_map_get(robotHandle, type, 1, 1, &addrMap);
    assert(result == sucess);
    printf("%d\n", addrMap.masterOffsetNo);
}

///添加地址映射
void api_demo_cr_cfg_comm_modbus_addr_map_add()
{
    SerialType type = rs485_1_CommSettings;
    ModbusAddrMap addrMap;
    int serialIndex = 1;
    addrMap.masterOffsetNo = 1;
    addrMap.functionNo = WriteBool;
    addrMap.masterStartAddr = 2;
    addrMap.slaveStartAddr = 1;
    CRresult result = cr_cfg_comm_modbus_addr_map_add(robotHandle, type, serialIndex, addrMap);
    assert(result == sucess);
}

///删除地址映射
void api_demo_cr_cfg_comm_modbus_addr_map_delete()
{
    SerialType type = rs485_1_CommSettings;
    CRresult result = cr_cfg_comm_modbus_addr_map_delete(robotHandle, type, 1, 1);
    assert(result == sucess);
}

///修改地址映射数据
void api_demo_cr_cfg_comm_modbus_addr_map_set()
{
    SerialType type = rs232_CommSettings;
    ModbusAddrMap addrMap;
    int serialIndex = 2;
    addrMap.masterOffsetNo = 1;
    addrMap.functionNo = WriteBool;
    addrMap.masterStartAddr = 2;
    addrMap.slaveStartAddr = 1;
    CRresult result = cr_cfg_comm_modbus_addr_map_set(robotHandle, type, serialIndex, 1, addrMap);
    assert(result == sucess);
}

///设置力控配置
void api_demo_cr_force_cfg_set()
{
    ForceConfig forceConfig = { 0 };   //结构体初始化
    char activeForceTCP_name[20] = "TCP_4";  //激活的力控传感器TCP的名称
    memcpy(forceConfig.forceCtrlTcpImpl.activeForceTCP_name, activeForceTCP_name, sizeof(activeForceTCP_name));
    char activePayload_name[20] = "ForcePayload7";   //激活的力控传感器负载的名称
    memcpy(forceConfig.forceCtrlTcpImpl.activeForcePayload_name, activePayload_name, sizeof(activePayload_name));
    ForceTCPMsg availTcp[20] = { { "TCP_4", 0, { 0,0,0,0,0,-110 } }, { "ForceTcp4", 1, { 0,0,0,180,0,0 } }, { "ForceTcp5", 2, { 0,0,0,180,0,0 } } };
    //当前待选的力控传感器TCP的配置信息
    memcpy(forceConfig.forceCtrlTcpImpl.availableForceTCP, availTcp, sizeof(ForceTCPMsg) * 20);
    ForcePayLoad availPayload[20] = { { "ForcePayload7", 0, 1.3,{ 1,2,3 } } , { "ForcePayload5", 1, 1.3,{ 1,2,3 } } , { "ForcePayload6", 2, 0.5,{ 0,0,0 } } };
    //当前待选的力控传感器负载的配置信息
    memcpy(forceConfig.forceCtrlTcpImpl.availableForcePayLoad, availPayload, sizeof(ForcePayLoad) * 20);
    forceConfig.forceCtrlTcpImpl.availableForceTCPLen = 3;
    //当前待选的力控传感器TCP的配置信息的个数
    forceConfig.forceCtrlTcpImpl.availableForcePayLoadLen = 3;
    // 当前待选的力控传感器负载的配置信息的个数

    forceConfig.commuConfig.autoConnect = 1;
    //自动与传感器通信，传感器开始接收数据
    forceConfig.commuConfig.mannaulOperate = 0;
    //自动与传感器通信，传感器开始接收数据
    forceConfig.commuConfig.paraBuf = 0;     //预留参数

    forceConfig.sensorMessage.venderNo = 0;   //传感器品牌
    forceConfig.sensorMessage.productNo = 1;  //传感器产品号，预留参数
    forceConfig.sensorMessage.sequenceNo = 0;  //传感器序列号，预留参数
    CRresult result = cr_force_cfg_set(robotHandle, forceConfig);   //设置力控配置
    assert(result == sucess); //判断设置力控配置是否成功
}

///读力控配置
void api_demo_cr_force_cfg_get()
{
    ForceConfig forceConfig = { 0 };
    CRresult result = cr_force_cfg_get(robotHandle, &forceConfig);  //读力控配置
    assert(result == sucess); //判断读力控配置是否成功
}

///开启力控并下发相关设置
void api_demo_cr_force_open()
{
    ForceSetting forceSetting = { 0 };
    forceSetting.forceBaseType = 0;
    //力控类型:  0-基于TCP力传感器,1-基于动力学,2-基于底座力传感器
    forceSetting.forceCtrlType = 1;  //力控用法:  0-运动力控,1-力控拖动
    int flexibleAxis[6] = { 0,0,1,0,0,0 };  //z轴可拖动
    memcpy(forceSetting.flexibleAxis, flexibleAxis, sizeof(flexibleAxis));
    CRresult result = cr_force_open(robotHandle, forceSetting);  //开启力控并下发相关配置
    assert(result == sucess); //判断开启力控并下发相关配置是否成功
}

///关闭力控
void api_demo_cr_force_close()
{
    CRresult result = cr_force_close(robotHandle);  //关闭力控
    assert(result == sucess); //判断关闭力控是否成功
}

///设置力控控制参数
void api_demo_cr_force_para_set()
{
    ForceCtlPara forceCtlPara = { 0 };
    double damping[6] = { 1,1,0.1,1,1,1 };  //x,y,Rx,Ry,Rz阻尼系数均为1,z阻尼系数为0.1
    double stiffness[6] = { 1,1,0.1,1,1,1 };  //x,y,Rx,Ry,Rz刚度均为1,z刚度为0.1
    double mass[6] = { 1,1,0.5,1,1,1 };  //x,y,Rx,Ry,Rz质量系数均为1,z质量系数为0.5
    double limits[6] = { 0.1,0.1,0.005,0.002,0.002,0.002 };
    //x,y方向速度保护为0.1m/s，z方向偏差保护为0.005m,Rx,Ry,Rz偏差保护为0.002rad
    memcpy(forceCtlPara.damping, damping, sizeof(double) * 6);
    memcpy(forceCtlPara.stiffness, stiffness, sizeof(double) * 6);
    memcpy(forceCtlPara.mass, mass, sizeof(double) * 6);
    memcpy(forceCtlPara.limits, limits, sizeof(double) * 6);

    double taskframe[6] = { 0,0,0,0,0,0 };  //力控坐标系为基坐标系
    double wrench[6] = { 0,0,10,0,0,0 };  //z轴正向施加10N的力
    memcpy(forceCtlPara.taskFrame, taskframe, sizeof(double) * 6);
    memcpy(forceCtlPara.wrench, wrench, sizeof(double) * 6);

    forceCtlPara.dampingLen = 6;  //0、1或6
    forceCtlPara.limitsLen = 6;  //0或6
    forceCtlPara.massLen = 6;  //0、1或6
    forceCtlPara.stiffnessLen = 6;  //0、1或6

    CRresult result = cr_force_para_set(robotHandle, forceCtlPara); //设置力控控制参数
    assert(result == sucess); //判断设置力控控制参数是否成功
}

///读力控控制参数
void api_demo_cr_force_para_get()
{
    ForceCtlPara forceCtlPara = { 0 };
    CRresult result = cr_force_para_get(robotHandle, &forceCtlPara);  //读力控控制参数
    assert(result == sucess); //判断读力控控制参数是否成功
}

///读力控数据
void api_demo_cr_force_data_get()
{
    ForceData forceData = { 0 };
    CRresult result = cr_force_data_get(robotHandle, &forceData);  //读力控数据
    assert(result == sucess); //判断读力控数据是否成功
}

int main()
{
    //典型demo使用示例
    CRresult result = cr_create_robot(&robotHandle, "192.168.6.6", 2323, "123");  // 机械臂连接
    if (result != sucess)
        return -1;
    api_demo_cr_move_joint();
    api_demo_cr_move_line();
    api_demo_cr_moveJog();
    api_demo_cr_get_tcpActualPose();
    api_demo_cr_get_currentTCPmsg();
    api_demo_cr_get_jointActualPos();
    api_demo_cr_get_stdDigitalOut();
    api_demo_cr_set_stdDigitalOut();
    api_demo_cr_get_boolRegValue();
    api_demo_cr_set_boolRegValue();
    api_demo_cr_kineForward();
    api_demo_cr_kineInverse();
    api_demo_cr_cfg_tcp_get();
    api_demo_cr_cfg_payload_get();

    result = cr_destroy_robot(robotHandle);
    if (result != sucess)
        return -1;
}

