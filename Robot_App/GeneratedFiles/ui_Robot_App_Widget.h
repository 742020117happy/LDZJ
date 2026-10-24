/********************************************************************************
** Form generated from reading UI file 'Robot_App_Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOT_APP_WIDGET_H
#define UI_ROBOT_APP_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Fr_Light.h"
#include "Magic_Lidar_View.h"
#include "Magic_Map_View.h"

QT_BEGIN_NAMESPACE

class Ui_Robot_App_Widget
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_15;
    QWidget *widget_10;
    QGridLayout *gridLayout_94;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QPushButton *Show_Work_Widget;
    QPushButton *Show_IO_Widget;
    QPushButton *Show_CGXi_Widget;
    QPushButton *Show_Pre_Scan_120_Widget;
    QPushButton *Show_Magic_Widget;
    QStackedWidget *stackedWidget;
    QWidget *CGXi_Widget;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_9;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_ip;
    QLineEdit *CGXi_IP;
    QLabel *label_port;
    QLineEdit *CGXi_Port;
    QPushButton *CGXi_Connect;
    QPushButton *CGXi_Disconnect;
    QLabel *label_3;
    c_Fr_Light *CGXi_Connected;
    QLabel *label_4;
    c_Fr_Light *CGXi_Ready;
    QLabel *label_10;
    c_Fr_Light *CGXi_auto_indicator;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *CGXi_Version;
    QLabel *label_6;
    QLineEdit *CGXi_Robot_Mode;
    QLabel *label_7;
    QLineEdit *CGXi_Error_Code;
    QLabel *label_speed;
    QLineEdit *CGXi_Global_Speed;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_7;
    QPushButton *Coils_1003;
    QPushButton *Coils_1007;
    QPushButton *Coils_1001;
    QPushButton *Coils_1004;
    QPushButton *Coils_1005;
    QPushButton *Coils_1006;
    QPushButton *Coils_1000;
    QPushButton *Coils_1002;
    QGroupBox *groupBox_DO_3;
    QGridLayout *gridLayout_12;
    QLabel *l_do_h3_6;
    c_Fr_Light *CGXi_CO0_State;
    QPushButton *CGXi_CO0_Set;
    QLabel *l_do_h2_5;
    QLabel *l_do_h4_3;
    QLabel *l_do_h1_6;
    c_Fr_Light *CGXi_CO5_State;
    QLabel *l_do_h3_5;
    QLabel *l_do_h4_5;
    QLabel *label_DO1_8;
    QPushButton *CGXi_CO5_Reset;
    QLabel *l_do_h3_4;
    QPushButton *CGXi_CO0_Reset;
    QLabel *l_do_h1_5;
    QLabel *l_do_h2_3;
    QLabel *l_do_h1_4;
    QLabel *l_do_h2_6;
    QLabel *l_do_h1_3;
    QPushButton *CGXi_CO5_Set;
    QLabel *l_do_h2_4;
    QLabel *l_do_h3_3;
    QLabel *l_do_h4_4;
    QLabel *label_DO0_3;
    QLabel *l_do_h4_6;
    QLabel *label_DO1_7;
    c_Fr_Light *CGXi_CO1_State;
    QPushButton *CGXi_CO1_Set;
    QPushButton *CGXi_CO1_Reset;
    QLabel *label_DO1_9;
    c_Fr_Light *CGXi_CO2_State;
    QPushButton *CGXi_CO2_Set;
    QPushButton *CGXi_CO2_Reset;
    QLabel *label_DO0_4;
    c_Fr_Light *CGXi_CO4_State;
    QPushButton *CGXi_CO4_Set;
    QPushButton *CGXi_CO4_Reset;
    QLabel *label_DO1_11;
    QPushButton *CGXi_CO3_Reset;
    QPushButton *CGXi_CO3_Set;
    c_Fr_Light *CGXi_CO3_State;
    QLabel *label_DO1_10;
    c_Fr_Light *CGXi_CO6_State;
    QPushButton *CGXi_CO6_Set;
    QPushButton *CGXi_CO6_Reset;
    QLabel *label_DO1_12;
    QPushButton *CGXi_CO7_Set;
    QPushButton *CGXi_CO7_Reset;
    c_Fr_Light *CGXi_CO7_State;
    QGroupBox *groupBox_Prog;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout;
    QLabel *label_8;
    QLineEdit *CGXi_Target_Prog_Index;
    QPushButton *Set_HoldingRegisters_88;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *CGXi_Prog_Pause;
    QPushButton *CGXi_Prog_Stop;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    c_Fr_Light *CGXi_Prog_Index;
    QLineEdit *CGXi_Current_Prog_Index;
    QHBoxLayout *horizontalLayout_7;
    c_Fr_Light *CGXi_program_status;
    QPushButton *CGXi_Prog_Start;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *CGXi_Clear_Error;
    QPushButton *CGXi_Clear_Warning;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QTextBrowser *CGXi_Log;
    QTabWidget *tabWidget_Status;
    QWidget *tab_Joint;
    QVBoxLayout *verticalLayout_Joint;
    QTableWidget *tableWidget_Joint;
    QWidget *tab_TCP;
    QGridLayout *gridLayout_8;
    QTableWidget *tableWidget_TCP;
    QWidget *tab_Robot;
    QVBoxLayout *verticalLayout_Robot;
    QTableWidget *tableWidget_Robot;
    QWidget *Pre_Scan_120_Widget;
    QGridLayout *gridLayout_20;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_24;
    QVBoxLayout *verticalLayout_50;
    QHBoxLayout *horizontalLayout_50;
    QLabel *label_120_Remote_Status;
    c_Fr_Light *Pre_Scan_120_Remote_Light;
    QLabel *label_120_Monitor_Status;
    c_Fr_Light *Pre_Scan_120_Monitor_Light;
    QLabel *label_120_Listen_Status;
    c_Fr_Light *Pre_Scan_120_Listen_Light;
    QLabel *label_120_Tran_Status;
    c_Fr_Light *Pre_Scan_120_Tran_Light;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_50B;
    QLabel *label_120_Client_Num;
    QLineEdit *Pre_Scan_120_Client_Num;
    QLabel *label_120_Cam_Num;
    QLineEdit *Pre_Scan_120_Cam_Num;
    QLabel *label_120_IP;
    QLineEdit *Pre_Scan_120_IP;
    QLabel *label_120_Port;
    QLineEdit *Pre_Scan_120_Port;
    QLabel *label_120_Monitor;
    QLineEdit *Pre_Scan_120_Monitor_Port;
    QLabel *label_120_Tran;
    QLineEdit *Pre_Scan_120_Tran_Port;
    QPushButton *Pre_Scan_120_Connect;
    QPushButton *Pre_Scan_120_Disconnect;
    QHBoxLayout *horizontalLayout_49;
    QGroupBox *groupBox_Task_Info_2;
    QGridLayout *gridLayout_22;
    QPushButton *set_Pre_Scan_120_TaskID;
    QLineEdit *w_Pre_Scan_120_TaskID;
    QLineEdit *w_Pre_Scan_120_Wheelset;
    QLineEdit *w_Pre_Scan_120_Axle;
    QLabel *label_120_TaskID_2;
    QLabel *label_120_Axle_2;
    QLineEdit *w_Pre_Scan_120_Repair;
    QLabel *label_120_Repair_2;
    QLabel *label_120_StartTime_2;
    QPushButton *set_Pre_Scan_120_Wheelset;
    QPushButton *set_Pre_Scan_120_Axle;
    QLabel *label_120_SendUnit_2;
    QPushButton *set_Pre_Scan_120_Repair;
    QLabel *label_120_Wheelset_2;
    QLineEdit *w_Pre_Scan_120_StartTime;
    QPushButton *set_Pre_Scan_120_StartTime;
    QPushButton *set_Pre_Scan_120_SendUnit;
    QLineEdit *w_Pre_Scan_120_SendUnit;
    QGroupBox *groupBox_Collect_Status_2;
    QGridLayout *gridLayout_102;
    QLabel *label_120_Gain_2;
    QLineEdit *w_Pre_Scan_120_Point;
    QPushButton *set_Pre_Scan_120_Part1;
    QPushButton *set_Pre_Scan_120_Point;
    QLineEdit *w_Pre_Scan_120_Part1;
    QLabel *label_120_Part2_2;
    QLineEdit *w_Pre_Scan_120_currentWheelset;
    QLineEdit *w_Pre_Scan_120_Part2;
    QLabel *label_120_Point_2;
    QLineEdit *w_Pre_Scan_120_Gain;
    QPushButton *set_Pre_Scan_120_Gain;
    QLabel *label_120_Prog_2;
    QPushButton *set_Pre_Scan_120_currentWheelset;
    QPushButton *set_Pre_Scan_120_Part2;
    QLabel *label_120_Part1_2;
    QGroupBox *groupBox_MySql;
    QHBoxLayout *horizontalLayout_55;
    QLabel *label_120_MySql_Status;
    c_Fr_Light *Pre_Scan_120_MySql_Light;
    QLineEdit *Pre_Scan_120_MySql_Server;
    QLabel *label_167;
    QLineEdit *MySql_Port;
    QLabel *label_156;
    QLineEdit *MySql_User;
    QLabel *label_149;
    QLineEdit *MySql_Password;
    QLabel *label_148;
    QLineEdit *MySql_Database;
    QPushButton *Pre_Scan_120_MySql_Reconnect;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_23;
    QTextEdit *Prec_Scan_120_Cmd;
    QHBoxLayout *horizontalLayout_53;
    QGroupBox *groupBox_Task_Info;
    QGridLayout *gridLayout_21;
    QLabel *label_120_TaskID;
    QLabel *label_120_Wheelset;
    QLineEdit *r_Pre_Scan_120_TaskID;
    QLabel *label_120_StartTime;
    QLineEdit *r_Pre_Scan_120_Wheelset;
    QLineEdit *r_Pre_Scan_120_StartTime;
    QLineEdit *r_Pre_Scan_120_Axle;
    QLabel *label_120_Axle;
    QLabel *label_120_Repair;
    QLineEdit *r_Pre_Scan_120_Repair;
    QLabel *label_120_SendUnit;
    QLineEdit *r_Pre_Scan_120_SendUnit;
    QGroupBox *groupBox_Collect_Status;
    QGridLayout *gridLayout_26;
    QLineEdit *r_Pre_Scan_120_Gain;
    QLineEdit *r_Pre_Scan_120_Point;
    QLineEdit *r_Pre_Scan_120_Part2;
    QLabel *label_120_LastUpdate;
    QLabel *label_120_Prog;
    QLabel *label_120_Part2;
    QLabel *label_120_Point;
    QLineEdit *Pre_Scan_120_LastUpdate;
    QLineEdit *r_Pre_Scan_120_Part1;
    QLineEdit *r_Pre_Scan_120_currentWheelset;
    QLabel *label_120_Gain;
    QLabel *label_120_Part1;
    QGroupBox *groupBox_Control;
    QGridLayout *gridLayout_25;
    QPushButton *Pre_Scan_120_Collector;
    QPushButton *Pre_Scan_120_Finish_Scan;
    QHBoxLayout *horizontalLayout_54;
    QSpinBox *Pre_Scan_120_Gain_Spin;
    QPushButton *Pre_Scan_120_Change_Gain;
    QPushButton *Pre_Scan_120_Start_Scan;
    QWidget *IO_Widget;
    QGridLayout *gridLayout_29;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_31;
    QGroupBox *groupBox_24;
    QGridLayout *gridLayout_30;
    QLabel *label_280;
    QSpinBox *Write_IO_HoldingRegisters_Size;
    QSpinBox *Write_IO_Coils_Addr;
    QSpinBox *Write_IO_HoldingRegisters_Addr;
    QLabel *label_281;
    QSpinBox *Write_IO_Coils_Size;
    QLabel *label_274;
    QLabel *label_139;
    QLabel *label_122;
    QLineEdit *IO_Ip;
    QLineEdit *IO_Port;
    QLabel *label_273;
    QGroupBox *groupBox_IO_DO;
    QGridLayout *gridLayout;
    QPushButton *btn_IO_AlarmGreen_ON;
    QPushButton *btn_IO_Robot_OFF;
    c_Fr_Light *Coils_1;
    c_Fr_Light *Coils_5;
    c_Fr_Light *Coils_4;
    QPushButton *btn_IO_AlarmGreen_OFF;
    QPushButton *btn_IO_Fan_OFF;
    QPushButton *btn_IO_AlarmYellow_OFF;
    QPushButton *btn_IO_Fan_ON;
    QPushButton *btn_IO_AlarmRed_OFF;
    c_Fr_Light *Coils_2;
    QPushButton *btn_IO_Robot_ON;
    c_Fr_Light *Coils_6;
    c_Fr_Light *Coils_3;
    QPushButton *btn_IO_AlarmRed_ON;
    QPushButton *btn_IO_AlarmYellow_ON;
    QGroupBox *groupBox_IO_Connect;
    QGridLayout *gridLayout_32;
    QLabel *label_25;
    c_Fr_Light *IO_Connected;
    QLabel *label_24;
    c_Fr_Light *IO_Ready;
    QPushButton *IO_Connect;
    QPushButton *IO_Disconnect;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_34;
    QGroupBox *groupBox_Voice_Config;
    QGridLayout *gridLayout_28;
    QLabel *label_Voice_Com;
    QComboBox *Voice_Com;
    QLabel *label_Voice_Baud;
    QComboBox *Voice_Baud;
    QLabel *label_Voice_Addr;
    QSpinBox *Voice_Addr;
    QLabel *label_Voice_Connected;
    c_Fr_Light *Voice_Connected;
    QLabel *label_Voice_Volume;
    QHBoxLayout *horizontalLayout_46;
    QPushButton *Voice_Connect;
    QPushButton *Voice_Disconnect;
    QLineEdit *Voice_Volume_Display;
    QGroupBox *groupBox_Voice_Info;
    QGridLayout *gridLayout_Voice_Info;
    QLabel *label_Voice_Device_Status;
    QLineEdit *Voice_Device_Status;
    QLabel *label_Voice_Current_Audio;
    QLineEdit *Voice_Current_Audio;
    QLabel *label_Voice_Count;
    QLineEdit *Voice_Count;
    QGroupBox *groupBox_Voice_Play;
    QVBoxLayout *verticalLayout_Voice_Play;
    QGridLayout *gridLayout_Voice_Buttons;
    QPushButton *btn_Voice_PA001;
    QPushButton *btn_Voice_PA002;
    QPushButton *btn_Voice_PA003;
    QPushButton *btn_Voice_PA004;
    QPushButton *btn_Voice_PA005;
    QPushButton *btn_Voice_PA006;
    QPushButton *btn_Voice_PA007;
    QPushButton *btn_Voice_PA008;
    QPushButton *btn_Voice_PA009;
    QPushButton *btn_Voice_PA010;
    QPushButton *btn_Voice_PA011;
    QPushButton *btn_Voice_PA012;
    QPushButton *btn_Voice_PA013;
    QPushButton *btn_Voice_PA014;
    QPushButton *btn_Voice_PA015;
    QPushButton *btn_Voice_PA016;
    QPushButton *btn_Voice_PA017;
    QPushButton *btn_Voice_PA018;
    QPushButton *btn_Voice_PA019;
    QPushButton *btn_Voice_PA020;
    QPushButton *btn_Voice_PA021;
    QPushButton *btn_Voice_PA022;
    QPushButton *btn_Voice_PA023;
    QPushButton *btn_Voice_PA024;
    QPushButton *btn_Voice_PA025;
    QHBoxLayout *horizontalLayout_Voice_Ctrl;
    QPushButton *btn_Voice_Stop;
    QPushButton *btn_Voice_Vol_Low;
    QPushButton *btn_Voice_Vol_Med;
    QPushButton *btn_Voice_Vol_High;
    QPushButton *btn_Voice_Test;
    QGroupBox *groupBox_Voice_Log;
    QGridLayout *gridLayout_Voice_Log;
    QTextBrowser *Voice_Log;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_33;
    QTextBrowser *IO_Log;
    QWidget *Work_Widget;
    QGridLayout *gridLayout_27;
    QGroupBox *Work_TaskGroup;
    QGridLayout *Work_TaskGrid;
    QLabel *label_Work_TaskID;
    QLineEdit *Work_TaskID;
    QLabel *label_Work_State;
    QLineEdit *Work_State;
    QLabel *label_Work_Wheel;
    QLineEdit *Work_Wheel;
    QLabel *label_Work_Pos;
    QLineEdit *Work_Pos;
    QLabel *label_Work_Images;
    QLineEdit *Work_Images;
    QLabel *label_Work_SendUnit;
    QLineEdit *Work_SendUnit;
    QLabel *label_Work_Repair;
    QLineEdit *Work_Repair;
    QLabel *label_Work_WheelsetNo;
    QLineEdit *Work_WheelsetNo;
    QLabel *label_Work_AxleNo;
    QLineEdit *Work_AxleNo;
    QLabel *label_Work_Gain;
    QLineEdit *Work_Gain;
    QLabel *label_Work_Part1;
    QLineEdit *Work_Part1;
    QLabel *label_Work_Part2;
    QLineEdit *Work_Part2;
    QLabel *label_Work_Point;
    QLineEdit *Work_Point;
    QLabel *label_Work_StartTime;
    QLineEdit *Work_StartTime;
    QLabel *label_Work_CarType;
    QLineEdit *Work_CarType;
    QHBoxLayout *horizontalLayout_48;
    QGroupBox *groupBox_FrontCamView;
    QVBoxLayout *verticalLayout_FrontCamView;
    QLabel *label_FrontCamera;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_19;
    c_Magic_Lidar_View *widget_LidarView;
    QGroupBox *groupBox_RearCamView;
    QVBoxLayout *verticalLayout_RearCamView;
    QLabel *label_RearCamera;
    QHBoxLayout *Work_TopRow;
    QGroupBox *Work_ServerGroup;
    QHBoxLayout *Work_ServerLayout;
    QLabel *label_Work_Client;
    c_Fr_Light *Work_Client_Light;
    QLabel *label_Work_Listen;
    c_Fr_Light *Work_Listen_Light;
    QLabel *label_Work_ConnNum;
    QLineEdit *Work_Client_Num;
    QLabel *label_Work_Port;
    QLineEdit *Work_Port;
    QLabel *label_Work_Checksum;
    QLineEdit *Work_Checksum;
    QHBoxLayout *Work_FlowRow;
    QGroupBox *Work_FlowGroup;
    QHBoxLayout *Work_FlowLayout;
    QLabel *label_Work_FlowState;
    QLineEdit *Work_Flow_State;
    QLineEdit *Work_Flow_Desc;
    QPushButton *Work_Btn_Start;
    QPushButton *Work_Btn_Pause;
    QPushButton *Work_Btn_Resume;
    QPushButton *Work_Btn_Cancel;
    QPushButton *Work_Btn_Stop;
    QPushButton *Work_Btn_Home;
    QHBoxLayout *Work_BottomRow;
    QGroupBox *Work_LogGroup;
    QVBoxLayout *Work_LogLayout;
    QTextEdit *Work_List;
    QGroupBox *Work_AlarmGroup;
    QVBoxLayout *Work_AlarmLayout;
    QTextEdit *Work_Alarm;
    QHBoxLayout *Work_StatusRow;
    QGroupBox *Work_SubsysGroup;
    QHBoxLayout *Work_SubsysLayout;
    QLabel *label_Work_Arm;
    c_Fr_Light *Work_Arm_Light;
    QLabel *label_Work_Chassis;
    c_Fr_Light *Work_Chassis_Light;
    QLabel *label_Work_Camera;
    c_Fr_Light *Work_Camera_Light;
    QLabel *label_Work_Server;
    c_Fr_Light *Work_Server_Light;
    QLabel *label_Work_Checksum_2;
    QLineEdit *EMIS_Url;
    QPushButton *actualStartTime;
    QPushButton *precisScanStartTime;
    QPushButton *precisScanEndTime;
    QSpacerItem *Work_SubsysSpacer;
    QWidget *Magic_Widget;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_14;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_Connect;
    QGridLayout *gridLayout_2;
    QLabel *label_IP;
    QLineEdit *Magic_IP;
    QLabel *label_Port;
    QLineEdit *Magic_Port;
    QLabel *label_User;
    QLineEdit *Magic_User;
    QLabel *label_Pass;
    QLineEdit *Magic_Pass;
    QPushButton *pushButton_Connect;
    QPushButton *pushButton_Login;
    QPushButton *pushButton_Disconnect;
    QLabel *label_MAC;
    QLineEdit *lineEdit_MAC;
    QGroupBox *groupBox_Pose;
    QGridLayout *gridLayout_11;
    QLabel *label_WX;
    QLabel *label_WY;
    QLabel *label_Angle;
    QLineEdit *lineEdit_GridX;
    QLineEdit *lineEdit_WX;
    QLineEdit *lineEdit_GridY;
    QLineEdit *lineEdit_Battery;
    QLabel *label_NavVer;
    QLabel *label_GridX;
    QLineEdit *lineEdit_WY;
    QLineEdit *lineEdit_AntiCollision;
    QLabel *label_ErrorCode;
    QLineEdit *lineEdit_CurrentMap;
    QLineEdit *lineEdit_Angle;
    QLabel *label_AntiCollision;
    QLabel *label_Battery;
    QLabel *label_WorkMode;
    QLineEdit *lineEdit_WorkMode;
    QLineEdit *lineEdit_ChassisVer;
    QLabel *label_ChassisVer;
    QLabel *label_GridY;
    QLineEdit *lineEdit_ErrorCode;
    QLineEdit *lineEdit_NavVer;
    QLabel *label_CurrentMap;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_ConnStatus;
    c_Fr_Light *light_Connected;
    QLabel *label_Ready;
    c_Fr_Light *light_Ready;
    QLabel *label_Localized;
    c_Fr_Light *light_Localized;
    QLabel *label_Charging;
    c_Fr_Light *light_Charging;
    QLabel *label_Task;
    c_Fr_Light *light_Task;
    QLabel *label_Lidar;
    c_Fr_Light *light_Lidar;
    QLabel *label_I;
    c_Fr_Light *light_IMU;
    QLabel *label_O;
    c_Fr_Light *light_Odom;
    QLabel *label_Cam;
    c_Fr_Light *light_Camera;
    QLabel *label_Estop;
    c_Fr_Light *light_Estop;
    QTabWidget *tabWidget_Magic;
    QWidget *tab_Map;
    QGridLayout *gridLayout_13;
    QGroupBox *groupBox_FixedNav;
    QHBoxLayout *horizontalLayout_FixedNav;
    QLabel *label_FixedX;
    QDoubleSpinBox *spin_FixedX;
    QLabel *label_FixedY;
    QDoubleSpinBox *spin_FixedY;
    QLabel *label_FixedAngle;
    QDoubleSpinBox *spin_FixedAngle;
    QPushButton *btn_FixedNavStart;
    QPushButton *btn_FixedNavLoop;
    QGroupBox *groupBox_InitPose;
    QHBoxLayout *horizontalLayout_InitPose;
    QComboBox *combo_InitPoint;
    QPushButton *btn_DynamicInit;
    QPushButton *btn_StaticInit;
    QPushButton *btn_GridInit;
    QPushButton *btn_InitResult;
    QGroupBox *groupBox_TaskControl;
    QHBoxLayout *horizontalLayout_TaskControl;
    QPushButton *btn_StartTask;
    QPushButton *btn_LoopStart;
    QPushButton *btn_PauseTask;
    QPushButton *btn_ResumeTask;
    QPushButton *btn_StopTask;
    QPushButton *btn_GetTaskLog;
    QLineEdit *lineEdit_TaskID;
    QGroupBox *groupBox_TaskSelect;
    QHBoxLayout *horizontalLayout_TaskSelect;
    QLabel *label_TaskType;
    QComboBox *combo_TaskType;
    QLabel *label_TaskName;
    QComboBox *combo_TaskName;
    QPushButton *btn_RefreshNavPoints;
    QLabel *label_LoopCount;
    QSpinBox *spin_LoopCount;
    QHBoxLayout *horizontalLayout_MapOps1;
    QComboBox *comboBox_MapList;
    QPushButton *btn_RefreshToken;
    QPushButton *btn_RefreshMapList;
    QPushButton *btn_SwitchMap;
    QGroupBox *groupBox_TaskStatus;
    QHBoxLayout *horizontalLayout_TaskStatus;
    QLabel *label_TaskStatusText;
    QProgressBar *progress_Task;
    QLabel *label_RemainTime;
    QLabel *label_RemainTimeValue;
    QLabel *label_LoopInfo;
    QWidget *tab_PathPoint;
    QVBoxLayout *verticalLayout_PathPoint;
    QTableWidget *table_NavPoints;
    QWidget *tab_System;
    QVBoxLayout *verticalLayout_System;
    QGroupBox *groupBox_Speed;
    QGridLayout *gridLayout_Speed;
    QLabel *label_GoalSpeed;
    QDoubleSpinBox *spin_GoalSpeed;
    QLabel *label_GraphSpeed;
    QDoubleSpinBox *spin_GraphSpeed;
    QLabel *label_RecordSpeed;
    QDoubleSpinBox *spin_RecordSpeed;
    QPushButton *btn_UpdateSpeed;
    QGroupBox *groupBox_Charge;
    QHBoxLayout *horizontalLayout_Charge;
    QLabel *label_ChargePoint;
    QLineEdit *lineEdit_ChargePoint;
    QPushButton *btn_StartRecharge;
    QPushButton *btn_DisRecharge;
    QPushButton *btn_PauseRecharge;
    QPushButton *btn_ResumeRecharge;
    QPushButton *btn_CancelRecharge;
    QLabel *label_ChargeStatus;
    QLabel *lbl_ChargeStatus;
    QGroupBox *groupBox_Move;
    QGridLayout *gridLayout_Move;
    QGroupBox *groupBox_SpeedControl;
    QHBoxLayout *horizontalLayout_SpeedControl;
    QLabel *label_LinearSpeed;
    QDoubleSpinBox *spin_LinearSpeed;
    QLabel *label_AngularSpeed;
    QDoubleSpinBox *spin_AngularSpeed;
    QGroupBox *groupBox_MoveButtons;
    QHBoxLayout *horizontalLayout_MoveButtons;
    QPushButton *btn_MoveForward;
    QPushButton *btn_MoveBackward;
    QPushButton *btn_TurnLeft;
    QPushButton *btn_TurnRight;
    QPushButton *btn_StopMove;
    QGroupBox *groupBox_MoveParams;
    QHBoxLayout *horizontalLayout_MoveParams;
    QLabel *label_MoveMode;
    QComboBox *combo_MoveMode;
    QLabel *label_MoveTarget;
    QDoubleSpinBox *spin_MoveTarget;
    QPushButton *btn_ExecuteMoveParams;
    QPushButton *btn_CancelMoveParams;
    QWidget *tab_Sensor;
    QGridLayout *gridLayout_18;
    QGroupBox *groupBox_IMU;
    QHBoxLayout *horizontalLayout_IMU;
    QLabel *label_IMU_AVX;
    QLineEdit *lineEdit_IMU_AVX;
    QLabel *label_IMU_AVY;
    QLineEdit *lineEdit_IMU_AVY;
    QLabel *label_IMU_AVZ;
    QLineEdit *lineEdit_IMU_AVZ;
    QLabel *label_IMU_LAX;
    QLineEdit *lineEdit_IMU_LAX;
    QLabel *label_IMU_LAY;
    QLineEdit *lineEdit_IMU_LAY;
    QLabel *label_IMU_LAZ;
    QLineEdit *lineEdit_IMU_LAZ;
    QGroupBox *groupBox_Odom;
    QHBoxLayout *horizontalLayout_Odom;
    QLabel *label_Odom_LX;
    QLineEdit *lineEdit_Odom_LX;
    QLabel *label_Odom_LY;
    QLineEdit *lineEdit_Odom_LY;
    QLabel *label_Odom_LZ;
    QLineEdit *lineEdit_Odom_LZ;
    QLabel *label_Odom_AX;
    QLineEdit *lineEdit_Odom_AX;
    QLabel *label_Odom_AY;
    QLineEdit *lineEdit_Odom_AY;
    QLabel *label_Odom_AZ;
    QLineEdit *lineEdit_Odom_AZ;
    QGroupBox *groupBox_GPS;
    QHBoxLayout *horizontalLayout_GPS;
    QLabel *label_GPS_Lat;
    QLineEdit *lineEdit_GPS_Lat;
    QLabel *label_GPS_Lon;
    QLineEdit *lineEdit_GPS_Lon;
    QLabel *label_GPS_Alt;
    QLineEdit *lineEdit_GPS_Alt;
    QGroupBox *groupBox_Ultrasonic;
    QGridLayout *gridLayout_Ultrasonic;
    QLabel *lbl_US_FL;
    QLineEdit *lineEdit_US_FL;
    QLabel *lbl_US_FR;
    QLineEdit *lineEdit_US_FR;
    QLabel *lbl_US_RL;
    QLineEdit *lineEdit_US_RL;
    QLabel *lbl_US_RR;
    QLineEdit *lineEdit_US_RR;
    QLabel *lbl_US_LF;
    QLineEdit *lineEdit_US_LF;
    QLabel *lbl_US_LR;
    QLineEdit *lineEdit_US_LR;
    QLabel *lbl_US_RF;
    QLineEdit *lineEdit_US_RF;
    QLabel *lbl_US_RR2;
    QLineEdit *lineEdit_US_RR2;
    QGroupBox *groupBox_CameraControl;
    QGridLayout *gridLayout_CameraControl;
    QLabel *label_FrontCamCtrl;
    QPushButton *btn_GetFrontRGB;
    QPushButton *btn_GetFrontDepth;
    QPushButton *btn_GetFrontPointCloud;
    QLabel *label_RearCamCtrl;
    QPushButton *btn_GetRearRGB;
    QPushButton *btn_GetRearDepth;
    QPushButton *btn_GetRearPointCloud;
    QGroupBox *groupBox_LogoLog;
    QVBoxLayout *verticalLayout_LogoLog;
    QHBoxLayout *horizontalLayout_Logo;
    QPushButton *btn_GetLogoBase64;
    QPushButton *btn_GetBackgroundBase64;
    QHBoxLayout *horizontalLayout_LogMgmt;
    QLabel *label_LogType;
    QComboBox *combo_LogType;
    QLabel *label_LogFileName;
    QLineEdit *lineEdit_LogFileName;
    QPushButton *btn_DownLogs;
    QPushButton *btn_DropLogs;
    QGroupBox *groupBox_MapList;
    QGridLayout *gridLayout_16;
    c_Magic_Map_View *widget_MapView;
    QGroupBox *groupBox_Log;
    QVBoxLayout *verticalLayout_Log;
    QTextEdit *Magic_Log;
    QStatusBar *Status_Bar;

    void setupUi(QMainWindow *Robot_App_Widget)
    {
        if (Robot_App_Widget->objectName().isEmpty())
            Robot_App_Widget->setObjectName(QString::fromUtf8("Robot_App_Widget"));
        Robot_App_Widget->setWindowModality(Qt::WindowModal);
        Robot_App_Widget->resize(1507, 897);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Robot_App_Widget->sizePolicy().hasHeightForWidth());
        Robot_App_Widget->setSizePolicy(sizePolicy);
        Robot_App_Widget->setMinimumSize(QSize(1280, 700));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Logo/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Robot_App_Widget->setWindowIcon(icon);
        centralWidget = new QWidget(Robot_App_Widget);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_15 = new QGridLayout(centralWidget);
        gridLayout_15->setSpacing(8);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_15->setContentsMargins(8, 8, 8, 8);
        widget_10 = new QWidget(centralWidget);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_10->sizePolicy().hasHeightForWidth());
        widget_10->setSizePolicy(sizePolicy1);
        widget_10->setMinimumSize(QSize(160, 0));
        widget_10->setMaximumSize(QSize(170, 16777215));
        gridLayout_94 = new QGridLayout(widget_10);
        gridLayout_94->setSpacing(6);
        gridLayout_94->setContentsMargins(11, 11, 11, 11);
        gridLayout_94->setObjectName(QString::fromUtf8("gridLayout_94"));
        groupBox_5 = new QGroupBox(widget_10);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy2);
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setVerticalSpacing(6);
        gridLayout_4->setContentsMargins(8, 8, 8, 8);
        Show_Work_Widget = new QPushButton(groupBox_5);
        Show_Work_Widget->setObjectName(QString::fromUtf8("Show_Work_Widget"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(Show_Work_Widget->sizePolicy().hasHeightForWidth());
        Show_Work_Widget->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(Show_Work_Widget, 0, 0, 1, 1);

        Show_IO_Widget = new QPushButton(groupBox_5);
        Show_IO_Widget->setObjectName(QString::fromUtf8("Show_IO_Widget"));
        sizePolicy3.setHeightForWidth(Show_IO_Widget->sizePolicy().hasHeightForWidth());
        Show_IO_Widget->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(Show_IO_Widget, 4, 0, 1, 1);

        Show_CGXi_Widget = new QPushButton(groupBox_5);
        Show_CGXi_Widget->setObjectName(QString::fromUtf8("Show_CGXi_Widget"));
        sizePolicy3.setHeightForWidth(Show_CGXi_Widget->sizePolicy().hasHeightForWidth());
        Show_CGXi_Widget->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(Show_CGXi_Widget, 2, 0, 1, 1);

        Show_Pre_Scan_120_Widget = new QPushButton(groupBox_5);
        Show_Pre_Scan_120_Widget->setObjectName(QString::fromUtf8("Show_Pre_Scan_120_Widget"));
        sizePolicy3.setHeightForWidth(Show_Pre_Scan_120_Widget->sizePolicy().hasHeightForWidth());
        Show_Pre_Scan_120_Widget->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(Show_Pre_Scan_120_Widget, 3, 0, 1, 1);

        Show_Magic_Widget = new QPushButton(groupBox_5);
        Show_Magic_Widget->setObjectName(QString::fromUtf8("Show_Magic_Widget"));
        sizePolicy3.setHeightForWidth(Show_Magic_Widget->sizePolicy().hasHeightForWidth());
        Show_Magic_Widget->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(Show_Magic_Widget, 1, 0, 1, 1);


        gridLayout_94->addWidget(groupBox_5, 1, 0, 1, 1);


        gridLayout_15->addWidget(widget_10, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy4);
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        stackedWidget->setLineWidth(1);
        CGXi_Widget = new QWidget();
        CGXi_Widget->setObjectName(QString::fromUtf8("CGXi_Widget"));
        gridLayout_3 = new QGridLayout(CGXi_Widget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_3 = new QGroupBox(CGXi_Widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_9 = new QGridLayout(groupBox_3);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_ip = new QLabel(groupBox_3);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_ip->sizePolicy().hasHeightForWidth());
        label_ip->setSizePolicy(sizePolicy5);

        horizontalLayout_4->addWidget(label_ip);

        CGXi_IP = new QLineEdit(groupBox_3);
        CGXi_IP->setObjectName(QString::fromUtf8("CGXi_IP"));
        sizePolicy.setHeightForWidth(CGXi_IP->sizePolicy().hasHeightForWidth());
        CGXi_IP->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(CGXi_IP);

        label_port = new QLabel(groupBox_3);
        label_port->setObjectName(QString::fromUtf8("label_port"));
        sizePolicy5.setHeightForWidth(label_port->sizePolicy().hasHeightForWidth());
        label_port->setSizePolicy(sizePolicy5);

        horizontalLayout_4->addWidget(label_port);

        CGXi_Port = new QLineEdit(groupBox_3);
        CGXi_Port->setObjectName(QString::fromUtf8("CGXi_Port"));
        sizePolicy.setHeightForWidth(CGXi_Port->sizePolicy().hasHeightForWidth());
        CGXi_Port->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(CGXi_Port);

        CGXi_Connect = new QPushButton(groupBox_3);
        CGXi_Connect->setObjectName(QString::fromUtf8("CGXi_Connect"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(CGXi_Connect->sizePolicy().hasHeightForWidth());
        CGXi_Connect->setSizePolicy(sizePolicy6);

        horizontalLayout_4->addWidget(CGXi_Connect);

        CGXi_Disconnect = new QPushButton(groupBox_3);
        CGXi_Disconnect->setObjectName(QString::fromUtf8("CGXi_Disconnect"));
        sizePolicy6.setHeightForWidth(CGXi_Disconnect->sizePolicy().hasHeightForWidth());
        CGXi_Disconnect->setSizePolicy(sizePolicy6);

        horizontalLayout_4->addWidget(CGXi_Disconnect);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy5.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy5);

        horizontalLayout_4->addWidget(label_3);

        CGXi_Connected = new c_Fr_Light(groupBox_3);
        CGXi_Connected->setObjectName(QString::fromUtf8("CGXi_Connected"));
        sizePolicy5.setHeightForWidth(CGXi_Connected->sizePolicy().hasHeightForWidth());
        CGXi_Connected->setSizePolicy(sizePolicy5);
        CGXi_Connected->setMinimumSize(QSize(20, 20));

        horizontalLayout_4->addWidget(CGXi_Connected);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy5.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy5);

        horizontalLayout_4->addWidget(label_4);

        CGXi_Ready = new c_Fr_Light(groupBox_3);
        CGXi_Ready->setObjectName(QString::fromUtf8("CGXi_Ready"));
        sizePolicy5.setHeightForWidth(CGXi_Ready->sizePolicy().hasHeightForWidth());
        CGXi_Ready->setSizePolicy(sizePolicy5);
        CGXi_Ready->setMinimumSize(QSize(20, 20));

        horizontalLayout_4->addWidget(CGXi_Ready);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy5.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy5);

        horizontalLayout_4->addWidget(label_10);

        CGXi_auto_indicator = new c_Fr_Light(groupBox_3);
        CGXi_auto_indicator->setObjectName(QString::fromUtf8("CGXi_auto_indicator"));
        sizePolicy5.setHeightForWidth(CGXi_auto_indicator->sizePolicy().hasHeightForWidth());
        CGXi_auto_indicator->setSizePolicy(sizePolicy5);
        CGXi_auto_indicator->setMinimumSize(QSize(20, 20));

        horizontalLayout_4->addWidget(CGXi_auto_indicator);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy5.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy5);

        horizontalLayout_5->addWidget(label_5);

        CGXi_Version = new QLineEdit(groupBox_3);
        CGXi_Version->setObjectName(QString::fromUtf8("CGXi_Version"));
        sizePolicy.setHeightForWidth(CGXi_Version->sizePolicy().hasHeightForWidth());
        CGXi_Version->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(CGXi_Version);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy5.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy5);

        horizontalLayout_5->addWidget(label_6);

        CGXi_Robot_Mode = new QLineEdit(groupBox_3);
        CGXi_Robot_Mode->setObjectName(QString::fromUtf8("CGXi_Robot_Mode"));
        sizePolicy.setHeightForWidth(CGXi_Robot_Mode->sizePolicy().hasHeightForWidth());
        CGXi_Robot_Mode->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(CGXi_Robot_Mode);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy5.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy5);

        horizontalLayout_5->addWidget(label_7);

        CGXi_Error_Code = new QLineEdit(groupBox_3);
        CGXi_Error_Code->setObjectName(QString::fromUtf8("CGXi_Error_Code"));
        sizePolicy.setHeightForWidth(CGXi_Error_Code->sizePolicy().hasHeightForWidth());
        CGXi_Error_Code->setSizePolicy(sizePolicy);
        CGXi_Error_Code->setMinimumSize(QSize(150, 0));

        horizontalLayout_5->addWidget(CGXi_Error_Code);

        label_speed = new QLabel(groupBox_3);
        label_speed->setObjectName(QString::fromUtf8("label_speed"));
        sizePolicy5.setHeightForWidth(label_speed->sizePolicy().hasHeightForWidth());
        label_speed->setSizePolicy(sizePolicy5);

        horizontalLayout_5->addWidget(label_speed);

        CGXi_Global_Speed = new QLineEdit(groupBox_3);
        CGXi_Global_Speed->setObjectName(QString::fromUtf8("CGXi_Global_Speed"));
        sizePolicy.setHeightForWidth(CGXi_Global_Speed->sizePolicy().hasHeightForWidth());
        CGXi_Global_Speed->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(CGXi_Global_Speed);


        verticalLayout_2->addLayout(horizontalLayout_5);

        groupBox_6 = new QGroupBox(groupBox_3);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        sizePolicy.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy);
        gridLayout_7 = new QGridLayout(groupBox_6);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        Coils_1003 = new QPushButton(groupBox_6);
        Coils_1003->setObjectName(QString::fromUtf8("Coils_1003"));
        QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(Coils_1003->sizePolicy().hasHeightForWidth());
        Coils_1003->setSizePolicy(sizePolicy7);

        gridLayout_7->addWidget(Coils_1003, 0, 3, 1, 1);

        Coils_1007 = new QPushButton(groupBox_6);
        Coils_1007->setObjectName(QString::fromUtf8("Coils_1007"));
        sizePolicy7.setHeightForWidth(Coils_1007->sizePolicy().hasHeightForWidth());
        Coils_1007->setSizePolicy(sizePolicy7);

        gridLayout_7->addWidget(Coils_1007, 1, 3, 1, 1);

        Coils_1001 = new QPushButton(groupBox_6);
        Coils_1001->setObjectName(QString::fromUtf8("Coils_1001"));
        sizePolicy7.setHeightForWidth(Coils_1001->sizePolicy().hasHeightForWidth());
        Coils_1001->setSizePolicy(sizePolicy7);

        gridLayout_7->addWidget(Coils_1001, 0, 1, 1, 1);

        Coils_1004 = new QPushButton(groupBox_6);
        Coils_1004->setObjectName(QString::fromUtf8("Coils_1004"));
        sizePolicy7.setHeightForWidth(Coils_1004->sizePolicy().hasHeightForWidth());
        Coils_1004->setSizePolicy(sizePolicy7);

        gridLayout_7->addWidget(Coils_1004, 1, 0, 1, 1);

        Coils_1005 = new QPushButton(groupBox_6);
        Coils_1005->setObjectName(QString::fromUtf8("Coils_1005"));
        sizePolicy7.setHeightForWidth(Coils_1005->sizePolicy().hasHeightForWidth());
        Coils_1005->setSizePolicy(sizePolicy7);

        gridLayout_7->addWidget(Coils_1005, 1, 1, 1, 1);

        Coils_1006 = new QPushButton(groupBox_6);
        Coils_1006->setObjectName(QString::fromUtf8("Coils_1006"));
        sizePolicy7.setHeightForWidth(Coils_1006->sizePolicy().hasHeightForWidth());
        Coils_1006->setSizePolicy(sizePolicy7);

        gridLayout_7->addWidget(Coils_1006, 1, 2, 1, 1);

        Coils_1000 = new QPushButton(groupBox_6);
        Coils_1000->setObjectName(QString::fromUtf8("Coils_1000"));
        sizePolicy7.setHeightForWidth(Coils_1000->sizePolicy().hasHeightForWidth());
        Coils_1000->setSizePolicy(sizePolicy7);

        gridLayout_7->addWidget(Coils_1000, 0, 0, 1, 1);

        Coils_1002 = new QPushButton(groupBox_6);
        Coils_1002->setObjectName(QString::fromUtf8("Coils_1002"));
        sizePolicy7.setHeightForWidth(Coils_1002->sizePolicy().hasHeightForWidth());
        Coils_1002->setSizePolicy(sizePolicy7);

        gridLayout_7->addWidget(Coils_1002, 0, 2, 1, 1);


        verticalLayout_2->addWidget(groupBox_6);

        groupBox_DO_3 = new QGroupBox(groupBox_3);
        groupBox_DO_3->setObjectName(QString::fromUtf8("groupBox_DO_3"));
        sizePolicy.setHeightForWidth(groupBox_DO_3->sizePolicy().hasHeightForWidth());
        groupBox_DO_3->setSizePolicy(sizePolicy);
        gridLayout_12 = new QGridLayout(groupBox_DO_3);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        l_do_h3_6 = new QLabel(groupBox_DO_3);
        l_do_h3_6->setObjectName(QString::fromUtf8("l_do_h3_6"));
        sizePolicy.setHeightForWidth(l_do_h3_6->sizePolicy().hasHeightForWidth());
        l_do_h3_6->setSizePolicy(sizePolicy);
        l_do_h3_6->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h3_6, 0, 14, 1, 1);

        CGXi_CO0_State = new c_Fr_Light(groupBox_DO_3);
        CGXi_CO0_State->setObjectName(QString::fromUtf8("CGXi_CO0_State"));
        QSizePolicy sizePolicy8(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(CGXi_CO0_State->sizePolicy().hasHeightForWidth());
        CGXi_CO0_State->setSizePolicy(sizePolicy8);
        CGXi_CO0_State->setMinimumSize(QSize(20, 20));

        gridLayout_12->addWidget(CGXi_CO0_State, 1, 1, 1, 1);

        CGXi_CO0_Set = new QPushButton(groupBox_DO_3);
        CGXi_CO0_Set->setObjectName(QString::fromUtf8("CGXi_CO0_Set"));

        gridLayout_12->addWidget(CGXi_CO0_Set, 1, 2, 1, 1);

        l_do_h2_5 = new QLabel(groupBox_DO_3);
        l_do_h2_5->setObjectName(QString::fromUtf8("l_do_h2_5"));
        sizePolicy.setHeightForWidth(l_do_h2_5->sizePolicy().hasHeightForWidth());
        l_do_h2_5->setSizePolicy(sizePolicy);
        l_do_h2_5->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h2_5, 0, 9, 1, 1);

        l_do_h4_3 = new QLabel(groupBox_DO_3);
        l_do_h4_3->setObjectName(QString::fromUtf8("l_do_h4_3"));
        sizePolicy.setHeightForWidth(l_do_h4_3->sizePolicy().hasHeightForWidth());
        l_do_h4_3->setSizePolicy(sizePolicy);
        l_do_h4_3->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h4_3, 0, 3, 1, 1);

        l_do_h1_6 = new QLabel(groupBox_DO_3);
        l_do_h1_6->setObjectName(QString::fromUtf8("l_do_h1_6"));
        sizePolicy.setHeightForWidth(l_do_h1_6->sizePolicy().hasHeightForWidth());
        l_do_h1_6->setSizePolicy(sizePolicy);
        l_do_h1_6->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h1_6, 0, 12, 1, 1);

        CGXi_CO5_State = new c_Fr_Light(groupBox_DO_3);
        CGXi_CO5_State->setObjectName(QString::fromUtf8("CGXi_CO5_State"));
        sizePolicy8.setHeightForWidth(CGXi_CO5_State->sizePolicy().hasHeightForWidth());
        CGXi_CO5_State->setSizePolicy(sizePolicy8);
        CGXi_CO5_State->setMinimumSize(QSize(20, 20));

        gridLayout_12->addWidget(CGXi_CO5_State, 2, 5, 1, 1);

        l_do_h3_5 = new QLabel(groupBox_DO_3);
        l_do_h3_5->setObjectName(QString::fromUtf8("l_do_h3_5"));
        sizePolicy.setHeightForWidth(l_do_h3_5->sizePolicy().hasHeightForWidth());
        l_do_h3_5->setSizePolicy(sizePolicy);
        l_do_h3_5->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h3_5, 0, 10, 1, 1);

        l_do_h4_5 = new QLabel(groupBox_DO_3);
        l_do_h4_5->setObjectName(QString::fromUtf8("l_do_h4_5"));
        sizePolicy.setHeightForWidth(l_do_h4_5->sizePolicy().hasHeightForWidth());
        l_do_h4_5->setSizePolicy(sizePolicy);
        l_do_h4_5->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h4_5, 0, 11, 1, 1);

        label_DO1_8 = new QLabel(groupBox_DO_3);
        label_DO1_8->setObjectName(QString::fromUtf8("label_DO1_8"));
        sizePolicy8.setHeightForWidth(label_DO1_8->sizePolicy().hasHeightForWidth());
        label_DO1_8->setSizePolicy(sizePolicy8);
        label_DO1_8->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_DO1_8, 2, 4, 1, 1);

        CGXi_CO5_Reset = new QPushButton(groupBox_DO_3);
        CGXi_CO5_Reset->setObjectName(QString::fromUtf8("CGXi_CO5_Reset"));

        gridLayout_12->addWidget(CGXi_CO5_Reset, 2, 7, 1, 1);

        l_do_h3_4 = new QLabel(groupBox_DO_3);
        l_do_h3_4->setObjectName(QString::fromUtf8("l_do_h3_4"));
        sizePolicy.setHeightForWidth(l_do_h3_4->sizePolicy().hasHeightForWidth());
        l_do_h3_4->setSizePolicy(sizePolicy);
        l_do_h3_4->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h3_4, 0, 6, 1, 1);

        CGXi_CO0_Reset = new QPushButton(groupBox_DO_3);
        CGXi_CO0_Reset->setObjectName(QString::fromUtf8("CGXi_CO0_Reset"));

        gridLayout_12->addWidget(CGXi_CO0_Reset, 1, 3, 1, 1);

        l_do_h1_5 = new QLabel(groupBox_DO_3);
        l_do_h1_5->setObjectName(QString::fromUtf8("l_do_h1_5"));
        sizePolicy.setHeightForWidth(l_do_h1_5->sizePolicy().hasHeightForWidth());
        l_do_h1_5->setSizePolicy(sizePolicy);
        l_do_h1_5->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h1_5, 0, 8, 1, 1);

        l_do_h2_3 = new QLabel(groupBox_DO_3);
        l_do_h2_3->setObjectName(QString::fromUtf8("l_do_h2_3"));
        sizePolicy.setHeightForWidth(l_do_h2_3->sizePolicy().hasHeightForWidth());
        l_do_h2_3->setSizePolicy(sizePolicy);
        l_do_h2_3->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h2_3, 0, 1, 1, 1);

        l_do_h1_4 = new QLabel(groupBox_DO_3);
        l_do_h1_4->setObjectName(QString::fromUtf8("l_do_h1_4"));
        sizePolicy.setHeightForWidth(l_do_h1_4->sizePolicy().hasHeightForWidth());
        l_do_h1_4->setSizePolicy(sizePolicy);
        l_do_h1_4->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h1_4, 0, 4, 1, 1);

        l_do_h2_6 = new QLabel(groupBox_DO_3);
        l_do_h2_6->setObjectName(QString::fromUtf8("l_do_h2_6"));
        sizePolicy.setHeightForWidth(l_do_h2_6->sizePolicy().hasHeightForWidth());
        l_do_h2_6->setSizePolicy(sizePolicy);
        l_do_h2_6->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h2_6, 0, 13, 1, 1);

        l_do_h1_3 = new QLabel(groupBox_DO_3);
        l_do_h1_3->setObjectName(QString::fromUtf8("l_do_h1_3"));
        sizePolicy.setHeightForWidth(l_do_h1_3->sizePolicy().hasHeightForWidth());
        l_do_h1_3->setSizePolicy(sizePolicy);
        l_do_h1_3->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h1_3, 0, 0, 1, 1);

        CGXi_CO5_Set = new QPushButton(groupBox_DO_3);
        CGXi_CO5_Set->setObjectName(QString::fromUtf8("CGXi_CO5_Set"));

        gridLayout_12->addWidget(CGXi_CO5_Set, 2, 6, 1, 1);

        l_do_h2_4 = new QLabel(groupBox_DO_3);
        l_do_h2_4->setObjectName(QString::fromUtf8("l_do_h2_4"));
        sizePolicy.setHeightForWidth(l_do_h2_4->sizePolicy().hasHeightForWidth());
        l_do_h2_4->setSizePolicy(sizePolicy);
        l_do_h2_4->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h2_4, 0, 5, 1, 1);

        l_do_h3_3 = new QLabel(groupBox_DO_3);
        l_do_h3_3->setObjectName(QString::fromUtf8("l_do_h3_3"));
        sizePolicy.setHeightForWidth(l_do_h3_3->sizePolicy().hasHeightForWidth());
        l_do_h3_3->setSizePolicy(sizePolicy);
        l_do_h3_3->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h3_3, 0, 2, 1, 1);

        l_do_h4_4 = new QLabel(groupBox_DO_3);
        l_do_h4_4->setObjectName(QString::fromUtf8("l_do_h4_4"));
        sizePolicy.setHeightForWidth(l_do_h4_4->sizePolicy().hasHeightForWidth());
        l_do_h4_4->setSizePolicy(sizePolicy);
        l_do_h4_4->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h4_4, 0, 7, 1, 1);

        label_DO0_3 = new QLabel(groupBox_DO_3);
        label_DO0_3->setObjectName(QString::fromUtf8("label_DO0_3"));
        sizePolicy8.setHeightForWidth(label_DO0_3->sizePolicy().hasHeightForWidth());
        label_DO0_3->setSizePolicy(sizePolicy8);
        label_DO0_3->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_DO0_3, 1, 0, 1, 1);

        l_do_h4_6 = new QLabel(groupBox_DO_3);
        l_do_h4_6->setObjectName(QString::fromUtf8("l_do_h4_6"));
        sizePolicy.setHeightForWidth(l_do_h4_6->sizePolicy().hasHeightForWidth());
        l_do_h4_6->setSizePolicy(sizePolicy);
        l_do_h4_6->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(l_do_h4_6, 0, 15, 1, 1);

        label_DO1_7 = new QLabel(groupBox_DO_3);
        label_DO1_7->setObjectName(QString::fromUtf8("label_DO1_7"));
        sizePolicy8.setHeightForWidth(label_DO1_7->sizePolicy().hasHeightForWidth());
        label_DO1_7->setSizePolicy(sizePolicy8);
        label_DO1_7->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_DO1_7, 1, 4, 1, 1);

        CGXi_CO1_State = new c_Fr_Light(groupBox_DO_3);
        CGXi_CO1_State->setObjectName(QString::fromUtf8("CGXi_CO1_State"));
        sizePolicy8.setHeightForWidth(CGXi_CO1_State->sizePolicy().hasHeightForWidth());
        CGXi_CO1_State->setSizePolicy(sizePolicy8);
        CGXi_CO1_State->setMinimumSize(QSize(20, 20));

        gridLayout_12->addWidget(CGXi_CO1_State, 1, 5, 1, 1);

        CGXi_CO1_Set = new QPushButton(groupBox_DO_3);
        CGXi_CO1_Set->setObjectName(QString::fromUtf8("CGXi_CO1_Set"));

        gridLayout_12->addWidget(CGXi_CO1_Set, 1, 6, 1, 1);

        CGXi_CO1_Reset = new QPushButton(groupBox_DO_3);
        CGXi_CO1_Reset->setObjectName(QString::fromUtf8("CGXi_CO1_Reset"));

        gridLayout_12->addWidget(CGXi_CO1_Reset, 1, 7, 1, 1);

        label_DO1_9 = new QLabel(groupBox_DO_3);
        label_DO1_9->setObjectName(QString::fromUtf8("label_DO1_9"));
        sizePolicy8.setHeightForWidth(label_DO1_9->sizePolicy().hasHeightForWidth());
        label_DO1_9->setSizePolicy(sizePolicy8);
        label_DO1_9->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_DO1_9, 1, 8, 1, 1);

        CGXi_CO2_State = new c_Fr_Light(groupBox_DO_3);
        CGXi_CO2_State->setObjectName(QString::fromUtf8("CGXi_CO2_State"));
        sizePolicy8.setHeightForWidth(CGXi_CO2_State->sizePolicy().hasHeightForWidth());
        CGXi_CO2_State->setSizePolicy(sizePolicy8);
        CGXi_CO2_State->setMinimumSize(QSize(20, 20));

        gridLayout_12->addWidget(CGXi_CO2_State, 1, 9, 1, 1);

        CGXi_CO2_Set = new QPushButton(groupBox_DO_3);
        CGXi_CO2_Set->setObjectName(QString::fromUtf8("CGXi_CO2_Set"));

        gridLayout_12->addWidget(CGXi_CO2_Set, 1, 10, 1, 1);

        CGXi_CO2_Reset = new QPushButton(groupBox_DO_3);
        CGXi_CO2_Reset->setObjectName(QString::fromUtf8("CGXi_CO2_Reset"));

        gridLayout_12->addWidget(CGXi_CO2_Reset, 1, 11, 1, 1);

        label_DO0_4 = new QLabel(groupBox_DO_3);
        label_DO0_4->setObjectName(QString::fromUtf8("label_DO0_4"));
        sizePolicy8.setHeightForWidth(label_DO0_4->sizePolicy().hasHeightForWidth());
        label_DO0_4->setSizePolicy(sizePolicy8);
        label_DO0_4->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_DO0_4, 2, 0, 1, 1);

        CGXi_CO4_State = new c_Fr_Light(groupBox_DO_3);
        CGXi_CO4_State->setObjectName(QString::fromUtf8("CGXi_CO4_State"));
        sizePolicy8.setHeightForWidth(CGXi_CO4_State->sizePolicy().hasHeightForWidth());
        CGXi_CO4_State->setSizePolicy(sizePolicy8);
        CGXi_CO4_State->setMinimumSize(QSize(20, 20));

        gridLayout_12->addWidget(CGXi_CO4_State, 2, 1, 1, 1);

        CGXi_CO4_Set = new QPushButton(groupBox_DO_3);
        CGXi_CO4_Set->setObjectName(QString::fromUtf8("CGXi_CO4_Set"));

        gridLayout_12->addWidget(CGXi_CO4_Set, 2, 2, 1, 1);

        CGXi_CO4_Reset = new QPushButton(groupBox_DO_3);
        CGXi_CO4_Reset->setObjectName(QString::fromUtf8("CGXi_CO4_Reset"));

        gridLayout_12->addWidget(CGXi_CO4_Reset, 2, 3, 1, 1);

        label_DO1_11 = new QLabel(groupBox_DO_3);
        label_DO1_11->setObjectName(QString::fromUtf8("label_DO1_11"));
        sizePolicy8.setHeightForWidth(label_DO1_11->sizePolicy().hasHeightForWidth());
        label_DO1_11->setSizePolicy(sizePolicy8);
        label_DO1_11->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_DO1_11, 1, 12, 1, 1);

        CGXi_CO3_Reset = new QPushButton(groupBox_DO_3);
        CGXi_CO3_Reset->setObjectName(QString::fromUtf8("CGXi_CO3_Reset"));

        gridLayout_12->addWidget(CGXi_CO3_Reset, 1, 15, 1, 1);

        CGXi_CO3_Set = new QPushButton(groupBox_DO_3);
        CGXi_CO3_Set->setObjectName(QString::fromUtf8("CGXi_CO3_Set"));

        gridLayout_12->addWidget(CGXi_CO3_Set, 1, 14, 1, 1);

        CGXi_CO3_State = new c_Fr_Light(groupBox_DO_3);
        CGXi_CO3_State->setObjectName(QString::fromUtf8("CGXi_CO3_State"));
        sizePolicy8.setHeightForWidth(CGXi_CO3_State->sizePolicy().hasHeightForWidth());
        CGXi_CO3_State->setSizePolicy(sizePolicy8);
        CGXi_CO3_State->setMinimumSize(QSize(20, 20));

        gridLayout_12->addWidget(CGXi_CO3_State, 1, 13, 1, 1);

        label_DO1_10 = new QLabel(groupBox_DO_3);
        label_DO1_10->setObjectName(QString::fromUtf8("label_DO1_10"));
        sizePolicy8.setHeightForWidth(label_DO1_10->sizePolicy().hasHeightForWidth());
        label_DO1_10->setSizePolicy(sizePolicy8);
        label_DO1_10->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_DO1_10, 2, 8, 1, 1);

        CGXi_CO6_State = new c_Fr_Light(groupBox_DO_3);
        CGXi_CO6_State->setObjectName(QString::fromUtf8("CGXi_CO6_State"));
        sizePolicy8.setHeightForWidth(CGXi_CO6_State->sizePolicy().hasHeightForWidth());
        CGXi_CO6_State->setSizePolicy(sizePolicy8);
        CGXi_CO6_State->setMinimumSize(QSize(20, 20));

        gridLayout_12->addWidget(CGXi_CO6_State, 2, 9, 1, 1);

        CGXi_CO6_Set = new QPushButton(groupBox_DO_3);
        CGXi_CO6_Set->setObjectName(QString::fromUtf8("CGXi_CO6_Set"));

        gridLayout_12->addWidget(CGXi_CO6_Set, 2, 10, 1, 1);

        CGXi_CO6_Reset = new QPushButton(groupBox_DO_3);
        CGXi_CO6_Reset->setObjectName(QString::fromUtf8("CGXi_CO6_Reset"));

        gridLayout_12->addWidget(CGXi_CO6_Reset, 2, 11, 1, 1);

        label_DO1_12 = new QLabel(groupBox_DO_3);
        label_DO1_12->setObjectName(QString::fromUtf8("label_DO1_12"));
        sizePolicy8.setHeightForWidth(label_DO1_12->sizePolicy().hasHeightForWidth());
        label_DO1_12->setSizePolicy(sizePolicy8);
        label_DO1_12->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_DO1_12, 2, 12, 1, 1);

        CGXi_CO7_Set = new QPushButton(groupBox_DO_3);
        CGXi_CO7_Set->setObjectName(QString::fromUtf8("CGXi_CO7_Set"));

        gridLayout_12->addWidget(CGXi_CO7_Set, 2, 14, 1, 1);

        CGXi_CO7_Reset = new QPushButton(groupBox_DO_3);
        CGXi_CO7_Reset->setObjectName(QString::fromUtf8("CGXi_CO7_Reset"));

        gridLayout_12->addWidget(CGXi_CO7_Reset, 2, 15, 1, 1);

        CGXi_CO7_State = new c_Fr_Light(groupBox_DO_3);
        CGXi_CO7_State->setObjectName(QString::fromUtf8("CGXi_CO7_State"));
        sizePolicy8.setHeightForWidth(CGXi_CO7_State->sizePolicy().hasHeightForWidth());
        CGXi_CO7_State->setSizePolicy(sizePolicy8);
        CGXi_CO7_State->setMinimumSize(QSize(20, 20));

        gridLayout_12->addWidget(CGXi_CO7_State, 2, 13, 1, 1);


        verticalLayout_2->addWidget(groupBox_DO_3);

        groupBox_Prog = new QGroupBox(groupBox_3);
        groupBox_Prog->setObjectName(QString::fromUtf8("groupBox_Prog"));
        sizePolicy.setHeightForWidth(groupBox_Prog->sizePolicy().hasHeightForWidth());
        groupBox_Prog->setSizePolicy(sizePolicy);
        gridLayout_6 = new QGridLayout(groupBox_Prog);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_8 = new QLabel(groupBox_Prog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy9(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy9);

        horizontalLayout->addWidget(label_8);

        CGXi_Target_Prog_Index = new QLineEdit(groupBox_Prog);
        CGXi_Target_Prog_Index->setObjectName(QString::fromUtf8("CGXi_Target_Prog_Index"));
        sizePolicy7.setHeightForWidth(CGXi_Target_Prog_Index->sizePolicy().hasHeightForWidth());
        CGXi_Target_Prog_Index->setSizePolicy(sizePolicy7);

        horizontalLayout->addWidget(CGXi_Target_Prog_Index);

        Set_HoldingRegisters_88 = new QPushButton(groupBox_Prog);
        Set_HoldingRegisters_88->setObjectName(QString::fromUtf8("Set_HoldingRegisters_88"));

        horizontalLayout->addWidget(Set_HoldingRegisters_88);


        gridLayout_6->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        CGXi_Prog_Pause = new QPushButton(groupBox_Prog);
        CGXi_Prog_Pause->setObjectName(QString::fromUtf8("CGXi_Prog_Pause"));
        sizePolicy7.setHeightForWidth(CGXi_Prog_Pause->sizePolicy().hasHeightForWidth());
        CGXi_Prog_Pause->setSizePolicy(sizePolicy7);
        CGXi_Prog_Pause->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(CGXi_Prog_Pause);

        CGXi_Prog_Stop = new QPushButton(groupBox_Prog);
        CGXi_Prog_Stop->setObjectName(QString::fromUtf8("CGXi_Prog_Stop"));
        sizePolicy7.setHeightForWidth(CGXi_Prog_Stop->sizePolicy().hasHeightForWidth());
        CGXi_Prog_Stop->setSizePolicy(sizePolicy7);
        CGXi_Prog_Stop->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(CGXi_Prog_Stop);


        gridLayout_6->addLayout(horizontalLayout_2, 2, 0, 1, 2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_9 = new QLabel(groupBox_Prog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy9.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy9);

        horizontalLayout_6->addWidget(label_9);

        CGXi_Prog_Index = new c_Fr_Light(groupBox_Prog);
        CGXi_Prog_Index->setObjectName(QString::fromUtf8("CGXi_Prog_Index"));
        sizePolicy5.setHeightForWidth(CGXi_Prog_Index->sizePolicy().hasHeightForWidth());
        CGXi_Prog_Index->setSizePolicy(sizePolicy5);
        CGXi_Prog_Index->setMinimumSize(QSize(20, 20));

        horizontalLayout_6->addWidget(CGXi_Prog_Index);

        CGXi_Current_Prog_Index = new QLineEdit(groupBox_Prog);
        CGXi_Current_Prog_Index->setObjectName(QString::fromUtf8("CGXi_Current_Prog_Index"));
        sizePolicy7.setHeightForWidth(CGXi_Current_Prog_Index->sizePolicy().hasHeightForWidth());
        CGXi_Current_Prog_Index->setSizePolicy(sizePolicy7);

        horizontalLayout_6->addWidget(CGXi_Current_Prog_Index);


        gridLayout_6->addLayout(horizontalLayout_6, 0, 1, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        CGXi_program_status = new c_Fr_Light(groupBox_Prog);
        CGXi_program_status->setObjectName(QString::fromUtf8("CGXi_program_status"));
        sizePolicy8.setHeightForWidth(CGXi_program_status->sizePolicy().hasHeightForWidth());
        CGXi_program_status->setSizePolicy(sizePolicy8);
        CGXi_program_status->setMinimumSize(QSize(20, 20));

        horizontalLayout_7->addWidget(CGXi_program_status);

        CGXi_Prog_Start = new QPushButton(groupBox_Prog);
        CGXi_Prog_Start->setObjectName(QString::fromUtf8("CGXi_Prog_Start"));
        sizePolicy7.setHeightForWidth(CGXi_Prog_Start->sizePolicy().hasHeightForWidth());
        CGXi_Prog_Start->setSizePolicy(sizePolicy7);
        CGXi_Prog_Start->setMinimumSize(QSize(0, 0));

        horizontalLayout_7->addWidget(CGXi_Prog_Start);


        gridLayout_6->addLayout(horizontalLayout_7, 1, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        CGXi_Clear_Error = new QPushButton(groupBox_Prog);
        CGXi_Clear_Error->setObjectName(QString::fromUtf8("CGXi_Clear_Error"));
        sizePolicy7.setHeightForWidth(CGXi_Clear_Error->sizePolicy().hasHeightForWidth());
        CGXi_Clear_Error->setSizePolicy(sizePolicy7);

        horizontalLayout_3->addWidget(CGXi_Clear_Error);

        CGXi_Clear_Warning = new QPushButton(groupBox_Prog);
        CGXi_Clear_Warning->setObjectName(QString::fromUtf8("CGXi_Clear_Warning"));
        sizePolicy7.setHeightForWidth(CGXi_Clear_Warning->sizePolicy().hasHeightForWidth());
        CGXi_Clear_Warning->setSizePolicy(sizePolicy7);

        horizontalLayout_3->addWidget(CGXi_Clear_Warning);


        gridLayout_6->addLayout(horizontalLayout_3, 3, 0, 1, 2);


        verticalLayout_2->addWidget(groupBox_Prog);


        gridLayout_9->addLayout(verticalLayout_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        CGXi_Log = new QTextBrowser(groupBox);
        CGXi_Log->setObjectName(QString::fromUtf8("CGXi_Log"));
        sizePolicy3.setHeightForWidth(CGXi_Log->sizePolicy().hasHeightForWidth());
        CGXi_Log->setSizePolicy(sizePolicy3);

        gridLayout_5->addWidget(CGXi_Log, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBox, 0, 1, 1, 1);

        tabWidget_Status = new QTabWidget(groupBox_3);
        tabWidget_Status->setObjectName(QString::fromUtf8("tabWidget_Status"));
        sizePolicy3.setHeightForWidth(tabWidget_Status->sizePolicy().hasHeightForWidth());
        tabWidget_Status->setSizePolicy(sizePolicy3);
        tab_Joint = new QWidget();
        tab_Joint->setObjectName(QString::fromUtf8("tab_Joint"));
        verticalLayout_Joint = new QVBoxLayout(tab_Joint);
        verticalLayout_Joint->setSpacing(6);
        verticalLayout_Joint->setContentsMargins(11, 11, 11, 11);
        verticalLayout_Joint->setObjectName(QString::fromUtf8("verticalLayout_Joint"));
        tableWidget_Joint = new QTableWidget(tab_Joint);
        if (tableWidget_Joint->columnCount() < 11)
            tableWidget_Joint->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        tableWidget_Joint->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        tableWidget_Joint->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        tableWidget_Joint->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignCenter);
        tableWidget_Joint->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignCenter);
        tableWidget_Joint->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignCenter);
        tableWidget_Joint->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignCenter);
        tableWidget_Joint->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setTextAlignment(Qt::AlignCenter);
        tableWidget_Joint->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setTextAlignment(Qt::AlignCenter);
        tableWidget_Joint->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setTextAlignment(Qt::AlignCenter);
        tableWidget_Joint->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setTextAlignment(Qt::AlignCenter);
        tableWidget_Joint->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        if (tableWidget_Joint->rowCount() < 6)
            tableWidget_Joint->setRowCount(6);
        tableWidget_Joint->setObjectName(QString::fromUtf8("tableWidget_Joint"));
        sizePolicy3.setHeightForWidth(tableWidget_Joint->sizePolicy().hasHeightForWidth());
        tableWidget_Joint->setSizePolicy(sizePolicy3);
        tableWidget_Joint->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_Joint->setAlternatingRowColors(true);
        tableWidget_Joint->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget_Joint->setRowCount(6);
        tableWidget_Joint->setColumnCount(11);
        tableWidget_Joint->horizontalHeader()->setStretchLastSection(true);
        tableWidget_Joint->verticalHeader()->setVisible(false);

        verticalLayout_Joint->addWidget(tableWidget_Joint);

        tabWidget_Status->addTab(tab_Joint, QString());
        tab_TCP = new QWidget();
        tab_TCP->setObjectName(QString::fromUtf8("tab_TCP"));
        gridLayout_8 = new QGridLayout(tab_TCP);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        tableWidget_TCP = new QTableWidget(tab_TCP);
        if (tableWidget_TCP->columnCount() < 7)
            tableWidget_TCP->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setTextAlignment(Qt::AlignCenter);
        tableWidget_TCP->setHorizontalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setTextAlignment(Qt::AlignCenter);
        tableWidget_TCP->setHorizontalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setTextAlignment(Qt::AlignCenter);
        tableWidget_TCP->setHorizontalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setTextAlignment(Qt::AlignCenter);
        tableWidget_TCP->setHorizontalHeaderItem(3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setTextAlignment(Qt::AlignCenter);
        tableWidget_TCP->setHorizontalHeaderItem(4, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setTextAlignment(Qt::AlignCenter);
        tableWidget_TCP->setHorizontalHeaderItem(5, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setTextAlignment(Qt::AlignCenter);
        tableWidget_TCP->setHorizontalHeaderItem(6, __qtablewidgetitem17);
        if (tableWidget_TCP->rowCount() < 6)
            tableWidget_TCP->setRowCount(6);
        tableWidget_TCP->setObjectName(QString::fromUtf8("tableWidget_TCP"));
        tableWidget_TCP->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_TCP->setAlternatingRowColors(true);
        tableWidget_TCP->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget_TCP->setRowCount(6);
        tableWidget_TCP->setColumnCount(7);
        tableWidget_TCP->horizontalHeader()->setStretchLastSection(true);
        tableWidget_TCP->verticalHeader()->setVisible(false);

        gridLayout_8->addWidget(tableWidget_TCP, 0, 0, 1, 1);

        tabWidget_Status->addTab(tab_TCP, QString());
        tab_Robot = new QWidget();
        tab_Robot->setObjectName(QString::fromUtf8("tab_Robot"));
        verticalLayout_Robot = new QVBoxLayout(tab_Robot);
        verticalLayout_Robot->setSpacing(6);
        verticalLayout_Robot->setContentsMargins(11, 11, 11, 11);
        verticalLayout_Robot->setObjectName(QString::fromUtf8("verticalLayout_Robot"));
        tableWidget_Robot = new QTableWidget(tab_Robot);
        if (tableWidget_Robot->columnCount() < 3)
            tableWidget_Robot->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        __qtablewidgetitem18->setTextAlignment(Qt::AlignCenter);
        tableWidget_Robot->setHorizontalHeaderItem(0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        __qtablewidgetitem19->setTextAlignment(Qt::AlignCenter);
        tableWidget_Robot->setHorizontalHeaderItem(1, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        __qtablewidgetitem20->setTextAlignment(Qt::AlignCenter);
        tableWidget_Robot->setHorizontalHeaderItem(2, __qtablewidgetitem20);
        if (tableWidget_Robot->rowCount() < 7)
            tableWidget_Robot->setRowCount(7);
        tableWidget_Robot->setObjectName(QString::fromUtf8("tableWidget_Robot"));
        QSizePolicy sizePolicy10(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(tableWidget_Robot->sizePolicy().hasHeightForWidth());
        tableWidget_Robot->setSizePolicy(sizePolicy10);
        tableWidget_Robot->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_Robot->setAlternatingRowColors(true);
        tableWidget_Robot->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget_Robot->setRowCount(7);
        tableWidget_Robot->setColumnCount(3);
        tableWidget_Robot->horizontalHeader()->setDefaultSectionSize(200);
        tableWidget_Robot->horizontalHeader()->setStretchLastSection(true);
        tableWidget_Robot->verticalHeader()->setVisible(false);

        verticalLayout_Robot->addWidget(tableWidget_Robot);

        tabWidget_Status->addTab(tab_Robot, QString());

        gridLayout_9->addWidget(tabWidget_Status, 1, 0, 1, 2);


        gridLayout_3->addWidget(groupBox_3, 1, 0, 1, 1);

        stackedWidget->addWidget(CGXi_Widget);
        Pre_Scan_120_Widget = new QWidget();
        Pre_Scan_120_Widget->setObjectName(QString::fromUtf8("Pre_Scan_120_Widget"));
        gridLayout_20 = new QGridLayout(Pre_Scan_120_Widget);
        gridLayout_20->setSpacing(6);
        gridLayout_20->setContentsMargins(11, 11, 11, 11);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        groupBox_8 = new QGroupBox(Pre_Scan_120_Widget);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        gridLayout_24 = new QGridLayout(groupBox_8);
        gridLayout_24->setSpacing(6);
        gridLayout_24->setContentsMargins(11, 11, 11, 11);
        gridLayout_24->setObjectName(QString::fromUtf8("gridLayout_24"));
        verticalLayout_50 = new QVBoxLayout();
        verticalLayout_50->setSpacing(6);
        verticalLayout_50->setObjectName(QString::fromUtf8("verticalLayout_50"));
        horizontalLayout_50 = new QHBoxLayout();
        horizontalLayout_50->setSpacing(6);
        horizontalLayout_50->setObjectName(QString::fromUtf8("horizontalLayout_50"));
        label_120_Remote_Status = new QLabel(groupBox_8);
        label_120_Remote_Status->setObjectName(QString::fromUtf8("label_120_Remote_Status"));
        sizePolicy8.setHeightForWidth(label_120_Remote_Status->sizePolicy().hasHeightForWidth());
        label_120_Remote_Status->setSizePolicy(sizePolicy8);

        horizontalLayout_50->addWidget(label_120_Remote_Status);

        Pre_Scan_120_Remote_Light = new c_Fr_Light(groupBox_8);
        Pre_Scan_120_Remote_Light->setObjectName(QString::fromUtf8("Pre_Scan_120_Remote_Light"));
        Pre_Scan_120_Remote_Light->setMinimumSize(QSize(16, 16));
        Pre_Scan_120_Remote_Light->setMaximumSize(QSize(16, 16));

        horizontalLayout_50->addWidget(Pre_Scan_120_Remote_Light);

        label_120_Monitor_Status = new QLabel(groupBox_8);
        label_120_Monitor_Status->setObjectName(QString::fromUtf8("label_120_Monitor_Status"));
        sizePolicy8.setHeightForWidth(label_120_Monitor_Status->sizePolicy().hasHeightForWidth());
        label_120_Monitor_Status->setSizePolicy(sizePolicy8);

        horizontalLayout_50->addWidget(label_120_Monitor_Status);

        Pre_Scan_120_Monitor_Light = new c_Fr_Light(groupBox_8);
        Pre_Scan_120_Monitor_Light->setObjectName(QString::fromUtf8("Pre_Scan_120_Monitor_Light"));
        Pre_Scan_120_Monitor_Light->setMinimumSize(QSize(16, 16));
        Pre_Scan_120_Monitor_Light->setMaximumSize(QSize(16, 16));

        horizontalLayout_50->addWidget(Pre_Scan_120_Monitor_Light);

        label_120_Listen_Status = new QLabel(groupBox_8);
        label_120_Listen_Status->setObjectName(QString::fromUtf8("label_120_Listen_Status"));
        sizePolicy8.setHeightForWidth(label_120_Listen_Status->sizePolicy().hasHeightForWidth());
        label_120_Listen_Status->setSizePolicy(sizePolicy8);

        horizontalLayout_50->addWidget(label_120_Listen_Status);

        Pre_Scan_120_Listen_Light = new c_Fr_Light(groupBox_8);
        Pre_Scan_120_Listen_Light->setObjectName(QString::fromUtf8("Pre_Scan_120_Listen_Light"));
        Pre_Scan_120_Listen_Light->setMinimumSize(QSize(16, 16));
        Pre_Scan_120_Listen_Light->setMaximumSize(QSize(16, 16));

        horizontalLayout_50->addWidget(Pre_Scan_120_Listen_Light);

        label_120_Tran_Status = new QLabel(groupBox_8);
        label_120_Tran_Status->setObjectName(QString::fromUtf8("label_120_Tran_Status"));
        sizePolicy8.setHeightForWidth(label_120_Tran_Status->sizePolicy().hasHeightForWidth());
        label_120_Tran_Status->setSizePolicy(sizePolicy8);

        horizontalLayout_50->addWidget(label_120_Tran_Status);

        Pre_Scan_120_Tran_Light = new c_Fr_Light(groupBox_8);
        Pre_Scan_120_Tran_Light->setObjectName(QString::fromUtf8("Pre_Scan_120_Tran_Light"));
        Pre_Scan_120_Tran_Light->setMinimumSize(QSize(16, 16));
        Pre_Scan_120_Tran_Light->setMaximumSize(QSize(16, 16));

        horizontalLayout_50->addWidget(Pre_Scan_120_Tran_Light);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_50->addItem(horizontalSpacer);


        verticalLayout_50->addLayout(horizontalLayout_50);

        horizontalLayout_50B = new QHBoxLayout();
        horizontalLayout_50B->setSpacing(6);
        horizontalLayout_50B->setObjectName(QString::fromUtf8("horizontalLayout_50B"));
        label_120_Client_Num = new QLabel(groupBox_8);
        label_120_Client_Num->setObjectName(QString::fromUtf8("label_120_Client_Num"));
        sizePolicy8.setHeightForWidth(label_120_Client_Num->sizePolicy().hasHeightForWidth());
        label_120_Client_Num->setSizePolicy(sizePolicy8);

        horizontalLayout_50B->addWidget(label_120_Client_Num);

        Pre_Scan_120_Client_Num = new QLineEdit(groupBox_8);
        Pre_Scan_120_Client_Num->setObjectName(QString::fromUtf8("Pre_Scan_120_Client_Num"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_Client_Num->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_Client_Num->setSizePolicy(sizePolicy7);
        Pre_Scan_120_Client_Num->setMaximumSize(QSize(16777215, 16777215));
        Pre_Scan_120_Client_Num->setReadOnly(true);

        horizontalLayout_50B->addWidget(Pre_Scan_120_Client_Num);

        label_120_Cam_Num = new QLabel(groupBox_8);
        label_120_Cam_Num->setObjectName(QString::fromUtf8("label_120_Cam_Num"));
        sizePolicy8.setHeightForWidth(label_120_Cam_Num->sizePolicy().hasHeightForWidth());
        label_120_Cam_Num->setSizePolicy(sizePolicy8);

        horizontalLayout_50B->addWidget(label_120_Cam_Num);

        Pre_Scan_120_Cam_Num = new QLineEdit(groupBox_8);
        Pre_Scan_120_Cam_Num->setObjectName(QString::fromUtf8("Pre_Scan_120_Cam_Num"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_Cam_Num->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_Cam_Num->setSizePolicy(sizePolicy7);
        Pre_Scan_120_Cam_Num->setMaximumSize(QSize(16777215, 16777215));
        Pre_Scan_120_Cam_Num->setReadOnly(true);

        horizontalLayout_50B->addWidget(Pre_Scan_120_Cam_Num);

        label_120_IP = new QLabel(groupBox_8);
        label_120_IP->setObjectName(QString::fromUtf8("label_120_IP"));
        sizePolicy8.setHeightForWidth(label_120_IP->sizePolicy().hasHeightForWidth());
        label_120_IP->setSizePolicy(sizePolicy8);

        horizontalLayout_50B->addWidget(label_120_IP);

        Pre_Scan_120_IP = new QLineEdit(groupBox_8);
        Pre_Scan_120_IP->setObjectName(QString::fromUtf8("Pre_Scan_120_IP"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_IP->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_IP->setSizePolicy(sizePolicy7);

        horizontalLayout_50B->addWidget(Pre_Scan_120_IP);

        label_120_Port = new QLabel(groupBox_8);
        label_120_Port->setObjectName(QString::fromUtf8("label_120_Port"));
        sizePolicy8.setHeightForWidth(label_120_Port->sizePolicy().hasHeightForWidth());
        label_120_Port->setSizePolicy(sizePolicy8);

        horizontalLayout_50B->addWidget(label_120_Port);

        Pre_Scan_120_Port = new QLineEdit(groupBox_8);
        Pre_Scan_120_Port->setObjectName(QString::fromUtf8("Pre_Scan_120_Port"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_Port->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_Port->setSizePolicy(sizePolicy7);
        Pre_Scan_120_Port->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_50B->addWidget(Pre_Scan_120_Port);

        label_120_Monitor = new QLabel(groupBox_8);
        label_120_Monitor->setObjectName(QString::fromUtf8("label_120_Monitor"));
        sizePolicy8.setHeightForWidth(label_120_Monitor->sizePolicy().hasHeightForWidth());
        label_120_Monitor->setSizePolicy(sizePolicy8);

        horizontalLayout_50B->addWidget(label_120_Monitor);

        Pre_Scan_120_Monitor_Port = new QLineEdit(groupBox_8);
        Pre_Scan_120_Monitor_Port->setObjectName(QString::fromUtf8("Pre_Scan_120_Monitor_Port"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_Monitor_Port->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_Monitor_Port->setSizePolicy(sizePolicy7);
        Pre_Scan_120_Monitor_Port->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_50B->addWidget(Pre_Scan_120_Monitor_Port);

        label_120_Tran = new QLabel(groupBox_8);
        label_120_Tran->setObjectName(QString::fromUtf8("label_120_Tran"));
        sizePolicy8.setHeightForWidth(label_120_Tran->sizePolicy().hasHeightForWidth());
        label_120_Tran->setSizePolicy(sizePolicy8);

        horizontalLayout_50B->addWidget(label_120_Tran);

        Pre_Scan_120_Tran_Port = new QLineEdit(groupBox_8);
        Pre_Scan_120_Tran_Port->setObjectName(QString::fromUtf8("Pre_Scan_120_Tran_Port"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_Tran_Port->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_Tran_Port->setSizePolicy(sizePolicy7);
        Pre_Scan_120_Tran_Port->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_50B->addWidget(Pre_Scan_120_Tran_Port);

        Pre_Scan_120_Connect = new QPushButton(groupBox_8);
        Pre_Scan_120_Connect->setObjectName(QString::fromUtf8("Pre_Scan_120_Connect"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_Connect->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_Connect->setSizePolicy(sizePolicy7);

        horizontalLayout_50B->addWidget(Pre_Scan_120_Connect);

        Pre_Scan_120_Disconnect = new QPushButton(groupBox_8);
        Pre_Scan_120_Disconnect->setObjectName(QString::fromUtf8("Pre_Scan_120_Disconnect"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_Disconnect->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_Disconnect->setSizePolicy(sizePolicy7);

        horizontalLayout_50B->addWidget(Pre_Scan_120_Disconnect);


        verticalLayout_50->addLayout(horizontalLayout_50B);


        gridLayout_24->addLayout(verticalLayout_50, 0, 0, 1, 1);

        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(6);
        horizontalLayout_49->setObjectName(QString::fromUtf8("horizontalLayout_49"));
        groupBox_Task_Info_2 = new QGroupBox(groupBox_8);
        groupBox_Task_Info_2->setObjectName(QString::fromUtf8("groupBox_Task_Info_2"));
        gridLayout_22 = new QGridLayout(groupBox_Task_Info_2);
        gridLayout_22->setSpacing(6);
        gridLayout_22->setContentsMargins(11, 11, 11, 11);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        set_Pre_Scan_120_TaskID = new QPushButton(groupBox_Task_Info_2);
        set_Pre_Scan_120_TaskID->setObjectName(QString::fromUtf8("set_Pre_Scan_120_TaskID"));
        sizePolicy9.setHeightForWidth(set_Pre_Scan_120_TaskID->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_TaskID->setSizePolicy(sizePolicy9);

        gridLayout_22->addWidget(set_Pre_Scan_120_TaskID, 0, 3, 1, 1);

        w_Pre_Scan_120_TaskID = new QLineEdit(groupBox_Task_Info_2);
        w_Pre_Scan_120_TaskID->setObjectName(QString::fromUtf8("w_Pre_Scan_120_TaskID"));
        QSizePolicy sizePolicy11(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_TaskID->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_TaskID->setSizePolicy(sizePolicy11);

        gridLayout_22->addWidget(w_Pre_Scan_120_TaskID, 0, 2, 2, 1);

        w_Pre_Scan_120_Wheelset = new QLineEdit(groupBox_Task_Info_2);
        w_Pre_Scan_120_Wheelset->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Wheelset"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Wheelset->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Wheelset->setSizePolicy(sizePolicy11);
        w_Pre_Scan_120_Wheelset->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_22->addWidget(w_Pre_Scan_120_Wheelset, 0, 6, 1, 1);

        w_Pre_Scan_120_Axle = new QLineEdit(groupBox_Task_Info_2);
        w_Pre_Scan_120_Axle->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Axle"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Axle->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Axle->setSizePolicy(sizePolicy11);
        w_Pre_Scan_120_Axle->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_22->addWidget(w_Pre_Scan_120_Axle, 3, 6, 1, 1);

        label_120_TaskID_2 = new QLabel(groupBox_Task_Info_2);
        label_120_TaskID_2->setObjectName(QString::fromUtf8("label_120_TaskID_2"));
        sizePolicy8.setHeightForWidth(label_120_TaskID_2->sizePolicy().hasHeightForWidth());
        label_120_TaskID_2->setSizePolicy(sizePolicy8);

        gridLayout_22->addWidget(label_120_TaskID_2, 0, 0, 2, 1);

        label_120_Axle_2 = new QLabel(groupBox_Task_Info_2);
        label_120_Axle_2->setObjectName(QString::fromUtf8("label_120_Axle_2"));
        sizePolicy8.setHeightForWidth(label_120_Axle_2->sizePolicy().hasHeightForWidth());
        label_120_Axle_2->setSizePolicy(sizePolicy8);

        gridLayout_22->addWidget(label_120_Axle_2, 3, 4, 1, 1);

        w_Pre_Scan_120_Repair = new QLineEdit(groupBox_Task_Info_2);
        w_Pre_Scan_120_Repair->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Repair"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Repair->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Repair->setSizePolicy(sizePolicy11);
        w_Pre_Scan_120_Repair->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_22->addWidget(w_Pre_Scan_120_Repair, 4, 2, 1, 1);

        label_120_Repair_2 = new QLabel(groupBox_Task_Info_2);
        label_120_Repair_2->setObjectName(QString::fromUtf8("label_120_Repair_2"));
        sizePolicy8.setHeightForWidth(label_120_Repair_2->sizePolicy().hasHeightForWidth());
        label_120_Repair_2->setSizePolicy(sizePolicy8);

        gridLayout_22->addWidget(label_120_Repair_2, 4, 0, 1, 1);

        label_120_StartTime_2 = new QLabel(groupBox_Task_Info_2);
        label_120_StartTime_2->setObjectName(QString::fromUtf8("label_120_StartTime_2"));
        sizePolicy8.setHeightForWidth(label_120_StartTime_2->sizePolicy().hasHeightForWidth());
        label_120_StartTime_2->setSizePolicy(sizePolicy8);

        gridLayout_22->addWidget(label_120_StartTime_2, 3, 0, 1, 1);

        set_Pre_Scan_120_Wheelset = new QPushButton(groupBox_Task_Info_2);
        set_Pre_Scan_120_Wheelset->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Wheelset"));
        sizePolicy9.setHeightForWidth(set_Pre_Scan_120_Wheelset->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Wheelset->setSizePolicy(sizePolicy9);

        gridLayout_22->addWidget(set_Pre_Scan_120_Wheelset, 0, 7, 1, 1);

        set_Pre_Scan_120_Axle = new QPushButton(groupBox_Task_Info_2);
        set_Pre_Scan_120_Axle->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Axle"));
        sizePolicy9.setHeightForWidth(set_Pre_Scan_120_Axle->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Axle->setSizePolicy(sizePolicy9);

        gridLayout_22->addWidget(set_Pre_Scan_120_Axle, 3, 7, 1, 1);

        label_120_SendUnit_2 = new QLabel(groupBox_Task_Info_2);
        label_120_SendUnit_2->setObjectName(QString::fromUtf8("label_120_SendUnit_2"));
        sizePolicy8.setHeightForWidth(label_120_SendUnit_2->sizePolicy().hasHeightForWidth());
        label_120_SendUnit_2->setSizePolicy(sizePolicy8);

        gridLayout_22->addWidget(label_120_SendUnit_2, 4, 4, 1, 1);

        set_Pre_Scan_120_Repair = new QPushButton(groupBox_Task_Info_2);
        set_Pre_Scan_120_Repair->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Repair"));
        sizePolicy9.setHeightForWidth(set_Pre_Scan_120_Repair->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Repair->setSizePolicy(sizePolicy9);

        gridLayout_22->addWidget(set_Pre_Scan_120_Repair, 4, 3, 1, 1);

        label_120_Wheelset_2 = new QLabel(groupBox_Task_Info_2);
        label_120_Wheelset_2->setObjectName(QString::fromUtf8("label_120_Wheelset_2"));
        sizePolicy8.setHeightForWidth(label_120_Wheelset_2->sizePolicy().hasHeightForWidth());
        label_120_Wheelset_2->setSizePolicy(sizePolicy8);

        gridLayout_22->addWidget(label_120_Wheelset_2, 0, 4, 1, 1);

        w_Pre_Scan_120_StartTime = new QLineEdit(groupBox_Task_Info_2);
        w_Pre_Scan_120_StartTime->setObjectName(QString::fromUtf8("w_Pre_Scan_120_StartTime"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_StartTime->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_StartTime->setSizePolicy(sizePolicy11);

        gridLayout_22->addWidget(w_Pre_Scan_120_StartTime, 3, 2, 1, 1);

        set_Pre_Scan_120_StartTime = new QPushButton(groupBox_Task_Info_2);
        set_Pre_Scan_120_StartTime->setObjectName(QString::fromUtf8("set_Pre_Scan_120_StartTime"));
        sizePolicy9.setHeightForWidth(set_Pre_Scan_120_StartTime->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_StartTime->setSizePolicy(sizePolicy9);

        gridLayout_22->addWidget(set_Pre_Scan_120_StartTime, 3, 3, 1, 1);

        set_Pre_Scan_120_SendUnit = new QPushButton(groupBox_Task_Info_2);
        set_Pre_Scan_120_SendUnit->setObjectName(QString::fromUtf8("set_Pre_Scan_120_SendUnit"));
        sizePolicy9.setHeightForWidth(set_Pre_Scan_120_SendUnit->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_SendUnit->setSizePolicy(sizePolicy9);

        gridLayout_22->addWidget(set_Pre_Scan_120_SendUnit, 4, 7, 1, 1);

        w_Pre_Scan_120_SendUnit = new QLineEdit(groupBox_Task_Info_2);
        w_Pre_Scan_120_SendUnit->setObjectName(QString::fromUtf8("w_Pre_Scan_120_SendUnit"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_SendUnit->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_SendUnit->setSizePolicy(sizePolicy11);
        w_Pre_Scan_120_SendUnit->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_22->addWidget(w_Pre_Scan_120_SendUnit, 4, 6, 1, 1);


        horizontalLayout_49->addWidget(groupBox_Task_Info_2);

        groupBox_Collect_Status_2 = new QGroupBox(groupBox_8);
        groupBox_Collect_Status_2->setObjectName(QString::fromUtf8("groupBox_Collect_Status_2"));
        gridLayout_102 = new QGridLayout(groupBox_Collect_Status_2);
        gridLayout_102->setSpacing(6);
        gridLayout_102->setContentsMargins(11, 11, 11, 11);
        gridLayout_102->setObjectName(QString::fromUtf8("gridLayout_102"));
        label_120_Gain_2 = new QLabel(groupBox_Collect_Status_2);
        label_120_Gain_2->setObjectName(QString::fromUtf8("label_120_Gain_2"));
        sizePolicy8.setHeightForWidth(label_120_Gain_2->sizePolicy().hasHeightForWidth());
        label_120_Gain_2->setSizePolicy(sizePolicy8);

        gridLayout_102->addWidget(label_120_Gain_2, 0, 3, 1, 1);

        w_Pre_Scan_120_Point = new QLineEdit(groupBox_Collect_Status_2);
        w_Pre_Scan_120_Point->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Point"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Point->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Point->setSizePolicy(sizePolicy11);

        gridLayout_102->addWidget(w_Pre_Scan_120_Point, 2, 1, 1, 1);

        set_Pre_Scan_120_Part1 = new QPushButton(groupBox_Collect_Status_2);
        set_Pre_Scan_120_Part1->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Part1"));
        sizePolicy9.setHeightForWidth(set_Pre_Scan_120_Part1->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Part1->setSizePolicy(sizePolicy9);

        gridLayout_102->addWidget(set_Pre_Scan_120_Part1, 1, 2, 1, 1);

        set_Pre_Scan_120_Point = new QPushButton(groupBox_Collect_Status_2);
        set_Pre_Scan_120_Point->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Point"));
        sizePolicy9.setHeightForWidth(set_Pre_Scan_120_Point->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Point->setSizePolicy(sizePolicy9);

        gridLayout_102->addWidget(set_Pre_Scan_120_Point, 2, 2, 1, 1);

        w_Pre_Scan_120_Part1 = new QLineEdit(groupBox_Collect_Status_2);
        w_Pre_Scan_120_Part1->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Part1"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Part1->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Part1->setSizePolicy(sizePolicy11);

        gridLayout_102->addWidget(w_Pre_Scan_120_Part1, 1, 1, 1, 1);

        label_120_Part2_2 = new QLabel(groupBox_Collect_Status_2);
        label_120_Part2_2->setObjectName(QString::fromUtf8("label_120_Part2_2"));
        sizePolicy8.setHeightForWidth(label_120_Part2_2->sizePolicy().hasHeightForWidth());
        label_120_Part2_2->setSizePolicy(sizePolicy8);

        gridLayout_102->addWidget(label_120_Part2_2, 1, 3, 1, 1);

        w_Pre_Scan_120_currentWheelset = new QLineEdit(groupBox_Collect_Status_2);
        w_Pre_Scan_120_currentWheelset->setObjectName(QString::fromUtf8("w_Pre_Scan_120_currentWheelset"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_currentWheelset->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_currentWheelset->setSizePolicy(sizePolicy11);

        gridLayout_102->addWidget(w_Pre_Scan_120_currentWheelset, 0, 1, 1, 1);

        w_Pre_Scan_120_Part2 = new QLineEdit(groupBox_Collect_Status_2);
        w_Pre_Scan_120_Part2->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Part2"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Part2->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Part2->setSizePolicy(sizePolicy11);

        gridLayout_102->addWidget(w_Pre_Scan_120_Part2, 1, 4, 1, 1);

        label_120_Point_2 = new QLabel(groupBox_Collect_Status_2);
        label_120_Point_2->setObjectName(QString::fromUtf8("label_120_Point_2"));
        sizePolicy8.setHeightForWidth(label_120_Point_2->sizePolicy().hasHeightForWidth());
        label_120_Point_2->setSizePolicy(sizePolicy8);

        gridLayout_102->addWidget(label_120_Point_2, 2, 0, 1, 1);

        w_Pre_Scan_120_Gain = new QLineEdit(groupBox_Collect_Status_2);
        w_Pre_Scan_120_Gain->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Gain"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Gain->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Gain->setSizePolicy(sizePolicy11);

        gridLayout_102->addWidget(w_Pre_Scan_120_Gain, 0, 4, 1, 1);

        set_Pre_Scan_120_Gain = new QPushButton(groupBox_Collect_Status_2);
        set_Pre_Scan_120_Gain->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Gain"));
        sizePolicy9.setHeightForWidth(set_Pre_Scan_120_Gain->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Gain->setSizePolicy(sizePolicy9);

        gridLayout_102->addWidget(set_Pre_Scan_120_Gain, 0, 5, 1, 1);

        label_120_Prog_2 = new QLabel(groupBox_Collect_Status_2);
        label_120_Prog_2->setObjectName(QString::fromUtf8("label_120_Prog_2"));
        sizePolicy8.setHeightForWidth(label_120_Prog_2->sizePolicy().hasHeightForWidth());
        label_120_Prog_2->setSizePolicy(sizePolicy8);

        gridLayout_102->addWidget(label_120_Prog_2, 0, 0, 1, 1);

        set_Pre_Scan_120_currentWheelset = new QPushButton(groupBox_Collect_Status_2);
        set_Pre_Scan_120_currentWheelset->setObjectName(QString::fromUtf8("set_Pre_Scan_120_currentWheelset"));
        sizePolicy9.setHeightForWidth(set_Pre_Scan_120_currentWheelset->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_currentWheelset->setSizePolicy(sizePolicy9);

        gridLayout_102->addWidget(set_Pre_Scan_120_currentWheelset, 0, 2, 1, 1);

        set_Pre_Scan_120_Part2 = new QPushButton(groupBox_Collect_Status_2);
        set_Pre_Scan_120_Part2->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Part2"));
        sizePolicy9.setHeightForWidth(set_Pre_Scan_120_Part2->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Part2->setSizePolicy(sizePolicy9);

        gridLayout_102->addWidget(set_Pre_Scan_120_Part2, 1, 5, 1, 1);

        label_120_Part1_2 = new QLabel(groupBox_Collect_Status_2);
        label_120_Part1_2->setObjectName(QString::fromUtf8("label_120_Part1_2"));
        sizePolicy8.setHeightForWidth(label_120_Part1_2->sizePolicy().hasHeightForWidth());
        label_120_Part1_2->setSizePolicy(sizePolicy8);

        gridLayout_102->addWidget(label_120_Part1_2, 1, 0, 1, 1);


        horizontalLayout_49->addWidget(groupBox_Collect_Status_2);


        gridLayout_24->addLayout(horizontalLayout_49, 2, 0, 1, 1);

        groupBox_MySql = new QGroupBox(groupBox_8);
        groupBox_MySql->setObjectName(QString::fromUtf8("groupBox_MySql"));
        horizontalLayout_55 = new QHBoxLayout(groupBox_MySql);
        horizontalLayout_55->setSpacing(6);
        horizontalLayout_55->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_55->setObjectName(QString::fromUtf8("horizontalLayout_55"));
        label_120_MySql_Status = new QLabel(groupBox_MySql);
        label_120_MySql_Status->setObjectName(QString::fromUtf8("label_120_MySql_Status"));
        sizePolicy8.setHeightForWidth(label_120_MySql_Status->sizePolicy().hasHeightForWidth());
        label_120_MySql_Status->setSizePolicy(sizePolicy8);

        horizontalLayout_55->addWidget(label_120_MySql_Status);

        Pre_Scan_120_MySql_Light = new c_Fr_Light(groupBox_MySql);
        Pre_Scan_120_MySql_Light->setObjectName(QString::fromUtf8("Pre_Scan_120_MySql_Light"));
        Pre_Scan_120_MySql_Light->setMinimumSize(QSize(16, 16));
        Pre_Scan_120_MySql_Light->setMaximumSize(QSize(16, 16));

        horizontalLayout_55->addWidget(Pre_Scan_120_MySql_Light);

        Pre_Scan_120_MySql_Server = new QLineEdit(groupBox_MySql);
        Pre_Scan_120_MySql_Server->setObjectName(QString::fromUtf8("Pre_Scan_120_MySql_Server"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_MySql_Server->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_MySql_Server->setSizePolicy(sizePolicy7);
        Pre_Scan_120_MySql_Server->setMaximumSize(QSize(16777215, 16777215));
        Pre_Scan_120_MySql_Server->setReadOnly(true);

        horizontalLayout_55->addWidget(Pre_Scan_120_MySql_Server);

        label_167 = new QLabel(groupBox_MySql);
        label_167->setObjectName(QString::fromUtf8("label_167"));
        sizePolicy9.setHeightForWidth(label_167->sizePolicy().hasHeightForWidth());
        label_167->setSizePolicy(sizePolicy9);

        horizontalLayout_55->addWidget(label_167);

        MySql_Port = new QLineEdit(groupBox_MySql);
        MySql_Port->setObjectName(QString::fromUtf8("MySql_Port"));
        sizePolicy7.setHeightForWidth(MySql_Port->sizePolicy().hasHeightForWidth());
        MySql_Port->setSizePolicy(sizePolicy7);

        horizontalLayout_55->addWidget(MySql_Port);

        label_156 = new QLabel(groupBox_MySql);
        label_156->setObjectName(QString::fromUtf8("label_156"));
        sizePolicy9.setHeightForWidth(label_156->sizePolicy().hasHeightForWidth());
        label_156->setSizePolicy(sizePolicy9);

        horizontalLayout_55->addWidget(label_156);

        MySql_User = new QLineEdit(groupBox_MySql);
        MySql_User->setObjectName(QString::fromUtf8("MySql_User"));
        sizePolicy7.setHeightForWidth(MySql_User->sizePolicy().hasHeightForWidth());
        MySql_User->setSizePolicy(sizePolicy7);

        horizontalLayout_55->addWidget(MySql_User);

        label_149 = new QLabel(groupBox_MySql);
        label_149->setObjectName(QString::fromUtf8("label_149"));
        sizePolicy8.setHeightForWidth(label_149->sizePolicy().hasHeightForWidth());
        label_149->setSizePolicy(sizePolicy8);

        horizontalLayout_55->addWidget(label_149);

        MySql_Password = new QLineEdit(groupBox_MySql);
        MySql_Password->setObjectName(QString::fromUtf8("MySql_Password"));
        sizePolicy7.setHeightForWidth(MySql_Password->sizePolicy().hasHeightForWidth());
        MySql_Password->setSizePolicy(sizePolicy7);

        horizontalLayout_55->addWidget(MySql_Password);

        label_148 = new QLabel(groupBox_MySql);
        label_148->setObjectName(QString::fromUtf8("label_148"));
        sizePolicy8.setHeightForWidth(label_148->sizePolicy().hasHeightForWidth());
        label_148->setSizePolicy(sizePolicy8);

        horizontalLayout_55->addWidget(label_148);

        MySql_Database = new QLineEdit(groupBox_MySql);
        MySql_Database->setObjectName(QString::fromUtf8("MySql_Database"));
        sizePolicy7.setHeightForWidth(MySql_Database->sizePolicy().hasHeightForWidth());
        MySql_Database->setSizePolicy(sizePolicy7);

        horizontalLayout_55->addWidget(MySql_Database);

        Pre_Scan_120_MySql_Reconnect = new QPushButton(groupBox_MySql);
        Pre_Scan_120_MySql_Reconnect->setObjectName(QString::fromUtf8("Pre_Scan_120_MySql_Reconnect"));

        horizontalLayout_55->addWidget(Pre_Scan_120_MySql_Reconnect);


        gridLayout_24->addWidget(groupBox_MySql, 3, 0, 1, 1);

        groupBox_9 = new QGroupBox(groupBox_8);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        gridLayout_23 = new QGridLayout(groupBox_9);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        Prec_Scan_120_Cmd = new QTextEdit(groupBox_9);
        Prec_Scan_120_Cmd->setObjectName(QString::fromUtf8("Prec_Scan_120_Cmd"));
        Prec_Scan_120_Cmd->setReadOnly(true);

        gridLayout_23->addWidget(Prec_Scan_120_Cmd, 1, 0, 1, 1);


        gridLayout_24->addWidget(groupBox_9, 5, 0, 1, 1);

        horizontalLayout_53 = new QHBoxLayout();
        horizontalLayout_53->setSpacing(6);
        horizontalLayout_53->setObjectName(QString::fromUtf8("horizontalLayout_53"));
        groupBox_Task_Info = new QGroupBox(groupBox_8);
        groupBox_Task_Info->setObjectName(QString::fromUtf8("groupBox_Task_Info"));
        gridLayout_21 = new QGridLayout(groupBox_Task_Info);
        gridLayout_21->setSpacing(6);
        gridLayout_21->setContentsMargins(11, 11, 11, 11);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        label_120_TaskID = new QLabel(groupBox_Task_Info);
        label_120_TaskID->setObjectName(QString::fromUtf8("label_120_TaskID"));
        sizePolicy8.setHeightForWidth(label_120_TaskID->sizePolicy().hasHeightForWidth());
        label_120_TaskID->setSizePolicy(sizePolicy8);

        gridLayout_21->addWidget(label_120_TaskID, 0, 0, 1, 1);

        label_120_Wheelset = new QLabel(groupBox_Task_Info);
        label_120_Wheelset->setObjectName(QString::fromUtf8("label_120_Wheelset"));
        sizePolicy8.setHeightForWidth(label_120_Wheelset->sizePolicy().hasHeightForWidth());
        label_120_Wheelset->setSizePolicy(sizePolicy8);

        gridLayout_21->addWidget(label_120_Wheelset, 0, 11, 1, 1);

        r_Pre_Scan_120_TaskID = new QLineEdit(groupBox_Task_Info);
        r_Pre_Scan_120_TaskID->setObjectName(QString::fromUtf8("r_Pre_Scan_120_TaskID"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_TaskID->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_TaskID->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_TaskID->setMaximumSize(QSize(16777215, 16777215));
        r_Pre_Scan_120_TaskID->setReadOnly(true);

        gridLayout_21->addWidget(r_Pre_Scan_120_TaskID, 0, 1, 1, 1);

        label_120_StartTime = new QLabel(groupBox_Task_Info);
        label_120_StartTime->setObjectName(QString::fromUtf8("label_120_StartTime"));
        sizePolicy8.setHeightForWidth(label_120_StartTime->sizePolicy().hasHeightForWidth());
        label_120_StartTime->setSizePolicy(sizePolicy8);

        gridLayout_21->addWidget(label_120_StartTime, 1, 0, 1, 1);

        r_Pre_Scan_120_Wheelset = new QLineEdit(groupBox_Task_Info);
        r_Pre_Scan_120_Wheelset->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Wheelset"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_Wheelset->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_Wheelset->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_Wheelset->setMaximumSize(QSize(16777215, 16777215));
        r_Pre_Scan_120_Wheelset->setReadOnly(true);

        gridLayout_21->addWidget(r_Pre_Scan_120_Wheelset, 0, 12, 1, 1);

        r_Pre_Scan_120_StartTime = new QLineEdit(groupBox_Task_Info);
        r_Pre_Scan_120_StartTime->setObjectName(QString::fromUtf8("r_Pre_Scan_120_StartTime"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_StartTime->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_StartTime->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_StartTime->setMaximumSize(QSize(16777215, 16777215));
        r_Pre_Scan_120_StartTime->setReadOnly(true);

        gridLayout_21->addWidget(r_Pre_Scan_120_StartTime, 1, 1, 1, 1);

        r_Pre_Scan_120_Axle = new QLineEdit(groupBox_Task_Info);
        r_Pre_Scan_120_Axle->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Axle"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_Axle->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_Axle->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_Axle->setMaximumSize(QSize(16777215, 16777215));
        r_Pre_Scan_120_Axle->setReadOnly(true);

        gridLayout_21->addWidget(r_Pre_Scan_120_Axle, 1, 12, 1, 1);

        label_120_Axle = new QLabel(groupBox_Task_Info);
        label_120_Axle->setObjectName(QString::fromUtf8("label_120_Axle"));
        sizePolicy8.setHeightForWidth(label_120_Axle->sizePolicy().hasHeightForWidth());
        label_120_Axle->setSizePolicy(sizePolicy8);

        gridLayout_21->addWidget(label_120_Axle, 1, 11, 1, 1);

        label_120_Repair = new QLabel(groupBox_Task_Info);
        label_120_Repair->setObjectName(QString::fromUtf8("label_120_Repair"));
        sizePolicy8.setHeightForWidth(label_120_Repair->sizePolicy().hasHeightForWidth());
        label_120_Repair->setSizePolicy(sizePolicy8);

        gridLayout_21->addWidget(label_120_Repair, 2, 0, 1, 1);

        r_Pre_Scan_120_Repair = new QLineEdit(groupBox_Task_Info);
        r_Pre_Scan_120_Repair->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Repair"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_Repair->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_Repair->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_Repair->setMaximumSize(QSize(16777215, 16777215));
        r_Pre_Scan_120_Repair->setReadOnly(true);

        gridLayout_21->addWidget(r_Pre_Scan_120_Repair, 2, 1, 1, 1);

        label_120_SendUnit = new QLabel(groupBox_Task_Info);
        label_120_SendUnit->setObjectName(QString::fromUtf8("label_120_SendUnit"));
        sizePolicy8.setHeightForWidth(label_120_SendUnit->sizePolicy().hasHeightForWidth());
        label_120_SendUnit->setSizePolicy(sizePolicy8);

        gridLayout_21->addWidget(label_120_SendUnit, 2, 11, 1, 1);

        r_Pre_Scan_120_SendUnit = new QLineEdit(groupBox_Task_Info);
        r_Pre_Scan_120_SendUnit->setObjectName(QString::fromUtf8("r_Pre_Scan_120_SendUnit"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_SendUnit->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_SendUnit->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_SendUnit->setMaximumSize(QSize(16777215, 16777215));
        r_Pre_Scan_120_SendUnit->setReadOnly(true);

        gridLayout_21->addWidget(r_Pre_Scan_120_SendUnit, 2, 12, 1, 1);


        horizontalLayout_53->addWidget(groupBox_Task_Info);

        groupBox_Collect_Status = new QGroupBox(groupBox_8);
        groupBox_Collect_Status->setObjectName(QString::fromUtf8("groupBox_Collect_Status"));
        gridLayout_26 = new QGridLayout(groupBox_Collect_Status);
        gridLayout_26->setSpacing(6);
        gridLayout_26->setContentsMargins(11, 11, 11, 11);
        gridLayout_26->setObjectName(QString::fromUtf8("gridLayout_26"));
        r_Pre_Scan_120_Gain = new QLineEdit(groupBox_Collect_Status);
        r_Pre_Scan_120_Gain->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Gain"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_Gain->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_Gain->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_Gain->setMaximumSize(QSize(16777215, 16777215));
        r_Pre_Scan_120_Gain->setReadOnly(true);

        gridLayout_26->addWidget(r_Pre_Scan_120_Gain, 0, 5, 1, 1);

        r_Pre_Scan_120_Point = new QLineEdit(groupBox_Collect_Status);
        r_Pre_Scan_120_Point->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Point"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_Point->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_Point->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_Point->setReadOnly(true);

        gridLayout_26->addWidget(r_Pre_Scan_120_Point, 2, 3, 1, 1);

        r_Pre_Scan_120_Part2 = new QLineEdit(groupBox_Collect_Status);
        r_Pre_Scan_120_Part2->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Part2"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_Part2->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_Part2->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_Part2->setReadOnly(true);

        gridLayout_26->addWidget(r_Pre_Scan_120_Part2, 1, 5, 1, 1);

        label_120_LastUpdate = new QLabel(groupBox_Collect_Status);
        label_120_LastUpdate->setObjectName(QString::fromUtf8("label_120_LastUpdate"));
        sizePolicy8.setHeightForWidth(label_120_LastUpdate->sizePolicy().hasHeightForWidth());
        label_120_LastUpdate->setSizePolicy(sizePolicy8);

        gridLayout_26->addWidget(label_120_LastUpdate, 2, 4, 1, 1);

        label_120_Prog = new QLabel(groupBox_Collect_Status);
        label_120_Prog->setObjectName(QString::fromUtf8("label_120_Prog"));
        sizePolicy8.setHeightForWidth(label_120_Prog->sizePolicy().hasHeightForWidth());
        label_120_Prog->setSizePolicy(sizePolicy8);

        gridLayout_26->addWidget(label_120_Prog, 0, 0, 1, 1);

        label_120_Part2 = new QLabel(groupBox_Collect_Status);
        label_120_Part2->setObjectName(QString::fromUtf8("label_120_Part2"));
        sizePolicy8.setHeightForWidth(label_120_Part2->sizePolicy().hasHeightForWidth());
        label_120_Part2->setSizePolicy(sizePolicy8);

        gridLayout_26->addWidget(label_120_Part2, 1, 4, 1, 1);

        label_120_Point = new QLabel(groupBox_Collect_Status);
        label_120_Point->setObjectName(QString::fromUtf8("label_120_Point"));
        sizePolicy8.setHeightForWidth(label_120_Point->sizePolicy().hasHeightForWidth());
        label_120_Point->setSizePolicy(sizePolicy8);

        gridLayout_26->addWidget(label_120_Point, 2, 0, 1, 1);

        Pre_Scan_120_LastUpdate = new QLineEdit(groupBox_Collect_Status);
        Pre_Scan_120_LastUpdate->setObjectName(QString::fromUtf8("Pre_Scan_120_LastUpdate"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_LastUpdate->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_LastUpdate->setSizePolicy(sizePolicy7);
        Pre_Scan_120_LastUpdate->setMaximumSize(QSize(16777215, 16777215));
        Pre_Scan_120_LastUpdate->setReadOnly(true);

        gridLayout_26->addWidget(Pre_Scan_120_LastUpdate, 2, 5, 1, 1);

        r_Pre_Scan_120_Part1 = new QLineEdit(groupBox_Collect_Status);
        r_Pre_Scan_120_Part1->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Part1"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_Part1->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_Part1->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_Part1->setReadOnly(true);

        gridLayout_26->addWidget(r_Pre_Scan_120_Part1, 1, 3, 1, 1);

        r_Pre_Scan_120_currentWheelset = new QLineEdit(groupBox_Collect_Status);
        r_Pre_Scan_120_currentWheelset->setObjectName(QString::fromUtf8("r_Pre_Scan_120_currentWheelset"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_currentWheelset->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_currentWheelset->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_currentWheelset->setReadOnly(true);

        gridLayout_26->addWidget(r_Pre_Scan_120_currentWheelset, 0, 3, 1, 1);

        label_120_Gain = new QLabel(groupBox_Collect_Status);
        label_120_Gain->setObjectName(QString::fromUtf8("label_120_Gain"));
        sizePolicy8.setHeightForWidth(label_120_Gain->sizePolicy().hasHeightForWidth());
        label_120_Gain->setSizePolicy(sizePolicy8);

        gridLayout_26->addWidget(label_120_Gain, 0, 4, 1, 1);

        label_120_Part1 = new QLabel(groupBox_Collect_Status);
        label_120_Part1->setObjectName(QString::fromUtf8("label_120_Part1"));
        sizePolicy8.setHeightForWidth(label_120_Part1->sizePolicy().hasHeightForWidth());
        label_120_Part1->setSizePolicy(sizePolicy8);

        gridLayout_26->addWidget(label_120_Part1, 1, 0, 1, 1);


        horizontalLayout_53->addWidget(groupBox_Collect_Status);

        groupBox_Control = new QGroupBox(groupBox_8);
        groupBox_Control->setObjectName(QString::fromUtf8("groupBox_Control"));
        gridLayout_25 = new QGridLayout(groupBox_Control);
        gridLayout_25->setSpacing(6);
        gridLayout_25->setContentsMargins(11, 11, 11, 11);
        gridLayout_25->setObjectName(QString::fromUtf8("gridLayout_25"));
        Pre_Scan_120_Collector = new QPushButton(groupBox_Control);
        Pre_Scan_120_Collector->setObjectName(QString::fromUtf8("Pre_Scan_120_Collector"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_Collector->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_Collector->setSizePolicy(sizePolicy7);
        Pre_Scan_120_Collector->setMinimumSize(QSize(100, 32));

        gridLayout_25->addWidget(Pre_Scan_120_Collector, 0, 1, 1, 1);

        Pre_Scan_120_Finish_Scan = new QPushButton(groupBox_Control);
        Pre_Scan_120_Finish_Scan->setObjectName(QString::fromUtf8("Pre_Scan_120_Finish_Scan"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_Finish_Scan->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_Finish_Scan->setSizePolicy(sizePolicy7);
        Pre_Scan_120_Finish_Scan->setMinimumSize(QSize(100, 32));

        gridLayout_25->addWidget(Pre_Scan_120_Finish_Scan, 1, 0, 1, 1);

        horizontalLayout_54 = new QHBoxLayout();
        horizontalLayout_54->setSpacing(6);
        horizontalLayout_54->setObjectName(QString::fromUtf8("horizontalLayout_54"));
        Pre_Scan_120_Gain_Spin = new QSpinBox(groupBox_Control);
        Pre_Scan_120_Gain_Spin->setObjectName(QString::fromUtf8("Pre_Scan_120_Gain_Spin"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_Gain_Spin->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_Gain_Spin->setSizePolicy(sizePolicy7);
        Pre_Scan_120_Gain_Spin->setMinimum(0);
        Pre_Scan_120_Gain_Spin->setMaximum(100);
        Pre_Scan_120_Gain_Spin->setValue(20);

        horizontalLayout_54->addWidget(Pre_Scan_120_Gain_Spin);

        Pre_Scan_120_Change_Gain = new QPushButton(groupBox_Control);
        Pre_Scan_120_Change_Gain->setObjectName(QString::fromUtf8("Pre_Scan_120_Change_Gain"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_Change_Gain->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_Change_Gain->setSizePolicy(sizePolicy7);

        horizontalLayout_54->addWidget(Pre_Scan_120_Change_Gain);


        gridLayout_25->addLayout(horizontalLayout_54, 1, 1, 1, 1);

        Pre_Scan_120_Start_Scan = new QPushButton(groupBox_Control);
        Pre_Scan_120_Start_Scan->setObjectName(QString::fromUtf8("Pre_Scan_120_Start_Scan"));
        sizePolicy7.setHeightForWidth(Pre_Scan_120_Start_Scan->sizePolicy().hasHeightForWidth());
        Pre_Scan_120_Start_Scan->setSizePolicy(sizePolicy7);
        Pre_Scan_120_Start_Scan->setMinimumSize(QSize(100, 32));

        gridLayout_25->addWidget(Pre_Scan_120_Start_Scan, 0, 0, 1, 1);


        horizontalLayout_53->addWidget(groupBox_Control);


        gridLayout_24->addLayout(horizontalLayout_53, 1, 0, 1, 1);


        gridLayout_20->addWidget(groupBox_8, 0, 0, 1, 1);

        stackedWidget->addWidget(Pre_Scan_120_Widget);
        IO_Widget = new QWidget();
        IO_Widget->setObjectName(QString::fromUtf8("IO_Widget"));
        gridLayout_29 = new QGridLayout(IO_Widget);
        gridLayout_29->setSpacing(6);
        gridLayout_29->setContentsMargins(11, 11, 11, 11);
        gridLayout_29->setObjectName(QString::fromUtf8("gridLayout_29"));
        groupBox_2 = new QGroupBox(IO_Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_31 = new QGridLayout(groupBox_2);
        gridLayout_31->setSpacing(6);
        gridLayout_31->setContentsMargins(11, 11, 11, 11);
        gridLayout_31->setObjectName(QString::fromUtf8("gridLayout_31"));
        groupBox_24 = new QGroupBox(groupBox_2);
        groupBox_24->setObjectName(QString::fromUtf8("groupBox_24"));
        sizePolicy3.setHeightForWidth(groupBox_24->sizePolicy().hasHeightForWidth());
        groupBox_24->setSizePolicy(sizePolicy3);
        gridLayout_30 = new QGridLayout(groupBox_24);
        gridLayout_30->setSpacing(4);
        gridLayout_30->setContentsMargins(11, 11, 11, 11);
        gridLayout_30->setObjectName(QString::fromUtf8("gridLayout_30"));
        gridLayout_30->setContentsMargins(6, 6, 6, 6);
        label_280 = new QLabel(groupBox_24);
        label_280->setObjectName(QString::fromUtf8("label_280"));
        sizePolicy3.setHeightForWidth(label_280->sizePolicy().hasHeightForWidth());
        label_280->setSizePolicy(sizePolicy3);

        gridLayout_30->addWidget(label_280, 5, 1, 1, 1);

        Write_IO_HoldingRegisters_Size = new QSpinBox(groupBox_24);
        Write_IO_HoldingRegisters_Size->setObjectName(QString::fromUtf8("Write_IO_HoldingRegisters_Size"));
        sizePolicy7.setHeightForWidth(Write_IO_HoldingRegisters_Size->sizePolicy().hasHeightForWidth());
        Write_IO_HoldingRegisters_Size->setSizePolicy(sizePolicy7);
        Write_IO_HoldingRegisters_Size->setMaximum(9999);
        Write_IO_HoldingRegisters_Size->setValue(4);

        gridLayout_30->addWidget(Write_IO_HoldingRegisters_Size, 5, 2, 1, 1);

        Write_IO_Coils_Addr = new QSpinBox(groupBox_24);
        Write_IO_Coils_Addr->setObjectName(QString::fromUtf8("Write_IO_Coils_Addr"));
        sizePolicy7.setHeightForWidth(Write_IO_Coils_Addr->sizePolicy().hasHeightForWidth());
        Write_IO_Coils_Addr->setSizePolicy(sizePolicy7);
        Write_IO_Coils_Addr->setMaximum(9999);

        gridLayout_30->addWidget(Write_IO_Coils_Addr, 2, 2, 1, 1);

        Write_IO_HoldingRegisters_Addr = new QSpinBox(groupBox_24);
        Write_IO_HoldingRegisters_Addr->setObjectName(QString::fromUtf8("Write_IO_HoldingRegisters_Addr"));
        sizePolicy7.setHeightForWidth(Write_IO_HoldingRegisters_Addr->sizePolicy().hasHeightForWidth());
        Write_IO_HoldingRegisters_Addr->setSizePolicy(sizePolicy7);
        Write_IO_HoldingRegisters_Addr->setMaximum(9999);

        gridLayout_30->addWidget(Write_IO_HoldingRegisters_Addr, 4, 2, 1, 1);

        label_281 = new QLabel(groupBox_24);
        label_281->setObjectName(QString::fromUtf8("label_281"));
        sizePolicy8.setHeightForWidth(label_281->sizePolicy().hasHeightForWidth());
        label_281->setSizePolicy(sizePolicy8);

        gridLayout_30->addWidget(label_281, 2, 1, 1, 1);

        Write_IO_Coils_Size = new QSpinBox(groupBox_24);
        Write_IO_Coils_Size->setObjectName(QString::fromUtf8("Write_IO_Coils_Size"));
        sizePolicy7.setHeightForWidth(Write_IO_Coils_Size->sizePolicy().hasHeightForWidth());
        Write_IO_Coils_Size->setSizePolicy(sizePolicy7);
        Write_IO_Coils_Size->setMaximum(9999);
        Write_IO_Coils_Size->setValue(16);

        gridLayout_30->addWidget(Write_IO_Coils_Size, 3, 2, 1, 1);

        label_274 = new QLabel(groupBox_24);
        label_274->setObjectName(QString::fromUtf8("label_274"));
        sizePolicy3.setHeightForWidth(label_274->sizePolicy().hasHeightForWidth());
        label_274->setSizePolicy(sizePolicy3);

        gridLayout_30->addWidget(label_274, 4, 1, 1, 1);

        label_139 = new QLabel(groupBox_24);
        label_139->setObjectName(QString::fromUtf8("label_139"));
        sizePolicy7.setHeightForWidth(label_139->sizePolicy().hasHeightForWidth());
        label_139->setSizePolicy(sizePolicy7);

        gridLayout_30->addWidget(label_139, 0, 1, 1, 1);

        label_122 = new QLabel(groupBox_24);
        label_122->setObjectName(QString::fromUtf8("label_122"));
        sizePolicy7.setHeightForWidth(label_122->sizePolicy().hasHeightForWidth());
        label_122->setSizePolicy(sizePolicy7);

        gridLayout_30->addWidget(label_122, 1, 1, 1, 1);

        IO_Ip = new QLineEdit(groupBox_24);
        IO_Ip->setObjectName(QString::fromUtf8("IO_Ip"));
        sizePolicy11.setHeightForWidth(IO_Ip->sizePolicy().hasHeightForWidth());
        IO_Ip->setSizePolicy(sizePolicy11);

        gridLayout_30->addWidget(IO_Ip, 0, 2, 1, 1);

        IO_Port = new QLineEdit(groupBox_24);
        IO_Port->setObjectName(QString::fromUtf8("IO_Port"));
        sizePolicy11.setHeightForWidth(IO_Port->sizePolicy().hasHeightForWidth());
        IO_Port->setSizePolicy(sizePolicy11);

        gridLayout_30->addWidget(IO_Port, 1, 2, 1, 1);

        label_273 = new QLabel(groupBox_24);
        label_273->setObjectName(QString::fromUtf8("label_273"));
        sizePolicy8.setHeightForWidth(label_273->sizePolicy().hasHeightForWidth());
        label_273->setSizePolicy(sizePolicy8);

        gridLayout_30->addWidget(label_273, 3, 1, 1, 1);


        gridLayout_31->addWidget(groupBox_24, 0, 1, 1, 1);

        groupBox_IO_DO = new QGroupBox(groupBox_2);
        groupBox_IO_DO->setObjectName(QString::fromUtf8("groupBox_IO_DO"));
        sizePolicy.setHeightForWidth(groupBox_IO_DO->sizePolicy().hasHeightForWidth());
        groupBox_IO_DO->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox_IO_DO);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn_IO_AlarmGreen_ON = new QPushButton(groupBox_IO_DO);
        btn_IO_AlarmGreen_ON->setObjectName(QString::fromUtf8("btn_IO_AlarmGreen_ON"));

        gridLayout->addWidget(btn_IO_AlarmGreen_ON, 0, 5, 1, 1);

        btn_IO_Robot_OFF = new QPushButton(groupBox_IO_DO);
        btn_IO_Robot_OFF->setObjectName(QString::fromUtf8("btn_IO_Robot_OFF"));

        gridLayout->addWidget(btn_IO_Robot_OFF, 1, 9, 1, 1);

        Coils_1 = new c_Fr_Light(groupBox_IO_DO);
        Coils_1->setObjectName(QString::fromUtf8("Coils_1"));
        Coils_1->setMinimumSize(QSize(20, 20));
        Coils_1->setMaximumSize(QSize(20, 20));

        gridLayout->addWidget(Coils_1, 0, 0, 1, 1);

        Coils_5 = new c_Fr_Light(groupBox_IO_DO);
        Coils_5->setObjectName(QString::fromUtf8("Coils_5"));
        Coils_5->setMinimumSize(QSize(20, 20));
        Coils_5->setMaximumSize(QSize(20, 20));

        gridLayout->addWidget(Coils_5, 0, 8, 1, 1);

        Coils_4 = new c_Fr_Light(groupBox_IO_DO);
        Coils_4->setObjectName(QString::fromUtf8("Coils_4"));
        Coils_4->setMinimumSize(QSize(20, 20));
        Coils_4->setMaximumSize(QSize(20, 20));

        gridLayout->addWidget(Coils_4, 0, 6, 1, 1);

        btn_IO_AlarmGreen_OFF = new QPushButton(groupBox_IO_DO);
        btn_IO_AlarmGreen_OFF->setObjectName(QString::fromUtf8("btn_IO_AlarmGreen_OFF"));

        gridLayout->addWidget(btn_IO_AlarmGreen_OFF, 1, 5, 1, 1);

        btn_IO_Fan_OFF = new QPushButton(groupBox_IO_DO);
        btn_IO_Fan_OFF->setObjectName(QString::fromUtf8("btn_IO_Fan_OFF"));

        gridLayout->addWidget(btn_IO_Fan_OFF, 1, 7, 1, 1);

        btn_IO_AlarmYellow_OFF = new QPushButton(groupBox_IO_DO);
        btn_IO_AlarmYellow_OFF->setObjectName(QString::fromUtf8("btn_IO_AlarmYellow_OFF"));

        gridLayout->addWidget(btn_IO_AlarmYellow_OFF, 1, 3, 1, 1);

        btn_IO_Fan_ON = new QPushButton(groupBox_IO_DO);
        btn_IO_Fan_ON->setObjectName(QString::fromUtf8("btn_IO_Fan_ON"));

        gridLayout->addWidget(btn_IO_Fan_ON, 0, 7, 1, 1);

        btn_IO_AlarmRed_OFF = new QPushButton(groupBox_IO_DO);
        btn_IO_AlarmRed_OFF->setObjectName(QString::fromUtf8("btn_IO_AlarmRed_OFF"));

        gridLayout->addWidget(btn_IO_AlarmRed_OFF, 1, 1, 1, 1);

        Coils_2 = new c_Fr_Light(groupBox_IO_DO);
        Coils_2->setObjectName(QString::fromUtf8("Coils_2"));
        Coils_2->setMinimumSize(QSize(20, 20));
        Coils_2->setMaximumSize(QSize(20, 20));

        gridLayout->addWidget(Coils_2, 0, 2, 1, 1);

        btn_IO_Robot_ON = new QPushButton(groupBox_IO_DO);
        btn_IO_Robot_ON->setObjectName(QString::fromUtf8("btn_IO_Robot_ON"));

        gridLayout->addWidget(btn_IO_Robot_ON, 0, 9, 1, 1);

        Coils_6 = new c_Fr_Light(groupBox_IO_DO);
        Coils_6->setObjectName(QString::fromUtf8("Coils_6"));
        Coils_6->setMinimumSize(QSize(20, 20));
        Coils_6->setMaximumSize(QSize(20, 20));

        gridLayout->addWidget(Coils_6, 1, 8, 1, 1);

        Coils_3 = new c_Fr_Light(groupBox_IO_DO);
        Coils_3->setObjectName(QString::fromUtf8("Coils_3"));
        Coils_3->setMinimumSize(QSize(20, 20));
        Coils_3->setMaximumSize(QSize(20, 20));

        gridLayout->addWidget(Coils_3, 0, 4, 1, 1);

        btn_IO_AlarmRed_ON = new QPushButton(groupBox_IO_DO);
        btn_IO_AlarmRed_ON->setObjectName(QString::fromUtf8("btn_IO_AlarmRed_ON"));

        gridLayout->addWidget(btn_IO_AlarmRed_ON, 0, 1, 1, 1);

        btn_IO_AlarmYellow_ON = new QPushButton(groupBox_IO_DO);
        btn_IO_AlarmYellow_ON->setObjectName(QString::fromUtf8("btn_IO_AlarmYellow_ON"));

        gridLayout->addWidget(btn_IO_AlarmYellow_ON, 0, 3, 1, 1);


        gridLayout_31->addWidget(groupBox_IO_DO, 2, 1, 1, 1);

        groupBox_IO_Connect = new QGroupBox(groupBox_2);
        groupBox_IO_Connect->setObjectName(QString::fromUtf8("groupBox_IO_Connect"));
        sizePolicy.setHeightForWidth(groupBox_IO_Connect->sizePolicy().hasHeightForWidth());
        groupBox_IO_Connect->setSizePolicy(sizePolicy);
        gridLayout_32 = new QGridLayout(groupBox_IO_Connect);
        gridLayout_32->setSpacing(6);
        gridLayout_32->setContentsMargins(11, 11, 11, 11);
        gridLayout_32->setObjectName(QString::fromUtf8("gridLayout_32"));
        label_25 = new QLabel(groupBox_IO_Connect);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_32->addWidget(label_25, 0, 0, 1, 1);

        IO_Connected = new c_Fr_Light(groupBox_IO_Connect);
        IO_Connected->setObjectName(QString::fromUtf8("IO_Connected"));
        IO_Connected->setMinimumSize(QSize(20, 20));

        gridLayout_32->addWidget(IO_Connected, 0, 1, 1, 1);

        label_24 = new QLabel(groupBox_IO_Connect);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_32->addWidget(label_24, 0, 2, 1, 1);

        IO_Ready = new c_Fr_Light(groupBox_IO_Connect);
        IO_Ready->setObjectName(QString::fromUtf8("IO_Ready"));
        IO_Ready->setMinimumSize(QSize(20, 20));

        gridLayout_32->addWidget(IO_Ready, 0, 3, 1, 1);

        IO_Connect = new QPushButton(groupBox_IO_Connect);
        IO_Connect->setObjectName(QString::fromUtf8("IO_Connect"));
        IO_Connect->setMinimumSize(QSize(80, 0));

        gridLayout_32->addWidget(IO_Connect, 0, 4, 1, 1);

        IO_Disconnect = new QPushButton(groupBox_IO_Connect);
        IO_Disconnect->setObjectName(QString::fromUtf8("IO_Disconnect"));
        IO_Disconnect->setMinimumSize(QSize(80, 0));

        gridLayout_32->addWidget(IO_Disconnect, 0, 5, 1, 1);


        gridLayout_31->addWidget(groupBox_IO_Connect, 1, 1, 1, 1);


        gridLayout_29->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_11 = new QGroupBox(IO_Widget);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        gridLayout_34 = new QGridLayout(groupBox_11);
        gridLayout_34->setSpacing(6);
        gridLayout_34->setContentsMargins(11, 11, 11, 11);
        gridLayout_34->setObjectName(QString::fromUtf8("gridLayout_34"));
        groupBox_Voice_Config = new QGroupBox(groupBox_11);
        groupBox_Voice_Config->setObjectName(QString::fromUtf8("groupBox_Voice_Config"));
        gridLayout_28 = new QGridLayout(groupBox_Voice_Config);
        gridLayout_28->setSpacing(6);
        gridLayout_28->setContentsMargins(11, 11, 11, 11);
        gridLayout_28->setObjectName(QString::fromUtf8("gridLayout_28"));
        label_Voice_Com = new QLabel(groupBox_Voice_Config);
        label_Voice_Com->setObjectName(QString::fromUtf8("label_Voice_Com"));
        sizePolicy8.setHeightForWidth(label_Voice_Com->sizePolicy().hasHeightForWidth());
        label_Voice_Com->setSizePolicy(sizePolicy8);

        gridLayout_28->addWidget(label_Voice_Com, 0, 0, 1, 1);

        Voice_Com = new QComboBox(groupBox_Voice_Config);
        Voice_Com->setObjectName(QString::fromUtf8("Voice_Com"));
        sizePolicy7.setHeightForWidth(Voice_Com->sizePolicy().hasHeightForWidth());
        Voice_Com->setSizePolicy(sizePolicy7);
        Voice_Com->setEditable(true);

        gridLayout_28->addWidget(Voice_Com, 0, 1, 1, 1);

        label_Voice_Baud = new QLabel(groupBox_Voice_Config);
        label_Voice_Baud->setObjectName(QString::fromUtf8("label_Voice_Baud"));
        sizePolicy8.setHeightForWidth(label_Voice_Baud->sizePolicy().hasHeightForWidth());
        label_Voice_Baud->setSizePolicy(sizePolicy8);

        gridLayout_28->addWidget(label_Voice_Baud, 0, 2, 1, 1);

        Voice_Baud = new QComboBox(groupBox_Voice_Config);
        Voice_Baud->addItem(QString());
        Voice_Baud->addItem(QString());
        Voice_Baud->addItem(QString());
        Voice_Baud->addItem(QString());
        Voice_Baud->setObjectName(QString::fromUtf8("Voice_Baud"));
        sizePolicy7.setHeightForWidth(Voice_Baud->sizePolicy().hasHeightForWidth());
        Voice_Baud->setSizePolicy(sizePolicy7);

        gridLayout_28->addWidget(Voice_Baud, 0, 3, 1, 1);

        label_Voice_Addr = new QLabel(groupBox_Voice_Config);
        label_Voice_Addr->setObjectName(QString::fromUtf8("label_Voice_Addr"));
        sizePolicy8.setHeightForWidth(label_Voice_Addr->sizePolicy().hasHeightForWidth());
        label_Voice_Addr->setSizePolicy(sizePolicy8);

        gridLayout_28->addWidget(label_Voice_Addr, 1, 0, 1, 1);

        Voice_Addr = new QSpinBox(groupBox_Voice_Config);
        Voice_Addr->setObjectName(QString::fromUtf8("Voice_Addr"));
        sizePolicy7.setHeightForWidth(Voice_Addr->sizePolicy().hasHeightForWidth());
        Voice_Addr->setSizePolicy(sizePolicy7);
        Voice_Addr->setMinimum(1);
        Voice_Addr->setMaximum(255);
        Voice_Addr->setValue(1);

        gridLayout_28->addWidget(Voice_Addr, 1, 1, 1, 1);

        label_Voice_Connected = new QLabel(groupBox_Voice_Config);
        label_Voice_Connected->setObjectName(QString::fromUtf8("label_Voice_Connected"));
        sizePolicy8.setHeightForWidth(label_Voice_Connected->sizePolicy().hasHeightForWidth());
        label_Voice_Connected->setSizePolicy(sizePolicy8);

        gridLayout_28->addWidget(label_Voice_Connected, 2, 0, 1, 1);

        Voice_Connected = new c_Fr_Light(groupBox_Voice_Config);
        Voice_Connected->setObjectName(QString::fromUtf8("Voice_Connected"));
        Voice_Connected->setMinimumSize(QSize(20, 20));

        gridLayout_28->addWidget(Voice_Connected, 2, 1, 1, 1);

        label_Voice_Volume = new QLabel(groupBox_Voice_Config);
        label_Voice_Volume->setObjectName(QString::fromUtf8("label_Voice_Volume"));
        sizePolicy8.setHeightForWidth(label_Voice_Volume->sizePolicy().hasHeightForWidth());
        label_Voice_Volume->setSizePolicy(sizePolicy8);

        gridLayout_28->addWidget(label_Voice_Volume, 2, 2, 1, 1);

        horizontalLayout_46 = new QHBoxLayout();
        horizontalLayout_46->setSpacing(6);
        horizontalLayout_46->setObjectName(QString::fromUtf8("horizontalLayout_46"));
        Voice_Connect = new QPushButton(groupBox_Voice_Config);
        Voice_Connect->setObjectName(QString::fromUtf8("Voice_Connect"));
        sizePolicy7.setHeightForWidth(Voice_Connect->sizePolicy().hasHeightForWidth());
        Voice_Connect->setSizePolicy(sizePolicy7);

        horizontalLayout_46->addWidget(Voice_Connect);

        Voice_Disconnect = new QPushButton(groupBox_Voice_Config);
        Voice_Disconnect->setObjectName(QString::fromUtf8("Voice_Disconnect"));
        sizePolicy7.setHeightForWidth(Voice_Disconnect->sizePolicy().hasHeightForWidth());
        Voice_Disconnect->setSizePolicy(sizePolicy7);

        horizontalLayout_46->addWidget(Voice_Disconnect);


        gridLayout_28->addLayout(horizontalLayout_46, 1, 2, 1, 2);

        Voice_Volume_Display = new QLineEdit(groupBox_Voice_Config);
        Voice_Volume_Display->setObjectName(QString::fromUtf8("Voice_Volume_Display"));
        sizePolicy7.setHeightForWidth(Voice_Volume_Display->sizePolicy().hasHeightForWidth());
        Voice_Volume_Display->setSizePolicy(sizePolicy7);
        Voice_Volume_Display->setReadOnly(true);

        gridLayout_28->addWidget(Voice_Volume_Display, 2, 3, 1, 1);


        gridLayout_34->addWidget(groupBox_Voice_Config, 0, 0, 2, 2);

        groupBox_Voice_Info = new QGroupBox(groupBox_11);
        groupBox_Voice_Info->setObjectName(QString::fromUtf8("groupBox_Voice_Info"));
        gridLayout_Voice_Info = new QGridLayout(groupBox_Voice_Info);
        gridLayout_Voice_Info->setSpacing(6);
        gridLayout_Voice_Info->setContentsMargins(11, 11, 11, 11);
        gridLayout_Voice_Info->setObjectName(QString::fromUtf8("gridLayout_Voice_Info"));
        label_Voice_Device_Status = new QLabel(groupBox_Voice_Info);
        label_Voice_Device_Status->setObjectName(QString::fromUtf8("label_Voice_Device_Status"));
        sizePolicy8.setHeightForWidth(label_Voice_Device_Status->sizePolicy().hasHeightForWidth());
        label_Voice_Device_Status->setSizePolicy(sizePolicy8);

        gridLayout_Voice_Info->addWidget(label_Voice_Device_Status, 0, 0, 1, 1);

        Voice_Device_Status = new QLineEdit(groupBox_Voice_Info);
        Voice_Device_Status->setObjectName(QString::fromUtf8("Voice_Device_Status"));
        sizePolicy7.setHeightForWidth(Voice_Device_Status->sizePolicy().hasHeightForWidth());
        Voice_Device_Status->setSizePolicy(sizePolicy7);
        Voice_Device_Status->setReadOnly(true);

        gridLayout_Voice_Info->addWidget(Voice_Device_Status, 0, 1, 1, 1);

        label_Voice_Current_Audio = new QLabel(groupBox_Voice_Info);
        label_Voice_Current_Audio->setObjectName(QString::fromUtf8("label_Voice_Current_Audio"));
        sizePolicy8.setHeightForWidth(label_Voice_Current_Audio->sizePolicy().hasHeightForWidth());
        label_Voice_Current_Audio->setSizePolicy(sizePolicy8);

        gridLayout_Voice_Info->addWidget(label_Voice_Current_Audio, 1, 0, 1, 1);

        Voice_Current_Audio = new QLineEdit(groupBox_Voice_Info);
        Voice_Current_Audio->setObjectName(QString::fromUtf8("Voice_Current_Audio"));
        sizePolicy7.setHeightForWidth(Voice_Current_Audio->sizePolicy().hasHeightForWidth());
        Voice_Current_Audio->setSizePolicy(sizePolicy7);
        Voice_Current_Audio->setReadOnly(true);

        gridLayout_Voice_Info->addWidget(Voice_Current_Audio, 1, 1, 1, 1);

        label_Voice_Count = new QLabel(groupBox_Voice_Info);
        label_Voice_Count->setObjectName(QString::fromUtf8("label_Voice_Count"));
        sizePolicy8.setHeightForWidth(label_Voice_Count->sizePolicy().hasHeightForWidth());
        label_Voice_Count->setSizePolicy(sizePolicy8);

        gridLayout_Voice_Info->addWidget(label_Voice_Count, 2, 0, 1, 1);

        Voice_Count = new QLineEdit(groupBox_Voice_Info);
        Voice_Count->setObjectName(QString::fromUtf8("Voice_Count"));
        sizePolicy7.setHeightForWidth(Voice_Count->sizePolicy().hasHeightForWidth());
        Voice_Count->setSizePolicy(sizePolicy7);
        Voice_Count->setReadOnly(true);

        gridLayout_Voice_Info->addWidget(Voice_Count, 2, 1, 1, 1);


        gridLayout_34->addWidget(groupBox_Voice_Info, 2, 0, 1, 2);

        groupBox_Voice_Play = new QGroupBox(groupBox_11);
        groupBox_Voice_Play->setObjectName(QString::fromUtf8("groupBox_Voice_Play"));
        sizePolicy10.setHeightForWidth(groupBox_Voice_Play->sizePolicy().hasHeightForWidth());
        groupBox_Voice_Play->setSizePolicy(sizePolicy10);
        verticalLayout_Voice_Play = new QVBoxLayout(groupBox_Voice_Play);
        verticalLayout_Voice_Play->setSpacing(6);
        verticalLayout_Voice_Play->setContentsMargins(11, 11, 11, 11);
        verticalLayout_Voice_Play->setObjectName(QString::fromUtf8("verticalLayout_Voice_Play"));
        gridLayout_Voice_Buttons = new QGridLayout();
        gridLayout_Voice_Buttons->setSpacing(6);
        gridLayout_Voice_Buttons->setObjectName(QString::fromUtf8("gridLayout_Voice_Buttons"));
        btn_Voice_PA001 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA001->setObjectName(QString::fromUtf8("btn_Voice_PA001"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA001->sizePolicy().hasHeightForWidth());
        btn_Voice_PA001->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA001, 0, 0, 1, 1);

        btn_Voice_PA002 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA002->setObjectName(QString::fromUtf8("btn_Voice_PA002"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA002->sizePolicy().hasHeightForWidth());
        btn_Voice_PA002->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA002, 0, 1, 1, 1);

        btn_Voice_PA003 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA003->setObjectName(QString::fromUtf8("btn_Voice_PA003"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA003->sizePolicy().hasHeightForWidth());
        btn_Voice_PA003->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA003, 0, 2, 1, 1);

        btn_Voice_PA004 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA004->setObjectName(QString::fromUtf8("btn_Voice_PA004"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA004->sizePolicy().hasHeightForWidth());
        btn_Voice_PA004->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA004, 0, 3, 1, 1);

        btn_Voice_PA005 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA005->setObjectName(QString::fromUtf8("btn_Voice_PA005"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA005->sizePolicy().hasHeightForWidth());
        btn_Voice_PA005->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA005, 0, 4, 1, 1);

        btn_Voice_PA006 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA006->setObjectName(QString::fromUtf8("btn_Voice_PA006"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA006->sizePolicy().hasHeightForWidth());
        btn_Voice_PA006->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA006, 1, 0, 1, 1);

        btn_Voice_PA007 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA007->setObjectName(QString::fromUtf8("btn_Voice_PA007"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA007->sizePolicy().hasHeightForWidth());
        btn_Voice_PA007->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA007, 1, 1, 1, 1);

        btn_Voice_PA008 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA008->setObjectName(QString::fromUtf8("btn_Voice_PA008"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA008->sizePolicy().hasHeightForWidth());
        btn_Voice_PA008->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA008, 1, 2, 1, 1);

        btn_Voice_PA009 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA009->setObjectName(QString::fromUtf8("btn_Voice_PA009"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA009->sizePolicy().hasHeightForWidth());
        btn_Voice_PA009->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA009, 1, 3, 1, 1);

        btn_Voice_PA010 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA010->setObjectName(QString::fromUtf8("btn_Voice_PA010"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA010->sizePolicy().hasHeightForWidth());
        btn_Voice_PA010->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA010, 1, 4, 1, 1);

        btn_Voice_PA011 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA011->setObjectName(QString::fromUtf8("btn_Voice_PA011"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA011->sizePolicy().hasHeightForWidth());
        btn_Voice_PA011->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA011, 2, 0, 1, 1);

        btn_Voice_PA012 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA012->setObjectName(QString::fromUtf8("btn_Voice_PA012"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA012->sizePolicy().hasHeightForWidth());
        btn_Voice_PA012->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA012, 2, 1, 1, 1);

        btn_Voice_PA013 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA013->setObjectName(QString::fromUtf8("btn_Voice_PA013"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA013->sizePolicy().hasHeightForWidth());
        btn_Voice_PA013->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA013, 2, 2, 1, 1);

        btn_Voice_PA014 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA014->setObjectName(QString::fromUtf8("btn_Voice_PA014"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA014->sizePolicy().hasHeightForWidth());
        btn_Voice_PA014->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA014, 2, 3, 1, 1);

        btn_Voice_PA015 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA015->setObjectName(QString::fromUtf8("btn_Voice_PA015"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA015->sizePolicy().hasHeightForWidth());
        btn_Voice_PA015->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA015, 2, 4, 1, 1);

        btn_Voice_PA016 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA016->setObjectName(QString::fromUtf8("btn_Voice_PA016"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA016->sizePolicy().hasHeightForWidth());
        btn_Voice_PA016->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA016, 3, 0, 1, 1);

        btn_Voice_PA017 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA017->setObjectName(QString::fromUtf8("btn_Voice_PA017"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA017->sizePolicy().hasHeightForWidth());
        btn_Voice_PA017->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA017, 3, 1, 1, 1);

        btn_Voice_PA018 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA018->setObjectName(QString::fromUtf8("btn_Voice_PA018"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA018->sizePolicy().hasHeightForWidth());
        btn_Voice_PA018->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA018, 3, 2, 1, 1);

        btn_Voice_PA019 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA019->setObjectName(QString::fromUtf8("btn_Voice_PA019"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA019->sizePolicy().hasHeightForWidth());
        btn_Voice_PA019->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA019, 3, 3, 1, 1);

        btn_Voice_PA020 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA020->setObjectName(QString::fromUtf8("btn_Voice_PA020"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA020->sizePolicy().hasHeightForWidth());
        btn_Voice_PA020->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA020, 3, 4, 1, 1);

        btn_Voice_PA021 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA021->setObjectName(QString::fromUtf8("btn_Voice_PA021"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA021->sizePolicy().hasHeightForWidth());
        btn_Voice_PA021->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA021, 4, 0, 1, 1);

        btn_Voice_PA022 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA022->setObjectName(QString::fromUtf8("btn_Voice_PA022"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA022->sizePolicy().hasHeightForWidth());
        btn_Voice_PA022->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA022, 4, 1, 1, 1);

        btn_Voice_PA023 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA023->setObjectName(QString::fromUtf8("btn_Voice_PA023"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA023->sizePolicy().hasHeightForWidth());
        btn_Voice_PA023->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA023, 4, 2, 1, 1);

        btn_Voice_PA024 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA024->setObjectName(QString::fromUtf8("btn_Voice_PA024"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA024->sizePolicy().hasHeightForWidth());
        btn_Voice_PA024->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA024, 4, 3, 1, 1);

        btn_Voice_PA025 = new QPushButton(groupBox_Voice_Play);
        btn_Voice_PA025->setObjectName(QString::fromUtf8("btn_Voice_PA025"));
        sizePolicy7.setHeightForWidth(btn_Voice_PA025->sizePolicy().hasHeightForWidth());
        btn_Voice_PA025->setSizePolicy(sizePolicy7);

        gridLayout_Voice_Buttons->addWidget(btn_Voice_PA025, 4, 4, 1, 1);


        verticalLayout_Voice_Play->addLayout(gridLayout_Voice_Buttons);

        horizontalLayout_Voice_Ctrl = new QHBoxLayout();
        horizontalLayout_Voice_Ctrl->setSpacing(6);
        horizontalLayout_Voice_Ctrl->setObjectName(QString::fromUtf8("horizontalLayout_Voice_Ctrl"));
        btn_Voice_Stop = new QPushButton(groupBox_Voice_Play);
        btn_Voice_Stop->setObjectName(QString::fromUtf8("btn_Voice_Stop"));
        sizePolicy7.setHeightForWidth(btn_Voice_Stop->sizePolicy().hasHeightForWidth());
        btn_Voice_Stop->setSizePolicy(sizePolicy7);

        horizontalLayout_Voice_Ctrl->addWidget(btn_Voice_Stop);

        btn_Voice_Vol_Low = new QPushButton(groupBox_Voice_Play);
        btn_Voice_Vol_Low->setObjectName(QString::fromUtf8("btn_Voice_Vol_Low"));
        sizePolicy7.setHeightForWidth(btn_Voice_Vol_Low->sizePolicy().hasHeightForWidth());
        btn_Voice_Vol_Low->setSizePolicy(sizePolicy7);

        horizontalLayout_Voice_Ctrl->addWidget(btn_Voice_Vol_Low);

        btn_Voice_Vol_Med = new QPushButton(groupBox_Voice_Play);
        btn_Voice_Vol_Med->setObjectName(QString::fromUtf8("btn_Voice_Vol_Med"));
        sizePolicy7.setHeightForWidth(btn_Voice_Vol_Med->sizePolicy().hasHeightForWidth());
        btn_Voice_Vol_Med->setSizePolicy(sizePolicy7);

        horizontalLayout_Voice_Ctrl->addWidget(btn_Voice_Vol_Med);

        btn_Voice_Vol_High = new QPushButton(groupBox_Voice_Play);
        btn_Voice_Vol_High->setObjectName(QString::fromUtf8("btn_Voice_Vol_High"));
        sizePolicy7.setHeightForWidth(btn_Voice_Vol_High->sizePolicy().hasHeightForWidth());
        btn_Voice_Vol_High->setSizePolicy(sizePolicy7);

        horizontalLayout_Voice_Ctrl->addWidget(btn_Voice_Vol_High);

        btn_Voice_Test = new QPushButton(groupBox_Voice_Play);
        btn_Voice_Test->setObjectName(QString::fromUtf8("btn_Voice_Test"));
        sizePolicy7.setHeightForWidth(btn_Voice_Test->sizePolicy().hasHeightForWidth());
        btn_Voice_Test->setSizePolicy(sizePolicy7);

        horizontalLayout_Voice_Ctrl->addWidget(btn_Voice_Test);


        verticalLayout_Voice_Play->addLayout(horizontalLayout_Voice_Ctrl);


        gridLayout_34->addWidget(groupBox_Voice_Play, 0, 2, 3, 1);


        gridLayout_29->addWidget(groupBox_11, 0, 0, 1, 1);

        groupBox_Voice_Log = new QGroupBox(IO_Widget);
        groupBox_Voice_Log->setObjectName(QString::fromUtf8("groupBox_Voice_Log"));
        gridLayout_Voice_Log = new QGridLayout(groupBox_Voice_Log);
        gridLayout_Voice_Log->setSpacing(6);
        gridLayout_Voice_Log->setContentsMargins(11, 11, 11, 11);
        gridLayout_Voice_Log->setObjectName(QString::fromUtf8("gridLayout_Voice_Log"));
        Voice_Log = new QTextBrowser(groupBox_Voice_Log);
        Voice_Log->setObjectName(QString::fromUtf8("Voice_Log"));

        gridLayout_Voice_Log->addWidget(Voice_Log, 0, 0, 1, 1);


        gridLayout_29->addWidget(groupBox_Voice_Log, 1, 0, 1, 1);

        groupBox_10 = new QGroupBox(IO_Widget);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        QSizePolicy sizePolicy12(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(1);
        sizePolicy12.setHeightForWidth(groupBox_10->sizePolicy().hasHeightForWidth());
        groupBox_10->setSizePolicy(sizePolicy12);
        gridLayout_33 = new QGridLayout(groupBox_10);
        gridLayout_33->setSpacing(6);
        gridLayout_33->setContentsMargins(11, 11, 11, 11);
        gridLayout_33->setObjectName(QString::fromUtf8("gridLayout_33"));
        IO_Log = new QTextBrowser(groupBox_10);
        IO_Log->setObjectName(QString::fromUtf8("IO_Log"));

        gridLayout_33->addWidget(IO_Log, 1, 0, 1, 1);


        gridLayout_29->addWidget(groupBox_10, 1, 1, 1, 1);

        stackedWidget->addWidget(IO_Widget);
        Work_Widget = new QWidget();
        Work_Widget->setObjectName(QString::fromUtf8("Work_Widget"));
        gridLayout_27 = new QGridLayout(Work_Widget);
        gridLayout_27->setSpacing(6);
        gridLayout_27->setContentsMargins(11, 11, 11, 11);
        gridLayout_27->setObjectName(QString::fromUtf8("gridLayout_27"));
        Work_TaskGroup = new QGroupBox(Work_Widget);
        Work_TaskGroup->setObjectName(QString::fromUtf8("Work_TaskGroup"));
        sizePolicy.setHeightForWidth(Work_TaskGroup->sizePolicy().hasHeightForWidth());
        Work_TaskGroup->setSizePolicy(sizePolicy);
        Work_TaskGrid = new QGridLayout(Work_TaskGroup);
        Work_TaskGrid->setSpacing(6);
        Work_TaskGrid->setContentsMargins(11, 11, 11, 11);
        Work_TaskGrid->setObjectName(QString::fromUtf8("Work_TaskGrid"));
        label_Work_TaskID = new QLabel(Work_TaskGroup);
        label_Work_TaskID->setObjectName(QString::fromUtf8("label_Work_TaskID"));
        sizePolicy8.setHeightForWidth(label_Work_TaskID->sizePolicy().hasHeightForWidth());
        label_Work_TaskID->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_TaskID, 0, 0, 1, 1);

        Work_TaskID = new QLineEdit(Work_TaskGroup);
        Work_TaskID->setObjectName(QString::fromUtf8("Work_TaskID"));
        sizePolicy7.setHeightForWidth(Work_TaskID->sizePolicy().hasHeightForWidth());
        Work_TaskID->setSizePolicy(sizePolicy7);
        Work_TaskID->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_TaskID->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_TaskID, 0, 1, 1, 1);

        label_Work_State = new QLabel(Work_TaskGroup);
        label_Work_State->setObjectName(QString::fromUtf8("label_Work_State"));
        sizePolicy8.setHeightForWidth(label_Work_State->sizePolicy().hasHeightForWidth());
        label_Work_State->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_State, 0, 2, 1, 1);

        Work_State = new QLineEdit(Work_TaskGroup);
        Work_State->setObjectName(QString::fromUtf8("Work_State"));
        sizePolicy.setHeightForWidth(Work_State->sizePolicy().hasHeightForWidth());
        Work_State->setSizePolicy(sizePolicy);
        Work_State->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_State->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_State, 0, 3, 1, 1);

        label_Work_Wheel = new QLabel(Work_TaskGroup);
        label_Work_Wheel->setObjectName(QString::fromUtf8("label_Work_Wheel"));
        sizePolicy8.setHeightForWidth(label_Work_Wheel->sizePolicy().hasHeightForWidth());
        label_Work_Wheel->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_Wheel, 0, 4, 1, 1);

        Work_Wheel = new QLineEdit(Work_TaskGroup);
        Work_Wheel->setObjectName(QString::fromUtf8("Work_Wheel"));
        sizePolicy.setHeightForWidth(Work_Wheel->sizePolicy().hasHeightForWidth());
        Work_Wheel->setSizePolicy(sizePolicy);
        Work_Wheel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_Wheel->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_Wheel, 0, 5, 1, 1);

        label_Work_Pos = new QLabel(Work_TaskGroup);
        label_Work_Pos->setObjectName(QString::fromUtf8("label_Work_Pos"));
        sizePolicy8.setHeightForWidth(label_Work_Pos->sizePolicy().hasHeightForWidth());
        label_Work_Pos->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_Pos, 0, 6, 1, 1);

        Work_Pos = new QLineEdit(Work_TaskGroup);
        Work_Pos->setObjectName(QString::fromUtf8("Work_Pos"));
        sizePolicy.setHeightForWidth(Work_Pos->sizePolicy().hasHeightForWidth());
        Work_Pos->setSizePolicy(sizePolicy);
        Work_Pos->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_Pos->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_Pos, 0, 7, 1, 1);

        label_Work_Images = new QLabel(Work_TaskGroup);
        label_Work_Images->setObjectName(QString::fromUtf8("label_Work_Images"));
        sizePolicy8.setHeightForWidth(label_Work_Images->sizePolicy().hasHeightForWidth());
        label_Work_Images->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_Images, 0, 8, 1, 1);

        Work_Images = new QLineEdit(Work_TaskGroup);
        Work_Images->setObjectName(QString::fromUtf8("Work_Images"));
        sizePolicy.setHeightForWidth(Work_Images->sizePolicy().hasHeightForWidth());
        Work_Images->setSizePolicy(sizePolicy);
        Work_Images->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_Images->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_Images, 0, 9, 1, 1);

        label_Work_SendUnit = new QLabel(Work_TaskGroup);
        label_Work_SendUnit->setObjectName(QString::fromUtf8("label_Work_SendUnit"));
        sizePolicy8.setHeightForWidth(label_Work_SendUnit->sizePolicy().hasHeightForWidth());
        label_Work_SendUnit->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_SendUnit, 1, 0, 1, 1);

        Work_SendUnit = new QLineEdit(Work_TaskGroup);
        Work_SendUnit->setObjectName(QString::fromUtf8("Work_SendUnit"));
        sizePolicy7.setHeightForWidth(Work_SendUnit->sizePolicy().hasHeightForWidth());
        Work_SendUnit->setSizePolicy(sizePolicy7);
        Work_SendUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_SendUnit->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_SendUnit, 1, 1, 1, 1);

        label_Work_Repair = new QLabel(Work_TaskGroup);
        label_Work_Repair->setObjectName(QString::fromUtf8("label_Work_Repair"));
        sizePolicy8.setHeightForWidth(label_Work_Repair->sizePolicy().hasHeightForWidth());
        label_Work_Repair->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_Repair, 1, 2, 1, 1);

        Work_Repair = new QLineEdit(Work_TaskGroup);
        Work_Repair->setObjectName(QString::fromUtf8("Work_Repair"));
        sizePolicy7.setHeightForWidth(Work_Repair->sizePolicy().hasHeightForWidth());
        Work_Repair->setSizePolicy(sizePolicy7);
        Work_Repair->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_Repair->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_Repair, 1, 3, 1, 1);

        label_Work_WheelsetNo = new QLabel(Work_TaskGroup);
        label_Work_WheelsetNo->setObjectName(QString::fromUtf8("label_Work_WheelsetNo"));
        sizePolicy8.setHeightForWidth(label_Work_WheelsetNo->sizePolicy().hasHeightForWidth());
        label_Work_WheelsetNo->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_WheelsetNo, 1, 4, 1, 1);

        Work_WheelsetNo = new QLineEdit(Work_TaskGroup);
        Work_WheelsetNo->setObjectName(QString::fromUtf8("Work_WheelsetNo"));
        sizePolicy7.setHeightForWidth(Work_WheelsetNo->sizePolicy().hasHeightForWidth());
        Work_WheelsetNo->setSizePolicy(sizePolicy7);
        Work_WheelsetNo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_WheelsetNo->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_WheelsetNo, 1, 5, 1, 3);

        label_Work_AxleNo = new QLabel(Work_TaskGroup);
        label_Work_AxleNo->setObjectName(QString::fromUtf8("label_Work_AxleNo"));
        sizePolicy8.setHeightForWidth(label_Work_AxleNo->sizePolicy().hasHeightForWidth());
        label_Work_AxleNo->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_AxleNo, 1, 8, 1, 1);

        Work_AxleNo = new QLineEdit(Work_TaskGroup);
        Work_AxleNo->setObjectName(QString::fromUtf8("Work_AxleNo"));
        sizePolicy7.setHeightForWidth(Work_AxleNo->sizePolicy().hasHeightForWidth());
        Work_AxleNo->setSizePolicy(sizePolicy7);
        Work_AxleNo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_AxleNo->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_AxleNo, 1, 9, 1, 1);

        label_Work_Gain = new QLabel(Work_TaskGroup);
        label_Work_Gain->setObjectName(QString::fromUtf8("label_Work_Gain"));
        sizePolicy8.setHeightForWidth(label_Work_Gain->sizePolicy().hasHeightForWidth());
        label_Work_Gain->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_Gain, 2, 0, 1, 1);

        Work_Gain = new QLineEdit(Work_TaskGroup);
        Work_Gain->setObjectName(QString::fromUtf8("Work_Gain"));
        sizePolicy.setHeightForWidth(Work_Gain->sizePolicy().hasHeightForWidth());
        Work_Gain->setSizePolicy(sizePolicy);
        Work_Gain->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_Gain->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_Gain, 2, 1, 1, 1);

        label_Work_Part1 = new QLabel(Work_TaskGroup);
        label_Work_Part1->setObjectName(QString::fromUtf8("label_Work_Part1"));
        sizePolicy8.setHeightForWidth(label_Work_Part1->sizePolicy().hasHeightForWidth());
        label_Work_Part1->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_Part1, 2, 2, 1, 1);

        Work_Part1 = new QLineEdit(Work_TaskGroup);
        Work_Part1->setObjectName(QString::fromUtf8("Work_Part1"));
        sizePolicy7.setHeightForWidth(Work_Part1->sizePolicy().hasHeightForWidth());
        Work_Part1->setSizePolicy(sizePolicy7);
        Work_Part1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_Part1->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_Part1, 2, 3, 1, 1);

        label_Work_Part2 = new QLabel(Work_TaskGroup);
        label_Work_Part2->setObjectName(QString::fromUtf8("label_Work_Part2"));
        sizePolicy8.setHeightForWidth(label_Work_Part2->sizePolicy().hasHeightForWidth());
        label_Work_Part2->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_Part2, 2, 4, 1, 1);

        Work_Part2 = new QLineEdit(Work_TaskGroup);
        Work_Part2->setObjectName(QString::fromUtf8("Work_Part2"));
        sizePolicy7.setHeightForWidth(Work_Part2->sizePolicy().hasHeightForWidth());
        Work_Part2->setSizePolicy(sizePolicy7);
        Work_Part2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_Part2->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_Part2, 2, 5, 1, 1);

        label_Work_Point = new QLabel(Work_TaskGroup);
        label_Work_Point->setObjectName(QString::fromUtf8("label_Work_Point"));
        sizePolicy8.setHeightForWidth(label_Work_Point->sizePolicy().hasHeightForWidth());
        label_Work_Point->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_Point, 2, 6, 1, 1);

        Work_Point = new QLineEdit(Work_TaskGroup);
        Work_Point->setObjectName(QString::fromUtf8("Work_Point"));
        sizePolicy7.setHeightForWidth(Work_Point->sizePolicy().hasHeightForWidth());
        Work_Point->setSizePolicy(sizePolicy7);
        Work_Point->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_Point->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_Point, 2, 7, 1, 1);

        label_Work_StartTime = new QLabel(Work_TaskGroup);
        label_Work_StartTime->setObjectName(QString::fromUtf8("label_Work_StartTime"));
        sizePolicy8.setHeightForWidth(label_Work_StartTime->sizePolicy().hasHeightForWidth());
        label_Work_StartTime->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_StartTime, 2, 8, 1, 1);

        Work_StartTime = new QLineEdit(Work_TaskGroup);
        Work_StartTime->setObjectName(QString::fromUtf8("Work_StartTime"));
        sizePolicy7.setHeightForWidth(Work_StartTime->sizePolicy().hasHeightForWidth());
        Work_StartTime->setSizePolicy(sizePolicy7);
        Work_StartTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_StartTime->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_StartTime, 2, 9, 1, 1);

        label_Work_CarType = new QLabel(Work_TaskGroup);
        label_Work_CarType->setObjectName(QString::fromUtf8("label_Work_CarType"));
        sizePolicy8.setHeightForWidth(label_Work_CarType->sizePolicy().hasHeightForWidth());
        label_Work_CarType->setSizePolicy(sizePolicy8);

        Work_TaskGrid->addWidget(label_Work_CarType, 6, 0, 1, 1);

        Work_CarType = new QLineEdit(Work_TaskGroup);
        Work_CarType->setObjectName(QString::fromUtf8("Work_CarType"));
        sizePolicy7.setHeightForWidth(Work_CarType->sizePolicy().hasHeightForWidth());
        Work_CarType->setSizePolicy(sizePolicy7);
        Work_CarType->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Work_CarType->setReadOnly(true);

        Work_TaskGrid->addWidget(Work_CarType, 6, 1, 1, 1);


        gridLayout_27->addWidget(Work_TaskGroup, 3, 0, 1, 1);

        horizontalLayout_48 = new QHBoxLayout();
        horizontalLayout_48->setSpacing(6);
        horizontalLayout_48->setObjectName(QString::fromUtf8("horizontalLayout_48"));
        groupBox_FrontCamView = new QGroupBox(Work_Widget);
        groupBox_FrontCamView->setObjectName(QString::fromUtf8("groupBox_FrontCamView"));
        sizePolicy4.setHeightForWidth(groupBox_FrontCamView->sizePolicy().hasHeightForWidth());
        groupBox_FrontCamView->setSizePolicy(sizePolicy4);
        verticalLayout_FrontCamView = new QVBoxLayout(groupBox_FrontCamView);
        verticalLayout_FrontCamView->setSpacing(6);
        verticalLayout_FrontCamView->setContentsMargins(11, 11, 11, 11);
        verticalLayout_FrontCamView->setObjectName(QString::fromUtf8("verticalLayout_FrontCamView"));
        label_FrontCamera = new QLabel(groupBox_FrontCamView);
        label_FrontCamera->setObjectName(QString::fromUtf8("label_FrontCamera"));
        sizePolicy4.setHeightForWidth(label_FrontCamera->sizePolicy().hasHeightForWidth());
        label_FrontCamera->setSizePolicy(sizePolicy4);
        label_FrontCamera->setMinimumSize(QSize(0, 0));
        label_FrontCamera->setMaximumSize(QSize(16777215, 16777215));
        label_FrontCamera->setScaledContents(true);
        label_FrontCamera->setAlignment(Qt::AlignCenter);

        verticalLayout_FrontCamView->addWidget(label_FrontCamera);


        horizontalLayout_48->addWidget(groupBox_FrontCamView);

        groupBox_4 = new QGroupBox(Work_Widget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy4.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy4);
        gridLayout_19 = new QGridLayout(groupBox_4);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        widget_LidarView = new c_Magic_Lidar_View(groupBox_4);
        widget_LidarView->setObjectName(QString::fromUtf8("widget_LidarView"));
        sizePolicy4.setHeightForWidth(widget_LidarView->sizePolicy().hasHeightForWidth());
        widget_LidarView->setSizePolicy(sizePolicy4);
        widget_LidarView->setMinimumSize(QSize(0, 0));
        widget_LidarView->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_19->addWidget(widget_LidarView, 0, 0, 1, 1);


        horizontalLayout_48->addWidget(groupBox_4);

        groupBox_RearCamView = new QGroupBox(Work_Widget);
        groupBox_RearCamView->setObjectName(QString::fromUtf8("groupBox_RearCamView"));
        sizePolicy4.setHeightForWidth(groupBox_RearCamView->sizePolicy().hasHeightForWidth());
        groupBox_RearCamView->setSizePolicy(sizePolicy4);
        verticalLayout_RearCamView = new QVBoxLayout(groupBox_RearCamView);
        verticalLayout_RearCamView->setSpacing(6);
        verticalLayout_RearCamView->setContentsMargins(11, 11, 11, 11);
        verticalLayout_RearCamView->setObjectName(QString::fromUtf8("verticalLayout_RearCamView"));
        label_RearCamera = new QLabel(groupBox_RearCamView);
        label_RearCamera->setObjectName(QString::fromUtf8("label_RearCamera"));
        sizePolicy4.setHeightForWidth(label_RearCamera->sizePolicy().hasHeightForWidth());
        label_RearCamera->setSizePolicy(sizePolicy4);
        label_RearCamera->setMinimumSize(QSize(0, 0));
        label_RearCamera->setMaximumSize(QSize(16777215, 16777215));
        label_RearCamera->setScaledContents(true);
        label_RearCamera->setAlignment(Qt::AlignCenter);

        verticalLayout_RearCamView->addWidget(label_RearCamera);


        horizontalLayout_48->addWidget(groupBox_RearCamView);


        gridLayout_27->addLayout(horizontalLayout_48, 4, 0, 1, 1);

        Work_TopRow = new QHBoxLayout();
        Work_TopRow->setSpacing(6);
        Work_TopRow->setObjectName(QString::fromUtf8("Work_TopRow"));
        Work_ServerGroup = new QGroupBox(Work_Widget);
        Work_ServerGroup->setObjectName(QString::fromUtf8("Work_ServerGroup"));
        sizePolicy.setHeightForWidth(Work_ServerGroup->sizePolicy().hasHeightForWidth());
        Work_ServerGroup->setSizePolicy(sizePolicy);
        Work_ServerLayout = new QHBoxLayout(Work_ServerGroup);
        Work_ServerLayout->setSpacing(6);
        Work_ServerLayout->setContentsMargins(11, 11, 11, 11);
        Work_ServerLayout->setObjectName(QString::fromUtf8("Work_ServerLayout"));
        label_Work_Client = new QLabel(Work_ServerGroup);
        label_Work_Client->setObjectName(QString::fromUtf8("label_Work_Client"));
        sizePolicy8.setHeightForWidth(label_Work_Client->sizePolicy().hasHeightForWidth());
        label_Work_Client->setSizePolicy(sizePolicy8);

        Work_ServerLayout->addWidget(label_Work_Client);

        Work_Client_Light = new c_Fr_Light(Work_ServerGroup);
        Work_Client_Light->setObjectName(QString::fromUtf8("Work_Client_Light"));
        sizePolicy5.setHeightForWidth(Work_Client_Light->sizePolicy().hasHeightForWidth());
        Work_Client_Light->setSizePolicy(sizePolicy5);
        Work_Client_Light->setMinimumSize(QSize(20, 20));

        Work_ServerLayout->addWidget(Work_Client_Light);

        label_Work_Listen = new QLabel(Work_ServerGroup);
        label_Work_Listen->setObjectName(QString::fromUtf8("label_Work_Listen"));
        sizePolicy8.setHeightForWidth(label_Work_Listen->sizePolicy().hasHeightForWidth());
        label_Work_Listen->setSizePolicy(sizePolicy8);

        Work_ServerLayout->addWidget(label_Work_Listen);

        Work_Listen_Light = new c_Fr_Light(Work_ServerGroup);
        Work_Listen_Light->setObjectName(QString::fromUtf8("Work_Listen_Light"));
        sizePolicy5.setHeightForWidth(Work_Listen_Light->sizePolicy().hasHeightForWidth());
        Work_Listen_Light->setSizePolicy(sizePolicy5);
        Work_Listen_Light->setMinimumSize(QSize(20, 20));

        Work_ServerLayout->addWidget(Work_Listen_Light);

        label_Work_ConnNum = new QLabel(Work_ServerGroup);
        label_Work_ConnNum->setObjectName(QString::fromUtf8("label_Work_ConnNum"));
        sizePolicy8.setHeightForWidth(label_Work_ConnNum->sizePolicy().hasHeightForWidth());
        label_Work_ConnNum->setSizePolicy(sizePolicy8);

        Work_ServerLayout->addWidget(label_Work_ConnNum);

        Work_Client_Num = new QLineEdit(Work_ServerGroup);
        Work_Client_Num->setObjectName(QString::fromUtf8("Work_Client_Num"));
        sizePolicy5.setHeightForWidth(Work_Client_Num->sizePolicy().hasHeightForWidth());
        Work_Client_Num->setSizePolicy(sizePolicy5);
        Work_Client_Num->setReadOnly(true);

        Work_ServerLayout->addWidget(Work_Client_Num);

        label_Work_Port = new QLabel(Work_ServerGroup);
        label_Work_Port->setObjectName(QString::fromUtf8("label_Work_Port"));
        sizePolicy8.setHeightForWidth(label_Work_Port->sizePolicy().hasHeightForWidth());
        label_Work_Port->setSizePolicy(sizePolicy8);

        Work_ServerLayout->addWidget(label_Work_Port);

        Work_Port = new QLineEdit(Work_ServerGroup);
        Work_Port->setObjectName(QString::fromUtf8("Work_Port"));
        sizePolicy5.setHeightForWidth(Work_Port->sizePolicy().hasHeightForWidth());
        Work_Port->setSizePolicy(sizePolicy5);
        Work_Port->setReadOnly(true);

        Work_ServerLayout->addWidget(Work_Port);

        label_Work_Checksum = new QLabel(Work_ServerGroup);
        label_Work_Checksum->setObjectName(QString::fromUtf8("label_Work_Checksum"));
        sizePolicy8.setHeightForWidth(label_Work_Checksum->sizePolicy().hasHeightForWidth());
        label_Work_Checksum->setSizePolicy(sizePolicy8);

        Work_ServerLayout->addWidget(label_Work_Checksum);

        Work_Checksum = new QLineEdit(Work_ServerGroup);
        Work_Checksum->setObjectName(QString::fromUtf8("Work_Checksum"));
        sizePolicy.setHeightForWidth(Work_Checksum->sizePolicy().hasHeightForWidth());
        Work_Checksum->setSizePolicy(sizePolicy);
        Work_Checksum->setReadOnly(true);

        Work_ServerLayout->addWidget(Work_Checksum);


        Work_TopRow->addWidget(Work_ServerGroup);


        gridLayout_27->addLayout(Work_TopRow, 0, 0, 1, 1);

        Work_FlowRow = new QHBoxLayout();
        Work_FlowRow->setSpacing(6);
        Work_FlowRow->setObjectName(QString::fromUtf8("Work_FlowRow"));
        Work_FlowGroup = new QGroupBox(Work_Widget);
        Work_FlowGroup->setObjectName(QString::fromUtf8("Work_FlowGroup"));
        sizePolicy.setHeightForWidth(Work_FlowGroup->sizePolicy().hasHeightForWidth());
        Work_FlowGroup->setSizePolicy(sizePolicy);
        Work_FlowLayout = new QHBoxLayout(Work_FlowGroup);
        Work_FlowLayout->setSpacing(6);
        Work_FlowLayout->setContentsMargins(11, 11, 11, 11);
        Work_FlowLayout->setObjectName(QString::fromUtf8("Work_FlowLayout"));
        label_Work_FlowState = new QLabel(Work_FlowGroup);
        label_Work_FlowState->setObjectName(QString::fromUtf8("label_Work_FlowState"));

        Work_FlowLayout->addWidget(label_Work_FlowState);

        Work_Flow_State = new QLineEdit(Work_FlowGroup);
        Work_Flow_State->setObjectName(QString::fromUtf8("Work_Flow_State"));
        Work_Flow_State->setAlignment(Qt::AlignCenter);
        Work_Flow_State->setReadOnly(true);

        Work_FlowLayout->addWidget(Work_Flow_State);

        Work_Flow_Desc = new QLineEdit(Work_FlowGroup);
        Work_Flow_Desc->setObjectName(QString::fromUtf8("Work_Flow_Desc"));
        Work_Flow_Desc->setReadOnly(true);

        Work_FlowLayout->addWidget(Work_Flow_Desc);

        Work_Btn_Start = new QPushButton(Work_FlowGroup);
        Work_Btn_Start->setObjectName(QString::fromUtf8("Work_Btn_Start"));

        Work_FlowLayout->addWidget(Work_Btn_Start);

        Work_Btn_Pause = new QPushButton(Work_FlowGroup);
        Work_Btn_Pause->setObjectName(QString::fromUtf8("Work_Btn_Pause"));

        Work_FlowLayout->addWidget(Work_Btn_Pause);

        Work_Btn_Resume = new QPushButton(Work_FlowGroup);
        Work_Btn_Resume->setObjectName(QString::fromUtf8("Work_Btn_Resume"));

        Work_FlowLayout->addWidget(Work_Btn_Resume);

        Work_Btn_Cancel = new QPushButton(Work_FlowGroup);
        Work_Btn_Cancel->setObjectName(QString::fromUtf8("Work_Btn_Cancel"));

        Work_FlowLayout->addWidget(Work_Btn_Cancel);

        Work_Btn_Stop = new QPushButton(Work_FlowGroup);
        Work_Btn_Stop->setObjectName(QString::fromUtf8("Work_Btn_Stop"));

        Work_FlowLayout->addWidget(Work_Btn_Stop);

        Work_Btn_Home = new QPushButton(Work_FlowGroup);
        Work_Btn_Home->setObjectName(QString::fromUtf8("Work_Btn_Home"));

        Work_FlowLayout->addWidget(Work_Btn_Home);


        Work_FlowRow->addWidget(Work_FlowGroup);


        gridLayout_27->addLayout(Work_FlowRow, 1, 0, 1, 1);

        Work_BottomRow = new QHBoxLayout();
        Work_BottomRow->setSpacing(6);
        Work_BottomRow->setObjectName(QString::fromUtf8("Work_BottomRow"));
        Work_LogGroup = new QGroupBox(Work_Widget);
        Work_LogGroup->setObjectName(QString::fromUtf8("Work_LogGroup"));
        QSizePolicy sizePolicy13(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy13.setHorizontalStretch(1);
        sizePolicy13.setVerticalStretch(0);
        sizePolicy13.setHeightForWidth(Work_LogGroup->sizePolicy().hasHeightForWidth());
        Work_LogGroup->setSizePolicy(sizePolicy13);
        Work_LogLayout = new QVBoxLayout(Work_LogGroup);
        Work_LogLayout->setSpacing(6);
        Work_LogLayout->setContentsMargins(11, 11, 11, 11);
        Work_LogLayout->setObjectName(QString::fromUtf8("Work_LogLayout"));
        Work_List = new QTextEdit(Work_LogGroup);
        Work_List->setObjectName(QString::fromUtf8("Work_List"));
        QSizePolicy sizePolicy14(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy14.setHorizontalStretch(0);
        sizePolicy14.setVerticalStretch(0);
        sizePolicy14.setHeightForWidth(Work_List->sizePolicy().hasHeightForWidth());
        Work_List->setSizePolicy(sizePolicy14);
        Work_List->setReadOnly(true);

        Work_LogLayout->addWidget(Work_List);


        Work_BottomRow->addWidget(Work_LogGroup);

        Work_AlarmGroup = new QGroupBox(Work_Widget);
        Work_AlarmGroup->setObjectName(QString::fromUtf8("Work_AlarmGroup"));
        sizePolicy13.setHeightForWidth(Work_AlarmGroup->sizePolicy().hasHeightForWidth());
        Work_AlarmGroup->setSizePolicy(sizePolicy13);
        Work_AlarmLayout = new QVBoxLayout(Work_AlarmGroup);
        Work_AlarmLayout->setSpacing(6);
        Work_AlarmLayout->setContentsMargins(11, 11, 11, 11);
        Work_AlarmLayout->setObjectName(QString::fromUtf8("Work_AlarmLayout"));
        Work_Alarm = new QTextEdit(Work_AlarmGroup);
        Work_Alarm->setObjectName(QString::fromUtf8("Work_Alarm"));
        sizePolicy14.setHeightForWidth(Work_Alarm->sizePolicy().hasHeightForWidth());
        Work_Alarm->setSizePolicy(sizePolicy14);
        Work_Alarm->setReadOnly(true);

        Work_AlarmLayout->addWidget(Work_Alarm);


        Work_BottomRow->addWidget(Work_AlarmGroup);


        gridLayout_27->addLayout(Work_BottomRow, 5, 0, 1, 1);

        Work_StatusRow = new QHBoxLayout();
        Work_StatusRow->setSpacing(6);
        Work_StatusRow->setObjectName(QString::fromUtf8("Work_StatusRow"));
        Work_SubsysGroup = new QGroupBox(Work_Widget);
        Work_SubsysGroup->setObjectName(QString::fromUtf8("Work_SubsysGroup"));
        sizePolicy.setHeightForWidth(Work_SubsysGroup->sizePolicy().hasHeightForWidth());
        Work_SubsysGroup->setSizePolicy(sizePolicy);
        Work_SubsysLayout = new QHBoxLayout(Work_SubsysGroup);
        Work_SubsysLayout->setSpacing(6);
        Work_SubsysLayout->setContentsMargins(11, 11, 11, 11);
        Work_SubsysLayout->setObjectName(QString::fromUtf8("Work_SubsysLayout"));
        label_Work_Arm = new QLabel(Work_SubsysGroup);
        label_Work_Arm->setObjectName(QString::fromUtf8("label_Work_Arm"));

        Work_SubsysLayout->addWidget(label_Work_Arm);

        Work_Arm_Light = new c_Fr_Light(Work_SubsysGroup);
        Work_Arm_Light->setObjectName(QString::fromUtf8("Work_Arm_Light"));
        sizePolicy5.setHeightForWidth(Work_Arm_Light->sizePolicy().hasHeightForWidth());
        Work_Arm_Light->setSizePolicy(sizePolicy5);
        Work_Arm_Light->setMinimumSize(QSize(20, 20));

        Work_SubsysLayout->addWidget(Work_Arm_Light);

        label_Work_Chassis = new QLabel(Work_SubsysGroup);
        label_Work_Chassis->setObjectName(QString::fromUtf8("label_Work_Chassis"));

        Work_SubsysLayout->addWidget(label_Work_Chassis);

        Work_Chassis_Light = new c_Fr_Light(Work_SubsysGroup);
        Work_Chassis_Light->setObjectName(QString::fromUtf8("Work_Chassis_Light"));
        sizePolicy5.setHeightForWidth(Work_Chassis_Light->sizePolicy().hasHeightForWidth());
        Work_Chassis_Light->setSizePolicy(sizePolicy5);
        Work_Chassis_Light->setMinimumSize(QSize(20, 20));

        Work_SubsysLayout->addWidget(Work_Chassis_Light);

        label_Work_Camera = new QLabel(Work_SubsysGroup);
        label_Work_Camera->setObjectName(QString::fromUtf8("label_Work_Camera"));

        Work_SubsysLayout->addWidget(label_Work_Camera);

        Work_Camera_Light = new c_Fr_Light(Work_SubsysGroup);
        Work_Camera_Light->setObjectName(QString::fromUtf8("Work_Camera_Light"));
        sizePolicy5.setHeightForWidth(Work_Camera_Light->sizePolicy().hasHeightForWidth());
        Work_Camera_Light->setSizePolicy(sizePolicy5);
        Work_Camera_Light->setMinimumSize(QSize(20, 20));

        Work_SubsysLayout->addWidget(Work_Camera_Light);

        label_Work_Server = new QLabel(Work_SubsysGroup);
        label_Work_Server->setObjectName(QString::fromUtf8("label_Work_Server"));

        Work_SubsysLayout->addWidget(label_Work_Server);

        Work_Server_Light = new c_Fr_Light(Work_SubsysGroup);
        Work_Server_Light->setObjectName(QString::fromUtf8("Work_Server_Light"));
        sizePolicy5.setHeightForWidth(Work_Server_Light->sizePolicy().hasHeightForWidth());
        Work_Server_Light->setSizePolicy(sizePolicy5);
        Work_Server_Light->setMinimumSize(QSize(20, 20));

        Work_SubsysLayout->addWidget(Work_Server_Light);

        label_Work_Checksum_2 = new QLabel(Work_SubsysGroup);
        label_Work_Checksum_2->setObjectName(QString::fromUtf8("label_Work_Checksum_2"));
        sizePolicy8.setHeightForWidth(label_Work_Checksum_2->sizePolicy().hasHeightForWidth());
        label_Work_Checksum_2->setSizePolicy(sizePolicy8);

        Work_SubsysLayout->addWidget(label_Work_Checksum_2);

        EMIS_Url = new QLineEdit(Work_SubsysGroup);
        EMIS_Url->setObjectName(QString::fromUtf8("EMIS_Url"));
        sizePolicy14.setHeightForWidth(EMIS_Url->sizePolicy().hasHeightForWidth());
        EMIS_Url->setSizePolicy(sizePolicy14);
        EMIS_Url->setReadOnly(true);

        Work_SubsysLayout->addWidget(EMIS_Url);

        actualStartTime = new QPushButton(Work_SubsysGroup);
        actualStartTime->setObjectName(QString::fromUtf8("actualStartTime"));

        Work_SubsysLayout->addWidget(actualStartTime);

        precisScanStartTime = new QPushButton(Work_SubsysGroup);
        precisScanStartTime->setObjectName(QString::fromUtf8("precisScanStartTime"));

        Work_SubsysLayout->addWidget(precisScanStartTime);

        precisScanEndTime = new QPushButton(Work_SubsysGroup);
        precisScanEndTime->setObjectName(QString::fromUtf8("precisScanEndTime"));

        Work_SubsysLayout->addWidget(precisScanEndTime);

        Work_SubsysSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Work_SubsysLayout->addItem(Work_SubsysSpacer);


        Work_StatusRow->addWidget(Work_SubsysGroup);


        gridLayout_27->addLayout(Work_StatusRow, 2, 0, 1, 1);

        stackedWidget->addWidget(Work_Widget);
        Magic_Widget = new QWidget();
        Magic_Widget->setObjectName(QString::fromUtf8("Magic_Widget"));
        gridLayout_10 = new QGridLayout(Magic_Widget);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        groupBox_7 = new QGroupBox(Magic_Widget);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout_14 = new QGridLayout(groupBox_7);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_Connect = new QGroupBox(groupBox_7);
        groupBox_Connect->setObjectName(QString::fromUtf8("groupBox_Connect"));
        sizePolicy.setHeightForWidth(groupBox_Connect->sizePolicy().hasHeightForWidth());
        groupBox_Connect->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBox_Connect);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_IP = new QLabel(groupBox_Connect);
        label_IP->setObjectName(QString::fromUtf8("label_IP"));

        gridLayout_2->addWidget(label_IP, 0, 0, 1, 1);

        Magic_IP = new QLineEdit(groupBox_Connect);
        Magic_IP->setObjectName(QString::fromUtf8("Magic_IP"));
        sizePolicy7.setHeightForWidth(Magic_IP->sizePolicy().hasHeightForWidth());
        Magic_IP->setSizePolicy(sizePolicy7);

        gridLayout_2->addWidget(Magic_IP, 0, 1, 1, 1);

        label_Port = new QLabel(groupBox_Connect);
        label_Port->setObjectName(QString::fromUtf8("label_Port"));

        gridLayout_2->addWidget(label_Port, 0, 2, 1, 1);

        Magic_Port = new QLineEdit(groupBox_Connect);
        Magic_Port->setObjectName(QString::fromUtf8("Magic_Port"));
        sizePolicy7.setHeightForWidth(Magic_Port->sizePolicy().hasHeightForWidth());
        Magic_Port->setSizePolicy(sizePolicy7);

        gridLayout_2->addWidget(Magic_Port, 0, 3, 1, 1);

        label_User = new QLabel(groupBox_Connect);
        label_User->setObjectName(QString::fromUtf8("label_User"));

        gridLayout_2->addWidget(label_User, 0, 4, 1, 1);

        Magic_User = new QLineEdit(groupBox_Connect);
        Magic_User->setObjectName(QString::fromUtf8("Magic_User"));
        sizePolicy7.setHeightForWidth(Magic_User->sizePolicy().hasHeightForWidth());
        Magic_User->setSizePolicy(sizePolicy7);

        gridLayout_2->addWidget(Magic_User, 0, 5, 1, 1);

        label_Pass = new QLabel(groupBox_Connect);
        label_Pass->setObjectName(QString::fromUtf8("label_Pass"));

        gridLayout_2->addWidget(label_Pass, 0, 6, 1, 1);

        Magic_Pass = new QLineEdit(groupBox_Connect);
        Magic_Pass->setObjectName(QString::fromUtf8("Magic_Pass"));
        sizePolicy7.setHeightForWidth(Magic_Pass->sizePolicy().hasHeightForWidth());
        Magic_Pass->setSizePolicy(sizePolicy7);
        Magic_Pass->setEchoMode(QLineEdit::Normal);

        gridLayout_2->addWidget(Magic_Pass, 0, 7, 1, 1);

        pushButton_Connect = new QPushButton(groupBox_Connect);
        pushButton_Connect->setObjectName(QString::fromUtf8("pushButton_Connect"));
        sizePolicy7.setHeightForWidth(pushButton_Connect->sizePolicy().hasHeightForWidth());
        pushButton_Connect->setSizePolicy(sizePolicy7);

        gridLayout_2->addWidget(pushButton_Connect, 0, 8, 1, 1);

        pushButton_Login = new QPushButton(groupBox_Connect);
        pushButton_Login->setObjectName(QString::fromUtf8("pushButton_Login"));
        sizePolicy7.setHeightForWidth(pushButton_Login->sizePolicy().hasHeightForWidth());
        pushButton_Login->setSizePolicy(sizePolicy7);

        gridLayout_2->addWidget(pushButton_Login, 0, 9, 1, 1);

        pushButton_Disconnect = new QPushButton(groupBox_Connect);
        pushButton_Disconnect->setObjectName(QString::fromUtf8("pushButton_Disconnect"));
        sizePolicy7.setHeightForWidth(pushButton_Disconnect->sizePolicy().hasHeightForWidth());
        pushButton_Disconnect->setSizePolicy(sizePolicy7);

        gridLayout_2->addWidget(pushButton_Disconnect, 0, 10, 1, 1);

        label_MAC = new QLabel(groupBox_Connect);
        label_MAC->setObjectName(QString::fromUtf8("label_MAC"));
        sizePolicy8.setHeightForWidth(label_MAC->sizePolicy().hasHeightForWidth());
        label_MAC->setSizePolicy(sizePolicy8);

        gridLayout_2->addWidget(label_MAC, 0, 11, 1, 1);

        lineEdit_MAC = new QLineEdit(groupBox_Connect);
        lineEdit_MAC->setObjectName(QString::fromUtf8("lineEdit_MAC"));
        sizePolicy11.setHeightForWidth(lineEdit_MAC->sizePolicy().hasHeightForWidth());
        lineEdit_MAC->setSizePolicy(sizePolicy11);
        lineEdit_MAC->setReadOnly(true);

        gridLayout_2->addWidget(lineEdit_MAC, 0, 12, 1, 1);


        verticalLayout_3->addWidget(groupBox_Connect);

        groupBox_Pose = new QGroupBox(groupBox_7);
        groupBox_Pose->setObjectName(QString::fromUtf8("groupBox_Pose"));
        sizePolicy.setHeightForWidth(groupBox_Pose->sizePolicy().hasHeightForWidth());
        groupBox_Pose->setSizePolicy(sizePolicy);
        gridLayout_11 = new QGridLayout(groupBox_Pose);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        label_WX = new QLabel(groupBox_Pose);
        label_WX->setObjectName(QString::fromUtf8("label_WX"));

        gridLayout_11->addWidget(label_WX, 1, 0, 1, 1);

        label_WY = new QLabel(groupBox_Pose);
        label_WY->setObjectName(QString::fromUtf8("label_WY"));

        gridLayout_11->addWidget(label_WY, 1, 2, 1, 1);

        label_Angle = new QLabel(groupBox_Pose);
        label_Angle->setObjectName(QString::fromUtf8("label_Angle"));

        gridLayout_11->addWidget(label_Angle, 1, 4, 1, 1);

        lineEdit_GridX = new QLineEdit(groupBox_Pose);
        lineEdit_GridX->setObjectName(QString::fromUtf8("lineEdit_GridX"));
        sizePolicy7.setHeightForWidth(lineEdit_GridX->sizePolicy().hasHeightForWidth());
        lineEdit_GridX->setSizePolicy(sizePolicy7);
        lineEdit_GridX->setReadOnly(true);

        gridLayout_11->addWidget(lineEdit_GridX, 2, 1, 1, 1);

        lineEdit_WX = new QLineEdit(groupBox_Pose);
        lineEdit_WX->setObjectName(QString::fromUtf8("lineEdit_WX"));
        sizePolicy7.setHeightForWidth(lineEdit_WX->sizePolicy().hasHeightForWidth());
        lineEdit_WX->setSizePolicy(sizePolicy7);
        lineEdit_WX->setReadOnly(true);

        gridLayout_11->addWidget(lineEdit_WX, 1, 1, 1, 1);

        lineEdit_GridY = new QLineEdit(groupBox_Pose);
        lineEdit_GridY->setObjectName(QString::fromUtf8("lineEdit_GridY"));
        sizePolicy7.setHeightForWidth(lineEdit_GridY->sizePolicy().hasHeightForWidth());
        lineEdit_GridY->setSizePolicy(sizePolicy7);
        lineEdit_GridY->setReadOnly(true);

        gridLayout_11->addWidget(lineEdit_GridY, 2, 3, 1, 1);

        lineEdit_Battery = new QLineEdit(groupBox_Pose);
        lineEdit_Battery->setObjectName(QString::fromUtf8("lineEdit_Battery"));
        sizePolicy7.setHeightForWidth(lineEdit_Battery->sizePolicy().hasHeightForWidth());
        lineEdit_Battery->setSizePolicy(sizePolicy7);
        lineEdit_Battery->setReadOnly(true);

        gridLayout_11->addWidget(lineEdit_Battery, 1, 7, 1, 1);

        label_NavVer = new QLabel(groupBox_Pose);
        label_NavVer->setObjectName(QString::fromUtf8("label_NavVer"));
        sizePolicy8.setHeightForWidth(label_NavVer->sizePolicy().hasHeightForWidth());
        label_NavVer->setSizePolicy(sizePolicy8);

        gridLayout_11->addWidget(label_NavVer, 2, 6, 1, 1);

        label_GridX = new QLabel(groupBox_Pose);
        label_GridX->setObjectName(QString::fromUtf8("label_GridX"));

        gridLayout_11->addWidget(label_GridX, 2, 0, 1, 1);

        lineEdit_WY = new QLineEdit(groupBox_Pose);
        lineEdit_WY->setObjectName(QString::fromUtf8("lineEdit_WY"));
        sizePolicy7.setHeightForWidth(lineEdit_WY->sizePolicy().hasHeightForWidth());
        lineEdit_WY->setSizePolicy(sizePolicy7);
        lineEdit_WY->setReadOnly(true);

        gridLayout_11->addWidget(lineEdit_WY, 1, 3, 1, 1);

        lineEdit_AntiCollision = new QLineEdit(groupBox_Pose);
        lineEdit_AntiCollision->setObjectName(QString::fromUtf8("lineEdit_AntiCollision"));
        sizePolicy7.setHeightForWidth(lineEdit_AntiCollision->sizePolicy().hasHeightForWidth());
        lineEdit_AntiCollision->setSizePolicy(sizePolicy7);
        lineEdit_AntiCollision->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_AntiCollision->setReadOnly(true);

        gridLayout_11->addWidget(lineEdit_AntiCollision, 3, 1, 1, 1);

        label_ErrorCode = new QLabel(groupBox_Pose);
        label_ErrorCode->setObjectName(QString::fromUtf8("label_ErrorCode"));
        sizePolicy8.setHeightForWidth(label_ErrorCode->sizePolicy().hasHeightForWidth());
        label_ErrorCode->setSizePolicy(sizePolicy8);

        gridLayout_11->addWidget(label_ErrorCode, 3, 4, 1, 1);

        lineEdit_CurrentMap = new QLineEdit(groupBox_Pose);
        lineEdit_CurrentMap->setObjectName(QString::fromUtf8("lineEdit_CurrentMap"));
        sizePolicy7.setHeightForWidth(lineEdit_CurrentMap->sizePolicy().hasHeightForWidth());
        lineEdit_CurrentMap->setSizePolicy(sizePolicy7);
        lineEdit_CurrentMap->setReadOnly(true);

        gridLayout_11->addWidget(lineEdit_CurrentMap, 2, 5, 1, 1);

        lineEdit_Angle = new QLineEdit(groupBox_Pose);
        lineEdit_Angle->setObjectName(QString::fromUtf8("lineEdit_Angle"));
        sizePolicy7.setHeightForWidth(lineEdit_Angle->sizePolicy().hasHeightForWidth());
        lineEdit_Angle->setSizePolicy(sizePolicy7);
        lineEdit_Angle->setReadOnly(true);

        gridLayout_11->addWidget(lineEdit_Angle, 1, 5, 1, 1);

        label_AntiCollision = new QLabel(groupBox_Pose);
        label_AntiCollision->setObjectName(QString::fromUtf8("label_AntiCollision"));
        sizePolicy8.setHeightForWidth(label_AntiCollision->sizePolicy().hasHeightForWidth());
        label_AntiCollision->setSizePolicy(sizePolicy8);

        gridLayout_11->addWidget(label_AntiCollision, 3, 0, 1, 1);

        label_Battery = new QLabel(groupBox_Pose);
        label_Battery->setObjectName(QString::fromUtf8("label_Battery"));

        gridLayout_11->addWidget(label_Battery, 1, 6, 1, 1);

        label_WorkMode = new QLabel(groupBox_Pose);
        label_WorkMode->setObjectName(QString::fromUtf8("label_WorkMode"));
        sizePolicy8.setHeightForWidth(label_WorkMode->sizePolicy().hasHeightForWidth());
        label_WorkMode->setSizePolicy(sizePolicy8);

        gridLayout_11->addWidget(label_WorkMode, 3, 2, 1, 1);

        lineEdit_WorkMode = new QLineEdit(groupBox_Pose);
        lineEdit_WorkMode->setObjectName(QString::fromUtf8("lineEdit_WorkMode"));
        sizePolicy7.setHeightForWidth(lineEdit_WorkMode->sizePolicy().hasHeightForWidth());
        lineEdit_WorkMode->setSizePolicy(sizePolicy7);
        lineEdit_WorkMode->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_WorkMode->setReadOnly(true);

        gridLayout_11->addWidget(lineEdit_WorkMode, 3, 3, 1, 1);

        lineEdit_ChassisVer = new QLineEdit(groupBox_Pose);
        lineEdit_ChassisVer->setObjectName(QString::fromUtf8("lineEdit_ChassisVer"));
        sizePolicy7.setHeightForWidth(lineEdit_ChassisVer->sizePolicy().hasHeightForWidth());
        lineEdit_ChassisVer->setSizePolicy(sizePolicy7);
        lineEdit_ChassisVer->setReadOnly(true);

        gridLayout_11->addWidget(lineEdit_ChassisVer, 3, 7, 1, 1);

        label_ChassisVer = new QLabel(groupBox_Pose);
        label_ChassisVer->setObjectName(QString::fromUtf8("label_ChassisVer"));
        sizePolicy8.setHeightForWidth(label_ChassisVer->sizePolicy().hasHeightForWidth());
        label_ChassisVer->setSizePolicy(sizePolicy8);

        gridLayout_11->addWidget(label_ChassisVer, 3, 6, 1, 1);

        label_GridY = new QLabel(groupBox_Pose);
        label_GridY->setObjectName(QString::fromUtf8("label_GridY"));

        gridLayout_11->addWidget(label_GridY, 2, 2, 1, 1);

        lineEdit_ErrorCode = new QLineEdit(groupBox_Pose);
        lineEdit_ErrorCode->setObjectName(QString::fromUtf8("lineEdit_ErrorCode"));
        sizePolicy7.setHeightForWidth(lineEdit_ErrorCode->sizePolicy().hasHeightForWidth());
        lineEdit_ErrorCode->setSizePolicy(sizePolicy7);
        lineEdit_ErrorCode->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_ErrorCode->setReadOnly(true);

        gridLayout_11->addWidget(lineEdit_ErrorCode, 3, 5, 1, 1);

        lineEdit_NavVer = new QLineEdit(groupBox_Pose);
        lineEdit_NavVer->setObjectName(QString::fromUtf8("lineEdit_NavVer"));
        sizePolicy7.setHeightForWidth(lineEdit_NavVer->sizePolicy().hasHeightForWidth());
        lineEdit_NavVer->setSizePolicy(sizePolicy7);
        lineEdit_NavVer->setReadOnly(true);

        gridLayout_11->addWidget(lineEdit_NavVer, 2, 7, 1, 1);

        label_CurrentMap = new QLabel(groupBox_Pose);
        label_CurrentMap->setObjectName(QString::fromUtf8("label_CurrentMap"));

        gridLayout_11->addWidget(label_CurrentMap, 2, 4, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_ConnStatus = new QLabel(groupBox_Pose);
        label_ConnStatus->setObjectName(QString::fromUtf8("label_ConnStatus"));

        horizontalLayout_8->addWidget(label_ConnStatus);

        light_Connected = new c_Fr_Light(groupBox_Pose);
        light_Connected->setObjectName(QString::fromUtf8("light_Connected"));
        light_Connected->setMinimumSize(QSize(20, 20));

        horizontalLayout_8->addWidget(light_Connected);

        label_Ready = new QLabel(groupBox_Pose);
        label_Ready->setObjectName(QString::fromUtf8("label_Ready"));

        horizontalLayout_8->addWidget(label_Ready);

        light_Ready = new c_Fr_Light(groupBox_Pose);
        light_Ready->setObjectName(QString::fromUtf8("light_Ready"));
        light_Ready->setMinimumSize(QSize(20, 20));

        horizontalLayout_8->addWidget(light_Ready);

        label_Localized = new QLabel(groupBox_Pose);
        label_Localized->setObjectName(QString::fromUtf8("label_Localized"));

        horizontalLayout_8->addWidget(label_Localized);

        light_Localized = new c_Fr_Light(groupBox_Pose);
        light_Localized->setObjectName(QString::fromUtf8("light_Localized"));
        light_Localized->setMinimumSize(QSize(20, 20));

        horizontalLayout_8->addWidget(light_Localized);

        label_Charging = new QLabel(groupBox_Pose);
        label_Charging->setObjectName(QString::fromUtf8("label_Charging"));

        horizontalLayout_8->addWidget(label_Charging);

        light_Charging = new c_Fr_Light(groupBox_Pose);
        light_Charging->setObjectName(QString::fromUtf8("light_Charging"));
        light_Charging->setMinimumSize(QSize(20, 20));

        horizontalLayout_8->addWidget(light_Charging);

        label_Task = new QLabel(groupBox_Pose);
        label_Task->setObjectName(QString::fromUtf8("label_Task"));

        horizontalLayout_8->addWidget(label_Task);

        light_Task = new c_Fr_Light(groupBox_Pose);
        light_Task->setObjectName(QString::fromUtf8("light_Task"));
        light_Task->setMinimumSize(QSize(20, 20));

        horizontalLayout_8->addWidget(light_Task);

        label_Lidar = new QLabel(groupBox_Pose);
        label_Lidar->setObjectName(QString::fromUtf8("label_Lidar"));

        horizontalLayout_8->addWidget(label_Lidar);

        light_Lidar = new c_Fr_Light(groupBox_Pose);
        light_Lidar->setObjectName(QString::fromUtf8("light_Lidar"));
        light_Lidar->setMinimumSize(QSize(20, 20));

        horizontalLayout_8->addWidget(light_Lidar);

        label_I = new QLabel(groupBox_Pose);
        label_I->setObjectName(QString::fromUtf8("label_I"));

        horizontalLayout_8->addWidget(label_I);

        light_IMU = new c_Fr_Light(groupBox_Pose);
        light_IMU->setObjectName(QString::fromUtf8("light_IMU"));
        light_IMU->setMinimumSize(QSize(20, 20));

        horizontalLayout_8->addWidget(light_IMU);

        label_O = new QLabel(groupBox_Pose);
        label_O->setObjectName(QString::fromUtf8("label_O"));

        horizontalLayout_8->addWidget(label_O);

        light_Odom = new c_Fr_Light(groupBox_Pose);
        light_Odom->setObjectName(QString::fromUtf8("light_Odom"));
        light_Odom->setMinimumSize(QSize(20, 20));

        horizontalLayout_8->addWidget(light_Odom);

        label_Cam = new QLabel(groupBox_Pose);
        label_Cam->setObjectName(QString::fromUtf8("label_Cam"));

        horizontalLayout_8->addWidget(label_Cam);

        light_Camera = new c_Fr_Light(groupBox_Pose);
        light_Camera->setObjectName(QString::fromUtf8("light_Camera"));
        light_Camera->setMinimumSize(QSize(20, 20));

        horizontalLayout_8->addWidget(light_Camera);

        label_Estop = new QLabel(groupBox_Pose);
        label_Estop->setObjectName(QString::fromUtf8("label_Estop"));

        horizontalLayout_8->addWidget(label_Estop);

        light_Estop = new c_Fr_Light(groupBox_Pose);
        light_Estop->setObjectName(QString::fromUtf8("light_Estop"));
        light_Estop->setMinimumSize(QSize(20, 20));

        horizontalLayout_8->addWidget(light_Estop);


        gridLayout_11->addLayout(horizontalLayout_8, 0, 0, 1, 8);


        verticalLayout_3->addWidget(groupBox_Pose);

        tabWidget_Magic = new QTabWidget(groupBox_7);
        tabWidget_Magic->setObjectName(QString::fromUtf8("tabWidget_Magic"));
        QSizePolicy sizePolicy15(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy15.setHorizontalStretch(0);
        sizePolicy15.setVerticalStretch(1);
        sizePolicy15.setHeightForWidth(tabWidget_Magic->sizePolicy().hasHeightForWidth());
        tabWidget_Magic->setSizePolicy(sizePolicy15);
        tab_Map = new QWidget();
        tab_Map->setObjectName(QString::fromUtf8("tab_Map"));
        gridLayout_13 = new QGridLayout(tab_Map);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        groupBox_FixedNav = new QGroupBox(tab_Map);
        groupBox_FixedNav->setObjectName(QString::fromUtf8("groupBox_FixedNav"));
        sizePolicy.setHeightForWidth(groupBox_FixedNav->sizePolicy().hasHeightForWidth());
        groupBox_FixedNav->setSizePolicy(sizePolicy);
        horizontalLayout_FixedNav = new QHBoxLayout(groupBox_FixedNav);
        horizontalLayout_FixedNav->setSpacing(6);
        horizontalLayout_FixedNav->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_FixedNav->setObjectName(QString::fromUtf8("horizontalLayout_FixedNav"));
        label_FixedX = new QLabel(groupBox_FixedNav);
        label_FixedX->setObjectName(QString::fromUtf8("label_FixedX"));
        sizePolicy5.setHeightForWidth(label_FixedX->sizePolicy().hasHeightForWidth());
        label_FixedX->setSizePolicy(sizePolicy5);

        horizontalLayout_FixedNav->addWidget(label_FixedX);

        spin_FixedX = new QDoubleSpinBox(groupBox_FixedNav);
        spin_FixedX->setObjectName(QString::fromUtf8("spin_FixedX"));
        spin_FixedX->setDecimals(0);
        spin_FixedX->setMinimum(-10000.000000000000000);
        spin_FixedX->setMaximum(10000.000000000000000);
        spin_FixedX->setSingleStep(1.000000000000000);

        horizontalLayout_FixedNav->addWidget(spin_FixedX);

        label_FixedY = new QLabel(groupBox_FixedNav);
        label_FixedY->setObjectName(QString::fromUtf8("label_FixedY"));
        sizePolicy5.setHeightForWidth(label_FixedY->sizePolicy().hasHeightForWidth());
        label_FixedY->setSizePolicy(sizePolicy5);

        horizontalLayout_FixedNav->addWidget(label_FixedY);

        spin_FixedY = new QDoubleSpinBox(groupBox_FixedNav);
        spin_FixedY->setObjectName(QString::fromUtf8("spin_FixedY"));
        spin_FixedY->setDecimals(0);
        spin_FixedY->setMinimum(-10000.000000000000000);
        spin_FixedY->setMaximum(10000.000000000000000);
        spin_FixedY->setSingleStep(1.000000000000000);

        horizontalLayout_FixedNav->addWidget(spin_FixedY);

        label_FixedAngle = new QLabel(groupBox_FixedNav);
        label_FixedAngle->setObjectName(QString::fromUtf8("label_FixedAngle"));
        sizePolicy5.setHeightForWidth(label_FixedAngle->sizePolicy().hasHeightForWidth());
        label_FixedAngle->setSizePolicy(sizePolicy5);

        horizontalLayout_FixedNav->addWidget(label_FixedAngle);

        spin_FixedAngle = new QDoubleSpinBox(groupBox_FixedNav);
        spin_FixedAngle->setObjectName(QString::fromUtf8("spin_FixedAngle"));
        spin_FixedAngle->setDecimals(1);
        spin_FixedAngle->setMinimum(-180.000000000000000);
        spin_FixedAngle->setMaximum(180.000000000000000);
        spin_FixedAngle->setSingleStep(1.000000000000000);

        horizontalLayout_FixedNav->addWidget(spin_FixedAngle);

        btn_FixedNavStart = new QPushButton(groupBox_FixedNav);
        btn_FixedNavStart->setObjectName(QString::fromUtf8("btn_FixedNavStart"));

        horizontalLayout_FixedNav->addWidget(btn_FixedNavStart);

        btn_FixedNavLoop = new QPushButton(groupBox_FixedNav);
        btn_FixedNavLoop->setObjectName(QString::fromUtf8("btn_FixedNavLoop"));

        horizontalLayout_FixedNav->addWidget(btn_FixedNavLoop);


        gridLayout_13->addWidget(groupBox_FixedNav, 6, 0, 1, 1);

        groupBox_InitPose = new QGroupBox(tab_Map);
        groupBox_InitPose->setObjectName(QString::fromUtf8("groupBox_InitPose"));
        sizePolicy.setHeightForWidth(groupBox_InitPose->sizePolicy().hasHeightForWidth());
        groupBox_InitPose->setSizePolicy(sizePolicy);
        horizontalLayout_InitPose = new QHBoxLayout(groupBox_InitPose);
        horizontalLayout_InitPose->setSpacing(6);
        horizontalLayout_InitPose->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_InitPose->setObjectName(QString::fromUtf8("horizontalLayout_InitPose"));
        combo_InitPoint = new QComboBox(groupBox_InitPose);
        combo_InitPoint->setObjectName(QString::fromUtf8("combo_InitPoint"));

        horizontalLayout_InitPose->addWidget(combo_InitPoint);

        btn_DynamicInit = new QPushButton(groupBox_InitPose);
        btn_DynamicInit->setObjectName(QString::fromUtf8("btn_DynamicInit"));

        horizontalLayout_InitPose->addWidget(btn_DynamicInit);

        btn_StaticInit = new QPushButton(groupBox_InitPose);
        btn_StaticInit->setObjectName(QString::fromUtf8("btn_StaticInit"));

        horizontalLayout_InitPose->addWidget(btn_StaticInit);

        btn_GridInit = new QPushButton(groupBox_InitPose);
        btn_GridInit->setObjectName(QString::fromUtf8("btn_GridInit"));

        horizontalLayout_InitPose->addWidget(btn_GridInit);

        btn_InitResult = new QPushButton(groupBox_InitPose);
        btn_InitResult->setObjectName(QString::fromUtf8("btn_InitResult"));

        horizontalLayout_InitPose->addWidget(btn_InitResult);


        gridLayout_13->addWidget(groupBox_InitPose, 2, 0, 1, 1);

        groupBox_TaskControl = new QGroupBox(tab_Map);
        groupBox_TaskControl->setObjectName(QString::fromUtf8("groupBox_TaskControl"));
        sizePolicy.setHeightForWidth(groupBox_TaskControl->sizePolicy().hasHeightForWidth());
        groupBox_TaskControl->setSizePolicy(sizePolicy);
        horizontalLayout_TaskControl = new QHBoxLayout(groupBox_TaskControl);
        horizontalLayout_TaskControl->setSpacing(6);
        horizontalLayout_TaskControl->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_TaskControl->setObjectName(QString::fromUtf8("horizontalLayout_TaskControl"));
        btn_StartTask = new QPushButton(groupBox_TaskControl);
        btn_StartTask->setObjectName(QString::fromUtf8("btn_StartTask"));

        horizontalLayout_TaskControl->addWidget(btn_StartTask);

        btn_LoopStart = new QPushButton(groupBox_TaskControl);
        btn_LoopStart->setObjectName(QString::fromUtf8("btn_LoopStart"));

        horizontalLayout_TaskControl->addWidget(btn_LoopStart);

        btn_PauseTask = new QPushButton(groupBox_TaskControl);
        btn_PauseTask->setObjectName(QString::fromUtf8("btn_PauseTask"));

        horizontalLayout_TaskControl->addWidget(btn_PauseTask);

        btn_ResumeTask = new QPushButton(groupBox_TaskControl);
        btn_ResumeTask->setObjectName(QString::fromUtf8("btn_ResumeTask"));

        horizontalLayout_TaskControl->addWidget(btn_ResumeTask);

        btn_StopTask = new QPushButton(groupBox_TaskControl);
        btn_StopTask->setObjectName(QString::fromUtf8("btn_StopTask"));

        horizontalLayout_TaskControl->addWidget(btn_StopTask);

        btn_GetTaskLog = new QPushButton(groupBox_TaskControl);
        btn_GetTaskLog->setObjectName(QString::fromUtf8("btn_GetTaskLog"));

        horizontalLayout_TaskControl->addWidget(btn_GetTaskLog);

        lineEdit_TaskID = new QLineEdit(groupBox_TaskControl);
        lineEdit_TaskID->setObjectName(QString::fromUtf8("lineEdit_TaskID"));

        horizontalLayout_TaskControl->addWidget(lineEdit_TaskID);


        gridLayout_13->addWidget(groupBox_TaskControl, 4, 0, 1, 1);

        groupBox_TaskSelect = new QGroupBox(tab_Map);
        groupBox_TaskSelect->setObjectName(QString::fromUtf8("groupBox_TaskSelect"));
        sizePolicy.setHeightForWidth(groupBox_TaskSelect->sizePolicy().hasHeightForWidth());
        groupBox_TaskSelect->setSizePolicy(sizePolicy);
        horizontalLayout_TaskSelect = new QHBoxLayout(groupBox_TaskSelect);
        horizontalLayout_TaskSelect->setSpacing(6);
        horizontalLayout_TaskSelect->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_TaskSelect->setObjectName(QString::fromUtf8("horizontalLayout_TaskSelect"));
        label_TaskType = new QLabel(groupBox_TaskSelect);
        label_TaskType->setObjectName(QString::fromUtf8("label_TaskType"));
        sizePolicy5.setHeightForWidth(label_TaskType->sizePolicy().hasHeightForWidth());
        label_TaskType->setSizePolicy(sizePolicy5);

        horizontalLayout_TaskSelect->addWidget(label_TaskType);

        combo_TaskType = new QComboBox(groupBox_TaskSelect);
        combo_TaskType->addItem(QString());
        combo_TaskType->addItem(QString());
        combo_TaskType->addItem(QString());
        combo_TaskType->addItem(QString());
        combo_TaskType->setObjectName(QString::fromUtf8("combo_TaskType"));

        horizontalLayout_TaskSelect->addWidget(combo_TaskType);

        label_TaskName = new QLabel(groupBox_TaskSelect);
        label_TaskName->setObjectName(QString::fromUtf8("label_TaskName"));
        sizePolicy5.setHeightForWidth(label_TaskName->sizePolicy().hasHeightForWidth());
        label_TaskName->setSizePolicy(sizePolicy5);

        horizontalLayout_TaskSelect->addWidget(label_TaskName);

        combo_TaskName = new QComboBox(groupBox_TaskSelect);
        combo_TaskName->setObjectName(QString::fromUtf8("combo_TaskName"));

        horizontalLayout_TaskSelect->addWidget(combo_TaskName);

        btn_RefreshNavPoints = new QPushButton(groupBox_TaskSelect);
        btn_RefreshNavPoints->setObjectName(QString::fromUtf8("btn_RefreshNavPoints"));

        horizontalLayout_TaskSelect->addWidget(btn_RefreshNavPoints);

        label_LoopCount = new QLabel(groupBox_TaskSelect);
        label_LoopCount->setObjectName(QString::fromUtf8("label_LoopCount"));
        sizePolicy5.setHeightForWidth(label_LoopCount->sizePolicy().hasHeightForWidth());
        label_LoopCount->setSizePolicy(sizePolicy5);

        horizontalLayout_TaskSelect->addWidget(label_LoopCount);

        spin_LoopCount = new QSpinBox(groupBox_TaskSelect);
        spin_LoopCount->setObjectName(QString::fromUtf8("spin_LoopCount"));
        spin_LoopCount->setMinimum(1);
        spin_LoopCount->setMaximum(999);
        spin_LoopCount->setValue(1);

        horizontalLayout_TaskSelect->addWidget(spin_LoopCount);


        gridLayout_13->addWidget(groupBox_TaskSelect, 3, 0, 1, 1);

        horizontalLayout_MapOps1 = new QHBoxLayout();
        horizontalLayout_MapOps1->setSpacing(6);
        horizontalLayout_MapOps1->setObjectName(QString::fromUtf8("horizontalLayout_MapOps1"));
        comboBox_MapList = new QComboBox(tab_Map);
        comboBox_MapList->setObjectName(QString::fromUtf8("comboBox_MapList"));
        sizePolicy7.setHeightForWidth(comboBox_MapList->sizePolicy().hasHeightForWidth());
        comboBox_MapList->setSizePolicy(sizePolicy7);

        horizontalLayout_MapOps1->addWidget(comboBox_MapList);

        btn_RefreshToken = new QPushButton(tab_Map);
        btn_RefreshToken->setObjectName(QString::fromUtf8("btn_RefreshToken"));
        sizePolicy9.setHeightForWidth(btn_RefreshToken->sizePolicy().hasHeightForWidth());
        btn_RefreshToken->setSizePolicy(sizePolicy9);

        horizontalLayout_MapOps1->addWidget(btn_RefreshToken);

        btn_RefreshMapList = new QPushButton(tab_Map);
        btn_RefreshMapList->setObjectName(QString::fromUtf8("btn_RefreshMapList"));
        sizePolicy9.setHeightForWidth(btn_RefreshMapList->sizePolicy().hasHeightForWidth());
        btn_RefreshMapList->setSizePolicy(sizePolicy9);

        horizontalLayout_MapOps1->addWidget(btn_RefreshMapList);

        btn_SwitchMap = new QPushButton(tab_Map);
        btn_SwitchMap->setObjectName(QString::fromUtf8("btn_SwitchMap"));
        sizePolicy9.setHeightForWidth(btn_SwitchMap->sizePolicy().hasHeightForWidth());
        btn_SwitchMap->setSizePolicy(sizePolicy9);

        horizontalLayout_MapOps1->addWidget(btn_SwitchMap);


        gridLayout_13->addLayout(horizontalLayout_MapOps1, 1, 0, 1, 1);

        groupBox_TaskStatus = new QGroupBox(tab_Map);
        groupBox_TaskStatus->setObjectName(QString::fromUtf8("groupBox_TaskStatus"));
        sizePolicy.setHeightForWidth(groupBox_TaskStatus->sizePolicy().hasHeightForWidth());
        groupBox_TaskStatus->setSizePolicy(sizePolicy);
        horizontalLayout_TaskStatus = new QHBoxLayout(groupBox_TaskStatus);
        horizontalLayout_TaskStatus->setSpacing(6);
        horizontalLayout_TaskStatus->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_TaskStatus->setObjectName(QString::fromUtf8("horizontalLayout_TaskStatus"));
        label_TaskStatusText = new QLabel(groupBox_TaskStatus);
        label_TaskStatusText->setObjectName(QString::fromUtf8("label_TaskStatusText"));
        sizePolicy.setHeightForWidth(label_TaskStatusText->sizePolicy().hasHeightForWidth());
        label_TaskStatusText->setSizePolicy(sizePolicy);

        horizontalLayout_TaskStatus->addWidget(label_TaskStatusText);

        progress_Task = new QProgressBar(groupBox_TaskStatus);
        progress_Task->setObjectName(QString::fromUtf8("progress_Task"));
        progress_Task->setValue(0);

        horizontalLayout_TaskStatus->addWidget(progress_Task);

        label_RemainTime = new QLabel(groupBox_TaskStatus);
        label_RemainTime->setObjectName(QString::fromUtf8("label_RemainTime"));
        sizePolicy.setHeightForWidth(label_RemainTime->sizePolicy().hasHeightForWidth());
        label_RemainTime->setSizePolicy(sizePolicy);

        horizontalLayout_TaskStatus->addWidget(label_RemainTime);

        label_RemainTimeValue = new QLabel(groupBox_TaskStatus);
        label_RemainTimeValue->setObjectName(QString::fromUtf8("label_RemainTimeValue"));

        horizontalLayout_TaskStatus->addWidget(label_RemainTimeValue);

        label_LoopInfo = new QLabel(groupBox_TaskStatus);
        label_LoopInfo->setObjectName(QString::fromUtf8("label_LoopInfo"));
        sizePolicy.setHeightForWidth(label_LoopInfo->sizePolicy().hasHeightForWidth());
        label_LoopInfo->setSizePolicy(sizePolicy);

        horizontalLayout_TaskStatus->addWidget(label_LoopInfo);


        gridLayout_13->addWidget(groupBox_TaskStatus, 5, 0, 1, 1);

        tabWidget_Magic->addTab(tab_Map, QString());
        tab_PathPoint = new QWidget();
        tab_PathPoint->setObjectName(QString::fromUtf8("tab_PathPoint"));
        verticalLayout_PathPoint = new QVBoxLayout(tab_PathPoint);
        verticalLayout_PathPoint->setSpacing(6);
        verticalLayout_PathPoint->setContentsMargins(11, 11, 11, 11);
        verticalLayout_PathPoint->setObjectName(QString::fromUtf8("verticalLayout_PathPoint"));
        table_NavPoints = new QTableWidget(tab_PathPoint);
        if (table_NavPoints->columnCount() < 5)
            table_NavPoints->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        table_NavPoints->setHorizontalHeaderItem(0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        table_NavPoints->setHorizontalHeaderItem(1, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        table_NavPoints->setHorizontalHeaderItem(2, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        table_NavPoints->setHorizontalHeaderItem(3, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        table_NavPoints->setHorizontalHeaderItem(4, __qtablewidgetitem25);
        table_NavPoints->setObjectName(QString::fromUtf8("table_NavPoints"));
        QSizePolicy sizePolicy16(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy16.setHorizontalStretch(0);
        sizePolicy16.setVerticalStretch(0);
        sizePolicy16.setHeightForWidth(table_NavPoints->sizePolicy().hasHeightForWidth());
        table_NavPoints->setSizePolicy(sizePolicy16);
        table_NavPoints->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_NavPoints->setSelectionMode(QAbstractItemView::SingleSelection);
        table_NavPoints->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_NavPoints->setColumnCount(5);
        table_NavPoints->horizontalHeader()->setStretchLastSection(true);
        table_NavPoints->verticalHeader()->setVisible(false);

        verticalLayout_PathPoint->addWidget(table_NavPoints);

        tabWidget_Magic->addTab(tab_PathPoint, QString());
        tab_System = new QWidget();
        tab_System->setObjectName(QString::fromUtf8("tab_System"));
        verticalLayout_System = new QVBoxLayout(tab_System);
        verticalLayout_System->setSpacing(6);
        verticalLayout_System->setContentsMargins(11, 11, 11, 11);
        verticalLayout_System->setObjectName(QString::fromUtf8("verticalLayout_System"));
        groupBox_Speed = new QGroupBox(tab_System);
        groupBox_Speed->setObjectName(QString::fromUtf8("groupBox_Speed"));
        sizePolicy.setHeightForWidth(groupBox_Speed->sizePolicy().hasHeightForWidth());
        groupBox_Speed->setSizePolicy(sizePolicy);
        gridLayout_Speed = new QGridLayout(groupBox_Speed);
        gridLayout_Speed->setSpacing(6);
        gridLayout_Speed->setContentsMargins(11, 11, 11, 11);
        gridLayout_Speed->setObjectName(QString::fromUtf8("gridLayout_Speed"));
        label_GoalSpeed = new QLabel(groupBox_Speed);
        label_GoalSpeed->setObjectName(QString::fromUtf8("label_GoalSpeed"));
        sizePolicy8.setHeightForWidth(label_GoalSpeed->sizePolicy().hasHeightForWidth());
        label_GoalSpeed->setSizePolicy(sizePolicy8);

        gridLayout_Speed->addWidget(label_GoalSpeed, 0, 0, 1, 1);

        spin_GoalSpeed = new QDoubleSpinBox(groupBox_Speed);
        spin_GoalSpeed->setObjectName(QString::fromUtf8("spin_GoalSpeed"));
        spin_GoalSpeed->setDecimals(2);
        spin_GoalSpeed->setMinimum(0.050000000000000);
        spin_GoalSpeed->setMaximum(1.500000000000000);
        spin_GoalSpeed->setSingleStep(0.050000000000000);
        spin_GoalSpeed->setValue(0.500000000000000);

        gridLayout_Speed->addWidget(spin_GoalSpeed, 0, 1, 1, 1);

        label_GraphSpeed = new QLabel(groupBox_Speed);
        label_GraphSpeed->setObjectName(QString::fromUtf8("label_GraphSpeed"));
        sizePolicy8.setHeightForWidth(label_GraphSpeed->sizePolicy().hasHeightForWidth());
        label_GraphSpeed->setSizePolicy(sizePolicy8);

        gridLayout_Speed->addWidget(label_GraphSpeed, 0, 2, 1, 1);

        spin_GraphSpeed = new QDoubleSpinBox(groupBox_Speed);
        spin_GraphSpeed->setObjectName(QString::fromUtf8("spin_GraphSpeed"));
        spin_GraphSpeed->setDecimals(2);
        spin_GraphSpeed->setMinimum(0.050000000000000);
        spin_GraphSpeed->setMaximum(1.500000000000000);
        spin_GraphSpeed->setSingleStep(0.050000000000000);
        spin_GraphSpeed->setValue(0.200000000000000);

        gridLayout_Speed->addWidget(spin_GraphSpeed, 0, 3, 1, 1);

        label_RecordSpeed = new QLabel(groupBox_Speed);
        label_RecordSpeed->setObjectName(QString::fromUtf8("label_RecordSpeed"));
        sizePolicy8.setHeightForWidth(label_RecordSpeed->sizePolicy().hasHeightForWidth());
        label_RecordSpeed->setSizePolicy(sizePolicy8);

        gridLayout_Speed->addWidget(label_RecordSpeed, 1, 0, 1, 1);

        spin_RecordSpeed = new QDoubleSpinBox(groupBox_Speed);
        spin_RecordSpeed->setObjectName(QString::fromUtf8("spin_RecordSpeed"));
        spin_RecordSpeed->setDecimals(2);
        spin_RecordSpeed->setMinimum(0.050000000000000);
        spin_RecordSpeed->setMaximum(1.500000000000000);
        spin_RecordSpeed->setSingleStep(0.050000000000000);
        spin_RecordSpeed->setValue(0.500000000000000);

        gridLayout_Speed->addWidget(spin_RecordSpeed, 1, 1, 1, 1);

        btn_UpdateSpeed = new QPushButton(groupBox_Speed);
        btn_UpdateSpeed->setObjectName(QString::fromUtf8("btn_UpdateSpeed"));

        gridLayout_Speed->addWidget(btn_UpdateSpeed, 1, 2, 1, 2);


        verticalLayout_System->addWidget(groupBox_Speed);

        groupBox_Charge = new QGroupBox(tab_System);
        groupBox_Charge->setObjectName(QString::fromUtf8("groupBox_Charge"));
        sizePolicy.setHeightForWidth(groupBox_Charge->sizePolicy().hasHeightForWidth());
        groupBox_Charge->setSizePolicy(sizePolicy);
        horizontalLayout_Charge = new QHBoxLayout(groupBox_Charge);
        horizontalLayout_Charge->setSpacing(6);
        horizontalLayout_Charge->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_Charge->setObjectName(QString::fromUtf8("horizontalLayout_Charge"));
        label_ChargePoint = new QLabel(groupBox_Charge);
        label_ChargePoint->setObjectName(QString::fromUtf8("label_ChargePoint"));
        sizePolicy.setHeightForWidth(label_ChargePoint->sizePolicy().hasHeightForWidth());
        label_ChargePoint->setSizePolicy(sizePolicy);

        horizontalLayout_Charge->addWidget(label_ChargePoint);

        lineEdit_ChargePoint = new QLineEdit(groupBox_Charge);
        lineEdit_ChargePoint->setObjectName(QString::fromUtf8("lineEdit_ChargePoint"));

        horizontalLayout_Charge->addWidget(lineEdit_ChargePoint);

        btn_StartRecharge = new QPushButton(groupBox_Charge);
        btn_StartRecharge->setObjectName(QString::fromUtf8("btn_StartRecharge"));

        horizontalLayout_Charge->addWidget(btn_StartRecharge);

        btn_DisRecharge = new QPushButton(groupBox_Charge);
        btn_DisRecharge->setObjectName(QString::fromUtf8("btn_DisRecharge"));

        horizontalLayout_Charge->addWidget(btn_DisRecharge);

        btn_PauseRecharge = new QPushButton(groupBox_Charge);
        btn_PauseRecharge->setObjectName(QString::fromUtf8("btn_PauseRecharge"));

        horizontalLayout_Charge->addWidget(btn_PauseRecharge);

        btn_ResumeRecharge = new QPushButton(groupBox_Charge);
        btn_ResumeRecharge->setObjectName(QString::fromUtf8("btn_ResumeRecharge"));

        horizontalLayout_Charge->addWidget(btn_ResumeRecharge);

        btn_CancelRecharge = new QPushButton(groupBox_Charge);
        btn_CancelRecharge->setObjectName(QString::fromUtf8("btn_CancelRecharge"));

        horizontalLayout_Charge->addWidget(btn_CancelRecharge);

        label_ChargeStatus = new QLabel(groupBox_Charge);
        label_ChargeStatus->setObjectName(QString::fromUtf8("label_ChargeStatus"));
        sizePolicy.setHeightForWidth(label_ChargeStatus->sizePolicy().hasHeightForWidth());
        label_ChargeStatus->setSizePolicy(sizePolicy);

        horizontalLayout_Charge->addWidget(label_ChargeStatus);

        lbl_ChargeStatus = new QLabel(groupBox_Charge);
        lbl_ChargeStatus->setObjectName(QString::fromUtf8("lbl_ChargeStatus"));
        sizePolicy.setHeightForWidth(lbl_ChargeStatus->sizePolicy().hasHeightForWidth());
        lbl_ChargeStatus->setSizePolicy(sizePolicy);

        horizontalLayout_Charge->addWidget(lbl_ChargeStatus);


        verticalLayout_System->addWidget(groupBox_Charge);

        groupBox_Move = new QGroupBox(tab_System);
        groupBox_Move->setObjectName(QString::fromUtf8("groupBox_Move"));
        sizePolicy.setHeightForWidth(groupBox_Move->sizePolicy().hasHeightForWidth());
        groupBox_Move->setSizePolicy(sizePolicy);
        gridLayout_Move = new QGridLayout(groupBox_Move);
        gridLayout_Move->setSpacing(6);
        gridLayout_Move->setContentsMargins(11, 11, 11, 11);
        gridLayout_Move->setObjectName(QString::fromUtf8("gridLayout_Move"));
        groupBox_SpeedControl = new QGroupBox(groupBox_Move);
        groupBox_SpeedControl->setObjectName(QString::fromUtf8("groupBox_SpeedControl"));
        sizePolicy.setHeightForWidth(groupBox_SpeedControl->sizePolicy().hasHeightForWidth());
        groupBox_SpeedControl->setSizePolicy(sizePolicy);
        horizontalLayout_SpeedControl = new QHBoxLayout(groupBox_SpeedControl);
        horizontalLayout_SpeedControl->setSpacing(6);
        horizontalLayout_SpeedControl->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_SpeedControl->setObjectName(QString::fromUtf8("horizontalLayout_SpeedControl"));
        label_LinearSpeed = new QLabel(groupBox_SpeedControl);
        label_LinearSpeed->setObjectName(QString::fromUtf8("label_LinearSpeed"));
        sizePolicy5.setHeightForWidth(label_LinearSpeed->sizePolicy().hasHeightForWidth());
        label_LinearSpeed->setSizePolicy(sizePolicy5);

        horizontalLayout_SpeedControl->addWidget(label_LinearSpeed);

        spin_LinearSpeed = new QDoubleSpinBox(groupBox_SpeedControl);
        spin_LinearSpeed->setObjectName(QString::fromUtf8("spin_LinearSpeed"));
        spin_LinearSpeed->setDecimals(2);
        spin_LinearSpeed->setMinimum(-1.500000000000000);
        spin_LinearSpeed->setMaximum(1.500000000000000);
        spin_LinearSpeed->setSingleStep(0.050000000000000);
        spin_LinearSpeed->setValue(0.200000000000000);

        horizontalLayout_SpeedControl->addWidget(spin_LinearSpeed);

        label_AngularSpeed = new QLabel(groupBox_SpeedControl);
        label_AngularSpeed->setObjectName(QString::fromUtf8("label_AngularSpeed"));
        sizePolicy5.setHeightForWidth(label_AngularSpeed->sizePolicy().hasHeightForWidth());
        label_AngularSpeed->setSizePolicy(sizePolicy5);

        horizontalLayout_SpeedControl->addWidget(label_AngularSpeed);

        spin_AngularSpeed = new QDoubleSpinBox(groupBox_SpeedControl);
        spin_AngularSpeed->setObjectName(QString::fromUtf8("spin_AngularSpeed"));
        spin_AngularSpeed->setDecimals(2);
        spin_AngularSpeed->setMinimum(-1.500000000000000);
        spin_AngularSpeed->setMaximum(1.500000000000000);
        spin_AngularSpeed->setSingleStep(0.050000000000000);
        spin_AngularSpeed->setValue(0.000000000000000);

        horizontalLayout_SpeedControl->addWidget(spin_AngularSpeed);


        gridLayout_Move->addWidget(groupBox_SpeedControl, 0, 0, 1, 6);

        groupBox_MoveButtons = new QGroupBox(groupBox_Move);
        groupBox_MoveButtons->setObjectName(QString::fromUtf8("groupBox_MoveButtons"));
        sizePolicy.setHeightForWidth(groupBox_MoveButtons->sizePolicy().hasHeightForWidth());
        groupBox_MoveButtons->setSizePolicy(sizePolicy);
        horizontalLayout_MoveButtons = new QHBoxLayout(groupBox_MoveButtons);
        horizontalLayout_MoveButtons->setSpacing(6);
        horizontalLayout_MoveButtons->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_MoveButtons->setObjectName(QString::fromUtf8("horizontalLayout_MoveButtons"));
        btn_MoveForward = new QPushButton(groupBox_MoveButtons);
        btn_MoveForward->setObjectName(QString::fromUtf8("btn_MoveForward"));

        horizontalLayout_MoveButtons->addWidget(btn_MoveForward);

        btn_MoveBackward = new QPushButton(groupBox_MoveButtons);
        btn_MoveBackward->setObjectName(QString::fromUtf8("btn_MoveBackward"));

        horizontalLayout_MoveButtons->addWidget(btn_MoveBackward);

        btn_TurnLeft = new QPushButton(groupBox_MoveButtons);
        btn_TurnLeft->setObjectName(QString::fromUtf8("btn_TurnLeft"));

        horizontalLayout_MoveButtons->addWidget(btn_TurnLeft);

        btn_TurnRight = new QPushButton(groupBox_MoveButtons);
        btn_TurnRight->setObjectName(QString::fromUtf8("btn_TurnRight"));

        horizontalLayout_MoveButtons->addWidget(btn_TurnRight);

        btn_StopMove = new QPushButton(groupBox_MoveButtons);
        btn_StopMove->setObjectName(QString::fromUtf8("btn_StopMove"));

        horizontalLayout_MoveButtons->addWidget(btn_StopMove);


        gridLayout_Move->addWidget(groupBox_MoveButtons, 1, 0, 1, 6);

        groupBox_MoveParams = new QGroupBox(groupBox_Move);
        groupBox_MoveParams->setObjectName(QString::fromUtf8("groupBox_MoveParams"));
        sizePolicy.setHeightForWidth(groupBox_MoveParams->sizePolicy().hasHeightForWidth());
        groupBox_MoveParams->setSizePolicy(sizePolicy);
        horizontalLayout_MoveParams = new QHBoxLayout(groupBox_MoveParams);
        horizontalLayout_MoveParams->setSpacing(6);
        horizontalLayout_MoveParams->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_MoveParams->setObjectName(QString::fromUtf8("horizontalLayout_MoveParams"));
        label_MoveMode = new QLabel(groupBox_MoveParams);
        label_MoveMode->setObjectName(QString::fromUtf8("label_MoveMode"));
        sizePolicy5.setHeightForWidth(label_MoveMode->sizePolicy().hasHeightForWidth());
        label_MoveMode->setSizePolicy(sizePolicy5);

        horizontalLayout_MoveParams->addWidget(label_MoveMode);

        combo_MoveMode = new QComboBox(groupBox_MoveParams);
        combo_MoveMode->addItem(QString());
        combo_MoveMode->addItem(QString());
        combo_MoveMode->setObjectName(QString::fromUtf8("combo_MoveMode"));

        horizontalLayout_MoveParams->addWidget(combo_MoveMode);

        label_MoveTarget = new QLabel(groupBox_MoveParams);
        label_MoveTarget->setObjectName(QString::fromUtf8("label_MoveTarget"));
        sizePolicy5.setHeightForWidth(label_MoveTarget->sizePolicy().hasHeightForWidth());
        label_MoveTarget->setSizePolicy(sizePolicy5);

        horizontalLayout_MoveParams->addWidget(label_MoveTarget);

        spin_MoveTarget = new QDoubleSpinBox(groupBox_MoveParams);
        spin_MoveTarget->setObjectName(QString::fromUtf8("spin_MoveTarget"));
        spin_MoveTarget->setDecimals(2);
        spin_MoveTarget->setMinimum(0.100000000000000);
        spin_MoveTarget->setMaximum(100.000000000000000);
        spin_MoveTarget->setSingleStep(0.100000000000000);
        spin_MoveTarget->setValue(1.000000000000000);

        horizontalLayout_MoveParams->addWidget(spin_MoveTarget);

        btn_ExecuteMoveParams = new QPushButton(groupBox_MoveParams);
        btn_ExecuteMoveParams->setObjectName(QString::fromUtf8("btn_ExecuteMoveParams"));

        horizontalLayout_MoveParams->addWidget(btn_ExecuteMoveParams);

        btn_CancelMoveParams = new QPushButton(groupBox_MoveParams);
        btn_CancelMoveParams->setObjectName(QString::fromUtf8("btn_CancelMoveParams"));

        horizontalLayout_MoveParams->addWidget(btn_CancelMoveParams);


        gridLayout_Move->addWidget(groupBox_MoveParams, 2, 0, 1, 6);


        verticalLayout_System->addWidget(groupBox_Move);

        tabWidget_Magic->addTab(tab_System, QString());
        tab_Sensor = new QWidget();
        tab_Sensor->setObjectName(QString::fromUtf8("tab_Sensor"));
        gridLayout_18 = new QGridLayout(tab_Sensor);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        groupBox_IMU = new QGroupBox(tab_Sensor);
        groupBox_IMU->setObjectName(QString::fromUtf8("groupBox_IMU"));
        sizePolicy.setHeightForWidth(groupBox_IMU->sizePolicy().hasHeightForWidth());
        groupBox_IMU->setSizePolicy(sizePolicy);
        horizontalLayout_IMU = new QHBoxLayout(groupBox_IMU);
        horizontalLayout_IMU->setSpacing(6);
        horizontalLayout_IMU->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_IMU->setObjectName(QString::fromUtf8("horizontalLayout_IMU"));
        label_IMU_AVX = new QLabel(groupBox_IMU);
        label_IMU_AVX->setObjectName(QString::fromUtf8("label_IMU_AVX"));
        sizePolicy.setHeightForWidth(label_IMU_AVX->sizePolicy().hasHeightForWidth());
        label_IMU_AVX->setSizePolicy(sizePolicy);

        horizontalLayout_IMU->addWidget(label_IMU_AVX);

        lineEdit_IMU_AVX = new QLineEdit(groupBox_IMU);
        lineEdit_IMU_AVX->setObjectName(QString::fromUtf8("lineEdit_IMU_AVX"));
        lineEdit_IMU_AVX->setReadOnly(true);

        horizontalLayout_IMU->addWidget(lineEdit_IMU_AVX);

        label_IMU_AVY = new QLabel(groupBox_IMU);
        label_IMU_AVY->setObjectName(QString::fromUtf8("label_IMU_AVY"));
        sizePolicy.setHeightForWidth(label_IMU_AVY->sizePolicy().hasHeightForWidth());
        label_IMU_AVY->setSizePolicy(sizePolicy);

        horizontalLayout_IMU->addWidget(label_IMU_AVY);

        lineEdit_IMU_AVY = new QLineEdit(groupBox_IMU);
        lineEdit_IMU_AVY->setObjectName(QString::fromUtf8("lineEdit_IMU_AVY"));
        lineEdit_IMU_AVY->setReadOnly(true);

        horizontalLayout_IMU->addWidget(lineEdit_IMU_AVY);

        label_IMU_AVZ = new QLabel(groupBox_IMU);
        label_IMU_AVZ->setObjectName(QString::fromUtf8("label_IMU_AVZ"));
        sizePolicy.setHeightForWidth(label_IMU_AVZ->sizePolicy().hasHeightForWidth());
        label_IMU_AVZ->setSizePolicy(sizePolicy);

        horizontalLayout_IMU->addWidget(label_IMU_AVZ);

        lineEdit_IMU_AVZ = new QLineEdit(groupBox_IMU);
        lineEdit_IMU_AVZ->setObjectName(QString::fromUtf8("lineEdit_IMU_AVZ"));
        lineEdit_IMU_AVZ->setReadOnly(true);

        horizontalLayout_IMU->addWidget(lineEdit_IMU_AVZ);

        label_IMU_LAX = new QLabel(groupBox_IMU);
        label_IMU_LAX->setObjectName(QString::fromUtf8("label_IMU_LAX"));
        sizePolicy.setHeightForWidth(label_IMU_LAX->sizePolicy().hasHeightForWidth());
        label_IMU_LAX->setSizePolicy(sizePolicy);

        horizontalLayout_IMU->addWidget(label_IMU_LAX);

        lineEdit_IMU_LAX = new QLineEdit(groupBox_IMU);
        lineEdit_IMU_LAX->setObjectName(QString::fromUtf8("lineEdit_IMU_LAX"));
        lineEdit_IMU_LAX->setReadOnly(true);

        horizontalLayout_IMU->addWidget(lineEdit_IMU_LAX);

        label_IMU_LAY = new QLabel(groupBox_IMU);
        label_IMU_LAY->setObjectName(QString::fromUtf8("label_IMU_LAY"));
        sizePolicy.setHeightForWidth(label_IMU_LAY->sizePolicy().hasHeightForWidth());
        label_IMU_LAY->setSizePolicy(sizePolicy);

        horizontalLayout_IMU->addWidget(label_IMU_LAY);

        lineEdit_IMU_LAY = new QLineEdit(groupBox_IMU);
        lineEdit_IMU_LAY->setObjectName(QString::fromUtf8("lineEdit_IMU_LAY"));
        lineEdit_IMU_LAY->setReadOnly(true);

        horizontalLayout_IMU->addWidget(lineEdit_IMU_LAY);

        label_IMU_LAZ = new QLabel(groupBox_IMU);
        label_IMU_LAZ->setObjectName(QString::fromUtf8("label_IMU_LAZ"));
        sizePolicy.setHeightForWidth(label_IMU_LAZ->sizePolicy().hasHeightForWidth());
        label_IMU_LAZ->setSizePolicy(sizePolicy);

        horizontalLayout_IMU->addWidget(label_IMU_LAZ);

        lineEdit_IMU_LAZ = new QLineEdit(groupBox_IMU);
        lineEdit_IMU_LAZ->setObjectName(QString::fromUtf8("lineEdit_IMU_LAZ"));
        lineEdit_IMU_LAZ->setReadOnly(true);

        horizontalLayout_IMU->addWidget(lineEdit_IMU_LAZ);


        gridLayout_18->addWidget(groupBox_IMU, 0, 0, 1, 2);

        groupBox_Odom = new QGroupBox(tab_Sensor);
        groupBox_Odom->setObjectName(QString::fromUtf8("groupBox_Odom"));
        sizePolicy.setHeightForWidth(groupBox_Odom->sizePolicy().hasHeightForWidth());
        groupBox_Odom->setSizePolicy(sizePolicy);
        horizontalLayout_Odom = new QHBoxLayout(groupBox_Odom);
        horizontalLayout_Odom->setSpacing(6);
        horizontalLayout_Odom->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_Odom->setObjectName(QString::fromUtf8("horizontalLayout_Odom"));
        label_Odom_LX = new QLabel(groupBox_Odom);
        label_Odom_LX->setObjectName(QString::fromUtf8("label_Odom_LX"));
        sizePolicy.setHeightForWidth(label_Odom_LX->sizePolicy().hasHeightForWidth());
        label_Odom_LX->setSizePolicy(sizePolicy);

        horizontalLayout_Odom->addWidget(label_Odom_LX);

        lineEdit_Odom_LX = new QLineEdit(groupBox_Odom);
        lineEdit_Odom_LX->setObjectName(QString::fromUtf8("lineEdit_Odom_LX"));
        lineEdit_Odom_LX->setReadOnly(true);

        horizontalLayout_Odom->addWidget(lineEdit_Odom_LX);

        label_Odom_LY = new QLabel(groupBox_Odom);
        label_Odom_LY->setObjectName(QString::fromUtf8("label_Odom_LY"));
        sizePolicy.setHeightForWidth(label_Odom_LY->sizePolicy().hasHeightForWidth());
        label_Odom_LY->setSizePolicy(sizePolicy);

        horizontalLayout_Odom->addWidget(label_Odom_LY);

        lineEdit_Odom_LY = new QLineEdit(groupBox_Odom);
        lineEdit_Odom_LY->setObjectName(QString::fromUtf8("lineEdit_Odom_LY"));
        lineEdit_Odom_LY->setReadOnly(true);

        horizontalLayout_Odom->addWidget(lineEdit_Odom_LY);

        label_Odom_LZ = new QLabel(groupBox_Odom);
        label_Odom_LZ->setObjectName(QString::fromUtf8("label_Odom_LZ"));
        sizePolicy.setHeightForWidth(label_Odom_LZ->sizePolicy().hasHeightForWidth());
        label_Odom_LZ->setSizePolicy(sizePolicy);

        horizontalLayout_Odom->addWidget(label_Odom_LZ);

        lineEdit_Odom_LZ = new QLineEdit(groupBox_Odom);
        lineEdit_Odom_LZ->setObjectName(QString::fromUtf8("lineEdit_Odom_LZ"));
        lineEdit_Odom_LZ->setReadOnly(true);

        horizontalLayout_Odom->addWidget(lineEdit_Odom_LZ);

        label_Odom_AX = new QLabel(groupBox_Odom);
        label_Odom_AX->setObjectName(QString::fromUtf8("label_Odom_AX"));
        sizePolicy.setHeightForWidth(label_Odom_AX->sizePolicy().hasHeightForWidth());
        label_Odom_AX->setSizePolicy(sizePolicy);

        horizontalLayout_Odom->addWidget(label_Odom_AX);

        lineEdit_Odom_AX = new QLineEdit(groupBox_Odom);
        lineEdit_Odom_AX->setObjectName(QString::fromUtf8("lineEdit_Odom_AX"));
        lineEdit_Odom_AX->setReadOnly(true);

        horizontalLayout_Odom->addWidget(lineEdit_Odom_AX);

        label_Odom_AY = new QLabel(groupBox_Odom);
        label_Odom_AY->setObjectName(QString::fromUtf8("label_Odom_AY"));
        sizePolicy.setHeightForWidth(label_Odom_AY->sizePolicy().hasHeightForWidth());
        label_Odom_AY->setSizePolicy(sizePolicy);

        horizontalLayout_Odom->addWidget(label_Odom_AY);

        lineEdit_Odom_AY = new QLineEdit(groupBox_Odom);
        lineEdit_Odom_AY->setObjectName(QString::fromUtf8("lineEdit_Odom_AY"));
        lineEdit_Odom_AY->setReadOnly(true);

        horizontalLayout_Odom->addWidget(lineEdit_Odom_AY);

        label_Odom_AZ = new QLabel(groupBox_Odom);
        label_Odom_AZ->setObjectName(QString::fromUtf8("label_Odom_AZ"));
        sizePolicy.setHeightForWidth(label_Odom_AZ->sizePolicy().hasHeightForWidth());
        label_Odom_AZ->setSizePolicy(sizePolicy);

        horizontalLayout_Odom->addWidget(label_Odom_AZ);

        lineEdit_Odom_AZ = new QLineEdit(groupBox_Odom);
        lineEdit_Odom_AZ->setObjectName(QString::fromUtf8("lineEdit_Odom_AZ"));
        lineEdit_Odom_AZ->setReadOnly(true);

        horizontalLayout_Odom->addWidget(lineEdit_Odom_AZ);


        gridLayout_18->addWidget(groupBox_Odom, 1, 0, 1, 2);

        groupBox_GPS = new QGroupBox(tab_Sensor);
        groupBox_GPS->setObjectName(QString::fromUtf8("groupBox_GPS"));
        sizePolicy.setHeightForWidth(groupBox_GPS->sizePolicy().hasHeightForWidth());
        groupBox_GPS->setSizePolicy(sizePolicy);
        horizontalLayout_GPS = new QHBoxLayout(groupBox_GPS);
        horizontalLayout_GPS->setSpacing(6);
        horizontalLayout_GPS->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_GPS->setObjectName(QString::fromUtf8("horizontalLayout_GPS"));
        label_GPS_Lat = new QLabel(groupBox_GPS);
        label_GPS_Lat->setObjectName(QString::fromUtf8("label_GPS_Lat"));
        sizePolicy.setHeightForWidth(label_GPS_Lat->sizePolicy().hasHeightForWidth());
        label_GPS_Lat->setSizePolicy(sizePolicy);

        horizontalLayout_GPS->addWidget(label_GPS_Lat);

        lineEdit_GPS_Lat = new QLineEdit(groupBox_GPS);
        lineEdit_GPS_Lat->setObjectName(QString::fromUtf8("lineEdit_GPS_Lat"));
        lineEdit_GPS_Lat->setReadOnly(true);

        horizontalLayout_GPS->addWidget(lineEdit_GPS_Lat);

        label_GPS_Lon = new QLabel(groupBox_GPS);
        label_GPS_Lon->setObjectName(QString::fromUtf8("label_GPS_Lon"));
        sizePolicy.setHeightForWidth(label_GPS_Lon->sizePolicy().hasHeightForWidth());
        label_GPS_Lon->setSizePolicy(sizePolicy);

        horizontalLayout_GPS->addWidget(label_GPS_Lon);

        lineEdit_GPS_Lon = new QLineEdit(groupBox_GPS);
        lineEdit_GPS_Lon->setObjectName(QString::fromUtf8("lineEdit_GPS_Lon"));
        lineEdit_GPS_Lon->setReadOnly(true);

        horizontalLayout_GPS->addWidget(lineEdit_GPS_Lon);

        label_GPS_Alt = new QLabel(groupBox_GPS);
        label_GPS_Alt->setObjectName(QString::fromUtf8("label_GPS_Alt"));
        sizePolicy.setHeightForWidth(label_GPS_Alt->sizePolicy().hasHeightForWidth());
        label_GPS_Alt->setSizePolicy(sizePolicy);

        horizontalLayout_GPS->addWidget(label_GPS_Alt);

        lineEdit_GPS_Alt = new QLineEdit(groupBox_GPS);
        lineEdit_GPS_Alt->setObjectName(QString::fromUtf8("lineEdit_GPS_Alt"));
        lineEdit_GPS_Alt->setReadOnly(true);

        horizontalLayout_GPS->addWidget(lineEdit_GPS_Alt);


        gridLayout_18->addWidget(groupBox_GPS, 2, 0, 1, 2);

        groupBox_Ultrasonic = new QGroupBox(tab_Sensor);
        groupBox_Ultrasonic->setObjectName(QString::fromUtf8("groupBox_Ultrasonic"));
        sizePolicy.setHeightForWidth(groupBox_Ultrasonic->sizePolicy().hasHeightForWidth());
        groupBox_Ultrasonic->setSizePolicy(sizePolicy);
        gridLayout_Ultrasonic = new QGridLayout(groupBox_Ultrasonic);
        gridLayout_Ultrasonic->setSpacing(6);
        gridLayout_Ultrasonic->setContentsMargins(11, 11, 11, 11);
        gridLayout_Ultrasonic->setObjectName(QString::fromUtf8("gridLayout_Ultrasonic"));
        lbl_US_FL = new QLabel(groupBox_Ultrasonic);
        lbl_US_FL->setObjectName(QString::fromUtf8("lbl_US_FL"));
        sizePolicy.setHeightForWidth(lbl_US_FL->sizePolicy().hasHeightForWidth());
        lbl_US_FL->setSizePolicy(sizePolicy);

        gridLayout_Ultrasonic->addWidget(lbl_US_FL, 0, 0, 1, 1);

        lineEdit_US_FL = new QLineEdit(groupBox_Ultrasonic);
        lineEdit_US_FL->setObjectName(QString::fromUtf8("lineEdit_US_FL"));
        lineEdit_US_FL->setReadOnly(true);

        gridLayout_Ultrasonic->addWidget(lineEdit_US_FL, 0, 1, 1, 1);

        lbl_US_FR = new QLabel(groupBox_Ultrasonic);
        lbl_US_FR->setObjectName(QString::fromUtf8("lbl_US_FR"));
        sizePolicy.setHeightForWidth(lbl_US_FR->sizePolicy().hasHeightForWidth());
        lbl_US_FR->setSizePolicy(sizePolicy);

        gridLayout_Ultrasonic->addWidget(lbl_US_FR, 0, 2, 1, 1);

        lineEdit_US_FR = new QLineEdit(groupBox_Ultrasonic);
        lineEdit_US_FR->setObjectName(QString::fromUtf8("lineEdit_US_FR"));
        lineEdit_US_FR->setReadOnly(true);

        gridLayout_Ultrasonic->addWidget(lineEdit_US_FR, 0, 3, 1, 1);

        lbl_US_RL = new QLabel(groupBox_Ultrasonic);
        lbl_US_RL->setObjectName(QString::fromUtf8("lbl_US_RL"));
        sizePolicy.setHeightForWidth(lbl_US_RL->sizePolicy().hasHeightForWidth());
        lbl_US_RL->setSizePolicy(sizePolicy);

        gridLayout_Ultrasonic->addWidget(lbl_US_RL, 0, 4, 1, 1);

        lineEdit_US_RL = new QLineEdit(groupBox_Ultrasonic);
        lineEdit_US_RL->setObjectName(QString::fromUtf8("lineEdit_US_RL"));
        lineEdit_US_RL->setReadOnly(true);

        gridLayout_Ultrasonic->addWidget(lineEdit_US_RL, 0, 5, 1, 1);

        lbl_US_RR = new QLabel(groupBox_Ultrasonic);
        lbl_US_RR->setObjectName(QString::fromUtf8("lbl_US_RR"));
        sizePolicy.setHeightForWidth(lbl_US_RR->sizePolicy().hasHeightForWidth());
        lbl_US_RR->setSizePolicy(sizePolicy);

        gridLayout_Ultrasonic->addWidget(lbl_US_RR, 0, 6, 1, 1);

        lineEdit_US_RR = new QLineEdit(groupBox_Ultrasonic);
        lineEdit_US_RR->setObjectName(QString::fromUtf8("lineEdit_US_RR"));
        lineEdit_US_RR->setReadOnly(true);

        gridLayout_Ultrasonic->addWidget(lineEdit_US_RR, 0, 7, 1, 1);

        lbl_US_LF = new QLabel(groupBox_Ultrasonic);
        lbl_US_LF->setObjectName(QString::fromUtf8("lbl_US_LF"));
        sizePolicy.setHeightForWidth(lbl_US_LF->sizePolicy().hasHeightForWidth());
        lbl_US_LF->setSizePolicy(sizePolicy);

        gridLayout_Ultrasonic->addWidget(lbl_US_LF, 1, 0, 1, 1);

        lineEdit_US_LF = new QLineEdit(groupBox_Ultrasonic);
        lineEdit_US_LF->setObjectName(QString::fromUtf8("lineEdit_US_LF"));
        lineEdit_US_LF->setReadOnly(true);

        gridLayout_Ultrasonic->addWidget(lineEdit_US_LF, 1, 1, 1, 1);

        lbl_US_LR = new QLabel(groupBox_Ultrasonic);
        lbl_US_LR->setObjectName(QString::fromUtf8("lbl_US_LR"));
        sizePolicy.setHeightForWidth(lbl_US_LR->sizePolicy().hasHeightForWidth());
        lbl_US_LR->setSizePolicy(sizePolicy);

        gridLayout_Ultrasonic->addWidget(lbl_US_LR, 1, 2, 1, 1);

        lineEdit_US_LR = new QLineEdit(groupBox_Ultrasonic);
        lineEdit_US_LR->setObjectName(QString::fromUtf8("lineEdit_US_LR"));
        lineEdit_US_LR->setReadOnly(true);

        gridLayout_Ultrasonic->addWidget(lineEdit_US_LR, 1, 3, 1, 1);

        lbl_US_RF = new QLabel(groupBox_Ultrasonic);
        lbl_US_RF->setObjectName(QString::fromUtf8("lbl_US_RF"));
        sizePolicy.setHeightForWidth(lbl_US_RF->sizePolicy().hasHeightForWidth());
        lbl_US_RF->setSizePolicy(sizePolicy);

        gridLayout_Ultrasonic->addWidget(lbl_US_RF, 1, 4, 1, 1);

        lineEdit_US_RF = new QLineEdit(groupBox_Ultrasonic);
        lineEdit_US_RF->setObjectName(QString::fromUtf8("lineEdit_US_RF"));
        lineEdit_US_RF->setReadOnly(true);

        gridLayout_Ultrasonic->addWidget(lineEdit_US_RF, 1, 5, 1, 1);

        lbl_US_RR2 = new QLabel(groupBox_Ultrasonic);
        lbl_US_RR2->setObjectName(QString::fromUtf8("lbl_US_RR2"));
        sizePolicy.setHeightForWidth(lbl_US_RR2->sizePolicy().hasHeightForWidth());
        lbl_US_RR2->setSizePolicy(sizePolicy);

        gridLayout_Ultrasonic->addWidget(lbl_US_RR2, 1, 6, 1, 1);

        lineEdit_US_RR2 = new QLineEdit(groupBox_Ultrasonic);
        lineEdit_US_RR2->setObjectName(QString::fromUtf8("lineEdit_US_RR2"));
        lineEdit_US_RR2->setReadOnly(true);

        gridLayout_Ultrasonic->addWidget(lineEdit_US_RR2, 1, 7, 1, 1);


        gridLayout_18->addWidget(groupBox_Ultrasonic, 3, 0, 1, 2);

        groupBox_CameraControl = new QGroupBox(tab_Sensor);
        groupBox_CameraControl->setObjectName(QString::fromUtf8("groupBox_CameraControl"));
        sizePolicy.setHeightForWidth(groupBox_CameraControl->sizePolicy().hasHeightForWidth());
        groupBox_CameraControl->setSizePolicy(sizePolicy);
        gridLayout_CameraControl = new QGridLayout(groupBox_CameraControl);
        gridLayout_CameraControl->setSpacing(6);
        gridLayout_CameraControl->setContentsMargins(11, 11, 11, 11);
        gridLayout_CameraControl->setObjectName(QString::fromUtf8("gridLayout_CameraControl"));
        label_FrontCamCtrl = new QLabel(groupBox_CameraControl);
        label_FrontCamCtrl->setObjectName(QString::fromUtf8("label_FrontCamCtrl"));

        gridLayout_CameraControl->addWidget(label_FrontCamCtrl, 0, 0, 1, 1);

        btn_GetFrontRGB = new QPushButton(groupBox_CameraControl);
        btn_GetFrontRGB->setObjectName(QString::fromUtf8("btn_GetFrontRGB"));

        gridLayout_CameraControl->addWidget(btn_GetFrontRGB, 0, 1, 1, 1);

        btn_GetFrontDepth = new QPushButton(groupBox_CameraControl);
        btn_GetFrontDepth->setObjectName(QString::fromUtf8("btn_GetFrontDepth"));

        gridLayout_CameraControl->addWidget(btn_GetFrontDepth, 0, 2, 1, 1);

        btn_GetFrontPointCloud = new QPushButton(groupBox_CameraControl);
        btn_GetFrontPointCloud->setObjectName(QString::fromUtf8("btn_GetFrontPointCloud"));

        gridLayout_CameraControl->addWidget(btn_GetFrontPointCloud, 0, 3, 1, 1);

        label_RearCamCtrl = new QLabel(groupBox_CameraControl);
        label_RearCamCtrl->setObjectName(QString::fromUtf8("label_RearCamCtrl"));

        gridLayout_CameraControl->addWidget(label_RearCamCtrl, 1, 0, 1, 1);

        btn_GetRearRGB = new QPushButton(groupBox_CameraControl);
        btn_GetRearRGB->setObjectName(QString::fromUtf8("btn_GetRearRGB"));

        gridLayout_CameraControl->addWidget(btn_GetRearRGB, 1, 1, 1, 1);

        btn_GetRearDepth = new QPushButton(groupBox_CameraControl);
        btn_GetRearDepth->setObjectName(QString::fromUtf8("btn_GetRearDepth"));

        gridLayout_CameraControl->addWidget(btn_GetRearDepth, 1, 2, 1, 1);

        btn_GetRearPointCloud = new QPushButton(groupBox_CameraControl);
        btn_GetRearPointCloud->setObjectName(QString::fromUtf8("btn_GetRearPointCloud"));

        gridLayout_CameraControl->addWidget(btn_GetRearPointCloud, 1, 3, 1, 1);


        gridLayout_18->addWidget(groupBox_CameraControl, 4, 0, 1, 1);

        groupBox_LogoLog = new QGroupBox(tab_Sensor);
        groupBox_LogoLog->setObjectName(QString::fromUtf8("groupBox_LogoLog"));
        sizePolicy.setHeightForWidth(groupBox_LogoLog->sizePolicy().hasHeightForWidth());
        groupBox_LogoLog->setSizePolicy(sizePolicy);
        verticalLayout_LogoLog = new QVBoxLayout(groupBox_LogoLog);
        verticalLayout_LogoLog->setSpacing(6);
        verticalLayout_LogoLog->setContentsMargins(11, 11, 11, 11);
        verticalLayout_LogoLog->setObjectName(QString::fromUtf8("verticalLayout_LogoLog"));
        horizontalLayout_Logo = new QHBoxLayout();
        horizontalLayout_Logo->setSpacing(6);
        horizontalLayout_Logo->setObjectName(QString::fromUtf8("horizontalLayout_Logo"));
        btn_GetLogoBase64 = new QPushButton(groupBox_LogoLog);
        btn_GetLogoBase64->setObjectName(QString::fromUtf8("btn_GetLogoBase64"));

        horizontalLayout_Logo->addWidget(btn_GetLogoBase64);

        btn_GetBackgroundBase64 = new QPushButton(groupBox_LogoLog);
        btn_GetBackgroundBase64->setObjectName(QString::fromUtf8("btn_GetBackgroundBase64"));

        horizontalLayout_Logo->addWidget(btn_GetBackgroundBase64);


        verticalLayout_LogoLog->addLayout(horizontalLayout_Logo);

        horizontalLayout_LogMgmt = new QHBoxLayout();
        horizontalLayout_LogMgmt->setSpacing(6);
        horizontalLayout_LogMgmt->setObjectName(QString::fromUtf8("horizontalLayout_LogMgmt"));
        label_LogType = new QLabel(groupBox_LogoLog);
        label_LogType->setObjectName(QString::fromUtf8("label_LogType"));

        horizontalLayout_LogMgmt->addWidget(label_LogType);

        combo_LogType = new QComboBox(groupBox_LogoLog);
        combo_LogType->addItem(QString());
        combo_LogType->addItem(QString());
        combo_LogType->addItem(QString());
        combo_LogType->addItem(QString());
        combo_LogType->setObjectName(QString::fromUtf8("combo_LogType"));

        horizontalLayout_LogMgmt->addWidget(combo_LogType);

        label_LogFileName = new QLabel(groupBox_LogoLog);
        label_LogFileName->setObjectName(QString::fromUtf8("label_LogFileName"));

        horizontalLayout_LogMgmt->addWidget(label_LogFileName);

        lineEdit_LogFileName = new QLineEdit(groupBox_LogoLog);
        lineEdit_LogFileName->setObjectName(QString::fromUtf8("lineEdit_LogFileName"));

        horizontalLayout_LogMgmt->addWidget(lineEdit_LogFileName);

        btn_DownLogs = new QPushButton(groupBox_LogoLog);
        btn_DownLogs->setObjectName(QString::fromUtf8("btn_DownLogs"));

        horizontalLayout_LogMgmt->addWidget(btn_DownLogs);

        btn_DropLogs = new QPushButton(groupBox_LogoLog);
        btn_DropLogs->setObjectName(QString::fromUtf8("btn_DropLogs"));

        horizontalLayout_LogMgmt->addWidget(btn_DropLogs);


        verticalLayout_LogoLog->addLayout(horizontalLayout_LogMgmt);


        gridLayout_18->addWidget(groupBox_LogoLog, 4, 1, 1, 1);

        tabWidget_Magic->addTab(tab_Sensor, QString());

        verticalLayout_3->addWidget(tabWidget_Magic);


        gridLayout_14->addLayout(verticalLayout_3, 0, 1, 1, 1);

        groupBox_MapList = new QGroupBox(groupBox_7);
        groupBox_MapList->setObjectName(QString::fromUtf8("groupBox_MapList"));
        QSizePolicy sizePolicy17(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy17.setHorizontalStretch(0);
        sizePolicy17.setVerticalStretch(1);
        sizePolicy17.setHeightForWidth(groupBox_MapList->sizePolicy().hasHeightForWidth());
        groupBox_MapList->setSizePolicy(sizePolicy17);
        gridLayout_16 = new QGridLayout(groupBox_MapList);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        widget_MapView = new c_Magic_Map_View(groupBox_MapList);
        widget_MapView->setObjectName(QString::fromUtf8("widget_MapView"));
        sizePolicy17.setHeightForWidth(widget_MapView->sizePolicy().hasHeightForWidth());
        widget_MapView->setSizePolicy(sizePolicy17);

        gridLayout_16->addWidget(widget_MapView, 0, 0, 1, 1);


        gridLayout_14->addWidget(groupBox_MapList, 0, 2, 1, 1);

        groupBox_Log = new QGroupBox(groupBox_7);
        groupBox_Log->setObjectName(QString::fromUtf8("groupBox_Log"));
        sizePolicy14.setHeightForWidth(groupBox_Log->sizePolicy().hasHeightForWidth());
        groupBox_Log->setSizePolicy(sizePolicy14);
        verticalLayout_Log = new QVBoxLayout(groupBox_Log);
        verticalLayout_Log->setSpacing(6);
        verticalLayout_Log->setContentsMargins(11, 11, 11, 11);
        verticalLayout_Log->setObjectName(QString::fromUtf8("verticalLayout_Log"));
        Magic_Log = new QTextEdit(groupBox_Log);
        Magic_Log->setObjectName(QString::fromUtf8("Magic_Log"));
        sizePolicy14.setHeightForWidth(Magic_Log->sizePolicy().hasHeightForWidth());
        Magic_Log->setSizePolicy(sizePolicy14);
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(9);
        Magic_Log->setFont(font);
        Magic_Log->setReadOnly(true);

        verticalLayout_Log->addWidget(Magic_Log);


        gridLayout_14->addWidget(groupBox_Log, 1, 0, 1, 3);


        gridLayout_10->addWidget(groupBox_7, 0, 0, 1, 1);

        stackedWidget->addWidget(Magic_Widget);

        gridLayout_15->addWidget(stackedWidget, 0, 1, 1, 1);

        Robot_App_Widget->setCentralWidget(centralWidget);
        Status_Bar = new QStatusBar(Robot_App_Widget);
        Status_Bar->setObjectName(QString::fromUtf8("Status_Bar"));
        Robot_App_Widget->setStatusBar(Status_Bar);

        retranslateUi(Robot_App_Widget);

        stackedWidget->setCurrentIndex(3);
        tabWidget_Status->setCurrentIndex(0);
        tabWidget_Magic->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Robot_App_Widget);
    } // setupUi

    void retranslateUi(QMainWindow *Robot_App_Widget)
    {
        Robot_App_Widget->setWindowTitle(QApplication::translate("Robot_App_Widget", "\346\231\272\350\203\275\345\272\225\351\203\250\345\267\241\346\243\200\346\234\272\345\231\250\344\272\272\346\216\247\345\210\266\345\271\263\345\217\260", nullptr));
        groupBox_5->setTitle(QApplication::translate("Robot_App_Widget", "\345\212\237\350\203\275\345\257\274\350\210\252", nullptr));
        Show_Work_Widget->setText(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241", nullptr));
        Show_IO_Widget->setText(QApplication::translate("Robot_App_Widget", "IO", nullptr));
        Show_CGXi_Widget->setText(QApplication::translate("Robot_App_Widget", "\346\234\272\346\242\260\350\207\202", nullptr));
        Show_Pre_Scan_120_Widget->setText(QApplication::translate("Robot_App_Widget", "\347\262\276\346\211\253", nullptr));
        Show_Magic_Widget->setText(QApplication::translate("Robot_App_Widget", "\345\272\225\347\233\230", nullptr));
        groupBox_3->setTitle(QApplication::translate("Robot_App_Widget", "\346\234\272\346\242\260\350\207\202", nullptr));
        label_ip->setText(QApplication::translate("Robot_App_Widget", "IP:", nullptr));
        CGXi_IP->setText(QApplication::translate("Robot_App_Widget", "192.168.6.6", nullptr));
        label_port->setText(QApplication::translate("Robot_App_Widget", "Port:", nullptr));
        CGXi_Port->setText(QApplication::translate("Robot_App_Widget", "502", nullptr));
        CGXi_Connect->setText(QApplication::translate("Robot_App_Widget", "\350\277\236\346\216\245", nullptr));
        CGXi_Disconnect->setText(QApplication::translate("Robot_App_Widget", "\346\226\255\345\274\200", nullptr));
        label_3->setText(QApplication::translate("Robot_App_Widget", "\350\277\236\346\216\245:", nullptr));
        label_4->setText(QApplication::translate("Robot_App_Widget", "\345\260\261\347\273\252:", nullptr));
        label_10->setText(QApplication::translate("Robot_App_Widget", "\350\207\252\345\212\250:", nullptr));
        label_5->setText(QApplication::translate("Robot_App_Widget", "\347\211\210\346\234\254:", nullptr));
        label_6->setText(QApplication::translate("Robot_App_Widget", "\346\250\241\345\274\217:", nullptr));
        label_7->setText(QApplication::translate("Robot_App_Widget", "\351\224\231\350\257\257\347\240\201:", nullptr));
        label_speed->setText(QApplication::translate("Robot_App_Widget", "\345\205\250\345\261\200\351\200\237\345\272\246(%):", nullptr));
        groupBox_6->setTitle(QApplication::translate("Robot_App_Widget", "\347\272\277\345\234\210\346\223\215\344\275\234\357\274\2101000~1008\357\274\211", nullptr));
        Coils_1003->setText(QApplication::translate("Robot_App_Widget", "\346\232\202\345\201\234\347\250\213\345\272\217\357\274\2101003\357\274\211", nullptr));
        Coils_1007->setText(QApplication::translate("Robot_App_Widget", "\346\270\205\351\231\244\346\225\205\351\232\234\357\274\2101007\357\274\211", nullptr));
        Coils_1001->setText(QApplication::translate("Robot_App_Widget", "\346\234\254\344\275\223\344\270\212\347\224\265\344\275\277\350\203\275\357\274\2101001\357\274\211", nullptr));
        Coils_1004->setText(QApplication::translate("Robot_App_Widget", "\345\201\234\346\255\242\347\250\213\345\272\217\357\274\2101004\357\274\211", nullptr));
        Coils_1005->setText(QApplication::translate("Robot_App_Widget", "\350\207\252\347\224\261\346\213\226\345\212\250\357\274\2101005\357\274\211", nullptr));
        Coils_1006->setText(QApplication::translate("Robot_App_Widget", "\344\270\213\344\275\277\350\203\275\357\274\2101006\357\274\211", nullptr));
        Coils_1000->setText(QApplication::translate("Robot_App_Widget", "\345\233\236\345\210\235\345\247\213\347\202\271\357\274\2101000\357\274\211", nullptr));
        Coils_1002->setText(QApplication::translate("Robot_App_Widget", "\345\220\257\345\212\250\347\250\213\345\272\217\357\274\2101002\357\274\211", nullptr));
        groupBox_DO_3->setTitle(QApplication::translate("Robot_App_Widget", "\345\217\257\351\205\215\346\225\260\345\255\227\350\276\223\345\207\272\357\274\210CO0-CO7\357\274\211", nullptr));
        l_do_h3_6->setText(QApplication::translate("Robot_App_Widget", "\347\275\2561", nullptr));
        CGXi_CO0_Set->setText(QApplication::translate("Robot_App_Widget", "\347\275\256\344\275\215", nullptr));
        l_do_h2_5->setText(QApplication::translate("Robot_App_Widget", "\347\212\266\346\200\201", nullptr));
        l_do_h4_3->setText(QApplication::translate("Robot_App_Widget", "\347\275\2560", nullptr));
        l_do_h1_6->setText(QApplication::translate("Robot_App_Widget", "\351\200\232\351\201\223", nullptr));
        l_do_h3_5->setText(QApplication::translate("Robot_App_Widget", "\347\275\2561 ", nullptr));
        l_do_h4_5->setText(QApplication::translate("Robot_App_Widget", "\347\275\2560", nullptr));
        label_DO1_8->setText(QApplication::translate("Robot_App_Widget", "CO5\346\232\202\345\201\234\344\270\272\351\253\230", nullptr));
        CGXi_CO5_Reset->setText(QApplication::translate("Robot_App_Widget", "\345\244\215\344\275\215", nullptr));
        l_do_h3_4->setText(QApplication::translate("Robot_App_Widget", "\347\275\2561", nullptr));
        CGXi_CO0_Reset->setText(QApplication::translate("Robot_App_Widget", "\345\244\215\344\275\215", nullptr));
        l_do_h1_5->setText(QApplication::translate("Robot_App_Widget", "\351\200\232\351\201\223", nullptr));
        l_do_h2_3->setText(QApplication::translate("Robot_App_Widget", "\347\212\266\346\200\201", nullptr));
        l_do_h1_4->setText(QApplication::translate("Robot_App_Widget", "\351\200\232\351\201\223", nullptr));
        l_do_h2_6->setText(QApplication::translate("Robot_App_Widget", "\347\212\266\346\200\201", nullptr));
        l_do_h1_3->setText(QApplication::translate("Robot_App_Widget", "\351\200\232\351\201\223", nullptr));
        CGXi_CO5_Set->setText(QApplication::translate("Robot_App_Widget", "\347\275\256\344\275\215", nullptr));
        l_do_h2_4->setText(QApplication::translate("Robot_App_Widget", "\347\212\266\346\200\201", nullptr));
        l_do_h3_3->setText(QApplication::translate("Robot_App_Widget", "\347\275\2561", nullptr));
        l_do_h4_4->setText(QApplication::translate("Robot_App_Widget", "\347\275\2560", nullptr));
        label_DO0_3->setText(QApplication::translate("Robot_App_Widget", "CO0\344\275\277\350\203\275\346\227\266\344\270\272\351\253\230", nullptr));
        l_do_h4_6->setText(QApplication::translate("Robot_App_Widget", "\347\275\2560", nullptr));
        label_DO1_7->setText(QApplication::translate("Robot_App_Widget", "CO1\344\270\212\347\224\265\346\227\266\344\270\272\351\253\230", nullptr));
        CGXi_CO1_Set->setText(QApplication::translate("Robot_App_Widget", "\347\275\256\344\275\215", nullptr));
        CGXi_CO1_Reset->setText(QApplication::translate("Robot_App_Widget", "\345\244\215\344\275\215", nullptr));
        label_DO1_9->setText(QApplication::translate("Robot_App_Widget", "CO2\345\274\200\346\234\272\346\227\266\344\270\272\351\253\230", nullptr));
        CGXi_CO2_Set->setText(QApplication::translate("Robot_App_Widget", "\347\275\256\344\275\215", nullptr));
        CGXi_CO2_Reset->setText(QApplication::translate("Robot_App_Widget", "\345\244\215\344\275\215", nullptr));
        label_DO0_4->setText(QApplication::translate("Robot_App_Widget", "CO4\345\201\234\346\255\242\344\270\272\351\253\230", nullptr));
        CGXi_CO4_Set->setText(QApplication::translate("Robot_App_Widget", "\347\275\256\344\275\215", nullptr));
        CGXi_CO4_Reset->setText(QApplication::translate("Robot_App_Widget", "\345\244\215\344\275\215", nullptr));
        label_DO1_11->setText(QApplication::translate("Robot_App_Widget", "CO3\351\224\231\350\257\257\346\227\266\344\270\272\351\253\230", nullptr));
        CGXi_CO3_Reset->setText(QApplication::translate("Robot_App_Widget", "\345\244\215\344\275\215", nullptr));
        CGXi_CO3_Set->setText(QApplication::translate("Robot_App_Widget", "\347\275\256\344\275\215", nullptr));
        label_DO1_10->setText(QApplication::translate("Robot_App_Widget", "CO6\350\277\220\345\212\250\344\270\272\351\253\230", nullptr));
        CGXi_CO6_Set->setText(QApplication::translate("Robot_App_Widget", "\347\275\256\344\275\215", nullptr));
        CGXi_CO6_Reset->setText(QApplication::translate("Robot_App_Widget", "\345\244\215\344\275\215", nullptr));
        label_DO1_12->setText(QApplication::translate("Robot_App_Widget", "DO7\345\210\235\345\247\213\344\275\215\344\270\272\351\253\230", nullptr));
        CGXi_CO7_Set->setText(QApplication::translate("Robot_App_Widget", "\347\275\256\344\275\215", nullptr));
        CGXi_CO7_Reset->setText(QApplication::translate("Robot_App_Widget", "\345\244\215\344\275\215", nullptr));
        groupBox_Prog->setTitle(QApplication::translate("Robot_App_Widget", "\347\250\213\345\272\217\344\270\216\347\263\273\347\273\237\346\216\247\345\210\266", nullptr));
        label_8->setText(QApplication::translate("Robot_App_Widget", "\347\233\256\346\240\207\347\264\242\345\274\225:", nullptr));
        Set_HoldingRegisters_88->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245\357\274\21088\357\274\211", nullptr));
        CGXi_Prog_Pause->setText(QApplication::translate("Robot_App_Widget", "\346\232\202\345\201\234\357\274\21089\357\274\211", nullptr));
        CGXi_Prog_Stop->setText(QApplication::translate("Robot_App_Widget", "\345\201\234\346\255\242\357\274\21089\357\274\211", nullptr));
        label_9->setText(QApplication::translate("Robot_App_Widget", "\345\275\223\345\211\215\347\264\242\345\274\225:", nullptr));
        CGXi_Prog_Start->setText(QApplication::translate("Robot_App_Widget", "\342\226\266 \345\220\257\345\212\250/\346\201\242\345\244\215\357\274\21089\357\274\211", nullptr));
        CGXi_Clear_Error->setText(QApplication::translate("Robot_App_Widget", "\346\270\205\351\231\244\351\224\231\350\257\257 (63)", nullptr));
        CGXi_Clear_Warning->setText(QApplication::translate("Robot_App_Widget", "\346\270\205\351\231\244\350\255\246\345\221\212 (64)", nullptr));
        groupBox->setTitle(QApplication::translate("Robot_App_Widget", "\346\234\272\346\242\260\350\207\202\346\227\245\345\277\227\344\277\241\346\201\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_Joint->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Robot_App_Widget", "\350\275\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_Joint->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Robot_App_Widget", "\346\250\241\345\274\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_Joint->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Robot_App_Widget", "\346\270\251\345\272\246(0.1\342\204\203)", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_Joint->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Robot_App_Widget", "\345\256\236\351\231\205\344\275\215\347\275\256(\302\260)", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_Joint->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("Robot_App_Widget", "\347\233\256\346\240\207\344\275\215\347\275\256(\302\260)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_Joint->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("Robot_App_Widget", "\345\256\236\351\231\205\351\200\237\345\272\246(\302\260/s)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_Joint->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("Robot_App_Widget", "\347\233\256\346\240\207\351\200\237\345\272\246(\302\260/s)", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_Joint->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("Robot_App_Widget", "\345\256\236\351\231\205\345\212\240\351\200\237\345\272\246(\302\260/s\302\262)", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_Joint->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("Robot_App_Widget", "\347\233\256\346\240\207\345\212\240\351\200\237\345\272\246(\302\260/s\302\262)", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_Joint->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("Robot_App_Widget", "\345\256\236\351\231\205\350\275\254\347\237\251(0.001)", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_Joint->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("Robot_App_Widget", "\347\233\256\346\240\207\350\275\254\347\237\251(0.001)", nullptr));
        tabWidget_Status->setTabText(tabWidget_Status->indexOf(tab_Joint), QApplication::translate("Robot_App_Widget", "\345\205\263\350\212\202\347\212\266\346\200\201 (Addr: 200~371)", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_TCP->horizontalHeaderItem(0);
        ___qtablewidgetitem11->setText(QApplication::translate("Robot_App_Widget", "\347\273\264\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_TCP->horizontalHeaderItem(1);
        ___qtablewidgetitem12->setText(QApplication::translate("Robot_App_Widget", "\345\256\236\351\231\205\344\275\215\347\275\256(mm/\302\260)", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_TCP->horizontalHeaderItem(2);
        ___qtablewidgetitem13->setText(QApplication::translate("Robot_App_Widget", "\347\233\256\346\240\207\344\275\215\347\275\256(mm/\302\260)", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_TCP->horizontalHeaderItem(3);
        ___qtablewidgetitem14->setText(QApplication::translate("Robot_App_Widget", "\345\256\236\351\231\205\351\200\237\345\272\246(mm/s,\302\260/s)", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_TCP->horizontalHeaderItem(4);
        ___qtablewidgetitem15->setText(QApplication::translate("Robot_App_Widget", "\347\233\256\346\240\207\351\200\237\345\272\246(mm/s,\302\260/s)", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_TCP->horizontalHeaderItem(5);
        ___qtablewidgetitem16->setText(QApplication::translate("Robot_App_Widget", "\345\256\236\351\231\205\345\212\233(N,Nm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_TCP->horizontalHeaderItem(6);
        ___qtablewidgetitem17->setText(QApplication::translate("Robot_App_Widget", "\347\233\256\346\240\207\345\212\233(N,Nm)", nullptr));
        tabWidget_Status->setTabText(tabWidget_Status->indexOf(tab_TCP), QApplication::translate("Robot_App_Widget", "TCP \347\212\266\346\200\201 (Addr: 500~611)", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_Robot->horizontalHeaderItem(0);
        ___qtablewidgetitem18->setText(QApplication::translate("Robot_App_Widget", "\345\217\202\346\225\260\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_Robot->horizontalHeaderItem(1);
        ___qtablewidgetitem19->setText(QApplication::translate("Robot_App_Widget", "\345\275\223\345\211\215\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_Robot->horizontalHeaderItem(2);
        ___qtablewidgetitem20->setText(QApplication::translate("Robot_App_Widget", "\345\215\225\344\275\215", nullptr));
        tabWidget_Status->setTabText(tabWidget_Status->indexOf(tab_Robot), QApplication::translate("Robot_App_Widget", "\346\234\272\345\231\250\344\272\272\347\212\266\346\200\201 (Addr: 850~863)", nullptr));
        groupBox_8->setTitle(QApplication::translate("Robot_App_Widget", "\347\262\276\346\211\253\347\233\270\346\234\272 \342\200\224 \347\253\213\345\210\233\347\273\223\346\236\204\345\205\211 T1", nullptr));
        label_120_Remote_Status->setText(QApplication::translate("Robot_App_Widget", "\350\277\234\347\250\213\345\217\221\351\200\201:", nullptr));
        label_120_Monitor_Status->setText(QApplication::translate("Robot_App_Widget", "\345\217\215\351\246\210\346\216\245\346\224\266:", nullptr));
        label_120_Listen_Status->setText(QApplication::translate("Robot_App_Widget", "TCP\347\233\221\345\220\254:", nullptr));
        label_120_Tran_Status->setText(QApplication::translate("Robot_App_Widget", "TCP\350\275\254\345\217\221:", nullptr));
        label_120_Client_Num->setText(QApplication::translate("Robot_App_Widget", "\345\256\242\346\210\267\347\253\257:", nullptr));
        label_120_Cam_Num->setText(QApplication::translate("Robot_App_Widget", "\347\233\270\346\234\272\347\274\226\345\217\267:", nullptr));
        Pre_Scan_120_Cam_Num->setText(QApplication::translate("Robot_App_Widget", "T1", nullptr));
        label_120_IP->setText(QApplication::translate("Robot_App_Widget", "\347\233\270\346\234\272IP:", nullptr));
        Pre_Scan_120_IP->setText(QApplication::translate("Robot_App_Widget", "192.168.6.35", nullptr));
        label_120_Port->setText(QApplication::translate("Robot_App_Widget", "\347\253\257\345\217\243:", nullptr));
        Pre_Scan_120_Port->setText(QApplication::translate("Robot_App_Widget", "8001", nullptr));
        label_120_Monitor->setText(QApplication::translate("Robot_App_Widget", "\345\217\215\351\246\210\347\253\257\345\217\243:", nullptr));
        Pre_Scan_120_Monitor_Port->setText(QApplication::translate("Robot_App_Widget", "8000", nullptr));
        label_120_Tran->setText(QApplication::translate("Robot_App_Widget", "\350\275\254\345\217\221\347\253\257\345\217\243:", nullptr));
        Pre_Scan_120_Tran_Port->setText(QApplication::translate("Robot_App_Widget", "9000", nullptr));
        Pre_Scan_120_Connect->setText(QApplication::translate("Robot_App_Widget", "\350\277\236\346\216\245", nullptr));
        Pre_Scan_120_Disconnect->setText(QApplication::translate("Robot_App_Widget", "\346\226\255\345\274\200", nullptr));
        groupBox_Task_Info_2->setTitle(QApplication::translate("Robot_App_Widget", "WEB\344\273\273\345\212\241\344\277\241\346\201\257\357\274\210\345\206\231\357\274\211", nullptr));
        set_Pre_Scan_120_TaskID->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        label_120_TaskID_2->setText(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241ID:", nullptr));
        label_120_Axle_2->setText(QApplication::translate("Robot_App_Widget", "\350\275\246\350\275\264\345\217\267:", nullptr));
        label_120_Repair_2->setText(QApplication::translate("Robot_App_Widget", "\344\277\256\347\250\213:", nullptr));
        label_120_StartTime_2->setText(QApplication::translate("Robot_App_Widget", "\345\274\200\345\247\213\346\227\266\351\227\264:", nullptr));
        set_Pre_Scan_120_Wheelset->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        set_Pre_Scan_120_Axle->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        label_120_SendUnit_2->setText(QApplication::translate("Robot_App_Widget", "\351\200\201\350\275\256\345\215\225\344\275\215:", nullptr));
        set_Pre_Scan_120_Repair->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        label_120_Wheelset_2->setText(QApplication::translate("Robot_App_Widget", "\350\275\256\345\257\271\345\217\267:", nullptr));
        set_Pre_Scan_120_StartTime->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        set_Pre_Scan_120_SendUnit->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        groupBox_Collect_Status_2->setTitle(QApplication::translate("Robot_App_Widget", "\351\207\207\351\233\206\347\212\266\346\200\201\357\274\210\345\206\231\357\274\211", nullptr));
        label_120_Gain_2->setText(QApplication::translate("Robot_App_Widget", "\347\233\270\346\234\272\345\242\236\347\233\212:", nullptr));
        set_Pre_Scan_120_Part1->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        set_Pre_Scan_120_Point->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        label_120_Part2_2->setText(QApplication::translate("Robot_App_Widget", "\344\272\214\347\272\247\351\203\250\344\273\266:", nullptr));
        label_120_Point_2->setText(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\347\202\271:", nullptr));
        set_Pre_Scan_120_Gain->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        label_120_Prog_2->setText(QApplication::translate("Robot_App_Widget", "\347\250\213\345\272\217\347\264\242\345\274\225:", nullptr));
        set_Pre_Scan_120_currentWheelset->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        set_Pre_Scan_120_Part2->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        label_120_Part1_2->setText(QApplication::translate("Robot_App_Widget", "\344\270\200\347\272\247\351\203\250\344\273\266:", nullptr));
        groupBox_MySql->setTitle(QApplication::translate("Robot_App_Widget", "\346\225\260\346\215\256\345\272\223\350\277\236\346\216\245", nullptr));
        label_120_MySql_Status->setText(QApplication::translate("Robot_App_Widget", "\347\212\266\346\200\201:", nullptr));
        label_167->setText(QApplication::translate("Robot_App_Widget", "\346\225\260\346\215\256\345\272\223\347\253\257\345\217\243\357\274\232", nullptr));
        label_156->setText(QApplication::translate("Robot_App_Widget", "\346\225\260\346\215\256\345\272\223\347\224\250\346\210\267\357\274\232", nullptr));
        MySql_User->setText(QString());
        label_149->setText(QApplication::translate("Robot_App_Widget", "\346\225\260\346\215\256\345\272\223\345\257\206\347\240\201\357\274\232", nullptr));
        label_148->setText(QApplication::translate("Robot_App_Widget", "\346\225\260\346\215\256\345\272\223\350\241\250\345\244\264\357\274\232", nullptr));
        Pre_Scan_120_MySql_Reconnect->setText(QApplication::translate("Robot_App_Widget", "\351\207\215\346\226\260\350\277\236\346\216\245", nullptr));
        groupBox_9->setTitle(QApplication::translate("Robot_App_Widget", "\345\267\246\347\262\276\346\211\253\346\266\210\346\201\257", nullptr));
        groupBox_Task_Info->setTitle(QApplication::translate("Robot_App_Widget", "WEB\344\273\273\345\212\241\344\277\241\346\201\257(\350\257\273)", nullptr));
        label_120_TaskID->setText(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241ID:", nullptr));
        label_120_Wheelset->setText(QApplication::translate("Robot_App_Widget", "\350\275\256\345\257\271\345\217\267:", nullptr));
        label_120_StartTime->setText(QApplication::translate("Robot_App_Widget", "\345\274\200\345\247\213\346\227\266\351\227\264:", nullptr));
        label_120_Axle->setText(QApplication::translate("Robot_App_Widget", "\350\275\246\350\275\264\345\217\267:", nullptr));
        label_120_Repair->setText(QApplication::translate("Robot_App_Widget", "\344\277\256\347\250\213:", nullptr));
        label_120_SendUnit->setText(QApplication::translate("Robot_App_Widget", "\351\200\201\350\275\256\345\215\225\344\275\215:", nullptr));
        groupBox_Collect_Status->setTitle(QApplication::translate("Robot_App_Widget", "\351\207\207\351\233\206\347\212\266\346\200\201\357\274\210\350\257\273\357\274\211", nullptr));
        label_120_LastUpdate->setText(QApplication::translate("Robot_App_Widget", "\346\234\200\345\220\216\346\233\264\346\226\260:", nullptr));
        label_120_Prog->setText(QApplication::translate("Robot_App_Widget", "\347\250\213\345\272\217\347\264\242\345\274\225:", nullptr));
        label_120_Part2->setText(QApplication::translate("Robot_App_Widget", "\344\272\214\347\272\247\351\203\250\344\273\266:", nullptr));
        label_120_Point->setText(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\347\202\271:", nullptr));
        label_120_Gain->setText(QApplication::translate("Robot_App_Widget", "\347\233\270\346\234\272\345\242\236\347\233\212:", nullptr));
        label_120_Part1->setText(QApplication::translate("Robot_App_Widget", "\344\270\200\347\272\247\351\203\250\344\273\266:", nullptr));
        groupBox_Control->setTitle(QApplication::translate("Robot_App_Widget", "\346\211\213\345\212\250\346\216\247\345\210\266", nullptr));
        Pre_Scan_120_Collector->setText(QApplication::translate("Robot_App_Widget", "\345\215\225\346\254\241\351\207\207\351\233\206", nullptr));
        Pre_Scan_120_Finish_Scan->setText(QApplication::translate("Robot_App_Widget", "\345\256\214\346\210\220\351\207\207\351\233\206", nullptr));
        Pre_Scan_120_Change_Gain->setText(QApplication::translate("Robot_App_Widget", "\350\256\276\347\275\256\345\242\236\347\233\212", nullptr));
        Pre_Scan_120_Start_Scan->setText(QApplication::translate("Robot_App_Widget", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        groupBox_2->setTitle(QApplication::translate("Robot_App_Widget", "IO\346\216\247\345\210\266", nullptr));
        groupBox_24->setTitle(QApplication::translate("Robot_App_Widget", "IO\346\250\241\345\235\227\351\200\232\350\256\257\345\217\202\346\225\260", nullptr));
        label_280->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\344\277\235\346\214\201\351\225\277\345\272\246:", nullptr));
        label_281->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\347\272\277\345\234\210\345\234\260\345\235\200:", nullptr));
        label_274->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\344\277\235\346\214\201\345\234\260\345\235\200:", nullptr));
        label_139->setText(QApplication::translate("Robot_App_Widget", "\346\250\241\345\235\227\345\234\260\345\235\200\357\274\232", nullptr));
        label_122->setText(QApplication::translate("Robot_App_Widget", "\346\250\241\345\235\227\347\253\257\345\217\243\357\274\232", nullptr));
        IO_Port->setText(QString());
        label_273->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\347\272\277\345\234\210\351\225\277\345\272\246:", nullptr));
        groupBox_IO_DO->setTitle(QApplication::translate("Robot_App_Widget", "\346\225\260\345\255\227\351\207\217\350\276\223\345\207\272\346\265\213\350\257\225  XB6S-3200B", nullptr));
        btn_IO_AlarmGreen_ON->setText(QApplication::translate("Robot_App_Widget", "\347\273\277\345\274\200", nullptr));
        btn_IO_Robot_OFF->setText(QApplication::translate("Robot_App_Widget", "\346\234\272\346\242\260\350\207\202\345\205\263", nullptr));
        btn_IO_AlarmGreen_OFF->setText(QApplication::translate("Robot_App_Widget", "\347\273\277\345\205\263", nullptr));
        btn_IO_Fan_OFF->setText(QApplication::translate("Robot_App_Widget", "\351\243\216\346\211\207\345\205\263", nullptr));
        btn_IO_AlarmYellow_OFF->setText(QApplication::translate("Robot_App_Widget", "\351\273\204\345\205\263", nullptr));
        btn_IO_Fan_ON->setText(QApplication::translate("Robot_App_Widget", "\351\243\216\346\211\207\345\274\200", nullptr));
        btn_IO_AlarmRed_OFF->setText(QApplication::translate("Robot_App_Widget", "\347\272\242\345\205\263", nullptr));
        btn_IO_Robot_ON->setText(QApplication::translate("Robot_App_Widget", "\346\234\272\346\242\260\350\207\202\345\274\200", nullptr));
        btn_IO_AlarmRed_ON->setText(QApplication::translate("Robot_App_Widget", "\347\272\242\345\274\200", nullptr));
        btn_IO_AlarmYellow_ON->setText(QApplication::translate("Robot_App_Widget", "\351\273\204\345\274\200", nullptr));
        groupBox_IO_Connect->setTitle(QApplication::translate("Robot_App_Widget", "\350\277\236\346\216\245\346\216\247\345\210\266", nullptr));
        label_25->setText(QApplication::translate("Robot_App_Widget", "\350\277\236\346\216\245:", nullptr));
        label_24->setText(QApplication::translate("Robot_App_Widget", "\345\260\261\347\273\252:", nullptr));
        IO_Connect->setText(QApplication::translate("Robot_App_Widget", "\350\277\236\346\216\245", nullptr));
        IO_Disconnect->setText(QApplication::translate("Robot_App_Widget", "\346\226\255\345\274\200", nullptr));
        groupBox_11->setTitle(QApplication::translate("Robot_App_Widget", "\350\257\255\351\237\263\346\212\245\350\255\246", nullptr));
        groupBox_Voice_Config->setTitle(QApplication::translate("Robot_App_Widget", "\351\200\232\344\277\241\351\205\215\347\275\256", nullptr));
        label_Voice_Com->setText(QApplication::translate("Robot_App_Widget", "COM\345\217\243:", nullptr));
        Voice_Com->setCurrentText(QApplication::translate("Robot_App_Widget", "COM1", nullptr));
        label_Voice_Baud->setText(QApplication::translate("Robot_App_Widget", "\346\263\242\347\211\271\347\216\207:", nullptr));
        Voice_Baud->setItemText(0, QApplication::translate("Robot_App_Widget", "9600", nullptr));
        Voice_Baud->setItemText(1, QApplication::translate("Robot_App_Widget", "19200", nullptr));
        Voice_Baud->setItemText(2, QApplication::translate("Robot_App_Widget", "38400", nullptr));
        Voice_Baud->setItemText(3, QApplication::translate("Robot_App_Widget", "115200", nullptr));

        label_Voice_Addr->setText(QApplication::translate("Robot_App_Widget", "\344\273\216\347\253\231:", nullptr));
        label_Voice_Connected->setText(QApplication::translate("Robot_App_Widget", "\350\277\236\346\216\245:", nullptr));
        label_Voice_Volume->setText(QApplication::translate("Robot_App_Widget", "\351\237\263\351\207\217:", nullptr));
        Voice_Connect->setText(QApplication::translate("Robot_App_Widget", "\350\277\236\346\216\245", nullptr));
        Voice_Disconnect->setText(QApplication::translate("Robot_App_Widget", "\346\226\255\345\274\200", nullptr));
        Voice_Volume_Display->setText(QApplication::translate("Robot_App_Widget", "\344\270\255(2)", nullptr));
        groupBox_Voice_Info->setTitle(QApplication::translate("Robot_App_Widget", "\346\222\255\346\212\245\344\277\241\346\201\257", nullptr));
        label_Voice_Device_Status->setText(QApplication::translate("Robot_App_Widget", "\350\256\276\345\244\207\347\212\266\346\200\201:", nullptr));
        Voice_Device_Status->setText(QApplication::translate("Robot_App_Widget", "\347\251\272\351\227\262", nullptr));
        label_Voice_Current_Audio->setText(QApplication::translate("Robot_App_Widget", "\345\275\223\345\211\215\351\237\263\351\242\221:", nullptr));
        label_Voice_Count->setText(QApplication::translate("Robot_App_Widget", "\346\222\255\346\212\245\346\254\241\346\225\260:", nullptr));
        Voice_Count->setText(QApplication::translate("Robot_App_Widget", "0", nullptr));
        groupBox_Voice_Play->setTitle(QApplication::translate("Robot_App_Widget", "\351\237\263\351\242\221\346\222\255\346\212\245", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA001->setToolTip(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\346\234\272\345\231\250\344\272\272\346\255\243\345\234\250\345\267\241\346\243\200\344\270\255\357\274\214\350\257\267\346\263\250\346\204\217\345\256\211\345\205\250", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA001->setText(QApplication::translate("Robot_App_Widget", "PA001", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA002->setToolTip(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\346\234\272\345\231\250\344\272\272\346\243\200\346\265\213\345\210\260\351\232\234\347\242\215\347\211\251", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA002->setText(QApplication::translate("Robot_App_Widget", "PA002", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA003->setToolTip(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\346\234\272\345\231\250\344\272\272\350\256\276\345\244\207\346\225\205\351\232\234\357\274\214\345\267\262\345\201\234\346\255\242\350\277\220\350\241\214", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA003->setText(QApplication::translate("Robot_App_Widget", "PA003", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA004->setToolTip(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\346\234\272\345\231\250\344\272\272\347\224\265\351\207\217\350\277\207\344\275\216\357\274\214\350\257\267\345\260\275\345\277\253\345\205\205\347\224\265", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA004->setText(QApplication::translate("Robot_App_Widget", "PA004", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA005->setToolTip(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\346\234\272\345\231\250\344\272\272\345\267\262\346\232\202\345\201\234\350\277\220\350\241\214\357\274\214\350\257\267\345\213\277\351\235\240\350\277\221", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA005->setText(QApplication::translate("Robot_App_Widget", "PA005", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA006->setToolTip(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\346\234\272\345\231\250\344\272\272\346\234\272\346\242\260\350\207\202\346\255\243\345\234\250\350\277\220\350\241\214\344\270\255\357\274\214\350\257\267\346\263\250\346\204\217", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA006->setText(QApplication::translate("Robot_App_Widget", "PA006", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA007->setToolTip(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\346\234\272\345\231\250\344\272\272\351\200\232\344\277\241\346\225\205\351\232\234\357\274\214\350\257\267\346\243\200\346\237\245\347\275\221\347\273\234", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA007->setText(QApplication::translate("Robot_App_Widget", "PA007", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA008->setToolTip(QApplication::translate("Robot_App_Widget", "\347\233\270\346\234\272\346\225\205\351\232\234\357\274\214\350\257\267\346\243\200\346\237\245\347\233\270\346\234\272\346\230\257\345\220\246\346\255\243\345\270\270", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA008->setText(QApplication::translate("Robot_App_Widget", "PA008", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA009->setToolTip(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\346\234\272\345\231\250\344\272\272\345\272\225\347\233\230\346\225\205\351\232\234\357\274\214\350\257\267\346\243\200\346\237\245", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA009->setText(QApplication::translate("Robot_App_Widget", "PA009", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA010->setToolTip(QApplication::translate("Robot_App_Widget", "\346\234\272\346\242\260\350\207\202\346\243\200\346\265\213\345\210\260\347\242\260\346\222\236\357\274\214\350\257\267\344\272\272\345\267\245\345\244\204\347\220\206", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA010->setText(QApplication::translate("Robot_App_Widget", "PA010", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA011->setToolTip(QApplication::translate("Robot_App_Widget", "\346\234\272\346\242\260\350\207\202\346\234\252\345\210\260\350\276\276\347\233\256\346\240\207\357\274\214\350\257\267\344\272\272\345\267\245\345\210\207\346\215\242", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA011->setText(QApplication::translate("Robot_App_Widget", "PA011", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA012->setToolTip(QApplication::translate("Robot_App_Widget", "\345\267\262\345\210\207\346\215\242\346\211\213\345\212\250\345\211\215\350\277\233\357\274\214\347\233\256\350\247\206\346\223\215\344\275\234", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA012->setText(QApplication::translate("Robot_App_Widget", "PA012", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA013->setToolTip(QApplication::translate("Robot_App_Widget", "\345\267\262\345\210\207\346\215\242\346\211\213\345\212\250\345\220\216\351\200\200\357\274\214\347\233\256\350\247\206\346\223\215\344\275\234", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA013->setText(QApplication::translate("Robot_App_Widget", "PA013", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA014->setToolTip(QApplication::translate("Robot_App_Widget", "\345\210\235\345\247\213\345\256\232\344\275\215\345\256\214\346\210\220", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA014->setText(QApplication::translate("Robot_App_Widget", "PA014", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA015->setToolTip(QApplication::translate("Robot_App_Widget", "\345\256\232\344\275\215\345\256\214\346\210\220", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA015->setText(QApplication::translate("Robot_App_Widget", "PA015", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA016->setToolTip(QApplication::translate("Robot_App_Widget", "\345\233\236\345\216\237\347\202\271\350\277\220\350\241\214\344\270\255\357\274\214\350\257\267\346\263\250\346\204\217\345\256\211\345\205\250", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA016->setText(QApplication::translate("Robot_App_Widget", "PA016", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA017->setToolTip(QApplication::translate("Robot_App_Widget", "\345\205\205\347\224\265\347\224\265\345\216\213\346\234\252\350\276\276\345\210\260\357\274\214\350\257\267\344\272\272\345\267\245\346\243\200\346\237\245", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA017->setText(QApplication::translate("Robot_App_Widget", "PA017", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA018->setToolTip(QApplication::translate("Robot_App_Widget", "\345\233\236\345\216\237\347\202\271\347\273\223\346\235\237\345\220\216\346\234\252\350\276\276\345\210\260\357\274\214\350\257\267\344\272\272\345\267\245\346\243\200\346\237\245", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA018->setText(QApplication::translate("Robot_App_Widget", "PA018", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA019->setToolTip(QApplication::translate("Robot_App_Widget", "\346\234\272\346\242\260\350\207\202\344\270\215\345\234\250\345\216\237\347\202\271\357\274\214\350\257\267\344\272\272\345\267\245\345\244\204\347\220\206", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA019->setText(QApplication::translate("Robot_App_Widget", "PA019", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA020->setToolTip(QApplication::translate("Robot_App_Widget", "\346\200\245\345\201\234\346\214\211\351\222\256\346\214\211\344\270\213\357\274\214\350\257\267\344\272\272\345\267\245\345\244\204\347\220\206", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA020->setText(QApplication::translate("Robot_App_Widget", "PA020", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA021->setToolTip(QApplication::translate("Robot_App_Widget", "\347\262\276\346\211\253\347\233\270\346\234\272\346\225\205\351\232\234\357\274\214\350\257\267\344\272\272\345\267\245\346\243\200\346\237\245", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA021->setText(QApplication::translate("Robot_App_Widget", "PA021", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA022->setToolTip(QApplication::translate("Robot_App_Widget", "\345\256\232\344\275\215\345\244\261\350\264\245\346\210\226\344\270\242\345\244\261\357\274\214\350\257\267\344\272\272\345\267\245\346\243\200\346\237\245", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA022->setText(QApplication::translate("Robot_App_Widget", "PA022", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA023->setToolTip(QApplication::translate("Robot_App_Widget", "\345\205\205\347\224\265\347\224\265\345\216\213\346\234\252\350\276\276\345\210\260\345\201\234\346\255\242\346\235\241\344\273\266", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA023->setText(QApplication::translate("Robot_App_Widget", "PA023", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA024->setToolTip(QApplication::translate("Robot_App_Widget", "\346\234\272\346\242\260\350\207\202\345\205\205\347\224\265\346\234\252\350\276\276\345\210\260\345\201\234\346\255\242\346\235\241\344\273\266", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA024->setText(QApplication::translate("Robot_App_Widget", "PA024", nullptr));
#ifndef QT_NO_TOOLTIP
        btn_Voice_PA025->setToolTip(QApplication::translate("Robot_App_Widget", "\347\246\201\346\255\242\351\200\232\350\241\214", nullptr));
#endif // QT_NO_TOOLTIP
        btn_Voice_PA025->setText(QApplication::translate("Robot_App_Widget", "PA025", nullptr));
        btn_Voice_Stop->setText(QApplication::translate("Robot_App_Widget", "\345\201\234\346\255\242\346\222\255\346\224\276", nullptr));
        btn_Voice_Vol_Low->setText(QApplication::translate("Robot_App_Widget", "\351\237\263\351\207\217:\344\275\216(1)", nullptr));
        btn_Voice_Vol_Med->setText(QApplication::translate("Robot_App_Widget", "\351\237\263\351\207\217:\344\270\255(2)", nullptr));
        btn_Voice_Vol_High->setText(QApplication::translate("Robot_App_Widget", "\351\237\263\351\207\217:\351\253\230(3)", nullptr));
        btn_Voice_Test->setText(QApplication::translate("Robot_App_Widget", "\346\265\213\350\257\225\346\222\255\346\212\245", nullptr));
        groupBox_Voice_Log->setTitle(QApplication::translate("Robot_App_Widget", "\346\222\255\346\212\245\350\256\260\345\275\225", nullptr));
        groupBox_10->setTitle(QApplication::translate("Robot_App_Widget", "IO\346\227\245\345\277\227", nullptr));
        Work_TaskGroup->setTitle(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241\347\212\266\346\200\201", nullptr));
        label_Work_TaskID->setText(QApplication::translate("Robot_App_Widget", "\344\273\273 \345\212\241 ID:", nullptr));
        label_Work_State->setText(QApplication::translate("Robot_App_Widget", "\347\212\266\346\200\201 :", nullptr));
        label_Work_Wheel->setText(QApplication::translate("Robot_App_Widget", "\350\275\256  \345\257\271:", nullptr));
        label_Work_Pos->setText(QApplication::translate("Robot_App_Widget", "\345\267\245\344\275\215:", nullptr));
        label_Work_Images->setText(QApplication::translate("Robot_App_Widget", "\345\233\276\345\203\217\346\225\260:", nullptr));
        label_Work_SendUnit->setText(QApplication::translate("Robot_App_Widget", "\351\200\201\346\243\200\345\215\225\344\275\215:", nullptr));
        label_Work_Repair->setText(QApplication::translate("Robot_App_Widget", "\344\277\256\347\250\213 :", nullptr));
        label_Work_WheelsetNo->setText(QApplication::translate("Robot_App_Widget", "\350\275\256\345\257\271\345\217\267:", nullptr));
        label_Work_AxleNo->setText(QApplication::translate("Robot_App_Widget", "\350\275\246\350\275\264\345\217\267:", nullptr));
        label_Work_Gain->setText(QApplication::translate("Robot_App_Widget", "\345\242\236  \347\233\212  :", nullptr));
        label_Work_Part1->setText(QApplication::translate("Robot_App_Widget", "\351\203\250\344\273\2661:", nullptr));
        label_Work_Part2->setText(QApplication::translate("Robot_App_Widget", "\351\203\250\344\273\266 2:", nullptr));
        label_Work_Point->setText(QApplication::translate("Robot_App_Widget", "\347\202\271\344\275\215:", nullptr));
        label_Work_StartTime->setText(QApplication::translate("Robot_App_Widget", "\345\274\200\345\247\213:", nullptr));
        label_Work_CarType->setText(QApplication::translate("Robot_App_Widget", "\350\275\246\345\236\213/\347\261\273\345\236\213:", nullptr));
        groupBox_FrontCamView->setTitle(QApplication::translate("Robot_App_Widget", "\345\211\215\347\233\270\346\234\272\347\224\273\351\235\242", nullptr));
        label_FrontCamera->setText(QApplication::translate("Robot_App_Widget", "\347\255\211\345\276\205\345\211\215\347\233\270\346\234\272\345\233\276\345\203\217...", nullptr));
        groupBox_4->setTitle(QApplication::translate("Robot_App_Widget", "\351\233\267\350\276\276", nullptr));
        groupBox_RearCamView->setTitle(QApplication::translate("Robot_App_Widget", "\345\220\216\347\233\270\346\234\272\347\224\273\351\235\242", nullptr));
        label_RearCamera->setText(QApplication::translate("Robot_App_Widget", "\347\255\211\345\276\205\345\220\216\347\233\270\346\234\272\345\233\276\345\203\217...", nullptr));
        Work_ServerGroup->setTitle(QApplication::translate("Robot_App_Widget", "WEB \346\234\215\345\212\241\345\231\250", nullptr));
        label_Work_Client->setText(QApplication::translate("Robot_App_Widget", "\345\256\242\346\210\267\347\253\257:", nullptr));
        label_Work_Listen->setText(QApplication::translate("Robot_App_Widget", "\347\233\221\345\220\254:", nullptr));
        label_Work_ConnNum->setText(QApplication::translate("Robot_App_Widget", "\350\277\236\346\216\245\346\225\260:", nullptr));
        label_Work_Port->setText(QApplication::translate("Robot_App_Widget", "\347\253\257\345\217\243:", nullptr));
        label_Work_Checksum->setText(QApplication::translate("Robot_App_Widget", "\346\240\241\351\252\214\347\240\201:", nullptr));
        Work_FlowGroup->setTitle(QApplication::translate("Robot_App_Widget", "\345\267\245\344\275\234\346\265\201\347\212\266\346\200\201", nullptr));
        label_Work_FlowState->setText(QApplication::translate("Robot_App_Widget", "\347\212\266\346\200\201:", nullptr));
        Work_Flow_State->setText(QApplication::translate("Robot_App_Widget", "\347\251\272\351\227\262", nullptr));
        Work_Btn_Start->setText(QApplication::translate("Robot_App_Widget", "\345\274\200\345\247\213\345\267\241\346\243\200", nullptr));
        Work_Btn_Pause->setText(QApplication::translate("Robot_App_Widget", "\346\232\202\345\201\234", nullptr));
        Work_Btn_Resume->setText(QApplication::translate("Robot_App_Widget", "\347\273\247\347\273\255", nullptr));
        Work_Btn_Cancel->setText(QApplication::translate("Robot_App_Widget", "\345\217\226\346\266\210", nullptr));
        Work_Btn_Stop->setText(QApplication::translate("Robot_App_Widget", "\346\200\245\345\201\234", nullptr));
        Work_Btn_Home->setText(QApplication::translate("Robot_App_Widget", "\345\233\236\345\216\237\347\202\271", nullptr));
        Work_LogGroup->setTitle(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\350\277\207\347\250\213", nullptr));
        Work_AlarmGroup->setTitle(QApplication::translate("Robot_App_Widget", "\347\263\273\347\273\237\346\212\245\350\255\246", nullptr));
        Work_SubsysGroup->setTitle(QApplication::translate("Robot_App_Widget", "\345\255\220\347\263\273\347\273\237\347\212\266\346\200\201", nullptr));
        label_Work_Arm->setText(QApplication::translate("Robot_App_Widget", "\346\234\272\346\242\260\350\207\202:", nullptr));
        label_Work_Chassis->setText(QApplication::translate("Robot_App_Widget", "\345\272\225\347\233\230:", nullptr));
        label_Work_Camera->setText(QApplication::translate("Robot_App_Widget", "\347\233\270\346\234\272:", nullptr));
        label_Work_Server->setText(QApplication::translate("Robot_App_Widget", "WEB:", nullptr));
        label_Work_Checksum_2->setText(QApplication::translate("Robot_App_Widget", "URL:", nullptr));
        EMIS_Url->setText(QApplication::translate("Robot_App_Widget", " http://192.168.0.107:80/robot/robot-service/emis/task/reportTime", nullptr));
        actualStartTime->setText(QApplication::translate("Robot_App_Widget", "\346\233\264\346\226\260\345\274\200\345\247\213\345\267\241\346\243\200\346\227\266\351\227\264", nullptr));
        precisScanStartTime->setText(QApplication::translate("Robot_App_Widget", "\346\233\264\346\226\260\347\262\276\346\211\253\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        precisScanEndTime->setText(QApplication::translate("Robot_App_Widget", "\346\233\264\346\226\260\347\262\276\346\211\253\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        groupBox_7->setTitle(QApplication::translate("Robot_App_Widget", "\345\272\225\347\233\230\346\216\247\345\210\266", nullptr));
        groupBox_Connect->setTitle(QApplication::translate("Robot_App_Widget", "\350\277\236\346\216\245\344\270\216\350\256\244\350\257\201", nullptr));
        label_IP->setText(QApplication::translate("Robot_App_Widget", "IP:", nullptr));
        Magic_IP->setText(QApplication::translate("Robot_App_Widget", "192.168.1.102", nullptr));
        label_Port->setText(QApplication::translate("Robot_App_Widget", "Port:", nullptr));
        Magic_Port->setText(QApplication::translate("Robot_App_Widget", "8888", nullptr));
        label_User->setText(QApplication::translate("Robot_App_Widget", "User:", nullptr));
        Magic_User->setText(QApplication::translate("Robot_App_Widget", "admin", nullptr));
        label_Pass->setText(QApplication::translate("Robot_App_Widget", "Pass:", nullptr));
        Magic_Pass->setText(QApplication::translate("Robot_App_Widget", "admin123", nullptr));
        pushButton_Connect->setText(QApplication::translate("Robot_App_Widget", "\350\277\236\346\216\245", nullptr));
        pushButton_Login->setText(QApplication::translate("Robot_App_Widget", "\347\231\273\345\275\225", nullptr));
        pushButton_Disconnect->setText(QApplication::translate("Robot_App_Widget", "\346\226\255\345\274\200", nullptr));
        label_MAC->setText(QApplication::translate("Robot_App_Widget", "MAC:", nullptr));
        groupBox_Pose->setTitle(QApplication::translate("Robot_App_Widget", "\347\263\273\347\273\237\347\212\266\346\200\201", nullptr));
        label_WX->setText(QApplication::translate("Robot_App_Widget", "World X:", nullptr));
        label_WY->setText(QApplication::translate("Robot_App_Widget", "World Y:", nullptr));
        label_Angle->setText(QApplication::translate("Robot_App_Widget", "Angle:", nullptr));
        label_NavVer->setText(QApplication::translate("Robot_App_Widget", "\345\257\274\350\210\252Ver:", nullptr));
        label_GridX->setText(QApplication::translate("Robot_App_Widget", "GridX:", nullptr));
        label_ErrorCode->setText(QApplication::translate("Robot_App_Widget", "\351\224\231\350\257\257:", nullptr));
        label_AntiCollision->setText(QApplication::translate("Robot_App_Widget", "\351\230\262\346\222\236:", nullptr));
        label_Battery->setText(QApplication::translate("Robot_App_Widget", "\347\224\265\351\207\217:", nullptr));
        label_WorkMode->setText(QApplication::translate("Robot_App_Widget", "\346\250\241\345\274\217:", nullptr));
        label_ChassisVer->setText(QApplication::translate("Robot_App_Widget", "\345\272\225\347\233\230Ver:", nullptr));
        label_GridY->setText(QApplication::translate("Robot_App_Widget", "GridY:", nullptr));
        label_CurrentMap->setText(QApplication::translate("Robot_App_Widget", "\345\275\223\345\211\215\345\234\260\345\233\276:", nullptr));
        label_ConnStatus->setText(QApplication::translate("Robot_App_Widget", "\350\277\236\346\216\245:", nullptr));
        label_Ready->setText(QApplication::translate("Robot_App_Widget", "\345\277\203\350\267\263:", nullptr));
        label_Localized->setText(QApplication::translate("Robot_App_Widget", "\345\256\232\344\275\215:", nullptr));
        label_Charging->setText(QApplication::translate("Robot_App_Widget", "\345\205\205\347\224\265:", nullptr));
        label_Task->setText(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241:", nullptr));
        label_Lidar->setText(QApplication::translate("Robot_App_Widget", "\346\277\200\345\205\211:", nullptr));
        label_I->setText(QApplication::translate("Robot_App_Widget", "IMU:", nullptr));
        label_O->setText(QApplication::translate("Robot_App_Widget", "\351\207\214\347\250\213:", nullptr));
        label_Cam->setText(QApplication::translate("Robot_App_Widget", "\347\233\270\346\234\272:", nullptr));
        label_Estop->setText(QApplication::translate("Robot_App_Widget", "\346\200\245\345\201\234:", nullptr));
        groupBox_FixedNav->setTitle(QApplication::translate("Robot_App_Widget", "\345\256\232\347\202\271\345\257\274\350\210\252\357\274\210\345\235\220\346\240\207\350\276\223\345\205\245\357\274\211", nullptr));
        label_FixedX->setText(QApplication::translate("Robot_App_Widget", "\346\240\205\346\240\274 X:", nullptr));
        label_FixedY->setText(QApplication::translate("Robot_App_Widget", "\346\240\205\346\240\274 Y:", nullptr));
        label_FixedAngle->setText(QApplication::translate("Robot_App_Widget", "\350\247\222\345\272\246(\302\260):", nullptr));
        btn_FixedNavStart->setText(QApplication::translate("Robot_App_Widget", "\345\256\232\347\202\271\345\257\274\350\210\252\357\274\210\345\215\225\346\254\241\357\274\211", nullptr));
        btn_FixedNavLoop->setText(QApplication::translate("Robot_App_Widget", "\345\256\232\347\202\271\345\257\274\350\210\252\357\274\210\345\276\252\347\216\257\357\274\211", nullptr));
        groupBox_InitPose->setTitle(QApplication::translate("Robot_App_Widget", "\344\275\215\345\247\277\345\210\235\345\247\213\345\214\226", nullptr));
        btn_DynamicInit->setText(QApplication::translate("Robot_App_Widget", "\345\212\250\346\200\201\345\210\235\345\247\213\345\214\226", nullptr));
        btn_StaticInit->setText(QApplication::translate("Robot_App_Widget", "\351\235\231\346\200\201\345\210\235\345\247\213\345\214\226", nullptr));
        btn_GridInit->setText(QApplication::translate("Robot_App_Widget", "\346\240\205\346\240\274\345\210\235\345\247\213\345\214\226", nullptr));
        btn_InitResult->setText(QApplication::translate("Robot_App_Widget", "\345\210\235\345\247\213\345\214\226\347\273\223\346\236\234", nullptr));
        groupBox_TaskControl->setTitle(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241\346\216\247\345\210\266", nullptr));
        btn_StartTask->setText(QApplication::translate("Robot_App_Widget", "\345\274\200\345\247\213", nullptr));
        btn_LoopStart->setText(QApplication::translate("Robot_App_Widget", "\345\276\252\347\216\257\345\274\200\345\247\213", nullptr));
        btn_PauseTask->setText(QApplication::translate("Robot_App_Widget", "\346\232\202\345\201\234", nullptr));
        btn_ResumeTask->setText(QApplication::translate("Robot_App_Widget", "\346\201\242\345\244\215", nullptr));
        btn_StopTask->setText(QApplication::translate("Robot_App_Widget", "\345\201\234\346\255\242", nullptr));
        btn_GetTaskLog->setText(QApplication::translate("Robot_App_Widget", "\350\216\267\345\217\226\346\227\245\345\277\227", nullptr));
        lineEdit_TaskID->setPlaceholderText(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241ID", nullptr));
        groupBox_TaskSelect->setTitle(QApplication::translate("Robot_App_Widget", "\351\200\211\346\213\251\344\273\273\345\212\241", nullptr));
        label_TaskType->setText(QApplication::translate("Robot_App_Widget", "\347\261\273\345\236\213:", nullptr));
        combo_TaskType->setItemText(0, QApplication::translate("Robot_App_Widget", "\345\257\274\350\210\252\347\202\271", nullptr));
        combo_TaskType->setItemText(1, QApplication::translate("Robot_App_Widget", "\346\211\213\347\273\230\350\267\257\345\276\204", nullptr));
        combo_TaskType->setItemText(2, QApplication::translate("Robot_App_Widget", "\345\275\225\345\210\266\350\267\257\345\276\204", nullptr));
        combo_TaskType->setItemText(3, QApplication::translate("Robot_App_Widget", "\350\267\257\345\276\204\347\273\204\345\220\210", nullptr));

        label_TaskName->setText(QApplication::translate("Robot_App_Widget", "\345\220\215\347\247\260:", nullptr));
        btn_RefreshNavPoints->setText(QApplication::translate("Robot_App_Widget", "\345\210\267\346\226\260\345\257\274\350\210\252\347\202\271", nullptr));
        label_LoopCount->setText(QApplication::translate("Robot_App_Widget", "\345\276\252\347\216\257\346\254\241\346\225\260:", nullptr));
        btn_RefreshToken->setText(QApplication::translate("Robot_App_Widget", "\345\210\267\346\226\260Token", nullptr));
        btn_RefreshMapList->setText(QApplication::translate("Robot_App_Widget", "\345\210\267\346\226\260\345\210\227\350\241\250", nullptr));
        btn_SwitchMap->setText(QApplication::translate("Robot_App_Widget", "\345\210\207\346\215\242", nullptr));
        groupBox_TaskStatus->setTitle(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241\347\212\266\346\200\201", nullptr));
        label_TaskStatusText->setText(QApplication::translate("Robot_App_Widget", "\347\251\272\351\227\262", nullptr));
        label_RemainTime->setText(QApplication::translate("Robot_App_Widget", "\345\211\251\344\275\231:", nullptr));
        label_RemainTimeValue->setText(QApplication::translate("Robot_App_Widget", "--", nullptr));
        label_LoopInfo->setText(QApplication::translate("Robot_App_Widget", "\345\276\252\347\216\257: 0/0", nullptr));
        tabWidget_Magic->setTabText(tabWidget_Magic->indexOf(tab_Map), QApplication::translate("Robot_App_Widget", "\345\234\260\345\233\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = table_NavPoints->horizontalHeaderItem(0);
        ___qtablewidgetitem21->setText(QApplication::translate("Robot_App_Widget", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = table_NavPoints->horizontalHeaderItem(1);
        ___qtablewidgetitem22->setText(QApplication::translate("Robot_App_Widget", "\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = table_NavPoints->horizontalHeaderItem(2);
        ___qtablewidgetitem23->setText(QApplication::translate("Robot_App_Widget", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = table_NavPoints->horizontalHeaderItem(3);
        ___qtablewidgetitem24->setText(QApplication::translate("Robot_App_Widget", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = table_NavPoints->horizontalHeaderItem(4);
        ___qtablewidgetitem25->setText(QApplication::translate("Robot_App_Widget", "\350\247\222\345\272\246", nullptr));
        tabWidget_Magic->setTabText(tabWidget_Magic->indexOf(tab_PathPoint), QApplication::translate("Robot_App_Widget", "\350\267\257\345\276\204\344\270\216\347\202\271", nullptr));
        groupBox_Speed->setTitle(QApplication::translate("Robot_App_Widget", "\346\234\200\345\244\247\351\200\237\345\272\246\350\256\276\347\275\256 (\347\253\213\345\215\263\347\224\237\346\225\210)", nullptr));
        label_GoalSpeed->setText(QApplication::translate("Robot_App_Widget", "\350\207\252\347\224\261\345\257\274\350\210\252 (m/s):", nullptr));
        label_GraphSpeed->setText(QApplication::translate("Robot_App_Widget", "\346\211\213\347\273\230\350\267\257\345\276\204 (m/s):", nullptr));
        label_RecordSpeed->setText(QApplication::translate("Robot_App_Widget", "\345\275\225\345\210\266\350\267\257\345\276\204 (m/s):", nullptr));
        btn_UpdateSpeed->setText(QApplication::translate("Robot_App_Widget", "\344\277\235\345\255\230\351\200\237\345\272\246\351\205\215\347\275\256", nullptr));
        groupBox_Charge->setTitle(QApplication::translate("Robot_App_Widget", "\350\207\252\344\270\273\345\205\205\347\224\265", nullptr));
        label_ChargePoint->setText(QApplication::translate("Robot_App_Widget", "\345\205\205\347\224\265\347\202\271\345\220\215\347\247\260:", nullptr));
        lineEdit_ChargePoint->setText(QApplication::translate("Robot_App_Widget", "P0", nullptr));
        btn_StartRecharge->setText(QApplication::translate("Robot_App_Widget", "\345\233\236\345\205\205", nullptr));
        btn_DisRecharge->setText(QApplication::translate("Robot_App_Widget", "\350\204\261\347\246\273", nullptr));
        btn_PauseRecharge->setText(QApplication::translate("Robot_App_Widget", "\346\232\202\345\201\234", nullptr));
        btn_ResumeRecharge->setText(QApplication::translate("Robot_App_Widget", "\346\201\242\345\244\215", nullptr));
        btn_CancelRecharge->setText(QApplication::translate("Robot_App_Widget", "\345\217\226\346\266\210", nullptr));
        label_ChargeStatus->setText(QApplication::translate("Robot_App_Widget", "\347\212\266\346\200\201:", nullptr));
        lbl_ChargeStatus->setText(QApplication::translate("Robot_App_Widget", "\345\276\205\345\221\275", nullptr));
        groupBox_Move->setTitle(QApplication::translate("Robot_App_Widget", "\347\247\273\345\212\250\346\216\247\345\210\266", nullptr));
        groupBox_SpeedControl->setTitle(QApplication::translate("Robot_App_Widget", "\351\200\237\345\272\246\346\216\247\345\210\266", nullptr));
        label_LinearSpeed->setText(QApplication::translate("Robot_App_Widget", "\347\272\277\351\200\237\345\272\246 (m/s):", nullptr));
        label_AngularSpeed->setText(QApplication::translate("Robot_App_Widget", "\350\247\222\351\200\237\345\272\246 (rad/s):", nullptr));
        groupBox_MoveButtons->setTitle(QApplication::translate("Robot_App_Widget", "\346\216\247\345\210\266\346\214\211\351\222\256", nullptr));
        btn_MoveForward->setText(QApplication::translate("Robot_App_Widget", "\345\211\215\350\277\233", nullptr));
        btn_MoveBackward->setText(QApplication::translate("Robot_App_Widget", "\345\220\216\351\200\200", nullptr));
        btn_TurnLeft->setText(QApplication::translate("Robot_App_Widget", "\345\267\246\346\227\213", nullptr));
        btn_TurnRight->setText(QApplication::translate("Robot_App_Widget", "\345\217\263\346\227\213", nullptr));
        btn_StopMove->setText(QApplication::translate("Robot_App_Widget", "\345\201\234\346\255\242", nullptr));
        groupBox_MoveParams->setTitle(QApplication::translate("Robot_App_Widget", "\345\256\232\350\267\235\347\246\273/\345\256\232\350\247\222\345\272\246\347\247\273\345\212\250", nullptr));
        label_MoveMode->setText(QApplication::translate("Robot_App_Widget", "\346\250\241\345\274\217:", nullptr));
        combo_MoveMode->setItemText(0, QApplication::translate("Robot_App_Widget", "\345\256\232\350\267\235\347\246\273", nullptr));
        combo_MoveMode->setItemText(1, QApplication::translate("Robot_App_Widget", "\345\256\232\350\247\222\345\272\246", nullptr));

        label_MoveTarget->setText(QApplication::translate("Robot_App_Widget", "\347\233\256\346\240\207\345\200\274:", nullptr));
        btn_ExecuteMoveParams->setText(QApplication::translate("Robot_App_Widget", "\346\211\247\350\241\214", nullptr));
        btn_CancelMoveParams->setText(QApplication::translate("Robot_App_Widget", "\345\217\226\346\266\210", nullptr));
        tabWidget_Magic->setTabText(tabWidget_Magic->indexOf(tab_System), QApplication::translate("Robot_App_Widget", "\347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        groupBox_IMU->setTitle(QApplication::translate("Robot_App_Widget", "IMU\346\225\260\346\215\256", nullptr));
        label_IMU_AVX->setText(QApplication::translate("Robot_App_Widget", "AVX:", nullptr));
        label_IMU_AVY->setText(QApplication::translate("Robot_App_Widget", "AVY:", nullptr));
        label_IMU_AVZ->setText(QApplication::translate("Robot_App_Widget", "AVZ:", nullptr));
        label_IMU_LAX->setText(QApplication::translate("Robot_App_Widget", "LAX:", nullptr));
        label_IMU_LAY->setText(QApplication::translate("Robot_App_Widget", "LAY:", nullptr));
        label_IMU_LAZ->setText(QApplication::translate("Robot_App_Widget", "LAZ:", nullptr));
        groupBox_Odom->setTitle(QApplication::translate("Robot_App_Widget", "\351\207\214\347\250\213\350\256\241\346\225\260\346\215\256", nullptr));
        label_Odom_LX->setText(QApplication::translate("Robot_App_Widget", "LX:", nullptr));
        label_Odom_LY->setText(QApplication::translate("Robot_App_Widget", "LY:", nullptr));
        label_Odom_LZ->setText(QApplication::translate("Robot_App_Widget", "LZ:", nullptr));
        label_Odom_AX->setText(QApplication::translate("Robot_App_Widget", "AX:", nullptr));
        label_Odom_AY->setText(QApplication::translate("Robot_App_Widget", "AY:", nullptr));
        label_Odom_AZ->setText(QApplication::translate("Robot_App_Widget", "AZ:", nullptr));
        groupBox_GPS->setTitle(QApplication::translate("Robot_App_Widget", "GPS\346\225\260\346\215\256", nullptr));
        label_GPS_Lat->setText(QApplication::translate("Robot_App_Widget", "\347\272\254\345\272\246:", nullptr));
        label_GPS_Lon->setText(QApplication::translate("Robot_App_Widget", "\347\273\217\345\272\246:", nullptr));
        label_GPS_Alt->setText(QApplication::translate("Robot_App_Widget", "\346\265\267\346\213\224:", nullptr));
        groupBox_Ultrasonic->setTitle(QApplication::translate("Robot_App_Widget", "\350\266\205\345\243\260\346\263\242\346\225\260\346\215\256", nullptr));
        lbl_US_FL->setText(QApplication::translate("Robot_App_Widget", "\345\211\215\345\267\246:", nullptr));
        lbl_US_FR->setText(QApplication::translate("Robot_App_Widget", "\345\211\215\345\217\263:", nullptr));
        lbl_US_RL->setText(QApplication::translate("Robot_App_Widget", "\345\220\216\345\267\246:", nullptr));
        lbl_US_RR->setText(QApplication::translate("Robot_App_Widget", "\345\220\216\345\217\263:", nullptr));
        lbl_US_LF->setText(QApplication::translate("Robot_App_Widget", "\345\267\246\344\276\247\345\211\215:", nullptr));
        lbl_US_LR->setText(QApplication::translate("Robot_App_Widget", "\345\267\246\344\276\247\345\220\216:", nullptr));
        lbl_US_RF->setText(QApplication::translate("Robot_App_Widget", "\345\217\263\344\276\247\345\211\215:", nullptr));
        lbl_US_RR2->setText(QApplication::translate("Robot_App_Widget", "\345\217\263\344\276\247\345\220\216:", nullptr));
        groupBox_CameraControl->setTitle(QApplication::translate("Robot_App_Widget", "\347\233\270\346\234\272\346\216\247\345\210\266", nullptr));
        label_FrontCamCtrl->setText(QApplication::translate("Robot_App_Widget", "\345\211\215\347\233\270\346\234\272:", nullptr));
        btn_GetFrontRGB->setText(QApplication::translate("Robot_App_Widget", "\345\275\251\350\211\262", nullptr));
        btn_GetFrontDepth->setText(QApplication::translate("Robot_App_Widget", "\346\267\261\345\272\246", nullptr));
        btn_GetFrontPointCloud->setText(QApplication::translate("Robot_App_Widget", "\347\202\271\344\272\221", nullptr));
        label_RearCamCtrl->setText(QApplication::translate("Robot_App_Widget", "\345\220\216\347\233\270\346\234\272:", nullptr));
        btn_GetRearRGB->setText(QApplication::translate("Robot_App_Widget", "\345\275\251\350\211\262", nullptr));
        btn_GetRearDepth->setText(QApplication::translate("Robot_App_Widget", "\346\267\261\345\272\246", nullptr));
        btn_GetRearPointCloud->setText(QApplication::translate("Robot_App_Widget", "\347\202\271\344\272\221", nullptr));
        groupBox_LogoLog->setTitle(QApplication::translate("Robot_App_Widget", "Logo\344\270\216\346\227\245\345\277\227\347\256\241\347\220\206", nullptr));
        btn_GetLogoBase64->setText(QApplication::translate("Robot_App_Widget", "\350\216\267\345\217\226Logo", nullptr));
        btn_GetBackgroundBase64->setText(QApplication::translate("Robot_App_Widget", "\350\216\267\345\217\226\350\203\214\346\231\257", nullptr));
        label_LogType->setText(QApplication::translate("Robot_App_Widget", "\347\261\273\345\236\213:", nullptr));
        combo_LogType->setItemText(0, QApplication::translate("Robot_App_Widget", "operation", nullptr));
        combo_LogType->setItemText(1, QApplication::translate("Robot_App_Widget", "launch", nullptr));
        combo_LogType->setItemText(2, QApplication::translate("Robot_App_Widget", "drive_error", nullptr));
        combo_LogType->setItemText(3, QApplication::translate("Robot_App_Widget", "rosbag", nullptr));

        label_LogFileName->setText(QApplication::translate("Robot_App_Widget", "\346\226\207\344\273\266\345\220\215:", nullptr));
        btn_DownLogs->setText(QApplication::translate("Robot_App_Widget", "\344\270\213\350\275\275", nullptr));
        btn_DropLogs->setText(QApplication::translate("Robot_App_Widget", "\345\210\240\351\231\244", nullptr));
        tabWidget_Magic->setTabText(tabWidget_Magic->indexOf(tab_Sensor), QApplication::translate("Robot_App_Widget", "\344\274\240\346\204\237\345\231\250\346\225\260\346\215\256", nullptr));
        groupBox_MapList->setTitle(QApplication::translate("Robot_App_Widget", "\345\234\260\345\233\276", nullptr));
        groupBox_Log->setTitle(QApplication::translate("Robot_App_Widget", "\346\227\245\345\277\227\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Robot_App_Widget: public Ui_Robot_App_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOT_APP_WIDGET_H
