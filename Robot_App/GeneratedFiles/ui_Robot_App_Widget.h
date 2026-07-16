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
#include <QtWidgets/QCheckBox>
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
    QPushButton *Show_Magic_Widget;
    QPushButton *Show_CGXi_Widget;
    QPushButton *Show_Pre_Scan_120_Widget;
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
    QGroupBox *groupBox_Jog;
    QGridLayout *gridLayout_17;
    QLabel *label_43;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_14;
    QLineEdit *CGXi_Jog_Type_r;
    c_Fr_Light *CGXi_Jog_Type;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_11;
    QComboBox *CGXi_Jog_Type_w;
    QLabel *label_38;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_13;
    QLineEdit *CGXi_Jog_Coord_r;
    c_Fr_Light *CGXi_Jog_Coord;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_12;
    QComboBox *CGXi_Jog_Coord_w;
    QLabel *label_26;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QLineEdit *CGXi_Jog_Speed_r;
    c_Fr_Light *CGXi_Jog_Speed;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_2;
    QLineEdit *CGXi_Jog_Speed_w;
    QHBoxLayout *horizontalLayout_47;
    QPushButton *Set_HoldingRegisters_810;
    QPushButton *Set_HoldingRegisters_800;
    QPushButton *Set_HoldingRegisters_803;
    QPushButton *Set_HoldingRegisters_801;
    QGroupBox *groupBox_JogTarget;
    QGridLayout *gridLayout_11;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_17;
    QLineEdit *CGXi_Jog_Tar_4_r;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_22;
    QLineEdit *CGXi_Jog_Tar_2_w;
    QLabel *label_32;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_18;
    QLineEdit *CGXi_Jog_Tar_1_r;
    QLabel *label_30;
    QLabel *label_31;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_21;
    QLineEdit *CGXi_Jog_Tar_0_w;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_20;
    QLineEdit *CGXi_Jog_Tar_5_r;
    QLabel *label_29;
    QLabel *label_28;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_16;
    QLineEdit *CGXi_Jog_Tar_2_r;
    QLabel *label_27;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_15;
    QLineEdit *CGXi_Jog_Tar_0_r;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_19;
    QLineEdit *CGXi_Jog_Tar_3_r;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_23;
    QLineEdit *CGXi_Jog_Tar_4_w;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_44;
    QLineEdit *CGXi_Jog_Tar_1_w;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_45;
    QLineEdit *CGXi_Jog_Tar_3_w;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_46;
    QLineEdit *CGXi_Jog_Tar_5_w;
    c_Fr_Light *CGXi_Jog_Tar_0;
    c_Fr_Light *CGXi_Jog_Tar_2;
    c_Fr_Light *CGXi_Jog_Tar_4;
    c_Fr_Light *CGXi_Jog_Tar_1;
    c_Fr_Light *CGXi_Jog_Tar_3;
    c_Fr_Light *CGXi_Jog_Tar_5;
    QGroupBox *groupBox_Config;
    QGridLayout *gridLayout_14;
    QHBoxLayout *horizontalLayout_32;
    QLabel *label_53;
    QLineEdit *CGXi_Payload_CY_r;
    QLabel *label_64;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_49;
    QLineEdit *CGXi_TCP_Off_Y_r;
    QHBoxLayout *horizontalLayout_33;
    QLabel *label_54;
    QLineEdit *CGXi_Payload_CZ_r;
    c_Fr_Light *CGXi_TCP_Off_X;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_69;
    QLineEdit *CGXi_TCP_Off_Rz_w;
    QLabel *label_35;
    QHBoxLayout *horizontalLayout_35;
    QLabel *label_56;
    QLineEdit *CGXi_TCP_Off_Y_w;
    QHBoxLayout *horizontalLayout_36;
    QLabel *label_57;
    QLineEdit *CGXi_TCP_Off_Z_w;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_52;
    QLineEdit *CGXi_Payload_CX_r;
    QPushButton *CGXi_Write_TCP;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_68;
    QLineEdit *CGXi_TCP_Off_Rz_r;
    QHBoxLayout *horizontalLayout_40;
    QLabel *label_63;
    QLineEdit *CGXi_Payload_CY_w;
    c_Fr_Light *CGXi_TCP_Off_Rz;
    QLabel *label_33;
    QHBoxLayout *horizontalLayout_38;
    QLabel *label_59;
    QLineEdit *CGXi_Payload_Mass_w;
    c_Fr_Light *CGXi_Payload_CZ;
    QLabel *label_39;
    QHBoxLayout *horizontalLayout_37;
    QLabel *label_58;
    QLineEdit *CGXi_TCP_Off_Rx_w;
    QPushButton *CGXi_Write_Payload;
    QHBoxLayout *horizontalLayout_34;
    QLabel *label_55;
    QLineEdit *CGXi_TCP_Off_X_w;
    QLabel *label_41;
    c_Fr_Light *CGXi_Payload_CY;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_47;
    QLineEdit *CGXi_TCP_Off_X_r;
    c_Fr_Light *CGXi_TCP_Off_Z;
    c_Fr_Light *CGXi_TCP_Off_Ry;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_50;
    QLineEdit *CGXi_TCP_Off_Rx_r;
    QHBoxLayout *horizontalLayout_39;
    QLabel *label_60;
    QLineEdit *CGXi_Payload_CX_w;
    QLabel *label_40;
    QHBoxLayout *horizontalLayout_42;
    QLabel *label_65;
    QLineEdit *CGXi_TCP_Off_Ry_r;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_51;
    QLineEdit *CGXi_Payload_Mass_r;
    c_Fr_Light *CGXi_TCP_Off_Y;
    QLabel *label_36;
    QLabel *label_34;
    QLabel *label_67;
    c_Fr_Light *CGXi_Payload_Mass;
    QHBoxLayout *horizontalLayout_41;
    QLabel *label_61;
    QLineEdit *CGXi_Payload_CZ_w;
    c_Fr_Light *CGXi_TCP_Off_Rx;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_48;
    QLineEdit *CGXi_TCP_Off_Z_r;
    c_Fr_Light *CGXi_Payload_CX;
    QHBoxLayout *horizontalLayout_43;
    QLabel *label_66;
    QLineEdit *CGXi_TCP_Off_Ry_w;
    QLabel *label_42;
    QVBoxLayout *verticalLayout;
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
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QTextBrowser *CGXi_Log;
    QWidget *Pre_Scan_120_Widget;
    QGridLayout *gridLayout_20;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_24;
    QHBoxLayout *horizontalLayout_50;
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
    QHBoxLayout *horizontalLayout_51;
    QLabel *label_120_Remote_Status;
    c_Fr_Light *Pre_Scan_120_Remote_Light;
    QLabel *label_120_Monitor_Status;
    c_Fr_Light *Pre_Scan_120_Monitor_Light;
    QLabel *label_120_Tran_Status;
    c_Fr_Light *Pre_Scan_120_Tran_Light;
    QLabel *label_120_Listen_Status;
    c_Fr_Light *Pre_Scan_120_Listen_Light;
    QLabel *label_120_Client_Num;
    QLineEdit *Pre_Scan_120_Client_Num;
    QLabel *label_120_Cam_Num;
    QLineEdit *Pre_Scan_120_Cam_Num;
    QLabel *label_120_LastUpdate;
    QLineEdit *Pre_Scan_120_LastUpdate;
    QSpacerItem *horizontalSpacer_30;
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
    QLabel *label_120_Prog;
    QLineEdit *r_Pre_Scan_120_currentWheelset;
    QLabel *label_120_Gain;
    QLineEdit *r_Pre_Scan_120_Gain;
    QLabel *label_120_Part1;
    QLineEdit *r_Pre_Scan_120_Part1;
    QLabel *label_120_Part2;
    QLineEdit *r_Pre_Scan_120_Part2;
    QLabel *label_120_Point;
    QLineEdit *r_Pre_Scan_120_Point;
    QGroupBox *groupBox_Control;
    QGridLayout *gridLayout_25;
    QPushButton *Pre_Scan_120_Start_Scan;
    QPushButton *Pre_Scan_120_Collector;
    QPushButton *Pre_Scan_120_Finish_Scan;
    QHBoxLayout *horizontalLayout_54;
    QSpinBox *Pre_Scan_120_Gain_Spin;
    QPushButton *Pre_Scan_120_Change_Gain;
    QHBoxLayout *horizontalLayout_52;
    QLabel *label_120_TotalImages;
    QLineEdit *r_Pre_Scan_120_TotalImages;
    QHBoxLayout *horizontalLayout_56;
    QLabel *label_120_WorkState;
    QComboBox *Pre_Scan_120_WorkState;
    QHBoxLayout *horizontalLayout_49;
    QGroupBox *groupBox_Task_Info_2;
    QGridLayout *gridLayout_22;
    QLineEdit *w_Pre_Scan_120_TaskID;
    QLineEdit *w_Pre_Scan_120_SendUnit;
    QLabel *label_120_Wheelset_2;
    QLineEdit *w_Pre_Scan_120_StartTime;
    QLineEdit *w_Pre_Scan_120_Repair;
    QLabel *label_120_Repair_2;
    QLabel *label_120_SendUnit_2;
    QLabel *label_120_StartTime_2;
    QLabel *label_120_Axle_2;
    QLabel *label_120_TaskID_2;
    QLineEdit *w_Pre_Scan_120_Wheelset;
    QLineEdit *w_Pre_Scan_120_Axle;
    QPushButton *set_Pre_Scan_120_TaskID;
    QPushButton *set_Pre_Scan_120_SendUnit;
    QPushButton *set_Pre_Scan_120_Repair;
    QPushButton *set_Pre_Scan_120_Wheelset;
    QPushButton *set_Pre_Scan_120_Axle;
    QPushButton *set_Pre_Scan_120_StartTime;
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
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_23;
    QTextEdit *Prec_Scan_120_Cmd;
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
    QSpacerItem *horizontalSpacer_31;
    QGroupBox *groupBox_Log;
    QVBoxLayout *verticalLayout_24;
    QTextEdit *Pre_Scan_120_Log;
    QWidget *Magic_Widget;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_Connect;
    QHBoxLayout *horizontalLayout_Connect;
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
    QGroupBox *groupBox_Pose;
    QHBoxLayout *horizontalLayout_Pose;
    QLabel *label_WX;
    QLineEdit *lineEdit_WX;
    QLabel *label_WY;
    QLineEdit *lineEdit_WY;
    QLabel *label_Angle;
    QLineEdit *lineEdit_Angle;
    QLabel *label_Battery;
    QLineEdit *lineEdit_Battery;
    QLabel *label_GridX;
    QLineEdit *lineEdit_GridX;
    QLabel *label_GridY;
    QLineEdit *lineEdit_GridY;
    QLabel *label_CurrentMap;
    QLineEdit *lineEdit_CurrentMap;
    QGroupBox *groupBox_SystemInfo;
    QHBoxLayout *horizontalLayout_SystemInfo;
    QLabel *label_AntiCollision;
    QLineEdit *lineEdit_AntiCollision;
    QLabel *label_WorkMode;
    QLineEdit *lineEdit_WorkMode;
    QLabel *label_ErrorCode;
    QLineEdit *lineEdit_ErrorCode;
    QLabel *label_ChassisVer;
    QLineEdit *lineEdit_ChassisVer;
    QLabel *label_NavVer;
    QLineEdit *lineEdit_NavVer;
    QGroupBox *groupBox_MapList;
    QGridLayout *gridLayout_16;
    c_Magic_Map_View *widget_MapView;
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
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget_Magic;
    QWidget *tab_Map;
    QGridLayout *gridLayout_13;
    QHBoxLayout *horizontalLayout_MapOps4;
    QPushButton *btn_EditMap;
    QPushButton *btn_SetObstacle;
    QPushButton *btn_GetObstacle;
    QHBoxLayout *horizontalLayout_MapOps2;
    QLineEdit *lineEdit_NewMapName;
    QPushButton *btn_RenameMap;
    QPushButton *btn_DeleteMap;
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
    QGroupBox *groupBox_TaskControl;
    QHBoxLayout *horizontalLayout_TaskControl;
    QPushButton *btn_StartTask;
    QPushButton *btn_LoopStart;
    QPushButton *btn_PauseTask;
    QPushButton *btn_ResumeTask;
    QPushButton *btn_StopTask;
    QPushButton *btn_SkipCurrentTask;
    QPushButton *btn_GetTaskLog;
    QPushButton *btn_UploadTaskImage;
    QPushButton *btn_DownloadTaskImage;
    QLineEdit *lineEdit_TaskID;
    QHBoxLayout *horizontalLayout_MapOps1;
    QComboBox *comboBox_MapList;
    QPushButton *btn_RefreshMapList;
    QPushButton *btn_SwitchMap;
    QGroupBox *groupBox_TaskSelect;
    QHBoxLayout *horizontalLayout_TaskSelect;
    QLabel *label_TaskType;
    QComboBox *combo_TaskType;
    QLabel *label_TaskName;
    QComboBox *combo_TaskName;
    QLabel *label_LoopCount;
    QSpinBox *spin_LoopCount;
    QHBoxLayout *horizontalLayout_MapOps5;
    QPushButton *btn_StopScanMap;
    QPushButton *btn_CancelScanMap;
    QPushButton *btn_RecoverMap;
    QPushButton *btn_QueryDefaultMap;
    QPushButton *btn_RefreshToken;
    QHBoxLayout *horizontalLayout_MapOps3;
    QPushButton *btn_DownloadMap;
    QPushButton *btn_UploadMap;
    QPushButton *btn_ExtendMap;
    QGroupBox *groupBox_TaskStatus;
    QHBoxLayout *horizontalLayout_TaskStatus;
    QLabel *label_TaskStatusText;
    QProgressBar *progress_Task;
    QLabel *label_RemainTime;
    QLabel *label_RemainTimeValue;
    QLabel *label_LoopInfo;
    QGroupBox *groupBox_InitPose;
    QHBoxLayout *horizontalLayout_InitPose;
    QComboBox *combo_InitPoint;
    QPushButton *btn_DynamicInit;
    QPushButton *btn_StaticInit;
    QPushButton *btn_GridInit;
    QPushButton *btn_InitResult;
    QWidget *tab_PathPoint;
    QVBoxLayout *verticalLayout_PathPoint;
    QTabWidget *tabWidget_PathPoint;
    QWidget *tab_NavPoint;
    QVBoxLayout *verticalLayout_NavPoint;
    QTableWidget *table_NavPoints;
    QHBoxLayout *horizontalLayout_NavOps;
    QPushButton *btn_AddNavPoint;
    QPushButton *btn_EditNavPoint;
    QPushButton *btn_DeleteNavPoint;
    QPushButton *btn_RefreshNavPoints;
    QWidget *tab_GraphPath;
    QVBoxLayout *verticalLayout_Graph;
    QTableWidget *table_GraphPaths;
    QHBoxLayout *horizontalLayout_GraphOps;
    QPushButton *btn_CreateGraphPath;
    QPushButton *btn_EditGraphPath;
    QPushButton *btn_DeleteGraphPath;
    QPushButton *btn_RenameGraphPath;
    QPushButton *btn_RefreshGraphPaths;
    QWidget *tab_RecordPath;
    QVBoxLayout *verticalLayout_Record;
    QTableWidget *table_RecordPaths;
    QHBoxLayout *horizontalLayout_RecordOps;
    QPushButton *btn_StartRecord;
    QPushButton *btn_StopRecord;
    QPushButton *btn_CancelRecord;
    QPushButton *btn_EditRecordPoints;
    QPushButton *btn_DeleteRecordPath;
    QPushButton *btn_RenameRecordPath;
    QPushButton *btn_RefreshRecordPaths;
    QWidget *tab_TaskQueue;
    QVBoxLayout *verticalLayout_Queue;
    QTableWidget *table_PathCombines;
    QHBoxLayout *horizontalLayout_QueueOps;
    QPushButton *btn_CreateCombine;
    QPushButton *btn_EditCombine;
    QPushButton *btn_DeleteCombine;
    QPushButton *btn_RenameCombine;
    QPushButton *btn_RefreshCombines;
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
    QGroupBox *groupBox_Obstacle;
    QHBoxLayout *horizontalLayout_Obstacle;
    QCheckBox *chk_GraphObstacle;
    QCheckBox *chk_RecordObstacle;
    QCheckBox *chk_LidarVoid;
    QPushButton *btn_SaveObstacle;
    QPushButton *btn_ResetDefault;
    QPushButton *btn_DownloadCfg;
    QPushButton *btn_UploadCfg;
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
    QGroupBox *groupBox_Log1;
    QVBoxLayout *verticalLayout_Log;
    QTextEdit *Magic_Log;
    QHBoxLayout *horizontalLayout_46;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout;
    QTextEdit *Worry_List;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_51;
    QTextEdit *Work_List;
    QStatusBar *Status_Bar;

    void setupUi(QMainWindow *Robot_App_Widget)
    {
        if (Robot_App_Widget->objectName().isEmpty())
            Robot_App_Widget->setObjectName(QString::fromUtf8("Robot_App_Widget"));
        Robot_App_Widget->setWindowModality(Qt::WindowModal);
        Robot_App_Widget->resize(1689, 1009);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Robot_App_Widget->sizePolicy().hasHeightForWidth());
        Robot_App_Widget->setSizePolicy(sizePolicy);
        Robot_App_Widget->setMinimumSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Logo/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Robot_App_Widget->setWindowIcon(icon);
        centralWidget = new QWidget(Robot_App_Widget);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_15 = new QGridLayout(centralWidget);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        widget_10 = new QWidget(centralWidget);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_10->sizePolicy().hasHeightForWidth());
        widget_10->setSizePolicy(sizePolicy1);
        widget_10->setMinimumSize(QSize(0, 0));
        widget_10->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_94 = new QGridLayout(widget_10);
        gridLayout_94->setSpacing(6);
        gridLayout_94->setContentsMargins(11, 11, 11, 11);
        gridLayout_94->setObjectName(QString::fromUtf8("gridLayout_94"));
        groupBox_5 = new QGroupBox(widget_10);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        sizePolicy1.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy1);
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        Show_Magic_Widget = new QPushButton(groupBox_5);
        Show_Magic_Widget->setObjectName(QString::fromUtf8("Show_Magic_Widget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Show_Magic_Widget->sizePolicy().hasHeightForWidth());
        Show_Magic_Widget->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(Show_Magic_Widget, 1, 0, 1, 1);

        Show_CGXi_Widget = new QPushButton(groupBox_5);
        Show_CGXi_Widget->setObjectName(QString::fromUtf8("Show_CGXi_Widget"));
        sizePolicy2.setHeightForWidth(Show_CGXi_Widget->sizePolicy().hasHeightForWidth());
        Show_CGXi_Widget->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(Show_CGXi_Widget, 2, 0, 1, 1);

        Show_Pre_Scan_120_Widget = new QPushButton(groupBox_5);
        Show_Pre_Scan_120_Widget->setObjectName(QString::fromUtf8("Show_Pre_Scan_120_Widget"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(Show_Pre_Scan_120_Widget->sizePolicy().hasHeightForWidth());
        Show_Pre_Scan_120_Widget->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(Show_Pre_Scan_120_Widget, 3, 0, 1, 1);


        gridLayout_94->addWidget(groupBox_5, 0, 0, 1, 1);


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
        sizePolicy3.setHeightForWidth(CGXi_CO0_State->sizePolicy().hasHeightForWidth());
        CGXi_CO0_State->setSizePolicy(sizePolicy3);
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
        sizePolicy3.setHeightForWidth(CGXi_CO5_State->sizePolicy().hasHeightForWidth());
        CGXi_CO5_State->setSizePolicy(sizePolicy3);
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
        sizePolicy3.setHeightForWidth(label_DO1_8->sizePolicy().hasHeightForWidth());
        label_DO1_8->setSizePolicy(sizePolicy3);
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
        sizePolicy3.setHeightForWidth(label_DO0_3->sizePolicy().hasHeightForWidth());
        label_DO0_3->setSizePolicy(sizePolicy3);
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
        sizePolicy3.setHeightForWidth(label_DO1_7->sizePolicy().hasHeightForWidth());
        label_DO1_7->setSizePolicy(sizePolicy3);
        label_DO1_7->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_DO1_7, 1, 4, 1, 1);

        CGXi_CO1_State = new c_Fr_Light(groupBox_DO_3);
        CGXi_CO1_State->setObjectName(QString::fromUtf8("CGXi_CO1_State"));
        sizePolicy3.setHeightForWidth(CGXi_CO1_State->sizePolicy().hasHeightForWidth());
        CGXi_CO1_State->setSizePolicy(sizePolicy3);
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
        sizePolicy3.setHeightForWidth(label_DO1_9->sizePolicy().hasHeightForWidth());
        label_DO1_9->setSizePolicy(sizePolicy3);
        label_DO1_9->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_DO1_9, 1, 8, 1, 1);

        CGXi_CO2_State = new c_Fr_Light(groupBox_DO_3);
        CGXi_CO2_State->setObjectName(QString::fromUtf8("CGXi_CO2_State"));
        sizePolicy3.setHeightForWidth(CGXi_CO2_State->sizePolicy().hasHeightForWidth());
        CGXi_CO2_State->setSizePolicy(sizePolicy3);
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
        sizePolicy3.setHeightForWidth(label_DO0_4->sizePolicy().hasHeightForWidth());
        label_DO0_4->setSizePolicy(sizePolicy3);
        label_DO0_4->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_DO0_4, 2, 0, 1, 1);

        CGXi_CO4_State = new c_Fr_Light(groupBox_DO_3);
        CGXi_CO4_State->setObjectName(QString::fromUtf8("CGXi_CO4_State"));
        sizePolicy3.setHeightForWidth(CGXi_CO4_State->sizePolicy().hasHeightForWidth());
        CGXi_CO4_State->setSizePolicy(sizePolicy3);
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
        sizePolicy3.setHeightForWidth(label_DO1_11->sizePolicy().hasHeightForWidth());
        label_DO1_11->setSizePolicy(sizePolicy3);
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
        sizePolicy3.setHeightForWidth(CGXi_CO3_State->sizePolicy().hasHeightForWidth());
        CGXi_CO3_State->setSizePolicy(sizePolicy3);
        CGXi_CO3_State->setMinimumSize(QSize(20, 20));

        gridLayout_12->addWidget(CGXi_CO3_State, 1, 13, 1, 1);

        label_DO1_10 = new QLabel(groupBox_DO_3);
        label_DO1_10->setObjectName(QString::fromUtf8("label_DO1_10"));
        sizePolicy3.setHeightForWidth(label_DO1_10->sizePolicy().hasHeightForWidth());
        label_DO1_10->setSizePolicy(sizePolicy3);
        label_DO1_10->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_DO1_10, 2, 8, 1, 1);

        CGXi_CO6_State = new c_Fr_Light(groupBox_DO_3);
        CGXi_CO6_State->setObjectName(QString::fromUtf8("CGXi_CO6_State"));
        sizePolicy3.setHeightForWidth(CGXi_CO6_State->sizePolicy().hasHeightForWidth());
        CGXi_CO6_State->setSizePolicy(sizePolicy3);
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
        sizePolicy3.setHeightForWidth(label_DO1_12->sizePolicy().hasHeightForWidth());
        label_DO1_12->setSizePolicy(sizePolicy3);
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
        sizePolicy3.setHeightForWidth(CGXi_CO7_State->sizePolicy().hasHeightForWidth());
        CGXi_CO7_State->setSizePolicy(sizePolicy3);
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
        QSizePolicy sizePolicy8(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy8);

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
        sizePolicy8.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy8);

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
        sizePolicy3.setHeightForWidth(CGXi_program_status->sizePolicy().hasHeightForWidth());
        CGXi_program_status->setSizePolicy(sizePolicy3);
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

        groupBox_Jog = new QGroupBox(groupBox_3);
        groupBox_Jog->setObjectName(QString::fromUtf8("groupBox_Jog"));
        sizePolicy2.setHeightForWidth(groupBox_Jog->sizePolicy().hasHeightForWidth());
        groupBox_Jog->setSizePolicy(sizePolicy2);
        gridLayout_17 = new QGridLayout(groupBox_Jog);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        label_43 = new QLabel(groupBox_Jog);
        label_43->setObjectName(QString::fromUtf8("label_43"));
        sizePolicy5.setHeightForWidth(label_43->sizePolicy().hasHeightForWidth());
        label_43->setSizePolicy(sizePolicy5);

        gridLayout_17->addWidget(label_43, 0, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_14 = new QLabel(groupBox_Jog);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy5.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy5);

        horizontalLayout_13->addWidget(label_14);

        CGXi_Jog_Type_r = new QLineEdit(groupBox_Jog);
        CGXi_Jog_Type_r->setObjectName(QString::fromUtf8("CGXi_Jog_Type_r"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Type_r->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Type_r->setSizePolicy(sizePolicy7);

        horizontalLayout_13->addWidget(CGXi_Jog_Type_r);


        gridLayout_17->addLayout(horizontalLayout_13, 0, 1, 1, 1);

        CGXi_Jog_Type = new c_Fr_Light(groupBox_Jog);
        CGXi_Jog_Type->setObjectName(QString::fromUtf8("CGXi_Jog_Type"));
        sizePolicy5.setHeightForWidth(CGXi_Jog_Type->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Type->setSizePolicy(sizePolicy5);
        CGXi_Jog_Type->setMinimumSize(QSize(20, 20));

        gridLayout_17->addWidget(CGXi_Jog_Type, 0, 2, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_11 = new QLabel(groupBox_Jog);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy5.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy5);

        horizontalLayout_10->addWidget(label_11);

        CGXi_Jog_Type_w = new QComboBox(groupBox_Jog);
        CGXi_Jog_Type_w->addItem(QString());
        CGXi_Jog_Type_w->addItem(QString());
        CGXi_Jog_Type_w->setObjectName(QString::fromUtf8("CGXi_Jog_Type_w"));

        horizontalLayout_10->addWidget(CGXi_Jog_Type_w);


        gridLayout_17->addLayout(horizontalLayout_10, 0, 3, 1, 1);

        label_38 = new QLabel(groupBox_Jog);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        sizePolicy5.setHeightForWidth(label_38->sizePolicy().hasHeightForWidth());
        label_38->setSizePolicy(sizePolicy5);

        gridLayout_17->addWidget(label_38, 1, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_13 = new QLabel(groupBox_Jog);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy5.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy5);

        horizontalLayout_12->addWidget(label_13);

        CGXi_Jog_Coord_r = new QLineEdit(groupBox_Jog);
        CGXi_Jog_Coord_r->setObjectName(QString::fromUtf8("CGXi_Jog_Coord_r"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Coord_r->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Coord_r->setSizePolicy(sizePolicy7);

        horizontalLayout_12->addWidget(CGXi_Jog_Coord_r);


        gridLayout_17->addLayout(horizontalLayout_12, 1, 1, 1, 1);

        CGXi_Jog_Coord = new c_Fr_Light(groupBox_Jog);
        CGXi_Jog_Coord->setObjectName(QString::fromUtf8("CGXi_Jog_Coord"));
        sizePolicy5.setHeightForWidth(CGXi_Jog_Coord->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Coord->setSizePolicy(sizePolicy5);
        CGXi_Jog_Coord->setMinimumSize(QSize(20, 20));

        gridLayout_17->addWidget(CGXi_Jog_Coord, 1, 2, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_12 = new QLabel(groupBox_Jog);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy5.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy5);

        horizontalLayout_11->addWidget(label_12);

        CGXi_Jog_Coord_w = new QComboBox(groupBox_Jog);
        CGXi_Jog_Coord_w->addItem(QString());
        CGXi_Jog_Coord_w->addItem(QString());
        CGXi_Jog_Coord_w->setObjectName(QString::fromUtf8("CGXi_Jog_Coord_w"));

        horizontalLayout_11->addWidget(CGXi_Jog_Coord_w);


        gridLayout_17->addLayout(horizontalLayout_11, 1, 3, 1, 1);

        label_26 = new QLabel(groupBox_Jog);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        sizePolicy5.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy5);

        gridLayout_17->addWidget(label_26, 2, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label = new QLabel(groupBox_Jog);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy5.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy5);

        horizontalLayout_8->addWidget(label);

        CGXi_Jog_Speed_r = new QLineEdit(groupBox_Jog);
        CGXi_Jog_Speed_r->setObjectName(QString::fromUtf8("CGXi_Jog_Speed_r"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Speed_r->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Speed_r->setSizePolicy(sizePolicy7);

        horizontalLayout_8->addWidget(CGXi_Jog_Speed_r);


        gridLayout_17->addLayout(horizontalLayout_8, 2, 1, 1, 1);

        CGXi_Jog_Speed = new c_Fr_Light(groupBox_Jog);
        CGXi_Jog_Speed->setObjectName(QString::fromUtf8("CGXi_Jog_Speed"));
        sizePolicy5.setHeightForWidth(CGXi_Jog_Speed->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Speed->setSizePolicy(sizePolicy5);
        CGXi_Jog_Speed->setMinimumSize(QSize(20, 20));

        gridLayout_17->addWidget(CGXi_Jog_Speed, 2, 2, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_2 = new QLabel(groupBox_Jog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy5.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy5);

        horizontalLayout_9->addWidget(label_2);

        CGXi_Jog_Speed_w = new QLineEdit(groupBox_Jog);
        CGXi_Jog_Speed_w->setObjectName(QString::fromUtf8("CGXi_Jog_Speed_w"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Speed_w->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Speed_w->setSizePolicy(sizePolicy7);

        horizontalLayout_9->addWidget(CGXi_Jog_Speed_w);


        gridLayout_17->addLayout(horizontalLayout_9, 2, 3, 1, 1);

        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setSpacing(6);
        horizontalLayout_47->setObjectName(QString::fromUtf8("horizontalLayout_47"));
        Set_HoldingRegisters_810 = new QPushButton(groupBox_Jog);
        Set_HoldingRegisters_810->setObjectName(QString::fromUtf8("Set_HoldingRegisters_810"));
        Set_HoldingRegisters_810->setMinimumSize(QSize(0, 0));

        horizontalLayout_47->addWidget(Set_HoldingRegisters_810);

        Set_HoldingRegisters_800 = new QPushButton(groupBox_Jog);
        Set_HoldingRegisters_800->setObjectName(QString::fromUtf8("Set_HoldingRegisters_800"));
        sizePolicy7.setHeightForWidth(Set_HoldingRegisters_800->sizePolicy().hasHeightForWidth());
        Set_HoldingRegisters_800->setSizePolicy(sizePolicy7);

        horizontalLayout_47->addWidget(Set_HoldingRegisters_800);

        Set_HoldingRegisters_803 = new QPushButton(groupBox_Jog);
        Set_HoldingRegisters_803->setObjectName(QString::fromUtf8("Set_HoldingRegisters_803"));
        sizePolicy7.setHeightForWidth(Set_HoldingRegisters_803->sizePolicy().hasHeightForWidth());
        Set_HoldingRegisters_803->setSizePolicy(sizePolicy7);

        horizontalLayout_47->addWidget(Set_HoldingRegisters_803);

        Set_HoldingRegisters_801 = new QPushButton(groupBox_Jog);
        Set_HoldingRegisters_801->setObjectName(QString::fromUtf8("Set_HoldingRegisters_801"));
        sizePolicy7.setHeightForWidth(Set_HoldingRegisters_801->sizePolicy().hasHeightForWidth());
        Set_HoldingRegisters_801->setSizePolicy(sizePolicy7);

        horizontalLayout_47->addWidget(Set_HoldingRegisters_801);


        gridLayout_17->addLayout(horizontalLayout_47, 4, 0, 1, 4);

        groupBox_JogTarget = new QGroupBox(groupBox_Jog);
        groupBox_JogTarget->setObjectName(QString::fromUtf8("groupBox_JogTarget"));
        gridLayout_11 = new QGridLayout(groupBox_JogTarget);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_17 = new QLabel(groupBox_JogTarget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        sizePolicy5.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy5);

        horizontalLayout_16->addWidget(label_17);

        CGXi_Jog_Tar_4_r = new QLineEdit(groupBox_JogTarget);
        CGXi_Jog_Tar_4_r->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_4_r"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Tar_4_r->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_4_r->setSizePolicy(sizePolicy7);

        horizontalLayout_16->addWidget(CGXi_Jog_Tar_4_r);


        gridLayout_11->addLayout(horizontalLayout_16, 4, 1, 1, 1);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_22 = new QLabel(groupBox_JogTarget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy5.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy5);

        horizontalLayout_21->addWidget(label_22);

        CGXi_Jog_Tar_2_w = new QLineEdit(groupBox_JogTarget);
        CGXi_Jog_Tar_2_w->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_2_w"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Tar_2_w->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_2_w->setSizePolicy(sizePolicy7);

        horizontalLayout_21->addWidget(CGXi_Jog_Tar_2_w);


        gridLayout_11->addLayout(horizontalLayout_21, 3, 1, 1, 1);

        label_32 = new QLabel(groupBox_JogTarget);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        sizePolicy3.setHeightForWidth(label_32->sizePolicy().hasHeightForWidth());
        label_32->setSizePolicy(sizePolicy3);

        gridLayout_11->addWidget(label_32, 4, 3, 1, 1);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_18 = new QLabel(groupBox_JogTarget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy5.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy5);

        horizontalLayout_17->addWidget(label_18);

        CGXi_Jog_Tar_1_r = new QLineEdit(groupBox_JogTarget);
        CGXi_Jog_Tar_1_r->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_1_r"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Tar_1_r->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_1_r->setSizePolicy(sizePolicy7);

        horizontalLayout_17->addWidget(CGXi_Jog_Tar_1_r);


        gridLayout_11->addLayout(horizontalLayout_17, 0, 4, 1, 1);

        label_30 = new QLabel(groupBox_JogTarget);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        sizePolicy3.setHeightForWidth(label_30->sizePolicy().hasHeightForWidth());
        label_30->setSizePolicy(sizePolicy3);

        gridLayout_11->addWidget(label_30, 2, 3, 1, 1);

        label_31 = new QLabel(groupBox_JogTarget);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        sizePolicy3.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy3);

        gridLayout_11->addWidget(label_31, 4, 0, 1, 1);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_21 = new QLabel(groupBox_JogTarget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy5.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy5);

        horizontalLayout_20->addWidget(label_21);

        CGXi_Jog_Tar_0_w = new QLineEdit(groupBox_JogTarget);
        CGXi_Jog_Tar_0_w->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_0_w"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Tar_0_w->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_0_w->setSizePolicy(sizePolicy7);

        horizontalLayout_20->addWidget(CGXi_Jog_Tar_0_w);


        gridLayout_11->addLayout(horizontalLayout_20, 1, 1, 1, 1);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_20 = new QLabel(groupBox_JogTarget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        sizePolicy5.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy5);

        horizontalLayout_19->addWidget(label_20);

        CGXi_Jog_Tar_5_r = new QLineEdit(groupBox_JogTarget);
        CGXi_Jog_Tar_5_r->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_5_r"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Tar_5_r->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_5_r->setSizePolicy(sizePolicy7);

        horizontalLayout_19->addWidget(CGXi_Jog_Tar_5_r);


        gridLayout_11->addLayout(horizontalLayout_19, 4, 4, 1, 1);

        label_29 = new QLabel(groupBox_JogTarget);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        sizePolicy3.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy3);

        gridLayout_11->addWidget(label_29, 2, 0, 1, 1);

        label_28 = new QLabel(groupBox_JogTarget);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        sizePolicy3.setHeightForWidth(label_28->sizePolicy().hasHeightForWidth());
        label_28->setSizePolicy(sizePolicy3);

        gridLayout_11->addWidget(label_28, 0, 3, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_16 = new QLabel(groupBox_JogTarget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy5.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy5);

        horizontalLayout_15->addWidget(label_16);

        CGXi_Jog_Tar_2_r = new QLineEdit(groupBox_JogTarget);
        CGXi_Jog_Tar_2_r->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_2_r"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Tar_2_r->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_2_r->setSizePolicy(sizePolicy7);

        horizontalLayout_15->addWidget(CGXi_Jog_Tar_2_r);


        gridLayout_11->addLayout(horizontalLayout_15, 2, 1, 1, 1);

        label_27 = new QLabel(groupBox_JogTarget);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        sizePolicy3.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy3);

        gridLayout_11->addWidget(label_27, 0, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_15 = new QLabel(groupBox_JogTarget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy5.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy5);

        horizontalLayout_14->addWidget(label_15);

        CGXi_Jog_Tar_0_r = new QLineEdit(groupBox_JogTarget);
        CGXi_Jog_Tar_0_r->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_0_r"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Tar_0_r->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_0_r->setSizePolicy(sizePolicy7);

        horizontalLayout_14->addWidget(CGXi_Jog_Tar_0_r);


        gridLayout_11->addLayout(horizontalLayout_14, 0, 1, 1, 1);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_19 = new QLabel(groupBox_JogTarget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy5.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy5);

        horizontalLayout_18->addWidget(label_19);

        CGXi_Jog_Tar_3_r = new QLineEdit(groupBox_JogTarget);
        CGXi_Jog_Tar_3_r->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_3_r"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Tar_3_r->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_3_r->setSizePolicy(sizePolicy7);

        horizontalLayout_18->addWidget(CGXi_Jog_Tar_3_r);


        gridLayout_11->addLayout(horizontalLayout_18, 2, 4, 1, 1);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_23 = new QLabel(groupBox_JogTarget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        sizePolicy5.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy5);

        horizontalLayout_22->addWidget(label_23);

        CGXi_Jog_Tar_4_w = new QLineEdit(groupBox_JogTarget);
        CGXi_Jog_Tar_4_w->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_4_w"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Tar_4_w->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_4_w->setSizePolicy(sizePolicy7);

        horizontalLayout_22->addWidget(CGXi_Jog_Tar_4_w);


        gridLayout_11->addLayout(horizontalLayout_22, 5, 1, 1, 1);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_44 = new QLabel(groupBox_JogTarget);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        sizePolicy5.setHeightForWidth(label_44->sizePolicy().hasHeightForWidth());
        label_44->setSizePolicy(sizePolicy5);

        horizontalLayout_23->addWidget(label_44);

        CGXi_Jog_Tar_1_w = new QLineEdit(groupBox_JogTarget);
        CGXi_Jog_Tar_1_w->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_1_w"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Tar_1_w->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_1_w->setSizePolicy(sizePolicy7);

        horizontalLayout_23->addWidget(CGXi_Jog_Tar_1_w);


        gridLayout_11->addLayout(horizontalLayout_23, 1, 4, 1, 1);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_45 = new QLabel(groupBox_JogTarget);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        sizePolicy5.setHeightForWidth(label_45->sizePolicy().hasHeightForWidth());
        label_45->setSizePolicy(sizePolicy5);

        horizontalLayout_24->addWidget(label_45);

        CGXi_Jog_Tar_3_w = new QLineEdit(groupBox_JogTarget);
        CGXi_Jog_Tar_3_w->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_3_w"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Tar_3_w->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_3_w->setSizePolicy(sizePolicy7);

        horizontalLayout_24->addWidget(CGXi_Jog_Tar_3_w);


        gridLayout_11->addLayout(horizontalLayout_24, 3, 4, 1, 1);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_46 = new QLabel(groupBox_JogTarget);
        label_46->setObjectName(QString::fromUtf8("label_46"));
        sizePolicy5.setHeightForWidth(label_46->sizePolicy().hasHeightForWidth());
        label_46->setSizePolicy(sizePolicy5);

        horizontalLayout_25->addWidget(label_46);

        CGXi_Jog_Tar_5_w = new QLineEdit(groupBox_JogTarget);
        CGXi_Jog_Tar_5_w->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_5_w"));
        sizePolicy7.setHeightForWidth(CGXi_Jog_Tar_5_w->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_5_w->setSizePolicy(sizePolicy7);

        horizontalLayout_25->addWidget(CGXi_Jog_Tar_5_w);


        gridLayout_11->addLayout(horizontalLayout_25, 5, 4, 1, 1);

        CGXi_Jog_Tar_0 = new c_Fr_Light(groupBox_JogTarget);
        CGXi_Jog_Tar_0->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_0"));
        sizePolicy5.setHeightForWidth(CGXi_Jog_Tar_0->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_0->setSizePolicy(sizePolicy5);
        CGXi_Jog_Tar_0->setMinimumSize(QSize(20, 20));

        gridLayout_11->addWidget(CGXi_Jog_Tar_0, 1, 0, 1, 1);

        CGXi_Jog_Tar_2 = new c_Fr_Light(groupBox_JogTarget);
        CGXi_Jog_Tar_2->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_2"));
        sizePolicy5.setHeightForWidth(CGXi_Jog_Tar_2->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_2->setSizePolicy(sizePolicy5);
        CGXi_Jog_Tar_2->setMinimumSize(QSize(20, 20));

        gridLayout_11->addWidget(CGXi_Jog_Tar_2, 3, 0, 1, 1);

        CGXi_Jog_Tar_4 = new c_Fr_Light(groupBox_JogTarget);
        CGXi_Jog_Tar_4->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_4"));
        sizePolicy5.setHeightForWidth(CGXi_Jog_Tar_4->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_4->setSizePolicy(sizePolicy5);
        CGXi_Jog_Tar_4->setMinimumSize(QSize(20, 20));

        gridLayout_11->addWidget(CGXi_Jog_Tar_4, 5, 0, 1, 1);

        CGXi_Jog_Tar_1 = new c_Fr_Light(groupBox_JogTarget);
        CGXi_Jog_Tar_1->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_1"));
        sizePolicy5.setHeightForWidth(CGXi_Jog_Tar_1->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_1->setSizePolicy(sizePolicy5);
        CGXi_Jog_Tar_1->setMinimumSize(QSize(20, 20));

        gridLayout_11->addWidget(CGXi_Jog_Tar_1, 1, 3, 1, 1);

        CGXi_Jog_Tar_3 = new c_Fr_Light(groupBox_JogTarget);
        CGXi_Jog_Tar_3->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_3"));
        sizePolicy5.setHeightForWidth(CGXi_Jog_Tar_3->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_3->setSizePolicy(sizePolicy5);
        CGXi_Jog_Tar_3->setMinimumSize(QSize(20, 20));

        gridLayout_11->addWidget(CGXi_Jog_Tar_3, 3, 3, 1, 1);

        CGXi_Jog_Tar_5 = new c_Fr_Light(groupBox_JogTarget);
        CGXi_Jog_Tar_5->setObjectName(QString::fromUtf8("CGXi_Jog_Tar_5"));
        sizePolicy5.setHeightForWidth(CGXi_Jog_Tar_5->sizePolicy().hasHeightForWidth());
        CGXi_Jog_Tar_5->setSizePolicy(sizePolicy5);
        CGXi_Jog_Tar_5->setMinimumSize(QSize(20, 20));

        gridLayout_11->addWidget(CGXi_Jog_Tar_5, 5, 3, 1, 1);


        gridLayout_17->addWidget(groupBox_JogTarget, 3, 0, 1, 4);


        verticalLayout_2->addWidget(groupBox_Jog);

        groupBox_Config = new QGroupBox(groupBox_3);
        groupBox_Config->setObjectName(QString::fromUtf8("groupBox_Config"));
        sizePolicy2.setHeightForWidth(groupBox_Config->sizePolicy().hasHeightForWidth());
        groupBox_Config->setSizePolicy(sizePolicy2);
        gridLayout_14 = new QGridLayout(groupBox_Config);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(6);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        label_53 = new QLabel(groupBox_Config);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        sizePolicy5.setHeightForWidth(label_53->sizePolicy().hasHeightForWidth());
        label_53->setSizePolicy(sizePolicy5);

        horizontalLayout_32->addWidget(label_53);

        CGXi_Payload_CY_r = new QLineEdit(groupBox_Config);
        CGXi_Payload_CY_r->setObjectName(QString::fromUtf8("CGXi_Payload_CY_r"));
        sizePolicy7.setHeightForWidth(CGXi_Payload_CY_r->sizePolicy().hasHeightForWidth());
        CGXi_Payload_CY_r->setSizePolicy(sizePolicy7);

        horizontalLayout_32->addWidget(CGXi_Payload_CY_r);


        gridLayout_14->addLayout(horizontalLayout_32, 13, 1, 1, 1);

        label_64 = new QLabel(groupBox_Config);
        label_64->setObjectName(QString::fromUtf8("label_64"));
        sizePolicy5.setHeightForWidth(label_64->sizePolicy().hasHeightForWidth());
        label_64->setSizePolicy(sizePolicy5);

        gridLayout_14->addWidget(label_64, 6, 0, 1, 1);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        label_49 = new QLabel(groupBox_Config);
        label_49->setObjectName(QString::fromUtf8("label_49"));
        sizePolicy5.setHeightForWidth(label_49->sizePolicy().hasHeightForWidth());
        label_49->setSizePolicy(sizePolicy5);

        horizontalLayout_27->addWidget(label_49);

        CGXi_TCP_Off_Y_r = new QLineEdit(groupBox_Config);
        CGXi_TCP_Off_Y_r->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Y_r"));
        sizePolicy7.setHeightForWidth(CGXi_TCP_Off_Y_r->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Y_r->setSizePolicy(sizePolicy7);

        horizontalLayout_27->addWidget(CGXi_TCP_Off_Y_r);


        gridLayout_14->addLayout(horizontalLayout_27, 0, 3, 1, 1);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(6);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        label_54 = new QLabel(groupBox_Config);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        sizePolicy5.setHeightForWidth(label_54->sizePolicy().hasHeightForWidth());
        label_54->setSizePolicy(sizePolicy5);

        horizontalLayout_33->addWidget(label_54);

        CGXi_Payload_CZ_r = new QLineEdit(groupBox_Config);
        CGXi_Payload_CZ_r->setObjectName(QString::fromUtf8("CGXi_Payload_CZ_r"));
        sizePolicy7.setHeightForWidth(CGXi_Payload_CZ_r->sizePolicy().hasHeightForWidth());
        CGXi_Payload_CZ_r->setSizePolicy(sizePolicy7);

        horizontalLayout_33->addWidget(CGXi_Payload_CZ_r);


        gridLayout_14->addLayout(horizontalLayout_33, 8, 3, 1, 1);

        CGXi_TCP_Off_X = new c_Fr_Light(groupBox_Config);
        CGXi_TCP_Off_X->setObjectName(QString::fromUtf8("CGXi_TCP_Off_X"));
        sizePolicy5.setHeightForWidth(CGXi_TCP_Off_X->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_X->setSizePolicy(sizePolicy5);
        CGXi_TCP_Off_X->setMinimumSize(QSize(20, 20));

        gridLayout_14->addWidget(CGXi_TCP_Off_X, 1, 0, 1, 1);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setSpacing(6);
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        label_69 = new QLabel(groupBox_Config);
        label_69->setObjectName(QString::fromUtf8("label_69"));
        sizePolicy5.setHeightForWidth(label_69->sizePolicy().hasHeightForWidth());
        label_69->setSizePolicy(sizePolicy5);

        horizontalLayout_45->addWidget(label_69);

        CGXi_TCP_Off_Rz_w = new QLineEdit(groupBox_Config);
        CGXi_TCP_Off_Rz_w->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Rz_w"));
        sizePolicy7.setHeightForWidth(CGXi_TCP_Off_Rz_w->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Rz_w->setSizePolicy(sizePolicy7);

        horizontalLayout_45->addWidget(CGXi_TCP_Off_Rz_w);


        gridLayout_14->addLayout(horizontalLayout_45, 7, 3, 1, 1);

        label_35 = new QLabel(groupBox_Config);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        sizePolicy5.setHeightForWidth(label_35->sizePolicy().hasHeightForWidth());
        label_35->setSizePolicy(sizePolicy5);

        gridLayout_14->addWidget(label_35, 4, 0, 1, 1);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setSpacing(6);
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        label_56 = new QLabel(groupBox_Config);
        label_56->setObjectName(QString::fromUtf8("label_56"));
        sizePolicy5.setHeightForWidth(label_56->sizePolicy().hasHeightForWidth());
        label_56->setSizePolicy(sizePolicy5);

        horizontalLayout_35->addWidget(label_56);

        CGXi_TCP_Off_Y_w = new QLineEdit(groupBox_Config);
        CGXi_TCP_Off_Y_w->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Y_w"));
        sizePolicy7.setHeightForWidth(CGXi_TCP_Off_Y_w->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Y_w->setSizePolicy(sizePolicy7);

        horizontalLayout_35->addWidget(CGXi_TCP_Off_Y_w);


        gridLayout_14->addLayout(horizontalLayout_35, 1, 3, 1, 1);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        label_57 = new QLabel(groupBox_Config);
        label_57->setObjectName(QString::fromUtf8("label_57"));
        sizePolicy5.setHeightForWidth(label_57->sizePolicy().hasHeightForWidth());
        label_57->setSizePolicy(sizePolicy5);

        horizontalLayout_36->addWidget(label_57);

        CGXi_TCP_Off_Z_w = new QLineEdit(groupBox_Config);
        CGXi_TCP_Off_Z_w->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Z_w"));
        sizePolicy7.setHeightForWidth(CGXi_TCP_Off_Z_w->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Z_w->setSizePolicy(sizePolicy7);

        horizontalLayout_36->addWidget(CGXi_TCP_Off_Z_w);


        gridLayout_14->addLayout(horizontalLayout_36, 5, 1, 1, 1);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        label_52 = new QLabel(groupBox_Config);
        label_52->setObjectName(QString::fromUtf8("label_52"));
        sizePolicy5.setHeightForWidth(label_52->sizePolicy().hasHeightForWidth());
        label_52->setSizePolicy(sizePolicy5);

        horizontalLayout_31->addWidget(label_52);

        CGXi_Payload_CX_r = new QLineEdit(groupBox_Config);
        CGXi_Payload_CX_r->setObjectName(QString::fromUtf8("CGXi_Payload_CX_r"));
        sizePolicy7.setHeightForWidth(CGXi_Payload_CX_r->sizePolicy().hasHeightForWidth());
        CGXi_Payload_CX_r->setSizePolicy(sizePolicy7);

        horizontalLayout_31->addWidget(CGXi_Payload_CX_r);


        gridLayout_14->addLayout(horizontalLayout_31, 13, 3, 1, 1);

        CGXi_Write_TCP = new QPushButton(groupBox_Config);
        CGXi_Write_TCP->setObjectName(QString::fromUtf8("CGXi_Write_TCP"));

        gridLayout_14->addWidget(CGXi_Write_TCP, 17, 0, 1, 2);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setSpacing(6);
        horizontalLayout_44->setObjectName(QString::fromUtf8("horizontalLayout_44"));
        label_68 = new QLabel(groupBox_Config);
        label_68->setObjectName(QString::fromUtf8("label_68"));
        sizePolicy5.setHeightForWidth(label_68->sizePolicy().hasHeightForWidth());
        label_68->setSizePolicy(sizePolicy5);

        horizontalLayout_44->addWidget(label_68);

        CGXi_TCP_Off_Rz_r = new QLineEdit(groupBox_Config);
        CGXi_TCP_Off_Rz_r->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Rz_r"));
        sizePolicy7.setHeightForWidth(CGXi_TCP_Off_Rz_r->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Rz_r->setSizePolicy(sizePolicy7);

        horizontalLayout_44->addWidget(CGXi_TCP_Off_Rz_r);


        gridLayout_14->addLayout(horizontalLayout_44, 6, 3, 1, 1);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setSpacing(6);
        horizontalLayout_40->setObjectName(QString::fromUtf8("horizontalLayout_40"));
        label_63 = new QLabel(groupBox_Config);
        label_63->setObjectName(QString::fromUtf8("label_63"));
        sizePolicy5.setHeightForWidth(label_63->sizePolicy().hasHeightForWidth());
        label_63->setSizePolicy(sizePolicy5);

        horizontalLayout_40->addWidget(label_63);

        CGXi_Payload_CY_w = new QLineEdit(groupBox_Config);
        CGXi_Payload_CY_w->setObjectName(QString::fromUtf8("CGXi_Payload_CY_w"));
        sizePolicy7.setHeightForWidth(CGXi_Payload_CY_w->sizePolicy().hasHeightForWidth());
        CGXi_Payload_CY_w->setSizePolicy(sizePolicy7);

        horizontalLayout_40->addWidget(CGXi_Payload_CY_w);


        gridLayout_14->addLayout(horizontalLayout_40, 14, 1, 1, 1);

        CGXi_TCP_Off_Rz = new c_Fr_Light(groupBox_Config);
        CGXi_TCP_Off_Rz->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Rz"));
        sizePolicy5.setHeightForWidth(CGXi_TCP_Off_Rz->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Rz->setSizePolicy(sizePolicy5);
        CGXi_TCP_Off_Rz->setMinimumSize(QSize(20, 20));

        gridLayout_14->addWidget(CGXi_TCP_Off_Rz, 7, 2, 1, 1);

        label_33 = new QLabel(groupBox_Config);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        sizePolicy5.setHeightForWidth(label_33->sizePolicy().hasHeightForWidth());
        label_33->setSizePolicy(sizePolicy5);

        gridLayout_14->addWidget(label_33, 0, 0, 1, 1);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setSpacing(6);
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        label_59 = new QLabel(groupBox_Config);
        label_59->setObjectName(QString::fromUtf8("label_59"));
        sizePolicy5.setHeightForWidth(label_59->sizePolicy().hasHeightForWidth());
        label_59->setSizePolicy(sizePolicy5);

        horizontalLayout_38->addWidget(label_59);

        CGXi_Payload_Mass_w = new QLineEdit(groupBox_Config);
        CGXi_Payload_Mass_w->setObjectName(QString::fromUtf8("CGXi_Payload_Mass_w"));
        sizePolicy7.setHeightForWidth(CGXi_Payload_Mass_w->sizePolicy().hasHeightForWidth());
        CGXi_Payload_Mass_w->setSizePolicy(sizePolicy7);

        horizontalLayout_38->addWidget(CGXi_Payload_Mass_w);


        gridLayout_14->addLayout(horizontalLayout_38, 12, 1, 1, 1);

        CGXi_Payload_CZ = new c_Fr_Light(groupBox_Config);
        CGXi_Payload_CZ->setObjectName(QString::fromUtf8("CGXi_Payload_CZ"));
        sizePolicy5.setHeightForWidth(CGXi_Payload_CZ->sizePolicy().hasHeightForWidth());
        CGXi_Payload_CZ->setSizePolicy(sizePolicy5);
        CGXi_Payload_CZ->setMinimumSize(QSize(20, 20));

        gridLayout_14->addWidget(CGXi_Payload_CZ, 12, 2, 1, 1);

        label_39 = new QLabel(groupBox_Config);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        sizePolicy5.setHeightForWidth(label_39->sizePolicy().hasHeightForWidth());
        label_39->setSizePolicy(sizePolicy5);

        gridLayout_14->addWidget(label_39, 8, 0, 1, 1);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setSpacing(6);
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        label_58 = new QLabel(groupBox_Config);
        label_58->setObjectName(QString::fromUtf8("label_58"));
        sizePolicy5.setHeightForWidth(label_58->sizePolicy().hasHeightForWidth());
        label_58->setSizePolicy(sizePolicy5);

        horizontalLayout_37->addWidget(label_58);

        CGXi_TCP_Off_Rx_w = new QLineEdit(groupBox_Config);
        CGXi_TCP_Off_Rx_w->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Rx_w"));
        sizePolicy7.setHeightForWidth(CGXi_TCP_Off_Rx_w->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Rx_w->setSizePolicy(sizePolicy7);

        horizontalLayout_37->addWidget(CGXi_TCP_Off_Rx_w);


        gridLayout_14->addLayout(horizontalLayout_37, 5, 3, 1, 1);

        CGXi_Write_Payload = new QPushButton(groupBox_Config);
        CGXi_Write_Payload->setObjectName(QString::fromUtf8("CGXi_Write_Payload"));

        gridLayout_14->addWidget(CGXi_Write_Payload, 17, 2, 1, 2);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setSpacing(6);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        label_55 = new QLabel(groupBox_Config);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        sizePolicy5.setHeightForWidth(label_55->sizePolicy().hasHeightForWidth());
        label_55->setSizePolicy(sizePolicy5);

        horizontalLayout_34->addWidget(label_55);

        CGXi_TCP_Off_X_w = new QLineEdit(groupBox_Config);
        CGXi_TCP_Off_X_w->setObjectName(QString::fromUtf8("CGXi_TCP_Off_X_w"));
        sizePolicy7.setHeightForWidth(CGXi_TCP_Off_X_w->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_X_w->setSizePolicy(sizePolicy7);

        horizontalLayout_34->addWidget(CGXi_TCP_Off_X_w);


        gridLayout_14->addLayout(horizontalLayout_34, 1, 1, 1, 1);

        label_41 = new QLabel(groupBox_Config);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        sizePolicy5.setHeightForWidth(label_41->sizePolicy().hasHeightForWidth());
        label_41->setSizePolicy(sizePolicy5);

        gridLayout_14->addWidget(label_41, 13, 0, 1, 1);

        CGXi_Payload_CY = new c_Fr_Light(groupBox_Config);
        CGXi_Payload_CY->setObjectName(QString::fromUtf8("CGXi_Payload_CY"));
        sizePolicy5.setHeightForWidth(CGXi_Payload_CY->sizePolicy().hasHeightForWidth());
        CGXi_Payload_CY->setSizePolicy(sizePolicy5);
        CGXi_Payload_CY->setMinimumSize(QSize(20, 20));

        gridLayout_14->addWidget(CGXi_Payload_CY, 14, 0, 1, 1);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        label_47 = new QLabel(groupBox_Config);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        sizePolicy5.setHeightForWidth(label_47->sizePolicy().hasHeightForWidth());
        label_47->setSizePolicy(sizePolicy5);

        horizontalLayout_26->addWidget(label_47);

        CGXi_TCP_Off_X_r = new QLineEdit(groupBox_Config);
        CGXi_TCP_Off_X_r->setObjectName(QString::fromUtf8("CGXi_TCP_Off_X_r"));
        sizePolicy7.setHeightForWidth(CGXi_TCP_Off_X_r->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_X_r->setSizePolicy(sizePolicy7);

        horizontalLayout_26->addWidget(CGXi_TCP_Off_X_r);


        gridLayout_14->addLayout(horizontalLayout_26, 0, 1, 1, 1);

        CGXi_TCP_Off_Z = new c_Fr_Light(groupBox_Config);
        CGXi_TCP_Off_Z->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Z"));
        sizePolicy5.setHeightForWidth(CGXi_TCP_Off_Z->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Z->setSizePolicy(sizePolicy5);
        CGXi_TCP_Off_Z->setMinimumSize(QSize(20, 20));

        gridLayout_14->addWidget(CGXi_TCP_Off_Z, 5, 0, 1, 1);

        CGXi_TCP_Off_Ry = new c_Fr_Light(groupBox_Config);
        CGXi_TCP_Off_Ry->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Ry"));
        sizePolicy5.setHeightForWidth(CGXi_TCP_Off_Ry->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Ry->setSizePolicy(sizePolicy5);
        CGXi_TCP_Off_Ry->setMinimumSize(QSize(20, 20));

        gridLayout_14->addWidget(CGXi_TCP_Off_Ry, 7, 0, 1, 1);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        label_50 = new QLabel(groupBox_Config);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        sizePolicy5.setHeightForWidth(label_50->sizePolicy().hasHeightForWidth());
        label_50->setSizePolicy(sizePolicy5);

        horizontalLayout_29->addWidget(label_50);

        CGXi_TCP_Off_Rx_r = new QLineEdit(groupBox_Config);
        CGXi_TCP_Off_Rx_r->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Rx_r"));
        sizePolicy7.setHeightForWidth(CGXi_TCP_Off_Rx_r->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Rx_r->setSizePolicy(sizePolicy7);

        horizontalLayout_29->addWidget(CGXi_TCP_Off_Rx_r);


        gridLayout_14->addLayout(horizontalLayout_29, 4, 3, 1, 1);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(6);
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        label_60 = new QLabel(groupBox_Config);
        label_60->setObjectName(QString::fromUtf8("label_60"));
        sizePolicy5.setHeightForWidth(label_60->sizePolicy().hasHeightForWidth());
        label_60->setSizePolicy(sizePolicy5);

        horizontalLayout_39->addWidget(label_60);

        CGXi_Payload_CX_w = new QLineEdit(groupBox_Config);
        CGXi_Payload_CX_w->setObjectName(QString::fromUtf8("CGXi_Payload_CX_w"));
        sizePolicy7.setHeightForWidth(CGXi_Payload_CX_w->sizePolicy().hasHeightForWidth());
        CGXi_Payload_CX_w->setSizePolicy(sizePolicy7);

        horizontalLayout_39->addWidget(CGXi_Payload_CX_w);


        gridLayout_14->addLayout(horizontalLayout_39, 14, 3, 1, 1);

        label_40 = new QLabel(groupBox_Config);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        sizePolicy5.setHeightForWidth(label_40->sizePolicy().hasHeightForWidth());
        label_40->setSizePolicy(sizePolicy5);

        gridLayout_14->addWidget(label_40, 13, 2, 1, 1);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setSpacing(6);
        horizontalLayout_42->setObjectName(QString::fromUtf8("horizontalLayout_42"));
        label_65 = new QLabel(groupBox_Config);
        label_65->setObjectName(QString::fromUtf8("label_65"));
        sizePolicy5.setHeightForWidth(label_65->sizePolicy().hasHeightForWidth());
        label_65->setSizePolicy(sizePolicy5);

        horizontalLayout_42->addWidget(label_65);

        CGXi_TCP_Off_Ry_r = new QLineEdit(groupBox_Config);
        CGXi_TCP_Off_Ry_r->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Ry_r"));
        sizePolicy7.setHeightForWidth(CGXi_TCP_Off_Ry_r->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Ry_r->setSizePolicy(sizePolicy7);

        horizontalLayout_42->addWidget(CGXi_TCP_Off_Ry_r);


        gridLayout_14->addLayout(horizontalLayout_42, 6, 1, 1, 1);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        label_51 = new QLabel(groupBox_Config);
        label_51->setObjectName(QString::fromUtf8("label_51"));
        sizePolicy5.setHeightForWidth(label_51->sizePolicy().hasHeightForWidth());
        label_51->setSizePolicy(sizePolicy5);

        horizontalLayout_30->addWidget(label_51);

        CGXi_Payload_Mass_r = new QLineEdit(groupBox_Config);
        CGXi_Payload_Mass_r->setObjectName(QString::fromUtf8("CGXi_Payload_Mass_r"));
        sizePolicy7.setHeightForWidth(CGXi_Payload_Mass_r->sizePolicy().hasHeightForWidth());
        CGXi_Payload_Mass_r->setSizePolicy(sizePolicy7);

        horizontalLayout_30->addWidget(CGXi_Payload_Mass_r);


        gridLayout_14->addLayout(horizontalLayout_30, 8, 1, 1, 1);

        CGXi_TCP_Off_Y = new c_Fr_Light(groupBox_Config);
        CGXi_TCP_Off_Y->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Y"));
        sizePolicy5.setHeightForWidth(CGXi_TCP_Off_Y->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Y->setSizePolicy(sizePolicy5);
        CGXi_TCP_Off_Y->setMinimumSize(QSize(20, 20));

        gridLayout_14->addWidget(CGXi_TCP_Off_Y, 1, 2, 1, 1);

        label_36 = new QLabel(groupBox_Config);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        sizePolicy5.setHeightForWidth(label_36->sizePolicy().hasHeightForWidth());
        label_36->setSizePolicy(sizePolicy5);

        gridLayout_14->addWidget(label_36, 4, 2, 1, 1);

        label_34 = new QLabel(groupBox_Config);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        sizePolicy5.setHeightForWidth(label_34->sizePolicy().hasHeightForWidth());
        label_34->setSizePolicy(sizePolicy5);

        gridLayout_14->addWidget(label_34, 0, 2, 1, 1);

        label_67 = new QLabel(groupBox_Config);
        label_67->setObjectName(QString::fromUtf8("label_67"));
        sizePolicy5.setHeightForWidth(label_67->sizePolicy().hasHeightForWidth());
        label_67->setSizePolicy(sizePolicy5);

        gridLayout_14->addWidget(label_67, 6, 2, 1, 1);

        CGXi_Payload_Mass = new c_Fr_Light(groupBox_Config);
        CGXi_Payload_Mass->setObjectName(QString::fromUtf8("CGXi_Payload_Mass"));
        sizePolicy5.setHeightForWidth(CGXi_Payload_Mass->sizePolicy().hasHeightForWidth());
        CGXi_Payload_Mass->setSizePolicy(sizePolicy5);
        CGXi_Payload_Mass->setMinimumSize(QSize(20, 20));

        gridLayout_14->addWidget(CGXi_Payload_Mass, 12, 0, 1, 1);

        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setSpacing(6);
        horizontalLayout_41->setObjectName(QString::fromUtf8("horizontalLayout_41"));
        label_61 = new QLabel(groupBox_Config);
        label_61->setObjectName(QString::fromUtf8("label_61"));
        sizePolicy5.setHeightForWidth(label_61->sizePolicy().hasHeightForWidth());
        label_61->setSizePolicy(sizePolicy5);

        horizontalLayout_41->addWidget(label_61);

        CGXi_Payload_CZ_w = new QLineEdit(groupBox_Config);
        CGXi_Payload_CZ_w->setObjectName(QString::fromUtf8("CGXi_Payload_CZ_w"));
        sizePolicy7.setHeightForWidth(CGXi_Payload_CZ_w->sizePolicy().hasHeightForWidth());
        CGXi_Payload_CZ_w->setSizePolicy(sizePolicy7);

        horizontalLayout_41->addWidget(CGXi_Payload_CZ_w);


        gridLayout_14->addLayout(horizontalLayout_41, 12, 3, 1, 1);

        CGXi_TCP_Off_Rx = new c_Fr_Light(groupBox_Config);
        CGXi_TCP_Off_Rx->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Rx"));
        sizePolicy5.setHeightForWidth(CGXi_TCP_Off_Rx->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Rx->setSizePolicy(sizePolicy5);
        CGXi_TCP_Off_Rx->setMinimumSize(QSize(20, 20));

        gridLayout_14->addWidget(CGXi_TCP_Off_Rx, 5, 2, 1, 1);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        label_48 = new QLabel(groupBox_Config);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        sizePolicy5.setHeightForWidth(label_48->sizePolicy().hasHeightForWidth());
        label_48->setSizePolicy(sizePolicy5);

        horizontalLayout_28->addWidget(label_48);

        CGXi_TCP_Off_Z_r = new QLineEdit(groupBox_Config);
        CGXi_TCP_Off_Z_r->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Z_r"));
        sizePolicy7.setHeightForWidth(CGXi_TCP_Off_Z_r->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Z_r->setSizePolicy(sizePolicy7);

        horizontalLayout_28->addWidget(CGXi_TCP_Off_Z_r);


        gridLayout_14->addLayout(horizontalLayout_28, 4, 1, 1, 1);

        CGXi_Payload_CX = new c_Fr_Light(groupBox_Config);
        CGXi_Payload_CX->setObjectName(QString::fromUtf8("CGXi_Payload_CX"));
        sizePolicy5.setHeightForWidth(CGXi_Payload_CX->sizePolicy().hasHeightForWidth());
        CGXi_Payload_CX->setSizePolicy(sizePolicy5);
        CGXi_Payload_CX->setMinimumSize(QSize(20, 20));

        gridLayout_14->addWidget(CGXi_Payload_CX, 14, 2, 1, 1);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setSpacing(6);
        horizontalLayout_43->setObjectName(QString::fromUtf8("horizontalLayout_43"));
        label_66 = new QLabel(groupBox_Config);
        label_66->setObjectName(QString::fromUtf8("label_66"));
        sizePolicy5.setHeightForWidth(label_66->sizePolicy().hasHeightForWidth());
        label_66->setSizePolicy(sizePolicy5);

        horizontalLayout_43->addWidget(label_66);

        CGXi_TCP_Off_Ry_w = new QLineEdit(groupBox_Config);
        CGXi_TCP_Off_Ry_w->setObjectName(QString::fromUtf8("CGXi_TCP_Off_Ry_w"));
        sizePolicy7.setHeightForWidth(CGXi_TCP_Off_Ry_w->sizePolicy().hasHeightForWidth());
        CGXi_TCP_Off_Ry_w->setSizePolicy(sizePolicy7);

        horizontalLayout_43->addWidget(CGXi_TCP_Off_Ry_w);


        gridLayout_14->addLayout(horizontalLayout_43, 7, 1, 1, 1);

        label_42 = new QLabel(groupBox_Config);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        sizePolicy5.setHeightForWidth(label_42->sizePolicy().hasHeightForWidth());
        label_42->setSizePolicy(sizePolicy5);

        gridLayout_14->addWidget(label_42, 8, 2, 1, 1);


        verticalLayout_2->addWidget(groupBox_Config);


        gridLayout_9->addLayout(verticalLayout_2, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget_Status = new QTabWidget(groupBox_3);
        tabWidget_Status->setObjectName(QString::fromUtf8("tabWidget_Status"));
        sizePolicy2.setHeightForWidth(tabWidget_Status->sizePolicy().hasHeightForWidth());
        tabWidget_Status->setSizePolicy(sizePolicy2);
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
        sizePolicy2.setHeightForWidth(tableWidget_Joint->sizePolicy().hasHeightForWidth());
        tableWidget_Joint->setSizePolicy(sizePolicy2);
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
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(tableWidget_Robot->sizePolicy().hasHeightForWidth());
        tableWidget_Robot->setSizePolicy(sizePolicy9);
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

        verticalLayout->addWidget(tabWidget_Status);

        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        CGXi_Log = new QTextBrowser(groupBox);
        CGXi_Log->setObjectName(QString::fromUtf8("CGXi_Log"));
        sizePolicy2.setHeightForWidth(CGXi_Log->sizePolicy().hasHeightForWidth());
        CGXi_Log->setSizePolicy(sizePolicy2);

        gridLayout_5->addWidget(CGXi_Log, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);


        gridLayout_9->addLayout(verticalLayout, 0, 1, 1, 1);


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
        horizontalLayout_50 = new QHBoxLayout();
        horizontalLayout_50->setSpacing(6);
        horizontalLayout_50->setObjectName(QString::fromUtf8("horizontalLayout_50"));
        label_120_IP = new QLabel(groupBox_8);
        label_120_IP->setObjectName(QString::fromUtf8("label_120_IP"));

        horizontalLayout_50->addWidget(label_120_IP);

        Pre_Scan_120_IP = new QLineEdit(groupBox_8);
        Pre_Scan_120_IP->setObjectName(QString::fromUtf8("Pre_Scan_120_IP"));

        horizontalLayout_50->addWidget(Pre_Scan_120_IP);

        label_120_Port = new QLabel(groupBox_8);
        label_120_Port->setObjectName(QString::fromUtf8("label_120_Port"));

        horizontalLayout_50->addWidget(label_120_Port);

        Pre_Scan_120_Port = new QLineEdit(groupBox_8);
        Pre_Scan_120_Port->setObjectName(QString::fromUtf8("Pre_Scan_120_Port"));
        Pre_Scan_120_Port->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_50->addWidget(Pre_Scan_120_Port);

        label_120_Monitor = new QLabel(groupBox_8);
        label_120_Monitor->setObjectName(QString::fromUtf8("label_120_Monitor"));

        horizontalLayout_50->addWidget(label_120_Monitor);

        Pre_Scan_120_Monitor_Port = new QLineEdit(groupBox_8);
        Pre_Scan_120_Monitor_Port->setObjectName(QString::fromUtf8("Pre_Scan_120_Monitor_Port"));
        Pre_Scan_120_Monitor_Port->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_50->addWidget(Pre_Scan_120_Monitor_Port);

        label_120_Tran = new QLabel(groupBox_8);
        label_120_Tran->setObjectName(QString::fromUtf8("label_120_Tran"));

        horizontalLayout_50->addWidget(label_120_Tran);

        Pre_Scan_120_Tran_Port = new QLineEdit(groupBox_8);
        Pre_Scan_120_Tran_Port->setObjectName(QString::fromUtf8("Pre_Scan_120_Tran_Port"));
        Pre_Scan_120_Tran_Port->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_50->addWidget(Pre_Scan_120_Tran_Port);

        Pre_Scan_120_Connect = new QPushButton(groupBox_8);
        Pre_Scan_120_Connect->setObjectName(QString::fromUtf8("Pre_Scan_120_Connect"));

        horizontalLayout_50->addWidget(Pre_Scan_120_Connect);

        Pre_Scan_120_Disconnect = new QPushButton(groupBox_8);
        Pre_Scan_120_Disconnect->setObjectName(QString::fromUtf8("Pre_Scan_120_Disconnect"));

        horizontalLayout_50->addWidget(Pre_Scan_120_Disconnect);


        gridLayout_24->addLayout(horizontalLayout_50, 0, 0, 1, 1);

        horizontalLayout_51 = new QHBoxLayout();
        horizontalLayout_51->setSpacing(6);
        horizontalLayout_51->setObjectName(QString::fromUtf8("horizontalLayout_51"));
        label_120_Remote_Status = new QLabel(groupBox_8);
        label_120_Remote_Status->setObjectName(QString::fromUtf8("label_120_Remote_Status"));

        horizontalLayout_51->addWidget(label_120_Remote_Status);

        Pre_Scan_120_Remote_Light = new c_Fr_Light(groupBox_8);
        Pre_Scan_120_Remote_Light->setObjectName(QString::fromUtf8("Pre_Scan_120_Remote_Light"));
        Pre_Scan_120_Remote_Light->setMinimumSize(QSize(16, 16));
        Pre_Scan_120_Remote_Light->setMaximumSize(QSize(16, 16));

        horizontalLayout_51->addWidget(Pre_Scan_120_Remote_Light);

        label_120_Monitor_Status = new QLabel(groupBox_8);
        label_120_Monitor_Status->setObjectName(QString::fromUtf8("label_120_Monitor_Status"));

        horizontalLayout_51->addWidget(label_120_Monitor_Status);

        Pre_Scan_120_Monitor_Light = new c_Fr_Light(groupBox_8);
        Pre_Scan_120_Monitor_Light->setObjectName(QString::fromUtf8("Pre_Scan_120_Monitor_Light"));
        Pre_Scan_120_Monitor_Light->setMinimumSize(QSize(16, 16));
        Pre_Scan_120_Monitor_Light->setMaximumSize(QSize(16, 16));

        horizontalLayout_51->addWidget(Pre_Scan_120_Monitor_Light);

        label_120_Tran_Status = new QLabel(groupBox_8);
        label_120_Tran_Status->setObjectName(QString::fromUtf8("label_120_Tran_Status"));

        horizontalLayout_51->addWidget(label_120_Tran_Status);

        Pre_Scan_120_Tran_Light = new c_Fr_Light(groupBox_8);
        Pre_Scan_120_Tran_Light->setObjectName(QString::fromUtf8("Pre_Scan_120_Tran_Light"));
        Pre_Scan_120_Tran_Light->setMinimumSize(QSize(16, 16));
        Pre_Scan_120_Tran_Light->setMaximumSize(QSize(16, 16));

        horizontalLayout_51->addWidget(Pre_Scan_120_Tran_Light);

        label_120_Listen_Status = new QLabel(groupBox_8);
        label_120_Listen_Status->setObjectName(QString::fromUtf8("label_120_Listen_Status"));

        horizontalLayout_51->addWidget(label_120_Listen_Status);

        Pre_Scan_120_Listen_Light = new c_Fr_Light(groupBox_8);
        Pre_Scan_120_Listen_Light->setObjectName(QString::fromUtf8("Pre_Scan_120_Listen_Light"));
        Pre_Scan_120_Listen_Light->setMinimumSize(QSize(16, 16));
        Pre_Scan_120_Listen_Light->setMaximumSize(QSize(16, 16));

        horizontalLayout_51->addWidget(Pre_Scan_120_Listen_Light);

        label_120_Client_Num = new QLabel(groupBox_8);
        label_120_Client_Num->setObjectName(QString::fromUtf8("label_120_Client_Num"));

        horizontalLayout_51->addWidget(label_120_Client_Num);

        Pre_Scan_120_Client_Num = new QLineEdit(groupBox_8);
        Pre_Scan_120_Client_Num->setObjectName(QString::fromUtf8("Pre_Scan_120_Client_Num"));
        Pre_Scan_120_Client_Num->setMaximumSize(QSize(40, 16777215));
        Pre_Scan_120_Client_Num->setReadOnly(true);

        horizontalLayout_51->addWidget(Pre_Scan_120_Client_Num);

        label_120_Cam_Num = new QLabel(groupBox_8);
        label_120_Cam_Num->setObjectName(QString::fromUtf8("label_120_Cam_Num"));

        horizontalLayout_51->addWidget(label_120_Cam_Num);

        Pre_Scan_120_Cam_Num = new QLineEdit(groupBox_8);
        Pre_Scan_120_Cam_Num->setObjectName(QString::fromUtf8("Pre_Scan_120_Cam_Num"));
        Pre_Scan_120_Cam_Num->setMaximumSize(QSize(40, 16777215));
        Pre_Scan_120_Cam_Num->setReadOnly(true);

        horizontalLayout_51->addWidget(Pre_Scan_120_Cam_Num);

        label_120_LastUpdate = new QLabel(groupBox_8);
        label_120_LastUpdate->setObjectName(QString::fromUtf8("label_120_LastUpdate"));

        horizontalLayout_51->addWidget(label_120_LastUpdate);

        Pre_Scan_120_LastUpdate = new QLineEdit(groupBox_8);
        Pre_Scan_120_LastUpdate->setObjectName(QString::fromUtf8("Pre_Scan_120_LastUpdate"));
        Pre_Scan_120_LastUpdate->setMaximumSize(QSize(140, 16777215));
        Pre_Scan_120_LastUpdate->setReadOnly(true);

        horizontalLayout_51->addWidget(Pre_Scan_120_LastUpdate);

        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_51->addItem(horizontalSpacer_30);


        gridLayout_24->addLayout(horizontalLayout_51, 1, 0, 1, 1);

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
        QSizePolicy sizePolicy10(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(label_120_TaskID->sizePolicy().hasHeightForWidth());
        label_120_TaskID->setSizePolicy(sizePolicy10);

        gridLayout_21->addWidget(label_120_TaskID, 0, 0, 1, 1);

        label_120_Wheelset = new QLabel(groupBox_Task_Info);
        label_120_Wheelset->setObjectName(QString::fromUtf8("label_120_Wheelset"));
        sizePolicy10.setHeightForWidth(label_120_Wheelset->sizePolicy().hasHeightForWidth());
        label_120_Wheelset->setSizePolicy(sizePolicy10);

        gridLayout_21->addWidget(label_120_Wheelset, 0, 11, 1, 1);

        r_Pre_Scan_120_TaskID = new QLineEdit(groupBox_Task_Info);
        r_Pre_Scan_120_TaskID->setObjectName(QString::fromUtf8("r_Pre_Scan_120_TaskID"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_TaskID->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_TaskID->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_TaskID->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_21->addWidget(r_Pre_Scan_120_TaskID, 0, 1, 1, 1);

        label_120_StartTime = new QLabel(groupBox_Task_Info);
        label_120_StartTime->setObjectName(QString::fromUtf8("label_120_StartTime"));
        sizePolicy10.setHeightForWidth(label_120_StartTime->sizePolicy().hasHeightForWidth());
        label_120_StartTime->setSizePolicy(sizePolicy10);

        gridLayout_21->addWidget(label_120_StartTime, 1, 0, 1, 1);

        r_Pre_Scan_120_Wheelset = new QLineEdit(groupBox_Task_Info);
        r_Pre_Scan_120_Wheelset->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Wheelset"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_Wheelset->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_Wheelset->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_Wheelset->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_21->addWidget(r_Pre_Scan_120_Wheelset, 0, 12, 1, 1);

        r_Pre_Scan_120_StartTime = new QLineEdit(groupBox_Task_Info);
        r_Pre_Scan_120_StartTime->setObjectName(QString::fromUtf8("r_Pre_Scan_120_StartTime"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_StartTime->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_StartTime->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_StartTime->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_21->addWidget(r_Pre_Scan_120_StartTime, 1, 1, 1, 1);

        r_Pre_Scan_120_Axle = new QLineEdit(groupBox_Task_Info);
        r_Pre_Scan_120_Axle->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Axle"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_Axle->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_Axle->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_Axle->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_21->addWidget(r_Pre_Scan_120_Axle, 1, 12, 1, 1);

        label_120_Axle = new QLabel(groupBox_Task_Info);
        label_120_Axle->setObjectName(QString::fromUtf8("label_120_Axle"));
        sizePolicy10.setHeightForWidth(label_120_Axle->sizePolicy().hasHeightForWidth());
        label_120_Axle->setSizePolicy(sizePolicy10);

        gridLayout_21->addWidget(label_120_Axle, 1, 11, 1, 1);

        label_120_Repair = new QLabel(groupBox_Task_Info);
        label_120_Repair->setObjectName(QString::fromUtf8("label_120_Repair"));
        sizePolicy10.setHeightForWidth(label_120_Repair->sizePolicy().hasHeightForWidth());
        label_120_Repair->setSizePolicy(sizePolicy10);

        gridLayout_21->addWidget(label_120_Repair, 2, 0, 1, 1);

        r_Pre_Scan_120_Repair = new QLineEdit(groupBox_Task_Info);
        r_Pre_Scan_120_Repair->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Repair"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_Repair->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_Repair->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_Repair->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_21->addWidget(r_Pre_Scan_120_Repair, 2, 1, 1, 1);

        label_120_SendUnit = new QLabel(groupBox_Task_Info);
        label_120_SendUnit->setObjectName(QString::fromUtf8("label_120_SendUnit"));
        sizePolicy10.setHeightForWidth(label_120_SendUnit->sizePolicy().hasHeightForWidth());
        label_120_SendUnit->setSizePolicy(sizePolicy10);

        gridLayout_21->addWidget(label_120_SendUnit, 2, 11, 1, 1);

        r_Pre_Scan_120_SendUnit = new QLineEdit(groupBox_Task_Info);
        r_Pre_Scan_120_SendUnit->setObjectName(QString::fromUtf8("r_Pre_Scan_120_SendUnit"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_SendUnit->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_SendUnit->setSizePolicy(sizePolicy7);
        r_Pre_Scan_120_SendUnit->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_21->addWidget(r_Pre_Scan_120_SendUnit, 2, 12, 1, 1);


        horizontalLayout_53->addWidget(groupBox_Task_Info);

        groupBox_Collect_Status = new QGroupBox(groupBox_8);
        groupBox_Collect_Status->setObjectName(QString::fromUtf8("groupBox_Collect_Status"));
        gridLayout_26 = new QGridLayout(groupBox_Collect_Status);
        gridLayout_26->setSpacing(6);
        gridLayout_26->setContentsMargins(11, 11, 11, 11);
        gridLayout_26->setObjectName(QString::fromUtf8("gridLayout_26"));
        label_120_Prog = new QLabel(groupBox_Collect_Status);
        label_120_Prog->setObjectName(QString::fromUtf8("label_120_Prog"));
        sizePolicy10.setHeightForWidth(label_120_Prog->sizePolicy().hasHeightForWidth());
        label_120_Prog->setSizePolicy(sizePolicy10);

        gridLayout_26->addWidget(label_120_Prog, 0, 0, 1, 1);

        r_Pre_Scan_120_currentWheelset = new QLineEdit(groupBox_Collect_Status);
        r_Pre_Scan_120_currentWheelset->setObjectName(QString::fromUtf8("r_Pre_Scan_120_currentWheelset"));

        gridLayout_26->addWidget(r_Pre_Scan_120_currentWheelset, 0, 1, 1, 1);

        label_120_Gain = new QLabel(groupBox_Collect_Status);
        label_120_Gain->setObjectName(QString::fromUtf8("label_120_Gain"));
        sizePolicy10.setHeightForWidth(label_120_Gain->sizePolicy().hasHeightForWidth());
        label_120_Gain->setSizePolicy(sizePolicy10);

        gridLayout_26->addWidget(label_120_Gain, 0, 2, 1, 1);

        r_Pre_Scan_120_Gain = new QLineEdit(groupBox_Collect_Status);
        r_Pre_Scan_120_Gain->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Gain"));
        QSizePolicy sizePolicy11(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(r_Pre_Scan_120_Gain->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_Gain->setSizePolicy(sizePolicy11);
        r_Pre_Scan_120_Gain->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_26->addWidget(r_Pre_Scan_120_Gain, 0, 3, 1, 1);

        label_120_Part1 = new QLabel(groupBox_Collect_Status);
        label_120_Part1->setObjectName(QString::fromUtf8("label_120_Part1"));
        sizePolicy10.setHeightForWidth(label_120_Part1->sizePolicy().hasHeightForWidth());
        label_120_Part1->setSizePolicy(sizePolicy10);

        gridLayout_26->addWidget(label_120_Part1, 1, 0, 1, 1);

        r_Pre_Scan_120_Part1 = new QLineEdit(groupBox_Collect_Status);
        r_Pre_Scan_120_Part1->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Part1"));

        gridLayout_26->addWidget(r_Pre_Scan_120_Part1, 1, 1, 1, 1);

        label_120_Part2 = new QLabel(groupBox_Collect_Status);
        label_120_Part2->setObjectName(QString::fromUtf8("label_120_Part2"));
        sizePolicy10.setHeightForWidth(label_120_Part2->sizePolicy().hasHeightForWidth());
        label_120_Part2->setSizePolicy(sizePolicy10);

        gridLayout_26->addWidget(label_120_Part2, 1, 2, 1, 1);

        r_Pre_Scan_120_Part2 = new QLineEdit(groupBox_Collect_Status);
        r_Pre_Scan_120_Part2->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Part2"));

        gridLayout_26->addWidget(r_Pre_Scan_120_Part2, 1, 3, 1, 1);

        label_120_Point = new QLabel(groupBox_Collect_Status);
        label_120_Point->setObjectName(QString::fromUtf8("label_120_Point"));
        sizePolicy10.setHeightForWidth(label_120_Point->sizePolicy().hasHeightForWidth());
        label_120_Point->setSizePolicy(sizePolicy10);

        gridLayout_26->addWidget(label_120_Point, 2, 0, 1, 1);

        r_Pre_Scan_120_Point = new QLineEdit(groupBox_Collect_Status);
        r_Pre_Scan_120_Point->setObjectName(QString::fromUtf8("r_Pre_Scan_120_Point"));

        gridLayout_26->addWidget(r_Pre_Scan_120_Point, 2, 1, 1, 1);


        horizontalLayout_53->addWidget(groupBox_Collect_Status);

        groupBox_Control = new QGroupBox(groupBox_8);
        groupBox_Control->setObjectName(QString::fromUtf8("groupBox_Control"));
        gridLayout_25 = new QGridLayout(groupBox_Control);
        gridLayout_25->setSpacing(6);
        gridLayout_25->setContentsMargins(11, 11, 11, 11);
        gridLayout_25->setObjectName(QString::fromUtf8("gridLayout_25"));
        Pre_Scan_120_Start_Scan = new QPushButton(groupBox_Control);
        Pre_Scan_120_Start_Scan->setObjectName(QString::fromUtf8("Pre_Scan_120_Start_Scan"));
        Pre_Scan_120_Start_Scan->setMinimumSize(QSize(100, 32));

        gridLayout_25->addWidget(Pre_Scan_120_Start_Scan, 0, 0, 1, 1);

        Pre_Scan_120_Collector = new QPushButton(groupBox_Control);
        Pre_Scan_120_Collector->setObjectName(QString::fromUtf8("Pre_Scan_120_Collector"));
        Pre_Scan_120_Collector->setMinimumSize(QSize(100, 32));

        gridLayout_25->addWidget(Pre_Scan_120_Collector, 0, 1, 1, 1);

        Pre_Scan_120_Finish_Scan = new QPushButton(groupBox_Control);
        Pre_Scan_120_Finish_Scan->setObjectName(QString::fromUtf8("Pre_Scan_120_Finish_Scan"));
        Pre_Scan_120_Finish_Scan->setMinimumSize(QSize(100, 32));

        gridLayout_25->addWidget(Pre_Scan_120_Finish_Scan, 1, 0, 1, 1);

        horizontalLayout_54 = new QHBoxLayout();
        horizontalLayout_54->setSpacing(6);
        horizontalLayout_54->setObjectName(QString::fromUtf8("horizontalLayout_54"));
        Pre_Scan_120_Gain_Spin = new QSpinBox(groupBox_Control);
        Pre_Scan_120_Gain_Spin->setObjectName(QString::fromUtf8("Pre_Scan_120_Gain_Spin"));
        Pre_Scan_120_Gain_Spin->setMinimum(0);
        Pre_Scan_120_Gain_Spin->setMaximum(100);
        Pre_Scan_120_Gain_Spin->setValue(20);

        horizontalLayout_54->addWidget(Pre_Scan_120_Gain_Spin);

        Pre_Scan_120_Change_Gain = new QPushButton(groupBox_Control);
        Pre_Scan_120_Change_Gain->setObjectName(QString::fromUtf8("Pre_Scan_120_Change_Gain"));

        horizontalLayout_54->addWidget(Pre_Scan_120_Change_Gain);


        gridLayout_25->addLayout(horizontalLayout_54, 1, 1, 1, 1);

        horizontalLayout_52 = new QHBoxLayout();
        horizontalLayout_52->setSpacing(6);
        horizontalLayout_52->setObjectName(QString::fromUtf8("horizontalLayout_52"));
        label_120_TotalImages = new QLabel(groupBox_Control);
        label_120_TotalImages->setObjectName(QString::fromUtf8("label_120_TotalImages"));
        sizePolicy3.setHeightForWidth(label_120_TotalImages->sizePolicy().hasHeightForWidth());
        label_120_TotalImages->setSizePolicy(sizePolicy3);

        horizontalLayout_52->addWidget(label_120_TotalImages);

        r_Pre_Scan_120_TotalImages = new QLineEdit(groupBox_Control);
        r_Pre_Scan_120_TotalImages->setObjectName(QString::fromUtf8("r_Pre_Scan_120_TotalImages"));
        sizePolicy7.setHeightForWidth(r_Pre_Scan_120_TotalImages->sizePolicy().hasHeightForWidth());
        r_Pre_Scan_120_TotalImages->setSizePolicy(sizePolicy7);

        horizontalLayout_52->addWidget(r_Pre_Scan_120_TotalImages);


        gridLayout_25->addLayout(horizontalLayout_52, 2, 0, 1, 2);

        horizontalLayout_56 = new QHBoxLayout();
        horizontalLayout_56->setSpacing(6);
        horizontalLayout_56->setObjectName(QString::fromUtf8("horizontalLayout_56"));
        label_120_WorkState = new QLabel(groupBox_Control);
        label_120_WorkState->setObjectName(QString::fromUtf8("label_120_WorkState"));
        sizePolicy3.setHeightForWidth(label_120_WorkState->sizePolicy().hasHeightForWidth());
        label_120_WorkState->setSizePolicy(sizePolicy3);

        horizontalLayout_56->addWidget(label_120_WorkState);

        Pre_Scan_120_WorkState = new QComboBox(groupBox_Control);
        Pre_Scan_120_WorkState->addItem(QString());
        Pre_Scan_120_WorkState->addItem(QString());
        Pre_Scan_120_WorkState->addItem(QString());
        Pre_Scan_120_WorkState->addItem(QString());
        Pre_Scan_120_WorkState->addItem(QString());
        Pre_Scan_120_WorkState->addItem(QString());
        Pre_Scan_120_WorkState->setObjectName(QString::fromUtf8("Pre_Scan_120_WorkState"));

        horizontalLayout_56->addWidget(Pre_Scan_120_WorkState);


        gridLayout_25->addLayout(horizontalLayout_56, 3, 0, 1, 2);


        horizontalLayout_53->addWidget(groupBox_Control);


        gridLayout_24->addLayout(horizontalLayout_53, 2, 0, 1, 1);

        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(6);
        horizontalLayout_49->setObjectName(QString::fromUtf8("horizontalLayout_49"));
        groupBox_Task_Info_2 = new QGroupBox(groupBox_8);
        groupBox_Task_Info_2->setObjectName(QString::fromUtf8("groupBox_Task_Info_2"));
        gridLayout_22 = new QGridLayout(groupBox_Task_Info_2);
        gridLayout_22->setSpacing(6);
        gridLayout_22->setContentsMargins(11, 11, 11, 11);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        w_Pre_Scan_120_TaskID = new QLineEdit(groupBox_Task_Info_2);
        w_Pre_Scan_120_TaskID->setObjectName(QString::fromUtf8("w_Pre_Scan_120_TaskID"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_TaskID->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_TaskID->setSizePolicy(sizePolicy11);

        gridLayout_22->addWidget(w_Pre_Scan_120_TaskID, 0, 2, 2, 1);

        w_Pre_Scan_120_SendUnit = new QLineEdit(groupBox_Task_Info_2);
        w_Pre_Scan_120_SendUnit->setObjectName(QString::fromUtf8("w_Pre_Scan_120_SendUnit"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_SendUnit->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_SendUnit->setSizePolicy(sizePolicy11);
        w_Pre_Scan_120_SendUnit->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_22->addWidget(w_Pre_Scan_120_SendUnit, 3, 2, 1, 1);

        label_120_Wheelset_2 = new QLabel(groupBox_Task_Info_2);
        label_120_Wheelset_2->setObjectName(QString::fromUtf8("label_120_Wheelset_2"));
        sizePolicy3.setHeightForWidth(label_120_Wheelset_2->sizePolicy().hasHeightForWidth());
        label_120_Wheelset_2->setSizePolicy(sizePolicy3);

        gridLayout_22->addWidget(label_120_Wheelset_2, 0, 4, 1, 1);

        w_Pre_Scan_120_StartTime = new QLineEdit(groupBox_Task_Info_2);
        w_Pre_Scan_120_StartTime->setObjectName(QString::fromUtf8("w_Pre_Scan_120_StartTime"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_StartTime->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_StartTime->setSizePolicy(sizePolicy11);

        gridLayout_22->addWidget(w_Pre_Scan_120_StartTime, 4, 5, 1, 1);

        w_Pre_Scan_120_Repair = new QLineEdit(groupBox_Task_Info_2);
        w_Pre_Scan_120_Repair->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Repair"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Repair->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Repair->setSizePolicy(sizePolicy11);
        w_Pre_Scan_120_Repair->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_22->addWidget(w_Pre_Scan_120_Repair, 4, 2, 1, 1);

        label_120_Repair_2 = new QLabel(groupBox_Task_Info_2);
        label_120_Repair_2->setObjectName(QString::fromUtf8("label_120_Repair_2"));
        sizePolicy3.setHeightForWidth(label_120_Repair_2->sizePolicy().hasHeightForWidth());
        label_120_Repair_2->setSizePolicy(sizePolicy3);

        gridLayout_22->addWidget(label_120_Repair_2, 4, 0, 1, 1);

        label_120_SendUnit_2 = new QLabel(groupBox_Task_Info_2);
        label_120_SendUnit_2->setObjectName(QString::fromUtf8("label_120_SendUnit_2"));
        sizePolicy3.setHeightForWidth(label_120_SendUnit_2->sizePolicy().hasHeightForWidth());
        label_120_SendUnit_2->setSizePolicy(sizePolicy3);

        gridLayout_22->addWidget(label_120_SendUnit_2, 4, 4, 1, 1);

        label_120_StartTime_2 = new QLabel(groupBox_Task_Info_2);
        label_120_StartTime_2->setObjectName(QString::fromUtf8("label_120_StartTime_2"));
        sizePolicy3.setHeightForWidth(label_120_StartTime_2->sizePolicy().hasHeightForWidth());
        label_120_StartTime_2->setSizePolicy(sizePolicy3);

        gridLayout_22->addWidget(label_120_StartTime_2, 3, 0, 1, 1);

        label_120_Axle_2 = new QLabel(groupBox_Task_Info_2);
        label_120_Axle_2->setObjectName(QString::fromUtf8("label_120_Axle_2"));
        sizePolicy3.setHeightForWidth(label_120_Axle_2->sizePolicy().hasHeightForWidth());
        label_120_Axle_2->setSizePolicy(sizePolicy3);

        gridLayout_22->addWidget(label_120_Axle_2, 3, 4, 1, 1);

        label_120_TaskID_2 = new QLabel(groupBox_Task_Info_2);
        label_120_TaskID_2->setObjectName(QString::fromUtf8("label_120_TaskID_2"));
        sizePolicy3.setHeightForWidth(label_120_TaskID_2->sizePolicy().hasHeightForWidth());
        label_120_TaskID_2->setSizePolicy(sizePolicy3);

        gridLayout_22->addWidget(label_120_TaskID_2, 0, 0, 2, 1);

        w_Pre_Scan_120_Wheelset = new QLineEdit(groupBox_Task_Info_2);
        w_Pre_Scan_120_Wheelset->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Wheelset"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Wheelset->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Wheelset->setSizePolicy(sizePolicy11);
        w_Pre_Scan_120_Wheelset->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_22->addWidget(w_Pre_Scan_120_Wheelset, 0, 5, 1, 1);

        w_Pre_Scan_120_Axle = new QLineEdit(groupBox_Task_Info_2);
        w_Pre_Scan_120_Axle->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Axle"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Axle->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Axle->setSizePolicy(sizePolicy11);
        w_Pre_Scan_120_Axle->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_22->addWidget(w_Pre_Scan_120_Axle, 3, 5, 1, 1);

        set_Pre_Scan_120_TaskID = new QPushButton(groupBox_Task_Info_2);
        set_Pre_Scan_120_TaskID->setObjectName(QString::fromUtf8("set_Pre_Scan_120_TaskID"));
        sizePolicy8.setHeightForWidth(set_Pre_Scan_120_TaskID->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_TaskID->setSizePolicy(sizePolicy8);

        gridLayout_22->addWidget(set_Pre_Scan_120_TaskID, 0, 3, 1, 1);

        set_Pre_Scan_120_SendUnit = new QPushButton(groupBox_Task_Info_2);
        set_Pre_Scan_120_SendUnit->setObjectName(QString::fromUtf8("set_Pre_Scan_120_SendUnit"));
        sizePolicy8.setHeightForWidth(set_Pre_Scan_120_SendUnit->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_SendUnit->setSizePolicy(sizePolicy8);

        gridLayout_22->addWidget(set_Pre_Scan_120_SendUnit, 3, 3, 1, 1);

        set_Pre_Scan_120_Repair = new QPushButton(groupBox_Task_Info_2);
        set_Pre_Scan_120_Repair->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Repair"));
        sizePolicy8.setHeightForWidth(set_Pre_Scan_120_Repair->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Repair->setSizePolicy(sizePolicy8);

        gridLayout_22->addWidget(set_Pre_Scan_120_Repair, 4, 3, 1, 1);

        set_Pre_Scan_120_Wheelset = new QPushButton(groupBox_Task_Info_2);
        set_Pre_Scan_120_Wheelset->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Wheelset"));
        sizePolicy8.setHeightForWidth(set_Pre_Scan_120_Wheelset->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Wheelset->setSizePolicy(sizePolicy8);

        gridLayout_22->addWidget(set_Pre_Scan_120_Wheelset, 0, 6, 1, 1);

        set_Pre_Scan_120_Axle = new QPushButton(groupBox_Task_Info_2);
        set_Pre_Scan_120_Axle->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Axle"));
        sizePolicy8.setHeightForWidth(set_Pre_Scan_120_Axle->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Axle->setSizePolicy(sizePolicy8);

        gridLayout_22->addWidget(set_Pre_Scan_120_Axle, 3, 6, 1, 1);

        set_Pre_Scan_120_StartTime = new QPushButton(groupBox_Task_Info_2);
        set_Pre_Scan_120_StartTime->setObjectName(QString::fromUtf8("set_Pre_Scan_120_StartTime"));
        sizePolicy8.setHeightForWidth(set_Pre_Scan_120_StartTime->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_StartTime->setSizePolicy(sizePolicy8);

        gridLayout_22->addWidget(set_Pre_Scan_120_StartTime, 4, 6, 1, 1);


        horizontalLayout_49->addWidget(groupBox_Task_Info_2);

        groupBox_Collect_Status_2 = new QGroupBox(groupBox_8);
        groupBox_Collect_Status_2->setObjectName(QString::fromUtf8("groupBox_Collect_Status_2"));
        gridLayout_102 = new QGridLayout(groupBox_Collect_Status_2);
        gridLayout_102->setSpacing(6);
        gridLayout_102->setContentsMargins(11, 11, 11, 11);
        gridLayout_102->setObjectName(QString::fromUtf8("gridLayout_102"));
        label_120_Gain_2 = new QLabel(groupBox_Collect_Status_2);
        label_120_Gain_2->setObjectName(QString::fromUtf8("label_120_Gain_2"));
        sizePolicy3.setHeightForWidth(label_120_Gain_2->sizePolicy().hasHeightForWidth());
        label_120_Gain_2->setSizePolicy(sizePolicy3);

        gridLayout_102->addWidget(label_120_Gain_2, 0, 3, 1, 1);

        w_Pre_Scan_120_Point = new QLineEdit(groupBox_Collect_Status_2);
        w_Pre_Scan_120_Point->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Point"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Point->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Point->setSizePolicy(sizePolicy11);

        gridLayout_102->addWidget(w_Pre_Scan_120_Point, 2, 1, 1, 1);

        set_Pre_Scan_120_Part1 = new QPushButton(groupBox_Collect_Status_2);
        set_Pre_Scan_120_Part1->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Part1"));
        sizePolicy8.setHeightForWidth(set_Pre_Scan_120_Part1->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Part1->setSizePolicy(sizePolicy8);

        gridLayout_102->addWidget(set_Pre_Scan_120_Part1, 1, 2, 1, 1);

        set_Pre_Scan_120_Point = new QPushButton(groupBox_Collect_Status_2);
        set_Pre_Scan_120_Point->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Point"));
        sizePolicy8.setHeightForWidth(set_Pre_Scan_120_Point->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Point->setSizePolicy(sizePolicy8);

        gridLayout_102->addWidget(set_Pre_Scan_120_Point, 2, 2, 1, 1);

        w_Pre_Scan_120_Part1 = new QLineEdit(groupBox_Collect_Status_2);
        w_Pre_Scan_120_Part1->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Part1"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Part1->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Part1->setSizePolicy(sizePolicy11);

        gridLayout_102->addWidget(w_Pre_Scan_120_Part1, 1, 1, 1, 1);

        label_120_Part2_2 = new QLabel(groupBox_Collect_Status_2);
        label_120_Part2_2->setObjectName(QString::fromUtf8("label_120_Part2_2"));
        sizePolicy3.setHeightForWidth(label_120_Part2_2->sizePolicy().hasHeightForWidth());
        label_120_Part2_2->setSizePolicy(sizePolicy3);

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
        sizePolicy3.setHeightForWidth(label_120_Point_2->sizePolicy().hasHeightForWidth());
        label_120_Point_2->setSizePolicy(sizePolicy3);

        gridLayout_102->addWidget(label_120_Point_2, 2, 0, 1, 1);

        w_Pre_Scan_120_Gain = new QLineEdit(groupBox_Collect_Status_2);
        w_Pre_Scan_120_Gain->setObjectName(QString::fromUtf8("w_Pre_Scan_120_Gain"));
        sizePolicy11.setHeightForWidth(w_Pre_Scan_120_Gain->sizePolicy().hasHeightForWidth());
        w_Pre_Scan_120_Gain->setSizePolicy(sizePolicy11);

        gridLayout_102->addWidget(w_Pre_Scan_120_Gain, 0, 4, 1, 1);

        set_Pre_Scan_120_Gain = new QPushButton(groupBox_Collect_Status_2);
        set_Pre_Scan_120_Gain->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Gain"));
        sizePolicy8.setHeightForWidth(set_Pre_Scan_120_Gain->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Gain->setSizePolicy(sizePolicy8);

        gridLayout_102->addWidget(set_Pre_Scan_120_Gain, 0, 5, 1, 1);

        label_120_Prog_2 = new QLabel(groupBox_Collect_Status_2);
        label_120_Prog_2->setObjectName(QString::fromUtf8("label_120_Prog_2"));
        sizePolicy3.setHeightForWidth(label_120_Prog_2->sizePolicy().hasHeightForWidth());
        label_120_Prog_2->setSizePolicy(sizePolicy3);

        gridLayout_102->addWidget(label_120_Prog_2, 0, 0, 1, 1);

        set_Pre_Scan_120_currentWheelset = new QPushButton(groupBox_Collect_Status_2);
        set_Pre_Scan_120_currentWheelset->setObjectName(QString::fromUtf8("set_Pre_Scan_120_currentWheelset"));
        sizePolicy8.setHeightForWidth(set_Pre_Scan_120_currentWheelset->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_currentWheelset->setSizePolicy(sizePolicy8);

        gridLayout_102->addWidget(set_Pre_Scan_120_currentWheelset, 0, 2, 1, 1);

        set_Pre_Scan_120_Part2 = new QPushButton(groupBox_Collect_Status_2);
        set_Pre_Scan_120_Part2->setObjectName(QString::fromUtf8("set_Pre_Scan_120_Part2"));
        sizePolicy8.setHeightForWidth(set_Pre_Scan_120_Part2->sizePolicy().hasHeightForWidth());
        set_Pre_Scan_120_Part2->setSizePolicy(sizePolicy8);

        gridLayout_102->addWidget(set_Pre_Scan_120_Part2, 1, 5, 1, 1);

        label_120_Part1_2 = new QLabel(groupBox_Collect_Status_2);
        label_120_Part1_2->setObjectName(QString::fromUtf8("label_120_Part1_2"));
        sizePolicy3.setHeightForWidth(label_120_Part1_2->sizePolicy().hasHeightForWidth());
        label_120_Part1_2->setSizePolicy(sizePolicy3);

        gridLayout_102->addWidget(label_120_Part1_2, 1, 0, 1, 1);


        horizontalLayout_49->addWidget(groupBox_Collect_Status_2);


        gridLayout_24->addLayout(horizontalLayout_49, 3, 0, 1, 1);

        groupBox_9 = new QGroupBox(groupBox_8);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        gridLayout_23 = new QGridLayout(groupBox_9);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        Prec_Scan_120_Cmd = new QTextEdit(groupBox_9);
        Prec_Scan_120_Cmd->setObjectName(QString::fromUtf8("Prec_Scan_120_Cmd"));
        Prec_Scan_120_Cmd->setReadOnly(true);

        gridLayout_23->addWidget(Prec_Scan_120_Cmd, 0, 0, 1, 1);


        gridLayout_24->addWidget(groupBox_9, 4, 0, 1, 1);

        groupBox_MySql = new QGroupBox(groupBox_8);
        groupBox_MySql->setObjectName(QString::fromUtf8("groupBox_MySql"));
        horizontalLayout_55 = new QHBoxLayout(groupBox_MySql);
        horizontalLayout_55->setSpacing(6);
        horizontalLayout_55->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_55->setObjectName(QString::fromUtf8("horizontalLayout_55"));
        label_120_MySql_Status = new QLabel(groupBox_MySql);
        label_120_MySql_Status->setObjectName(QString::fromUtf8("label_120_MySql_Status"));

        horizontalLayout_55->addWidget(label_120_MySql_Status);

        Pre_Scan_120_MySql_Light = new c_Fr_Light(groupBox_MySql);
        Pre_Scan_120_MySql_Light->setObjectName(QString::fromUtf8("Pre_Scan_120_MySql_Light"));
        Pre_Scan_120_MySql_Light->setMinimumSize(QSize(16, 16));
        Pre_Scan_120_MySql_Light->setMaximumSize(QSize(16, 16));

        horizontalLayout_55->addWidget(Pre_Scan_120_MySql_Light);

        Pre_Scan_120_MySql_Server = new QLineEdit(groupBox_MySql);
        Pre_Scan_120_MySql_Server->setObjectName(QString::fromUtf8("Pre_Scan_120_MySql_Server"));
        Pre_Scan_120_MySql_Server->setMaximumSize(QSize(120, 16777215));
        Pre_Scan_120_MySql_Server->setReadOnly(true);

        horizontalLayout_55->addWidget(Pre_Scan_120_MySql_Server);

        label_167 = new QLabel(groupBox_MySql);
        label_167->setObjectName(QString::fromUtf8("label_167"));
        sizePolicy7.setHeightForWidth(label_167->sizePolicy().hasHeightForWidth());
        label_167->setSizePolicy(sizePolicy7);

        horizontalLayout_55->addWidget(label_167);

        MySql_Port = new QLineEdit(groupBox_MySql);
        MySql_Port->setObjectName(QString::fromUtf8("MySql_Port"));
        sizePolicy11.setHeightForWidth(MySql_Port->sizePolicy().hasHeightForWidth());
        MySql_Port->setSizePolicy(sizePolicy11);

        horizontalLayout_55->addWidget(MySql_Port);

        label_156 = new QLabel(groupBox_MySql);
        label_156->setObjectName(QString::fromUtf8("label_156"));
        sizePolicy7.setHeightForWidth(label_156->sizePolicy().hasHeightForWidth());
        label_156->setSizePolicy(sizePolicy7);

        horizontalLayout_55->addWidget(label_156);

        MySql_User = new QLineEdit(groupBox_MySql);
        MySql_User->setObjectName(QString::fromUtf8("MySql_User"));
        sizePolicy11.setHeightForWidth(MySql_User->sizePolicy().hasHeightForWidth());
        MySql_User->setSizePolicy(sizePolicy11);

        horizontalLayout_55->addWidget(MySql_User);

        label_149 = new QLabel(groupBox_MySql);
        label_149->setObjectName(QString::fromUtf8("label_149"));

        horizontalLayout_55->addWidget(label_149);

        MySql_Password = new QLineEdit(groupBox_MySql);
        MySql_Password->setObjectName(QString::fromUtf8("MySql_Password"));

        horizontalLayout_55->addWidget(MySql_Password);

        label_148 = new QLabel(groupBox_MySql);
        label_148->setObjectName(QString::fromUtf8("label_148"));

        horizontalLayout_55->addWidget(label_148);

        MySql_Database = new QLineEdit(groupBox_MySql);
        MySql_Database->setObjectName(QString::fromUtf8("MySql_Database"));

        horizontalLayout_55->addWidget(MySql_Database);

        Pre_Scan_120_MySql_Reconnect = new QPushButton(groupBox_MySql);
        Pre_Scan_120_MySql_Reconnect->setObjectName(QString::fromUtf8("Pre_Scan_120_MySql_Reconnect"));

        horizontalLayout_55->addWidget(Pre_Scan_120_MySql_Reconnect);

        horizontalSpacer_31 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_55->addItem(horizontalSpacer_31);


        gridLayout_24->addWidget(groupBox_MySql, 5, 0, 1, 1);

        groupBox_Log = new QGroupBox(groupBox_8);
        groupBox_Log->setObjectName(QString::fromUtf8("groupBox_Log"));
        verticalLayout_24 = new QVBoxLayout(groupBox_Log);
        verticalLayout_24->setSpacing(6);
        verticalLayout_24->setContentsMargins(11, 11, 11, 11);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        Pre_Scan_120_Log = new QTextEdit(groupBox_Log);
        Pre_Scan_120_Log->setObjectName(QString::fromUtf8("Pre_Scan_120_Log"));
        Pre_Scan_120_Log->setReadOnly(true);

        verticalLayout_24->addWidget(Pre_Scan_120_Log);


        gridLayout_24->addWidget(groupBox_Log, 6, 0, 1, 1);


        gridLayout_20->addWidget(groupBox_8, 0, 0, 1, 1);

        stackedWidget->addWidget(Pre_Scan_120_Widget);
        Magic_Widget = new QWidget();
        Magic_Widget->setObjectName(QString::fromUtf8("Magic_Widget"));
        gridLayout_10 = new QGridLayout(Magic_Widget);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        groupBox_7 = new QGroupBox(Magic_Widget);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout_2 = new QGridLayout(groupBox_7);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_Connect = new QGroupBox(groupBox_7);
        groupBox_Connect->setObjectName(QString::fromUtf8("groupBox_Connect"));
        sizePolicy.setHeightForWidth(groupBox_Connect->sizePolicy().hasHeightForWidth());
        groupBox_Connect->setSizePolicy(sizePolicy);
        horizontalLayout_Connect = new QHBoxLayout(groupBox_Connect);
        horizontalLayout_Connect->setSpacing(6);
        horizontalLayout_Connect->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_Connect->setObjectName(QString::fromUtf8("horizontalLayout_Connect"));
        label_IP = new QLabel(groupBox_Connect);
        label_IP->setObjectName(QString::fromUtf8("label_IP"));

        horizontalLayout_Connect->addWidget(label_IP);

        Magic_IP = new QLineEdit(groupBox_Connect);
        Magic_IP->setObjectName(QString::fromUtf8("Magic_IP"));
        sizePolicy7.setHeightForWidth(Magic_IP->sizePolicy().hasHeightForWidth());
        Magic_IP->setSizePolicy(sizePolicy7);

        horizontalLayout_Connect->addWidget(Magic_IP);

        label_Port = new QLabel(groupBox_Connect);
        label_Port->setObjectName(QString::fromUtf8("label_Port"));

        horizontalLayout_Connect->addWidget(label_Port);

        Magic_Port = new QLineEdit(groupBox_Connect);
        Magic_Port->setObjectName(QString::fromUtf8("Magic_Port"));
        sizePolicy7.setHeightForWidth(Magic_Port->sizePolicy().hasHeightForWidth());
        Magic_Port->setSizePolicy(sizePolicy7);

        horizontalLayout_Connect->addWidget(Magic_Port);

        label_User = new QLabel(groupBox_Connect);
        label_User->setObjectName(QString::fromUtf8("label_User"));

        horizontalLayout_Connect->addWidget(label_User);

        Magic_User = new QLineEdit(groupBox_Connect);
        Magic_User->setObjectName(QString::fromUtf8("Magic_User"));
        sizePolicy7.setHeightForWidth(Magic_User->sizePolicy().hasHeightForWidth());
        Magic_User->setSizePolicy(sizePolicy7);

        horizontalLayout_Connect->addWidget(Magic_User);

        label_Pass = new QLabel(groupBox_Connect);
        label_Pass->setObjectName(QString::fromUtf8("label_Pass"));

        horizontalLayout_Connect->addWidget(label_Pass);

        Magic_Pass = new QLineEdit(groupBox_Connect);
        Magic_Pass->setObjectName(QString::fromUtf8("Magic_Pass"));
        sizePolicy7.setHeightForWidth(Magic_Pass->sizePolicy().hasHeightForWidth());
        Magic_Pass->setSizePolicy(sizePolicy7);
        Magic_Pass->setEchoMode(QLineEdit::Normal);

        horizontalLayout_Connect->addWidget(Magic_Pass);

        pushButton_Connect = new QPushButton(groupBox_Connect);
        pushButton_Connect->setObjectName(QString::fromUtf8("pushButton_Connect"));
        sizePolicy7.setHeightForWidth(pushButton_Connect->sizePolicy().hasHeightForWidth());
        pushButton_Connect->setSizePolicy(sizePolicy7);

        horizontalLayout_Connect->addWidget(pushButton_Connect);

        pushButton_Login = new QPushButton(groupBox_Connect);
        pushButton_Login->setObjectName(QString::fromUtf8("pushButton_Login"));
        sizePolicy7.setHeightForWidth(pushButton_Login->sizePolicy().hasHeightForWidth());
        pushButton_Login->setSizePolicy(sizePolicy7);

        horizontalLayout_Connect->addWidget(pushButton_Login);

        pushButton_Disconnect = new QPushButton(groupBox_Connect);
        pushButton_Disconnect->setObjectName(QString::fromUtf8("pushButton_Disconnect"));
        sizePolicy7.setHeightForWidth(pushButton_Disconnect->sizePolicy().hasHeightForWidth());
        pushButton_Disconnect->setSizePolicy(sizePolicy7);

        horizontalLayout_Connect->addWidget(pushButton_Disconnect);

        label_MAC = new QLabel(groupBox_Connect);
        label_MAC->setObjectName(QString::fromUtf8("label_MAC"));
        sizePolicy3.setHeightForWidth(label_MAC->sizePolicy().hasHeightForWidth());
        label_MAC->setSizePolicy(sizePolicy3);

        horizontalLayout_Connect->addWidget(label_MAC);

        lineEdit_MAC = new QLineEdit(groupBox_Connect);
        lineEdit_MAC->setObjectName(QString::fromUtf8("lineEdit_MAC"));
        sizePolicy11.setHeightForWidth(lineEdit_MAC->sizePolicy().hasHeightForWidth());
        lineEdit_MAC->setSizePolicy(sizePolicy11);
        lineEdit_MAC->setReadOnly(true);

        horizontalLayout_Connect->addWidget(lineEdit_MAC);

        label_ConnStatus = new QLabel(groupBox_Connect);
        label_ConnStatus->setObjectName(QString::fromUtf8("label_ConnStatus"));

        horizontalLayout_Connect->addWidget(label_ConnStatus);

        light_Connected = new c_Fr_Light(groupBox_Connect);
        light_Connected->setObjectName(QString::fromUtf8("light_Connected"));
        light_Connected->setMinimumSize(QSize(20, 20));

        horizontalLayout_Connect->addWidget(light_Connected);

        label_Ready = new QLabel(groupBox_Connect);
        label_Ready->setObjectName(QString::fromUtf8("label_Ready"));

        horizontalLayout_Connect->addWidget(label_Ready);

        light_Ready = new c_Fr_Light(groupBox_Connect);
        light_Ready->setObjectName(QString::fromUtf8("light_Ready"));
        light_Ready->setMinimumSize(QSize(20, 20));

        horizontalLayout_Connect->addWidget(light_Ready);

        label_Localized = new QLabel(groupBox_Connect);
        label_Localized->setObjectName(QString::fromUtf8("label_Localized"));

        horizontalLayout_Connect->addWidget(label_Localized);

        light_Localized = new c_Fr_Light(groupBox_Connect);
        light_Localized->setObjectName(QString::fromUtf8("light_Localized"));
        light_Localized->setMinimumSize(QSize(20, 20));

        horizontalLayout_Connect->addWidget(light_Localized);

        label_Charging = new QLabel(groupBox_Connect);
        label_Charging->setObjectName(QString::fromUtf8("label_Charging"));

        horizontalLayout_Connect->addWidget(label_Charging);

        light_Charging = new c_Fr_Light(groupBox_Connect);
        light_Charging->setObjectName(QString::fromUtf8("light_Charging"));
        light_Charging->setMinimumSize(QSize(20, 20));

        horizontalLayout_Connect->addWidget(light_Charging);

        label_Task = new QLabel(groupBox_Connect);
        label_Task->setObjectName(QString::fromUtf8("label_Task"));

        horizontalLayout_Connect->addWidget(label_Task);

        light_Task = new c_Fr_Light(groupBox_Connect);
        light_Task->setObjectName(QString::fromUtf8("light_Task"));
        light_Task->setMinimumSize(QSize(20, 20));

        horizontalLayout_Connect->addWidget(light_Task);

        label_Lidar = new QLabel(groupBox_Connect);
        label_Lidar->setObjectName(QString::fromUtf8("label_Lidar"));

        horizontalLayout_Connect->addWidget(label_Lidar);

        light_Lidar = new c_Fr_Light(groupBox_Connect);
        light_Lidar->setObjectName(QString::fromUtf8("light_Lidar"));
        light_Lidar->setMinimumSize(QSize(20, 20));

        horizontalLayout_Connect->addWidget(light_Lidar);

        label_I = new QLabel(groupBox_Connect);
        label_I->setObjectName(QString::fromUtf8("label_I"));

        horizontalLayout_Connect->addWidget(label_I);

        light_IMU = new c_Fr_Light(groupBox_Connect);
        light_IMU->setObjectName(QString::fromUtf8("light_IMU"));
        light_IMU->setMinimumSize(QSize(20, 20));

        horizontalLayout_Connect->addWidget(light_IMU);

        label_O = new QLabel(groupBox_Connect);
        label_O->setObjectName(QString::fromUtf8("label_O"));

        horizontalLayout_Connect->addWidget(label_O);

        light_Odom = new c_Fr_Light(groupBox_Connect);
        light_Odom->setObjectName(QString::fromUtf8("light_Odom"));
        light_Odom->setMinimumSize(QSize(20, 20));

        horizontalLayout_Connect->addWidget(light_Odom);

        label_Cam = new QLabel(groupBox_Connect);
        label_Cam->setObjectName(QString::fromUtf8("label_Cam"));

        horizontalLayout_Connect->addWidget(label_Cam);

        light_Camera = new c_Fr_Light(groupBox_Connect);
        light_Camera->setObjectName(QString::fromUtf8("light_Camera"));
        light_Camera->setMinimumSize(QSize(20, 20));

        horizontalLayout_Connect->addWidget(light_Camera);

        label_Estop = new QLabel(groupBox_Connect);
        label_Estop->setObjectName(QString::fromUtf8("label_Estop"));

        horizontalLayout_Connect->addWidget(label_Estop);

        light_Estop = new c_Fr_Light(groupBox_Connect);
        light_Estop->setObjectName(QString::fromUtf8("light_Estop"));
        light_Estop->setMinimumSize(QSize(20, 20));

        horizontalLayout_Connect->addWidget(light_Estop);


        gridLayout_2->addWidget(groupBox_Connect, 0, 0, 1, 2);

        groupBox_Pose = new QGroupBox(groupBox_7);
        groupBox_Pose->setObjectName(QString::fromUtf8("groupBox_Pose"));
        sizePolicy.setHeightForWidth(groupBox_Pose->sizePolicy().hasHeightForWidth());
        groupBox_Pose->setSizePolicy(sizePolicy);
        horizontalLayout_Pose = new QHBoxLayout(groupBox_Pose);
        horizontalLayout_Pose->setSpacing(6);
        horizontalLayout_Pose->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_Pose->setObjectName(QString::fromUtf8("horizontalLayout_Pose"));
        label_WX = new QLabel(groupBox_Pose);
        label_WX->setObjectName(QString::fromUtf8("label_WX"));

        horizontalLayout_Pose->addWidget(label_WX);

        lineEdit_WX = new QLineEdit(groupBox_Pose);
        lineEdit_WX->setObjectName(QString::fromUtf8("lineEdit_WX"));
        sizePolicy7.setHeightForWidth(lineEdit_WX->sizePolicy().hasHeightForWidth());
        lineEdit_WX->setSizePolicy(sizePolicy7);
        lineEdit_WX->setReadOnly(true);

        horizontalLayout_Pose->addWidget(lineEdit_WX);

        label_WY = new QLabel(groupBox_Pose);
        label_WY->setObjectName(QString::fromUtf8("label_WY"));

        horizontalLayout_Pose->addWidget(label_WY);

        lineEdit_WY = new QLineEdit(groupBox_Pose);
        lineEdit_WY->setObjectName(QString::fromUtf8("lineEdit_WY"));
        sizePolicy7.setHeightForWidth(lineEdit_WY->sizePolicy().hasHeightForWidth());
        lineEdit_WY->setSizePolicy(sizePolicy7);
        lineEdit_WY->setReadOnly(true);

        horizontalLayout_Pose->addWidget(lineEdit_WY);

        label_Angle = new QLabel(groupBox_Pose);
        label_Angle->setObjectName(QString::fromUtf8("label_Angle"));

        horizontalLayout_Pose->addWidget(label_Angle);

        lineEdit_Angle = new QLineEdit(groupBox_Pose);
        lineEdit_Angle->setObjectName(QString::fromUtf8("lineEdit_Angle"));
        sizePolicy7.setHeightForWidth(lineEdit_Angle->sizePolicy().hasHeightForWidth());
        lineEdit_Angle->setSizePolicy(sizePolicy7);
        lineEdit_Angle->setReadOnly(true);

        horizontalLayout_Pose->addWidget(lineEdit_Angle);

        label_Battery = new QLabel(groupBox_Pose);
        label_Battery->setObjectName(QString::fromUtf8("label_Battery"));

        horizontalLayout_Pose->addWidget(label_Battery);

        lineEdit_Battery = new QLineEdit(groupBox_Pose);
        lineEdit_Battery->setObjectName(QString::fromUtf8("lineEdit_Battery"));
        sizePolicy7.setHeightForWidth(lineEdit_Battery->sizePolicy().hasHeightForWidth());
        lineEdit_Battery->setSizePolicy(sizePolicy7);
        lineEdit_Battery->setReadOnly(true);

        horizontalLayout_Pose->addWidget(lineEdit_Battery);

        label_GridX = new QLabel(groupBox_Pose);
        label_GridX->setObjectName(QString::fromUtf8("label_GridX"));

        horizontalLayout_Pose->addWidget(label_GridX);

        lineEdit_GridX = new QLineEdit(groupBox_Pose);
        lineEdit_GridX->setObjectName(QString::fromUtf8("lineEdit_GridX"));
        sizePolicy7.setHeightForWidth(lineEdit_GridX->sizePolicy().hasHeightForWidth());
        lineEdit_GridX->setSizePolicy(sizePolicy7);
        lineEdit_GridX->setReadOnly(true);

        horizontalLayout_Pose->addWidget(lineEdit_GridX);

        label_GridY = new QLabel(groupBox_Pose);
        label_GridY->setObjectName(QString::fromUtf8("label_GridY"));

        horizontalLayout_Pose->addWidget(label_GridY);

        lineEdit_GridY = new QLineEdit(groupBox_Pose);
        lineEdit_GridY->setObjectName(QString::fromUtf8("lineEdit_GridY"));
        lineEdit_GridY->setReadOnly(true);

        horizontalLayout_Pose->addWidget(lineEdit_GridY);

        label_CurrentMap = new QLabel(groupBox_Pose);
        label_CurrentMap->setObjectName(QString::fromUtf8("label_CurrentMap"));

        horizontalLayout_Pose->addWidget(label_CurrentMap);

        lineEdit_CurrentMap = new QLineEdit(groupBox_Pose);
        lineEdit_CurrentMap->setObjectName(QString::fromUtf8("lineEdit_CurrentMap"));
        sizePolicy7.setHeightForWidth(lineEdit_CurrentMap->sizePolicy().hasHeightForWidth());
        lineEdit_CurrentMap->setSizePolicy(sizePolicy7);
        lineEdit_CurrentMap->setReadOnly(true);

        horizontalLayout_Pose->addWidget(lineEdit_CurrentMap);


        gridLayout_2->addWidget(groupBox_Pose, 1, 0, 1, 1);

        groupBox_SystemInfo = new QGroupBox(groupBox_7);
        groupBox_SystemInfo->setObjectName(QString::fromUtf8("groupBox_SystemInfo"));
        sizePolicy.setHeightForWidth(groupBox_SystemInfo->sizePolicy().hasHeightForWidth());
        groupBox_SystemInfo->setSizePolicy(sizePolicy);
        horizontalLayout_SystemInfo = new QHBoxLayout(groupBox_SystemInfo);
        horizontalLayout_SystemInfo->setSpacing(6);
        horizontalLayout_SystemInfo->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_SystemInfo->setObjectName(QString::fromUtf8("horizontalLayout_SystemInfo"));
        label_AntiCollision = new QLabel(groupBox_SystemInfo);
        label_AntiCollision->setObjectName(QString::fromUtf8("label_AntiCollision"));
        sizePolicy3.setHeightForWidth(label_AntiCollision->sizePolicy().hasHeightForWidth());
        label_AntiCollision->setSizePolicy(sizePolicy3);

        horizontalLayout_SystemInfo->addWidget(label_AntiCollision);

        lineEdit_AntiCollision = new QLineEdit(groupBox_SystemInfo);
        lineEdit_AntiCollision->setObjectName(QString::fromUtf8("lineEdit_AntiCollision"));
        sizePolicy7.setHeightForWidth(lineEdit_AntiCollision->sizePolicy().hasHeightForWidth());
        lineEdit_AntiCollision->setSizePolicy(sizePolicy7);
        lineEdit_AntiCollision->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_AntiCollision->setReadOnly(true);

        horizontalLayout_SystemInfo->addWidget(lineEdit_AntiCollision);

        label_WorkMode = new QLabel(groupBox_SystemInfo);
        label_WorkMode->setObjectName(QString::fromUtf8("label_WorkMode"));
        sizePolicy3.setHeightForWidth(label_WorkMode->sizePolicy().hasHeightForWidth());
        label_WorkMode->setSizePolicy(sizePolicy3);

        horizontalLayout_SystemInfo->addWidget(label_WorkMode);

        lineEdit_WorkMode = new QLineEdit(groupBox_SystemInfo);
        lineEdit_WorkMode->setObjectName(QString::fromUtf8("lineEdit_WorkMode"));
        sizePolicy7.setHeightForWidth(lineEdit_WorkMode->sizePolicy().hasHeightForWidth());
        lineEdit_WorkMode->setSizePolicy(sizePolicy7);
        lineEdit_WorkMode->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_WorkMode->setReadOnly(true);

        horizontalLayout_SystemInfo->addWidget(lineEdit_WorkMode);

        label_ErrorCode = new QLabel(groupBox_SystemInfo);
        label_ErrorCode->setObjectName(QString::fromUtf8("label_ErrorCode"));
        sizePolicy3.setHeightForWidth(label_ErrorCode->sizePolicy().hasHeightForWidth());
        label_ErrorCode->setSizePolicy(sizePolicy3);

        horizontalLayout_SystemInfo->addWidget(label_ErrorCode);

        lineEdit_ErrorCode = new QLineEdit(groupBox_SystemInfo);
        lineEdit_ErrorCode->setObjectName(QString::fromUtf8("lineEdit_ErrorCode"));
        sizePolicy7.setHeightForWidth(lineEdit_ErrorCode->sizePolicy().hasHeightForWidth());
        lineEdit_ErrorCode->setSizePolicy(sizePolicy7);
        lineEdit_ErrorCode->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_ErrorCode->setReadOnly(true);

        horizontalLayout_SystemInfo->addWidget(lineEdit_ErrorCode);

        label_ChassisVer = new QLabel(groupBox_SystemInfo);
        label_ChassisVer->setObjectName(QString::fromUtf8("label_ChassisVer"));
        sizePolicy3.setHeightForWidth(label_ChassisVer->sizePolicy().hasHeightForWidth());
        label_ChassisVer->setSizePolicy(sizePolicy3);

        horizontalLayout_SystemInfo->addWidget(label_ChassisVer);

        lineEdit_ChassisVer = new QLineEdit(groupBox_SystemInfo);
        lineEdit_ChassisVer->setObjectName(QString::fromUtf8("lineEdit_ChassisVer"));
        sizePolicy7.setHeightForWidth(lineEdit_ChassisVer->sizePolicy().hasHeightForWidth());
        lineEdit_ChassisVer->setSizePolicy(sizePolicy7);
        lineEdit_ChassisVer->setReadOnly(true);

        horizontalLayout_SystemInfo->addWidget(lineEdit_ChassisVer);

        label_NavVer = new QLabel(groupBox_SystemInfo);
        label_NavVer->setObjectName(QString::fromUtf8("label_NavVer"));
        sizePolicy3.setHeightForWidth(label_NavVer->sizePolicy().hasHeightForWidth());
        label_NavVer->setSizePolicy(sizePolicy3);

        horizontalLayout_SystemInfo->addWidget(label_NavVer);

        lineEdit_NavVer = new QLineEdit(groupBox_SystemInfo);
        lineEdit_NavVer->setObjectName(QString::fromUtf8("lineEdit_NavVer"));
        sizePolicy7.setHeightForWidth(lineEdit_NavVer->sizePolicy().hasHeightForWidth());
        lineEdit_NavVer->setSizePolicy(sizePolicy7);
        lineEdit_NavVer->setReadOnly(true);

        horizontalLayout_SystemInfo->addWidget(lineEdit_NavVer);


        gridLayout_2->addWidget(groupBox_SystemInfo, 2, 0, 1, 1);

        groupBox_MapList = new QGroupBox(groupBox_7);
        groupBox_MapList->setObjectName(QString::fromUtf8("groupBox_MapList"));
        QSizePolicy sizePolicy12(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(1);
        sizePolicy12.setHeightForWidth(groupBox_MapList->sizePolicy().hasHeightForWidth());
        groupBox_MapList->setSizePolicy(sizePolicy12);
        gridLayout_16 = new QGridLayout(groupBox_MapList);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        widget_MapView = new c_Magic_Map_View(groupBox_MapList);
        widget_MapView->setObjectName(QString::fromUtf8("widget_MapView"));
        QSizePolicy sizePolicy13(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy13.setHorizontalStretch(1);
        sizePolicy13.setVerticalStretch(1);
        sizePolicy13.setHeightForWidth(widget_MapView->sizePolicy().hasHeightForWidth());
        widget_MapView->setSizePolicy(sizePolicy13);

        gridLayout_16->addWidget(widget_MapView, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_MapList, 3, 0, 1, 1);

        horizontalLayout_48 = new QHBoxLayout();
        horizontalLayout_48->setSpacing(6);
        horizontalLayout_48->setObjectName(QString::fromUtf8("horizontalLayout_48"));
        groupBox_FrontCamView = new QGroupBox(groupBox_7);
        groupBox_FrontCamView->setObjectName(QString::fromUtf8("groupBox_FrontCamView"));
        QSizePolicy sizePolicy14(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy14.setHorizontalStretch(0);
        sizePolicy14.setVerticalStretch(0);
        sizePolicy14.setHeightForWidth(groupBox_FrontCamView->sizePolicy().hasHeightForWidth());
        groupBox_FrontCamView->setSizePolicy(sizePolicy14);
        verticalLayout_FrontCamView = new QVBoxLayout(groupBox_FrontCamView);
        verticalLayout_FrontCamView->setSpacing(6);
        verticalLayout_FrontCamView->setContentsMargins(11, 11, 11, 11);
        verticalLayout_FrontCamView->setObjectName(QString::fromUtf8("verticalLayout_FrontCamView"));
        label_FrontCamera = new QLabel(groupBox_FrontCamView);
        label_FrontCamera->setObjectName(QString::fromUtf8("label_FrontCamera"));
        sizePolicy7.setHeightForWidth(label_FrontCamera->sizePolicy().hasHeightForWidth());
        label_FrontCamera->setSizePolicy(sizePolicy7);
        label_FrontCamera->setMinimumSize(QSize(300, 200));
        label_FrontCamera->setMaximumSize(QSize(800, 600));
        label_FrontCamera->setScaledContents(true);
        label_FrontCamera->setAlignment(Qt::AlignCenter);

        verticalLayout_FrontCamView->addWidget(label_FrontCamera);


        horizontalLayout_48->addWidget(groupBox_FrontCamView);

        groupBox_4 = new QGroupBox(groupBox_7);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy14.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy14);
        gridLayout_19 = new QGridLayout(groupBox_4);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        widget_LidarView = new c_Magic_Lidar_View(groupBox_4);
        widget_LidarView->setObjectName(QString::fromUtf8("widget_LidarView"));
        sizePolicy11.setHeightForWidth(widget_LidarView->sizePolicy().hasHeightForWidth());
        widget_LidarView->setSizePolicy(sizePolicy11);
        widget_LidarView->setMinimumSize(QSize(300, 200));
        widget_LidarView->setMaximumSize(QSize(16777215, 500));

        gridLayout_19->addWidget(widget_LidarView, 0, 0, 1, 1);


        horizontalLayout_48->addWidget(groupBox_4);

        groupBox_RearCamView = new QGroupBox(groupBox_7);
        groupBox_RearCamView->setObjectName(QString::fromUtf8("groupBox_RearCamView"));
        sizePolicy14.setHeightForWidth(groupBox_RearCamView->sizePolicy().hasHeightForWidth());
        groupBox_RearCamView->setSizePolicy(sizePolicy14);
        verticalLayout_RearCamView = new QVBoxLayout(groupBox_RearCamView);
        verticalLayout_RearCamView->setSpacing(6);
        verticalLayout_RearCamView->setContentsMargins(11, 11, 11, 11);
        verticalLayout_RearCamView->setObjectName(QString::fromUtf8("verticalLayout_RearCamView"));
        label_RearCamera = new QLabel(groupBox_RearCamView);
        label_RearCamera->setObjectName(QString::fromUtf8("label_RearCamera"));
        sizePolicy7.setHeightForWidth(label_RearCamera->sizePolicy().hasHeightForWidth());
        label_RearCamera->setSizePolicy(sizePolicy7);
        label_RearCamera->setMinimumSize(QSize(300, 200));
        label_RearCamera->setMaximumSize(QSize(800, 600));
        label_RearCamera->setScaledContents(true);
        label_RearCamera->setAlignment(Qt::AlignCenter);

        verticalLayout_RearCamView->addWidget(label_RearCamera);


        horizontalLayout_48->addWidget(groupBox_RearCamView);


        gridLayout_2->addLayout(horizontalLayout_48, 4, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabWidget_Magic = new QTabWidget(groupBox_7);
        tabWidget_Magic->setObjectName(QString::fromUtf8("tabWidget_Magic"));
        QSizePolicy sizePolicy15(QSizePolicy::Preferred, QSizePolicy::Maximum);
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
        horizontalLayout_MapOps4 = new QHBoxLayout();
        horizontalLayout_MapOps4->setSpacing(6);
        horizontalLayout_MapOps4->setObjectName(QString::fromUtf8("horizontalLayout_MapOps4"));
        btn_EditMap = new QPushButton(tab_Map);
        btn_EditMap->setObjectName(QString::fromUtf8("btn_EditMap"));

        horizontalLayout_MapOps4->addWidget(btn_EditMap);

        btn_SetObstacle = new QPushButton(tab_Map);
        btn_SetObstacle->setObjectName(QString::fromUtf8("btn_SetObstacle"));

        horizontalLayout_MapOps4->addWidget(btn_SetObstacle);

        btn_GetObstacle = new QPushButton(tab_Map);
        btn_GetObstacle->setObjectName(QString::fromUtf8("btn_GetObstacle"));

        horizontalLayout_MapOps4->addWidget(btn_GetObstacle);


        gridLayout_13->addLayout(horizontalLayout_MapOps4, 5, 0, 1, 1);

        horizontalLayout_MapOps2 = new QHBoxLayout();
        horizontalLayout_MapOps2->setSpacing(6);
        horizontalLayout_MapOps2->setObjectName(QString::fromUtf8("horizontalLayout_MapOps2"));
        lineEdit_NewMapName = new QLineEdit(tab_Map);
        lineEdit_NewMapName->setObjectName(QString::fromUtf8("lineEdit_NewMapName"));

        horizontalLayout_MapOps2->addWidget(lineEdit_NewMapName);

        btn_RenameMap = new QPushButton(tab_Map);
        btn_RenameMap->setObjectName(QString::fromUtf8("btn_RenameMap"));

        horizontalLayout_MapOps2->addWidget(btn_RenameMap);

        btn_DeleteMap = new QPushButton(tab_Map);
        btn_DeleteMap->setObjectName(QString::fromUtf8("btn_DeleteMap"));

        horizontalLayout_MapOps2->addWidget(btn_DeleteMap);


        gridLayout_13->addLayout(horizontalLayout_MapOps2, 3, 0, 1, 1);

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


        gridLayout_13->addWidget(groupBox_FixedNav, 10, 0, 1, 1);

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

        btn_SkipCurrentTask = new QPushButton(groupBox_TaskControl);
        btn_SkipCurrentTask->setObjectName(QString::fromUtf8("btn_SkipCurrentTask"));

        horizontalLayout_TaskControl->addWidget(btn_SkipCurrentTask);

        btn_GetTaskLog = new QPushButton(groupBox_TaskControl);
        btn_GetTaskLog->setObjectName(QString::fromUtf8("btn_GetTaskLog"));

        horizontalLayout_TaskControl->addWidget(btn_GetTaskLog);

        btn_UploadTaskImage = new QPushButton(groupBox_TaskControl);
        btn_UploadTaskImage->setObjectName(QString::fromUtf8("btn_UploadTaskImage"));

        horizontalLayout_TaskControl->addWidget(btn_UploadTaskImage);

        btn_DownloadTaskImage = new QPushButton(groupBox_TaskControl);
        btn_DownloadTaskImage->setObjectName(QString::fromUtf8("btn_DownloadTaskImage"));

        horizontalLayout_TaskControl->addWidget(btn_DownloadTaskImage);

        lineEdit_TaskID = new QLineEdit(groupBox_TaskControl);
        lineEdit_TaskID->setObjectName(QString::fromUtf8("lineEdit_TaskID"));

        horizontalLayout_TaskControl->addWidget(lineEdit_TaskID);


        gridLayout_13->addWidget(groupBox_TaskControl, 8, 0, 1, 1);

        horizontalLayout_MapOps1 = new QHBoxLayout();
        horizontalLayout_MapOps1->setSpacing(6);
        horizontalLayout_MapOps1->setObjectName(QString::fromUtf8("horizontalLayout_MapOps1"));
        comboBox_MapList = new QComboBox(tab_Map);
        comboBox_MapList->setObjectName(QString::fromUtf8("comboBox_MapList"));
        sizePolicy11.setHeightForWidth(comboBox_MapList->sizePolicy().hasHeightForWidth());
        comboBox_MapList->setSizePolicy(sizePolicy11);

        horizontalLayout_MapOps1->addWidget(comboBox_MapList);

        btn_RefreshMapList = new QPushButton(tab_Map);
        btn_RefreshMapList->setObjectName(QString::fromUtf8("btn_RefreshMapList"));

        horizontalLayout_MapOps1->addWidget(btn_RefreshMapList);

        btn_SwitchMap = new QPushButton(tab_Map);
        btn_SwitchMap->setObjectName(QString::fromUtf8("btn_SwitchMap"));

        horizontalLayout_MapOps1->addWidget(btn_SwitchMap);


        gridLayout_13->addLayout(horizontalLayout_MapOps1, 1, 0, 1, 1);

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


        gridLayout_13->addWidget(groupBox_TaskSelect, 7, 0, 1, 1);

        horizontalLayout_MapOps5 = new QHBoxLayout();
        horizontalLayout_MapOps5->setSpacing(6);
        horizontalLayout_MapOps5->setObjectName(QString::fromUtf8("horizontalLayout_MapOps5"));
        btn_StopScanMap = new QPushButton(tab_Map);
        btn_StopScanMap->setObjectName(QString::fromUtf8("btn_StopScanMap"));

        horizontalLayout_MapOps5->addWidget(btn_StopScanMap);

        btn_CancelScanMap = new QPushButton(tab_Map);
        btn_CancelScanMap->setObjectName(QString::fromUtf8("btn_CancelScanMap"));

        horizontalLayout_MapOps5->addWidget(btn_CancelScanMap);

        btn_RecoverMap = new QPushButton(tab_Map);
        btn_RecoverMap->setObjectName(QString::fromUtf8("btn_RecoverMap"));

        horizontalLayout_MapOps5->addWidget(btn_RecoverMap);

        btn_QueryDefaultMap = new QPushButton(tab_Map);
        btn_QueryDefaultMap->setObjectName(QString::fromUtf8("btn_QueryDefaultMap"));

        horizontalLayout_MapOps5->addWidget(btn_QueryDefaultMap);

        btn_RefreshToken = new QPushButton(tab_Map);
        btn_RefreshToken->setObjectName(QString::fromUtf8("btn_RefreshToken"));

        horizontalLayout_MapOps5->addWidget(btn_RefreshToken);


        gridLayout_13->addLayout(horizontalLayout_MapOps5, 2, 0, 1, 1);

        horizontalLayout_MapOps3 = new QHBoxLayout();
        horizontalLayout_MapOps3->setSpacing(6);
        horizontalLayout_MapOps3->setObjectName(QString::fromUtf8("horizontalLayout_MapOps3"));
        btn_DownloadMap = new QPushButton(tab_Map);
        btn_DownloadMap->setObjectName(QString::fromUtf8("btn_DownloadMap"));

        horizontalLayout_MapOps3->addWidget(btn_DownloadMap);

        btn_UploadMap = new QPushButton(tab_Map);
        btn_UploadMap->setObjectName(QString::fromUtf8("btn_UploadMap"));

        horizontalLayout_MapOps3->addWidget(btn_UploadMap);

        btn_ExtendMap = new QPushButton(tab_Map);
        btn_ExtendMap->setObjectName(QString::fromUtf8("btn_ExtendMap"));

        horizontalLayout_MapOps3->addWidget(btn_ExtendMap);


        gridLayout_13->addLayout(horizontalLayout_MapOps3, 4, 0, 1, 1);

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


        gridLayout_13->addWidget(groupBox_TaskStatus, 9, 0, 1, 1);

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


        gridLayout_13->addWidget(groupBox_InitPose, 6, 0, 1, 1);

        tabWidget_Magic->addTab(tab_Map, QString());
        tab_PathPoint = new QWidget();
        tab_PathPoint->setObjectName(QString::fromUtf8("tab_PathPoint"));
        verticalLayout_PathPoint = new QVBoxLayout(tab_PathPoint);
        verticalLayout_PathPoint->setSpacing(6);
        verticalLayout_PathPoint->setContentsMargins(11, 11, 11, 11);
        verticalLayout_PathPoint->setObjectName(QString::fromUtf8("verticalLayout_PathPoint"));
        tabWidget_PathPoint = new QTabWidget(tab_PathPoint);
        tabWidget_PathPoint->setObjectName(QString::fromUtf8("tabWidget_PathPoint"));
        sizePolicy2.setHeightForWidth(tabWidget_PathPoint->sizePolicy().hasHeightForWidth());
        tabWidget_PathPoint->setSizePolicy(sizePolicy2);
        tab_NavPoint = new QWidget();
        tab_NavPoint->setObjectName(QString::fromUtf8("tab_NavPoint"));
        verticalLayout_NavPoint = new QVBoxLayout(tab_NavPoint);
        verticalLayout_NavPoint->setSpacing(6);
        verticalLayout_NavPoint->setContentsMargins(11, 11, 11, 11);
        verticalLayout_NavPoint->setObjectName(QString::fromUtf8("verticalLayout_NavPoint"));
        table_NavPoints = new QTableWidget(tab_NavPoint);
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

        verticalLayout_NavPoint->addWidget(table_NavPoints);

        horizontalLayout_NavOps = new QHBoxLayout();
        horizontalLayout_NavOps->setSpacing(6);
        horizontalLayout_NavOps->setObjectName(QString::fromUtf8("horizontalLayout_NavOps"));
        btn_AddNavPoint = new QPushButton(tab_NavPoint);
        btn_AddNavPoint->setObjectName(QString::fromUtf8("btn_AddNavPoint"));

        horizontalLayout_NavOps->addWidget(btn_AddNavPoint);

        btn_EditNavPoint = new QPushButton(tab_NavPoint);
        btn_EditNavPoint->setObjectName(QString::fromUtf8("btn_EditNavPoint"));

        horizontalLayout_NavOps->addWidget(btn_EditNavPoint);

        btn_DeleteNavPoint = new QPushButton(tab_NavPoint);
        btn_DeleteNavPoint->setObjectName(QString::fromUtf8("btn_DeleteNavPoint"));

        horizontalLayout_NavOps->addWidget(btn_DeleteNavPoint);

        btn_RefreshNavPoints = new QPushButton(tab_NavPoint);
        btn_RefreshNavPoints->setObjectName(QString::fromUtf8("btn_RefreshNavPoints"));

        horizontalLayout_NavOps->addWidget(btn_RefreshNavPoints);


        verticalLayout_NavPoint->addLayout(horizontalLayout_NavOps);

        tabWidget_PathPoint->addTab(tab_NavPoint, QString());
        tab_GraphPath = new QWidget();
        tab_GraphPath->setObjectName(QString::fromUtf8("tab_GraphPath"));
        verticalLayout_Graph = new QVBoxLayout(tab_GraphPath);
        verticalLayout_Graph->setSpacing(6);
        verticalLayout_Graph->setContentsMargins(11, 11, 11, 11);
        verticalLayout_Graph->setObjectName(QString::fromUtf8("verticalLayout_Graph"));
        table_GraphPaths = new QTableWidget(tab_GraphPath);
        if (table_GraphPaths->columnCount() < 3)
            table_GraphPaths->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        table_GraphPaths->setHorizontalHeaderItem(0, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        table_GraphPaths->setHorizontalHeaderItem(1, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        table_GraphPaths->setHorizontalHeaderItem(2, __qtablewidgetitem28);
        table_GraphPaths->setObjectName(QString::fromUtf8("table_GraphPaths"));
        sizePolicy14.setHeightForWidth(table_GraphPaths->sizePolicy().hasHeightForWidth());
        table_GraphPaths->setSizePolicy(sizePolicy14);
        table_GraphPaths->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_GraphPaths->setSelectionMode(QAbstractItemView::SingleSelection);
        table_GraphPaths->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_GraphPaths->setColumnCount(3);
        table_GraphPaths->horizontalHeader()->setStretchLastSection(true);
        table_GraphPaths->verticalHeader()->setVisible(false);

        verticalLayout_Graph->addWidget(table_GraphPaths);

        horizontalLayout_GraphOps = new QHBoxLayout();
        horizontalLayout_GraphOps->setSpacing(6);
        horizontalLayout_GraphOps->setObjectName(QString::fromUtf8("horizontalLayout_GraphOps"));
        btn_CreateGraphPath = new QPushButton(tab_GraphPath);
        btn_CreateGraphPath->setObjectName(QString::fromUtf8("btn_CreateGraphPath"));

        horizontalLayout_GraphOps->addWidget(btn_CreateGraphPath);

        btn_EditGraphPath = new QPushButton(tab_GraphPath);
        btn_EditGraphPath->setObjectName(QString::fromUtf8("btn_EditGraphPath"));

        horizontalLayout_GraphOps->addWidget(btn_EditGraphPath);

        btn_DeleteGraphPath = new QPushButton(tab_GraphPath);
        btn_DeleteGraphPath->setObjectName(QString::fromUtf8("btn_DeleteGraphPath"));

        horizontalLayout_GraphOps->addWidget(btn_DeleteGraphPath);

        btn_RenameGraphPath = new QPushButton(tab_GraphPath);
        btn_RenameGraphPath->setObjectName(QString::fromUtf8("btn_RenameGraphPath"));

        horizontalLayout_GraphOps->addWidget(btn_RenameGraphPath);

        btn_RefreshGraphPaths = new QPushButton(tab_GraphPath);
        btn_RefreshGraphPaths->setObjectName(QString::fromUtf8("btn_RefreshGraphPaths"));

        horizontalLayout_GraphOps->addWidget(btn_RefreshGraphPaths);


        verticalLayout_Graph->addLayout(horizontalLayout_GraphOps);

        tabWidget_PathPoint->addTab(tab_GraphPath, QString());
        tab_RecordPath = new QWidget();
        tab_RecordPath->setObjectName(QString::fromUtf8("tab_RecordPath"));
        verticalLayout_Record = new QVBoxLayout(tab_RecordPath);
        verticalLayout_Record->setSpacing(6);
        verticalLayout_Record->setContentsMargins(11, 11, 11, 11);
        verticalLayout_Record->setObjectName(QString::fromUtf8("verticalLayout_Record"));
        table_RecordPaths = new QTableWidget(tab_RecordPath);
        if (table_RecordPaths->columnCount() < 2)
            table_RecordPaths->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        table_RecordPaths->setHorizontalHeaderItem(0, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        table_RecordPaths->setHorizontalHeaderItem(1, __qtablewidgetitem30);
        table_RecordPaths->setObjectName(QString::fromUtf8("table_RecordPaths"));
        sizePolicy14.setHeightForWidth(table_RecordPaths->sizePolicy().hasHeightForWidth());
        table_RecordPaths->setSizePolicy(sizePolicy14);
        table_RecordPaths->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_RecordPaths->setSelectionMode(QAbstractItemView::SingleSelection);
        table_RecordPaths->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_RecordPaths->setColumnCount(2);
        table_RecordPaths->horizontalHeader()->setStretchLastSection(true);
        table_RecordPaths->verticalHeader()->setVisible(false);

        verticalLayout_Record->addWidget(table_RecordPaths);

        horizontalLayout_RecordOps = new QHBoxLayout();
        horizontalLayout_RecordOps->setSpacing(6);
        horizontalLayout_RecordOps->setObjectName(QString::fromUtf8("horizontalLayout_RecordOps"));
        btn_StartRecord = new QPushButton(tab_RecordPath);
        btn_StartRecord->setObjectName(QString::fromUtf8("btn_StartRecord"));

        horizontalLayout_RecordOps->addWidget(btn_StartRecord);

        btn_StopRecord = new QPushButton(tab_RecordPath);
        btn_StopRecord->setObjectName(QString::fromUtf8("btn_StopRecord"));

        horizontalLayout_RecordOps->addWidget(btn_StopRecord);

        btn_CancelRecord = new QPushButton(tab_RecordPath);
        btn_CancelRecord->setObjectName(QString::fromUtf8("btn_CancelRecord"));

        horizontalLayout_RecordOps->addWidget(btn_CancelRecord);

        btn_EditRecordPoints = new QPushButton(tab_RecordPath);
        btn_EditRecordPoints->setObjectName(QString::fromUtf8("btn_EditRecordPoints"));

        horizontalLayout_RecordOps->addWidget(btn_EditRecordPoints);

        btn_DeleteRecordPath = new QPushButton(tab_RecordPath);
        btn_DeleteRecordPath->setObjectName(QString::fromUtf8("btn_DeleteRecordPath"));

        horizontalLayout_RecordOps->addWidget(btn_DeleteRecordPath);

        btn_RenameRecordPath = new QPushButton(tab_RecordPath);
        btn_RenameRecordPath->setObjectName(QString::fromUtf8("btn_RenameRecordPath"));

        horizontalLayout_RecordOps->addWidget(btn_RenameRecordPath);

        btn_RefreshRecordPaths = new QPushButton(tab_RecordPath);
        btn_RefreshRecordPaths->setObjectName(QString::fromUtf8("btn_RefreshRecordPaths"));

        horizontalLayout_RecordOps->addWidget(btn_RefreshRecordPaths);


        verticalLayout_Record->addLayout(horizontalLayout_RecordOps);

        tabWidget_PathPoint->addTab(tab_RecordPath, QString());
        tab_TaskQueue = new QWidget();
        tab_TaskQueue->setObjectName(QString::fromUtf8("tab_TaskQueue"));
        verticalLayout_Queue = new QVBoxLayout(tab_TaskQueue);
        verticalLayout_Queue->setSpacing(6);
        verticalLayout_Queue->setContentsMargins(11, 11, 11, 11);
        verticalLayout_Queue->setObjectName(QString::fromUtf8("verticalLayout_Queue"));
        table_PathCombines = new QTableWidget(tab_TaskQueue);
        if (table_PathCombines->columnCount() < 2)
            table_PathCombines->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        table_PathCombines->setHorizontalHeaderItem(0, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        table_PathCombines->setHorizontalHeaderItem(1, __qtablewidgetitem32);
        table_PathCombines->setObjectName(QString::fromUtf8("table_PathCombines"));
        sizePolicy14.setHeightForWidth(table_PathCombines->sizePolicy().hasHeightForWidth());
        table_PathCombines->setSizePolicy(sizePolicy14);
        table_PathCombines->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_PathCombines->setSelectionMode(QAbstractItemView::SingleSelection);
        table_PathCombines->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_PathCombines->setColumnCount(2);
        table_PathCombines->horizontalHeader()->setStretchLastSection(true);
        table_PathCombines->verticalHeader()->setVisible(false);

        verticalLayout_Queue->addWidget(table_PathCombines);

        horizontalLayout_QueueOps = new QHBoxLayout();
        horizontalLayout_QueueOps->setSpacing(6);
        horizontalLayout_QueueOps->setObjectName(QString::fromUtf8("horizontalLayout_QueueOps"));
        btn_CreateCombine = new QPushButton(tab_TaskQueue);
        btn_CreateCombine->setObjectName(QString::fromUtf8("btn_CreateCombine"));

        horizontalLayout_QueueOps->addWidget(btn_CreateCombine);

        btn_EditCombine = new QPushButton(tab_TaskQueue);
        btn_EditCombine->setObjectName(QString::fromUtf8("btn_EditCombine"));

        horizontalLayout_QueueOps->addWidget(btn_EditCombine);

        btn_DeleteCombine = new QPushButton(tab_TaskQueue);
        btn_DeleteCombine->setObjectName(QString::fromUtf8("btn_DeleteCombine"));

        horizontalLayout_QueueOps->addWidget(btn_DeleteCombine);

        btn_RenameCombine = new QPushButton(tab_TaskQueue);
        btn_RenameCombine->setObjectName(QString::fromUtf8("btn_RenameCombine"));

        horizontalLayout_QueueOps->addWidget(btn_RenameCombine);

        btn_RefreshCombines = new QPushButton(tab_TaskQueue);
        btn_RefreshCombines->setObjectName(QString::fromUtf8("btn_RefreshCombines"));

        horizontalLayout_QueueOps->addWidget(btn_RefreshCombines);


        verticalLayout_Queue->addLayout(horizontalLayout_QueueOps);

        tabWidget_PathPoint->addTab(tab_TaskQueue, QString());

        verticalLayout_PathPoint->addWidget(tabWidget_PathPoint);

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
        sizePolicy3.setHeightForWidth(label_GoalSpeed->sizePolicy().hasHeightForWidth());
        label_GoalSpeed->setSizePolicy(sizePolicy3);

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
        sizePolicy3.setHeightForWidth(label_GraphSpeed->sizePolicy().hasHeightForWidth());
        label_GraphSpeed->setSizePolicy(sizePolicy3);

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
        sizePolicy3.setHeightForWidth(label_RecordSpeed->sizePolicy().hasHeightForWidth());
        label_RecordSpeed->setSizePolicy(sizePolicy3);

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

        groupBox_Obstacle = new QGroupBox(tab_System);
        groupBox_Obstacle->setObjectName(QString::fromUtf8("groupBox_Obstacle"));
        sizePolicy.setHeightForWidth(groupBox_Obstacle->sizePolicy().hasHeightForWidth());
        groupBox_Obstacle->setSizePolicy(sizePolicy);
        horizontalLayout_Obstacle = new QHBoxLayout(groupBox_Obstacle);
        horizontalLayout_Obstacle->setSpacing(6);
        horizontalLayout_Obstacle->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_Obstacle->setObjectName(QString::fromUtf8("horizontalLayout_Obstacle"));
        chk_GraphObstacle = new QCheckBox(groupBox_Obstacle);
        chk_GraphObstacle->setObjectName(QString::fromUtf8("chk_GraphObstacle"));

        horizontalLayout_Obstacle->addWidget(chk_GraphObstacle);

        chk_RecordObstacle = new QCheckBox(groupBox_Obstacle);
        chk_RecordObstacle->setObjectName(QString::fromUtf8("chk_RecordObstacle"));

        horizontalLayout_Obstacle->addWidget(chk_RecordObstacle);

        chk_LidarVoid = new QCheckBox(groupBox_Obstacle);
        chk_LidarVoid->setObjectName(QString::fromUtf8("chk_LidarVoid"));

        horizontalLayout_Obstacle->addWidget(chk_LidarVoid);

        btn_SaveObstacle = new QPushButton(groupBox_Obstacle);
        btn_SaveObstacle->setObjectName(QString::fromUtf8("btn_SaveObstacle"));

        horizontalLayout_Obstacle->addWidget(btn_SaveObstacle);

        btn_ResetDefault = new QPushButton(groupBox_Obstacle);
        btn_ResetDefault->setObjectName(QString::fromUtf8("btn_ResetDefault"));

        horizontalLayout_Obstacle->addWidget(btn_ResetDefault);

        btn_DownloadCfg = new QPushButton(groupBox_Obstacle);
        btn_DownloadCfg->setObjectName(QString::fromUtf8("btn_DownloadCfg"));

        horizontalLayout_Obstacle->addWidget(btn_DownloadCfg);

        btn_UploadCfg = new QPushButton(groupBox_Obstacle);
        btn_UploadCfg->setObjectName(QString::fromUtf8("btn_UploadCfg"));

        horizontalLayout_Obstacle->addWidget(btn_UploadCfg);


        verticalLayout_System->addWidget(groupBox_Obstacle);

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

        groupBox_Log1 = new QGroupBox(groupBox_7);
        groupBox_Log1->setObjectName(QString::fromUtf8("groupBox_Log1"));
        sizePolicy4.setHeightForWidth(groupBox_Log1->sizePolicy().hasHeightForWidth());
        groupBox_Log1->setSizePolicy(sizePolicy4);
        verticalLayout_Log = new QVBoxLayout(groupBox_Log1);
        verticalLayout_Log->setSpacing(6);
        verticalLayout_Log->setContentsMargins(11, 11, 11, 11);
        verticalLayout_Log->setObjectName(QString::fromUtf8("verticalLayout_Log"));
        Magic_Log = new QTextEdit(groupBox_Log1);
        Magic_Log->setObjectName(QString::fromUtf8("Magic_Log"));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(9);
        Magic_Log->setFont(font);
        Magic_Log->setReadOnly(true);

        verticalLayout_Log->addWidget(Magic_Log);


        verticalLayout_3->addWidget(groupBox_Log1);


        gridLayout_2->addLayout(verticalLayout_3, 1, 1, 4, 1);


        gridLayout_10->addWidget(groupBox_7, 0, 0, 1, 1);

        stackedWidget->addWidget(Magic_Widget);

        gridLayout_15->addWidget(stackedWidget, 0, 1, 1, 1);

        horizontalLayout_46 = new QHBoxLayout();
        horizontalLayout_46->setSpacing(6);
        horizontalLayout_46->setObjectName(QString::fromUtf8("horizontalLayout_46"));
        groupBox_11 = new QGroupBox(centralWidget);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        sizePolicy.setHeightForWidth(groupBox_11->sizePolicy().hasHeightForWidth());
        groupBox_11->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox_11);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Worry_List = new QTextEdit(groupBox_11);
        Worry_List->setObjectName(QString::fromUtf8("Worry_List"));
        sizePolicy.setHeightForWidth(Worry_List->sizePolicy().hasHeightForWidth());
        Worry_List->setSizePolicy(sizePolicy);
        Worry_List->setReadOnly(true);

        gridLayout->addWidget(Worry_List, 0, 0, 1, 1);


        horizontalLayout_46->addWidget(groupBox_11);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout_51 = new QGridLayout(groupBox_2);
        gridLayout_51->setSpacing(6);
        gridLayout_51->setContentsMargins(11, 11, 11, 11);
        gridLayout_51->setObjectName(QString::fromUtf8("gridLayout_51"));
        Work_List = new QTextEdit(groupBox_2);
        Work_List->setObjectName(QString::fromUtf8("Work_List"));
        sizePolicy.setHeightForWidth(Work_List->sizePolicy().hasHeightForWidth());
        Work_List->setSizePolicy(sizePolicy);
        Work_List->setReadOnly(true);

        gridLayout_51->addWidget(Work_List, 0, 0, 1, 1);


        horizontalLayout_46->addWidget(groupBox_2);


        gridLayout_15->addLayout(horizontalLayout_46, 1, 0, 1, 2);

        Robot_App_Widget->setCentralWidget(centralWidget);
        Status_Bar = new QStatusBar(Robot_App_Widget);
        Status_Bar->setObjectName(QString::fromUtf8("Status_Bar"));
        Robot_App_Widget->setStatusBar(Status_Bar);

        retranslateUi(Robot_App_Widget);

        stackedWidget->setCurrentIndex(1);
        tabWidget_Status->setCurrentIndex(0);
        tabWidget_Magic->setCurrentIndex(0);
        tabWidget_PathPoint->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Robot_App_Widget);
    } // setupUi

    void retranslateUi(QMainWindow *Robot_App_Widget)
    {
        Robot_App_Widget->setWindowTitle(QApplication::translate("Robot_App_Widget", "\346\231\272\350\203\275\345\272\225\351\203\250\345\267\241\346\243\200\346\234\272\345\231\250\344\272\272\346\216\247\345\210\266\345\271\263\345\217\260", nullptr));
        groupBox_5->setTitle(QApplication::translate("Robot_App_Widget", "\350\217\234\345\215\225", nullptr));
        Show_Magic_Widget->setText(QApplication::translate("Robot_App_Widget", "\345\272\225\347\233\230", nullptr));
        Show_CGXi_Widget->setText(QApplication::translate("Robot_App_Widget", "\346\234\272\346\242\260\350\207\202", nullptr));
        Show_Pre_Scan_120_Widget->setText(QApplication::translate("Robot_App_Widget", "\347\262\276\346\211\253", nullptr));
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
        groupBox_DO_3->setTitle(QApplication::translate("Robot_App_Widget", "\345\217\257\351\205\215\346\225\260\345\255\227\350\276\223\345\207\272 (CO0-CO7)\345\217\257\351\200\211\350\207\252\345\212\250\345\244\215\344\275\215\345\222\214\346\211\213\345\212\250\345\244\215\344\275\215", nullptr));
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
        groupBox_Jog->setTitle(QApplication::translate("Robot_App_Widget", "\350\277\220\345\212\250\346\216\247\345\210\266 (\347\202\271\345\212\250 / \347\273\235\345\257\271\344\275\215\347\275\256)", nullptr));
        label_43->setText(QApplication::translate("Robot_App_Widget", "\347\261\273\345\236\213(800):", nullptr));
        label_14->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_11->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        CGXi_Jog_Type_w->setItemText(0, QApplication::translate("Robot_App_Widget", "0 - \347\233\264\347\272\277\350\277\220\345\212\250", nullptr));
        CGXi_Jog_Type_w->setItemText(1, QApplication::translate("Robot_App_Widget", "1 - \345\205\263\350\212\202\350\277\220\345\212\250", nullptr));

        label_38->setText(QApplication::translate("Robot_App_Widget", "\345\235\220\346\240\207(803):", nullptr));
        label_13->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_12->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        CGXi_Jog_Coord_w->setItemText(0, QApplication::translate("Robot_App_Widget", "0 - \345\237\272\345\235\220\346\240\207\347\263\273", nullptr));
        CGXi_Jog_Coord_w->setItemText(1, QApplication::translate("Robot_App_Widget", "1 - \345\267\245\345\205\267\345\235\220\346\240\207\347\263\273", nullptr));

        label_26->setText(QApplication::translate("Robot_App_Widget", "\351\200\237\345\272\246(801):", nullptr));
        label->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_2->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        Set_HoldingRegisters_810->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245\347\233\256\346\240\207\344\275\215\347\275\256\347\233\256\346\240\207\344\275\215\347\275\256 (810-821\357\274\211", nullptr));
        Set_HoldingRegisters_800->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245\347\202\271\345\212\250\347\261\273\345\236\213(800)", nullptr));
        Set_HoldingRegisters_803->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245\347\202\271\345\212\250\345\235\220\346\240\207\347\263\273(803)", nullptr));
        Set_HoldingRegisters_801->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245\347\202\271\345\212\250\351\200\237\345\272\246\346\257\224\344\276\213 (801-802)", nullptr));
        groupBox_JogTarget->setTitle(QApplication::translate("Robot_App_Widget", "\347\233\256\346\240\207\344\275\215\347\275\256 (810~821)", nullptr));
        label_17->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_22->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_32->setText(QApplication::translate("Robot_App_Widget", "Rz / J6:", nullptr));
        label_18->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_30->setText(QApplication::translate("Robot_App_Widget", "Rx / J4:", nullptr));
        label_31->setText(QApplication::translate("Robot_App_Widget", "Ry / J5:", nullptr));
        label_21->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_20->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_29->setText(QApplication::translate("Robot_App_Widget", "Z / J3:", nullptr));
        label_28->setText(QApplication::translate("Robot_App_Widget", "Y / J2:", nullptr));
        label_16->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_27->setText(QApplication::translate("Robot_App_Widget", "X / J1:", nullptr));
        label_15->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_19->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_23->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_44->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_45->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_46->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        groupBox_Config->setTitle(QApplication::translate("Robot_App_Widget", "\345\217\202\346\225\260\351\205\215\347\275\256 (TCP\345\201\217\347\247\273 & \350\264\237\350\275\275)", nullptr));
        label_53->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_64->setText(QApplication::translate("Robot_App_Widget", "TCP Ry:", nullptr));
        label_49->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_54->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_69->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_35->setText(QApplication::translate("Robot_App_Widget", "TCP Z:", nullptr));
        label_56->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_57->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_52->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        CGXi_Write_TCP->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245 TCP \345\201\217\347\247\273\357\274\210700-711\357\274\211", nullptr));
        label_68->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_63->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_33->setText(QApplication::translate("Robot_App_Widget", "TCP X:", nullptr));
        label_59->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_39->setText(QApplication::translate("Robot_App_Widget", "Mass:", nullptr));
        label_58->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        CGXi_Write_Payload->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245\350\264\237\350\275\275\345\217\202\346\225\260\357\274\210720-727\357\274\211", nullptr));
        label_55->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_41->setText(QApplication::translate("Robot_App_Widget", "CY:", nullptr));
        label_47->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_50->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_60->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_40->setText(QApplication::translate("Robot_App_Widget", "CX:", nullptr));
        label_65->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_51->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_36->setText(QApplication::translate("Robot_App_Widget", "TCP Rx:", nullptr));
        label_34->setText(QApplication::translate("Robot_App_Widget", "TCP Y:", nullptr));
        label_67->setText(QApplication::translate("Robot_App_Widget", "TCP Rz:", nullptr));
        label_61->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_48->setText(QApplication::translate("Robot_App_Widget", "\350\257\273", nullptr));
        label_66->setText(QApplication::translate("Robot_App_Widget", "\345\206\231", nullptr));
        label_42->setText(QApplication::translate("Robot_App_Widget", "CZ:", nullptr));
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
        groupBox->setTitle(QApplication::translate("Robot_App_Widget", "\346\234\272\346\242\260\350\207\202\346\227\245\345\277\227\344\277\241\346\201\257", nullptr));
        groupBox_8->setTitle(QApplication::translate("Robot_App_Widget", "\347\262\276\346\211\253\347\233\270\346\234\272 \342\200\224 \347\253\213\345\210\233\347\273\223\346\236\204\345\205\211 T1", nullptr));
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
        label_120_Remote_Status->setText(QApplication::translate("Robot_App_Widget", "\350\277\234\347\250\213\345\217\221\351\200\201:", nullptr));
        label_120_Monitor_Status->setText(QApplication::translate("Robot_App_Widget", "\345\217\215\351\246\210\346\216\245\346\224\266:", nullptr));
        label_120_Tran_Status->setText(QApplication::translate("Robot_App_Widget", "TCP\350\275\254\345\217\221:", nullptr));
        label_120_Listen_Status->setText(QApplication::translate("Robot_App_Widget", "TCP\347\233\221\345\220\254:", nullptr));
        label_120_Client_Num->setText(QApplication::translate("Robot_App_Widget", "\345\256\242\346\210\267\347\253\257:", nullptr));
        label_120_Cam_Num->setText(QApplication::translate("Robot_App_Widget", "\347\233\270\346\234\272\347\274\226\345\217\267:", nullptr));
        Pre_Scan_120_Cam_Num->setText(QApplication::translate("Robot_App_Widget", "T1", nullptr));
        label_120_LastUpdate->setText(QApplication::translate("Robot_App_Widget", "\346\234\200\345\220\216\346\233\264\346\226\260:", nullptr));
        groupBox_Task_Info->setTitle(QApplication::translate("Robot_App_Widget", "WEB\344\273\273\345\212\241\344\277\241\346\201\257(\350\257\273)", nullptr));
        label_120_TaskID->setText(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241ID:", nullptr));
        label_120_Wheelset->setText(QApplication::translate("Robot_App_Widget", "\350\275\256\345\257\271\345\217\267:", nullptr));
        label_120_StartTime->setText(QApplication::translate("Robot_App_Widget", "\345\274\200\345\247\213\346\227\266\351\227\264:", nullptr));
        label_120_Axle->setText(QApplication::translate("Robot_App_Widget", "\350\275\246\350\275\264\345\217\267:", nullptr));
        label_120_Repair->setText(QApplication::translate("Robot_App_Widget", "\344\277\256\347\250\213:", nullptr));
        label_120_SendUnit->setText(QApplication::translate("Robot_App_Widget", "\351\200\201\350\275\256\345\215\225\344\275\215:", nullptr));
        groupBox_Collect_Status->setTitle(QApplication::translate("Robot_App_Widget", "\351\207\207\351\233\206\347\212\266\346\200\201\357\274\210\350\257\273\357\274\211", nullptr));
        label_120_Prog->setText(QApplication::translate("Robot_App_Widget", "\347\250\213\345\272\217\347\264\242\345\274\225:", nullptr));
        label_120_Gain->setText(QApplication::translate("Robot_App_Widget", "\347\233\270\346\234\272\345\242\236\347\233\212:", nullptr));
        label_120_Part1->setText(QApplication::translate("Robot_App_Widget", "\344\270\200\347\272\247\351\203\250\344\273\266:", nullptr));
        label_120_Part2->setText(QApplication::translate("Robot_App_Widget", "\344\272\214\347\272\247\351\203\250\344\273\266:", nullptr));
        label_120_Point->setText(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\347\202\271:", nullptr));
        groupBox_Control->setTitle(QApplication::translate("Robot_App_Widget", "\346\211\213\345\212\250\346\216\247\345\210\266", nullptr));
        Pre_Scan_120_Start_Scan->setText(QApplication::translate("Robot_App_Widget", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        Pre_Scan_120_Collector->setText(QApplication::translate("Robot_App_Widget", "\345\215\225\346\254\241\351\207\207\351\233\206", nullptr));
        Pre_Scan_120_Finish_Scan->setText(QApplication::translate("Robot_App_Widget", "\345\256\214\346\210\220\351\207\207\351\233\206", nullptr));
        Pre_Scan_120_Change_Gain->setText(QApplication::translate("Robot_App_Widget", "\350\256\276\347\275\256\345\242\236\347\233\212", nullptr));
        label_120_TotalImages->setText(QApplication::translate("Robot_App_Widget", "\351\207\207\351\233\206\345\233\276\345\203\217:", nullptr));
        label_120_WorkState->setText(QApplication::translate("Robot_App_Widget", "\345\267\245\344\275\234\347\212\266\346\200\201:", nullptr));
        Pre_Scan_120_WorkState->setItemText(0, QApplication::translate("Robot_App_Widget", "\347\251\272\351\227\262", nullptr));
        Pre_Scan_120_WorkState->setItemText(1, QApplication::translate("Robot_App_Widget", "\345\260\261\347\273\252", nullptr));
        Pre_Scan_120_WorkState->setItemText(2, QApplication::translate("Robot_App_Widget", "\351\207\207\351\233\206\344\270\255", nullptr));
        Pre_Scan_120_WorkState->setItemText(3, QApplication::translate("Robot_App_Widget", "\346\232\202\345\201\234", nullptr));
        Pre_Scan_120_WorkState->setItemText(4, QApplication::translate("Robot_App_Widget", "\345\256\214\346\210\220", nullptr));
        Pre_Scan_120_WorkState->setItemText(5, QApplication::translate("Robot_App_Widget", "\351\224\231\350\257\257", nullptr));

        groupBox_Task_Info_2->setTitle(QApplication::translate("Robot_App_Widget", "WEB\344\273\273\345\212\241\344\277\241\346\201\257\357\274\210\345\206\231\357\274\211", nullptr));
        label_120_Wheelset_2->setText(QApplication::translate("Robot_App_Widget", "\350\275\256\345\257\271\345\217\267:", nullptr));
        label_120_Repair_2->setText(QApplication::translate("Robot_App_Widget", "\344\277\256\347\250\213:", nullptr));
        label_120_SendUnit_2->setText(QApplication::translate("Robot_App_Widget", "\351\200\201\350\275\256\345\215\225\344\275\215:", nullptr));
        label_120_StartTime_2->setText(QApplication::translate("Robot_App_Widget", "\345\274\200\345\247\213\346\227\266\351\227\264:", nullptr));
        label_120_Axle_2->setText(QApplication::translate("Robot_App_Widget", "\350\275\246\350\275\264\345\217\267:", nullptr));
        label_120_TaskID_2->setText(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241ID:", nullptr));
        set_Pre_Scan_120_TaskID->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        set_Pre_Scan_120_SendUnit->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        set_Pre_Scan_120_Repair->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        set_Pre_Scan_120_Wheelset->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        set_Pre_Scan_120_Axle->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
        set_Pre_Scan_120_StartTime->setText(QApplication::translate("Robot_App_Widget", "\345\206\231\345\205\245", nullptr));
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
        groupBox_9->setTitle(QApplication::translate("Robot_App_Widget", "\345\267\246\347\262\276\346\211\253\346\266\210\346\201\257", nullptr));
        groupBox_MySql->setTitle(QApplication::translate("Robot_App_Widget", "\346\225\260\346\215\256\345\272\223\350\277\236\346\216\245", nullptr));
        label_120_MySql_Status->setText(QApplication::translate("Robot_App_Widget", "\347\212\266\346\200\201:", nullptr));
        label_167->setText(QApplication::translate("Robot_App_Widget", "\346\225\260\346\215\256\345\272\223\347\253\257\345\217\243\357\274\232", nullptr));
        label_156->setText(QApplication::translate("Robot_App_Widget", "\346\225\260\346\215\256\345\272\223\347\224\250\346\210\267\357\274\232", nullptr));
        MySql_User->setText(QString());
        label_149->setText(QApplication::translate("Robot_App_Widget", "\346\225\260\346\215\256\345\272\223\345\257\206\347\240\201\357\274\232", nullptr));
        label_148->setText(QApplication::translate("Robot_App_Widget", "\346\225\260\346\215\256\345\272\223\350\241\250\345\244\264\357\274\232", nullptr));
        Pre_Scan_120_MySql_Reconnect->setText(QApplication::translate("Robot_App_Widget", "\351\207\215\346\226\260\350\277\236\346\216\245", nullptr));
        groupBox_Log->setTitle(QApplication::translate("Robot_App_Widget", "\351\200\232\350\256\257\346\227\245\345\277\227", nullptr));
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
        groupBox_Pose->setTitle(QApplication::translate("Robot_App_Widget", "\345\256\236\346\227\266\344\275\215\345\247\277", nullptr));
        label_WX->setText(QApplication::translate("Robot_App_Widget", "World X:", nullptr));
        label_WY->setText(QApplication::translate("Robot_App_Widget", "World Y:", nullptr));
        label_Angle->setText(QApplication::translate("Robot_App_Widget", "Angle:", nullptr));
        label_Battery->setText(QApplication::translate("Robot_App_Widget", "\347\224\265\351\207\217:", nullptr));
        label_GridX->setText(QApplication::translate("Robot_App_Widget", "GridX:", nullptr));
        label_GridY->setText(QApplication::translate("Robot_App_Widget", "GridY:", nullptr));
        label_CurrentMap->setText(QApplication::translate("Robot_App_Widget", "\345\275\223\345\211\215\345\234\260\345\233\276:", nullptr));
        groupBox_SystemInfo->setTitle(QApplication::translate("Robot_App_Widget", "\347\263\273\347\273\237\347\212\266\346\200\201", nullptr));
        label_AntiCollision->setText(QApplication::translate("Robot_App_Widget", "\351\230\262\346\222\236:", nullptr));
        label_WorkMode->setText(QApplication::translate("Robot_App_Widget", "\346\250\241\345\274\217:", nullptr));
        label_ErrorCode->setText(QApplication::translate("Robot_App_Widget", "\351\224\231\350\257\257:", nullptr));
        label_ChassisVer->setText(QApplication::translate("Robot_App_Widget", "\345\272\225\347\233\230Ver:", nullptr));
        label_NavVer->setText(QApplication::translate("Robot_App_Widget", "\345\257\274\350\210\252Ver:", nullptr));
        groupBox_MapList->setTitle(QApplication::translate("Robot_App_Widget", "\345\234\260\345\233\276", nullptr));
        groupBox_FrontCamView->setTitle(QApplication::translate("Robot_App_Widget", "\345\211\215\347\233\270\346\234\272\347\224\273\351\235\242", nullptr));
        label_FrontCamera->setStyleSheet(QApplication::translate("Robot_App_Widget", "background-color: #1a1a1a; border: 1px solid #3c3c3c;", nullptr));
        label_FrontCamera->setText(QApplication::translate("Robot_App_Widget", "\347\255\211\345\276\205\345\211\215\347\233\270\346\234\272\345\233\276\345\203\217...", nullptr));
        groupBox_4->setTitle(QApplication::translate("Robot_App_Widget", "\351\233\267\350\276\276", nullptr));
        groupBox_RearCamView->setTitle(QApplication::translate("Robot_App_Widget", "\345\220\216\347\233\270\346\234\272\347\224\273\351\235\242", nullptr));
        label_RearCamera->setStyleSheet(QApplication::translate("Robot_App_Widget", "background-color: #1a1a1a; border: 1px solid #3c3c3c;", nullptr));
        label_RearCamera->setText(QApplication::translate("Robot_App_Widget", "\347\255\211\345\276\205\345\220\216\347\233\270\346\234\272\345\233\276\345\203\217...", nullptr));
        btn_EditMap->setText(QApplication::translate("Robot_App_Widget", "\345\216\237\345\233\276\347\274\226\350\276\221", nullptr));
        btn_SetObstacle->setText(QApplication::translate("Robot_App_Widget", "\350\256\276\347\275\256\347\211\271\346\256\212\345\214\272\345\237\237", nullptr));
        btn_GetObstacle->setText(QApplication::translate("Robot_App_Widget", "\350\216\267\345\217\226\347\211\271\346\256\212\345\214\272\345\237\237", nullptr));
        lineEdit_NewMapName->setPlaceholderText(QApplication::translate("Robot_App_Widget", "\346\226\260\345\234\260\345\233\276\345\220\215\347\247\260", nullptr));
        btn_RenameMap->setText(QApplication::translate("Robot_App_Widget", "\351\207\215\345\221\275\345\220\215", nullptr));
        btn_DeleteMap->setText(QApplication::translate("Robot_App_Widget", "\345\210\240\351\231\244", nullptr));
        groupBox_FixedNav->setTitle(QApplication::translate("Robot_App_Widget", "\345\256\232\347\202\271\345\257\274\350\210\252\357\274\210\345\235\220\346\240\207\350\276\223\345\205\245\357\274\211", nullptr));
        label_FixedX->setText(QApplication::translate("Robot_App_Widget", "\346\240\205\346\240\274 X:", nullptr));
        label_FixedY->setText(QApplication::translate("Robot_App_Widget", "\346\240\205\346\240\274 Y:", nullptr));
        label_FixedAngle->setText(QApplication::translate("Robot_App_Widget", "\350\247\222\345\272\246(\302\260):", nullptr));
        btn_FixedNavStart->setText(QApplication::translate("Robot_App_Widget", "\345\256\232\347\202\271\345\257\274\350\210\252\357\274\210\345\215\225\346\254\241\357\274\211", nullptr));
        btn_FixedNavLoop->setText(QApplication::translate("Robot_App_Widget", "\345\256\232\347\202\271\345\257\274\350\210\252\357\274\210\345\276\252\347\216\257\357\274\211", nullptr));
        groupBox_TaskControl->setTitle(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241\346\216\247\345\210\266", nullptr));
        btn_StartTask->setText(QApplication::translate("Robot_App_Widget", "\345\274\200\345\247\213", nullptr));
        btn_LoopStart->setText(QApplication::translate("Robot_App_Widget", "\345\276\252\347\216\257\345\274\200\345\247\213", nullptr));
        btn_PauseTask->setText(QApplication::translate("Robot_App_Widget", "\346\232\202\345\201\234", nullptr));
        btn_ResumeTask->setText(QApplication::translate("Robot_App_Widget", "\346\201\242\345\244\215", nullptr));
        btn_StopTask->setText(QApplication::translate("Robot_App_Widget", "\345\201\234\346\255\242", nullptr));
        btn_SkipCurrentTask->setText(QApplication::translate("Robot_App_Widget", "\350\267\263\350\277\207\345\275\223\345\211\215", nullptr));
        btn_GetTaskLog->setText(QApplication::translate("Robot_App_Widget", "\350\216\267\345\217\226\346\227\245\345\277\227", nullptr));
        btn_UploadTaskImage->setText(QApplication::translate("Robot_App_Widget", "\344\270\212\344\274\240\345\233\276\347\211\207", nullptr));
        btn_DownloadTaskImage->setText(QApplication::translate("Robot_App_Widget", "\344\270\213\350\275\275\345\233\276\347\211\207", nullptr));
        lineEdit_TaskID->setPlaceholderText(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241ID", nullptr));
        btn_RefreshMapList->setText(QApplication::translate("Robot_App_Widget", "\345\210\267\346\226\260\345\210\227\350\241\250", nullptr));
        btn_SwitchMap->setText(QApplication::translate("Robot_App_Widget", "\345\210\207\346\215\242", nullptr));
        groupBox_TaskSelect->setTitle(QApplication::translate("Robot_App_Widget", "\351\200\211\346\213\251\344\273\273\345\212\241", nullptr));
        label_TaskType->setText(QApplication::translate("Robot_App_Widget", "\347\261\273\345\236\213:", nullptr));
        combo_TaskType->setItemText(0, QApplication::translate("Robot_App_Widget", "\345\257\274\350\210\252\347\202\271", nullptr));
        combo_TaskType->setItemText(1, QApplication::translate("Robot_App_Widget", "\346\211\213\347\273\230\350\267\257\345\276\204", nullptr));
        combo_TaskType->setItemText(2, QApplication::translate("Robot_App_Widget", "\345\275\225\345\210\266\350\267\257\345\276\204", nullptr));
        combo_TaskType->setItemText(3, QApplication::translate("Robot_App_Widget", "\350\267\257\345\276\204\347\273\204\345\220\210", nullptr));

        label_TaskName->setText(QApplication::translate("Robot_App_Widget", "\345\220\215\347\247\260:", nullptr));
        label_LoopCount->setText(QApplication::translate("Robot_App_Widget", "\345\276\252\347\216\257\346\254\241\346\225\260:", nullptr));
        btn_StopScanMap->setText(QApplication::translate("Robot_App_Widget", "\345\201\234\346\255\242\345\273\272\345\233\276", nullptr));
        btn_CancelScanMap->setText(QApplication::translate("Robot_App_Widget", "\345\217\226\346\266\210\345\273\272\345\233\276", nullptr));
        btn_RecoverMap->setText(QApplication::translate("Robot_App_Widget", "\346\201\242\345\244\215\345\234\260\345\233\276", nullptr));
        btn_QueryDefaultMap->setText(QApplication::translate("Robot_App_Widget", "\346\237\245\350\257\242\351\273\230\350\256\244\345\234\260\345\233\276", nullptr));
        btn_RefreshToken->setText(QApplication::translate("Robot_App_Widget", "\345\210\267\346\226\260Token", nullptr));
        btn_DownloadMap->setText(QApplication::translate("Robot_App_Widget", "\344\270\213\350\275\275\345\234\260\345\233\276\346\226\207\344\273\266", nullptr));
        btn_UploadMap->setText(QApplication::translate("Robot_App_Widget", "\344\270\212\344\274\240\345\234\260\345\233\276\346\226\207\344\273\266", nullptr));
        btn_ExtendMap->setText(QApplication::translate("Robot_App_Widget", "\346\211\251\345\261\225\345\273\272\345\233\276", nullptr));
        groupBox_TaskStatus->setTitle(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241\347\212\266\346\200\201", nullptr));
        label_TaskStatusText->setText(QApplication::translate("Robot_App_Widget", "\347\251\272\351\227\262", nullptr));
        label_RemainTime->setText(QApplication::translate("Robot_App_Widget", "\345\211\251\344\275\231:", nullptr));
        label_RemainTimeValue->setText(QApplication::translate("Robot_App_Widget", "--", nullptr));
        label_LoopInfo->setText(QApplication::translate("Robot_App_Widget", "\345\276\252\347\216\257: 0/0", nullptr));
        groupBox_InitPose->setTitle(QApplication::translate("Robot_App_Widget", "\344\275\215\345\247\277\345\210\235\345\247\213\345\214\226", nullptr));
        btn_DynamicInit->setText(QApplication::translate("Robot_App_Widget", "\345\212\250\346\200\201\345\210\235\345\247\213\345\214\226", nullptr));
        btn_StaticInit->setText(QApplication::translate("Robot_App_Widget", "\351\235\231\346\200\201\345\210\235\345\247\213\345\214\226", nullptr));
        btn_GridInit->setText(QApplication::translate("Robot_App_Widget", "\346\240\205\346\240\274\345\210\235\345\247\213\345\214\226", nullptr));
        btn_InitResult->setText(QApplication::translate("Robot_App_Widget", "\345\210\235\345\247\213\345\214\226\347\273\223\346\236\234", nullptr));
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
        btn_AddNavPoint->setText(QApplication::translate("Robot_App_Widget", "\345\210\233\345\273\272", nullptr));
        btn_EditNavPoint->setText(QApplication::translate("Robot_App_Widget", "\347\274\226\350\276\221", nullptr));
        btn_DeleteNavPoint->setText(QApplication::translate("Robot_App_Widget", "\345\210\240\351\231\244", nullptr));
        btn_RefreshNavPoints->setText(QApplication::translate("Robot_App_Widget", "\345\210\267\346\226\260\345\210\227\350\241\250", nullptr));
        tabWidget_PathPoint->setTabText(tabWidget_PathPoint->indexOf(tab_NavPoint), QApplication::translate("Robot_App_Widget", "\345\257\274\350\210\252\347\202\271", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = table_GraphPaths->horizontalHeaderItem(0);
        ___qtablewidgetitem26->setText(QApplication::translate("Robot_App_Widget", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = table_GraphPaths->horizontalHeaderItem(1);
        ___qtablewidgetitem27->setText(QApplication::translate("Robot_App_Widget", "\351\225\277\345\272\246(m)", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = table_GraphPaths->horizontalHeaderItem(2);
        ___qtablewidgetitem28->setText(QApplication::translate("Robot_App_Widget", "\351\227\255\347\216\257", nullptr));
        btn_CreateGraphPath->setText(QApplication::translate("Robot_App_Widget", "\345\210\233\345\273\272", nullptr));
        btn_EditGraphPath->setText(QApplication::translate("Robot_App_Widget", "\347\274\226\350\276\221", nullptr));
        btn_DeleteGraphPath->setText(QApplication::translate("Robot_App_Widget", "\345\210\240\351\231\244", nullptr));
        btn_RenameGraphPath->setText(QApplication::translate("Robot_App_Widget", "\351\207\215\345\221\275\345\220\215", nullptr));
        btn_RefreshGraphPaths->setText(QApplication::translate("Robot_App_Widget", "\345\210\267\346\226\260\345\210\227\350\241\250", nullptr));
        tabWidget_PathPoint->setTabText(tabWidget_PathPoint->indexOf(tab_GraphPath), QApplication::translate("Robot_App_Widget", "\346\211\213\347\273\230\350\267\257\345\276\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = table_RecordPaths->horizontalHeaderItem(0);
        ___qtablewidgetitem29->setText(QApplication::translate("Robot_App_Widget", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = table_RecordPaths->horizontalHeaderItem(1);
        ___qtablewidgetitem30->setText(QApplication::translate("Robot_App_Widget", "\347\202\271\346\225\260", nullptr));
        btn_StartRecord->setText(QApplication::translate("Robot_App_Widget", "\345\274\200\345\247\213\345\275\225\345\210\266", nullptr));
        btn_StopRecord->setText(QApplication::translate("Robot_App_Widget", "\345\201\234\346\255\242\345\271\266\344\277\235\345\255\230", nullptr));
        btn_CancelRecord->setText(QApplication::translate("Robot_App_Widget", "\345\217\226\346\266\210\345\275\225\345\210\266", nullptr));
        btn_EditRecordPoints->setText(QApplication::translate("Robot_App_Widget", "\347\274\226\350\276\221\345\212\250\344\275\234\347\202\271", nullptr));
        btn_DeleteRecordPath->setText(QApplication::translate("Robot_App_Widget", "\345\210\240\351\231\244", nullptr));
        btn_RenameRecordPath->setText(QApplication::translate("Robot_App_Widget", "\351\207\215\345\221\275\345\220\215", nullptr));
        btn_RefreshRecordPaths->setText(QApplication::translate("Robot_App_Widget", "\345\210\267\346\226\260\345\210\227\350\241\250", nullptr));
        tabWidget_PathPoint->setTabText(tabWidget_PathPoint->indexOf(tab_RecordPath), QApplication::translate("Robot_App_Widget", "\345\275\225\345\210\266\350\267\257\345\276\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = table_PathCombines->horizontalHeaderItem(0);
        ___qtablewidgetitem31->setText(QApplication::translate("Robot_App_Widget", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = table_PathCombines->horizontalHeaderItem(1);
        ___qtablewidgetitem32->setText(QApplication::translate("Robot_App_Widget", "\344\273\273\345\212\241\346\225\260", nullptr));
        btn_CreateCombine->setText(QApplication::translate("Robot_App_Widget", "\345\210\233\345\273\272", nullptr));
        btn_EditCombine->setText(QApplication::translate("Robot_App_Widget", "\347\274\226\350\276\221", nullptr));
        btn_DeleteCombine->setText(QApplication::translate("Robot_App_Widget", "\345\210\240\351\231\244", nullptr));
        btn_RenameCombine->setText(QApplication::translate("Robot_App_Widget", "\351\207\215\345\221\275\345\220\215", nullptr));
        btn_RefreshCombines->setText(QApplication::translate("Robot_App_Widget", "\345\210\267\346\226\260\345\210\227\350\241\250", nullptr));
        tabWidget_PathPoint->setTabText(tabWidget_PathPoint->indexOf(tab_TaskQueue), QApplication::translate("Robot_App_Widget", "\350\267\257\345\276\204\347\273\204\345\220\210", nullptr));
        tabWidget_Magic->setTabText(tabWidget_Magic->indexOf(tab_PathPoint), QApplication::translate("Robot_App_Widget", "\350\267\257\345\276\204\344\270\216\347\202\271", nullptr));
        groupBox_Speed->setTitle(QApplication::translate("Robot_App_Widget", "\346\234\200\345\244\247\351\200\237\345\272\246\350\256\276\347\275\256 (\347\253\213\345\215\263\347\224\237\346\225\210)", nullptr));
        label_GoalSpeed->setText(QApplication::translate("Robot_App_Widget", "\350\207\252\347\224\261\345\257\274\350\210\252 (m/s):", nullptr));
        label_GraphSpeed->setText(QApplication::translate("Robot_App_Widget", "\346\211\213\347\273\230\350\267\257\345\276\204 (m/s):", nullptr));
        label_RecordSpeed->setText(QApplication::translate("Robot_App_Widget", "\345\275\225\345\210\266\350\267\257\345\276\204 (m/s):", nullptr));
        btn_UpdateSpeed->setText(QApplication::translate("Robot_App_Widget", "\344\277\235\345\255\230\351\200\237\345\272\246\351\205\215\347\275\256", nullptr));
        groupBox_Obstacle->setTitle(QApplication::translate("Robot_App_Widget", "\347\273\225\351\232\234\345\201\234\351\232\234 (\351\234\200\351\207\215\345\220\257\345\257\274\350\210\252)", nullptr));
        chk_GraphObstacle->setText(QApplication::translate("Robot_App_Widget", "\346\211\213\347\273\230\350\267\257\345\276\204\351\201\277\351\232\234", nullptr));
        chk_RecordObstacle->setText(QApplication::translate("Robot_App_Widget", "\345\275\225\345\210\266\350\267\257\345\276\204\351\201\277\351\232\234", nullptr));
        chk_LidarVoid->setText(QApplication::translate("Robot_App_Widget", "\347\252\204\351\201\223\345\220\257\347\224\250\351\233\267\350\276\276", nullptr));
        btn_SaveObstacle->setText(QApplication::translate("Robot_App_Widget", "\344\277\235\345\255\230\351\205\215\347\275\256", nullptr));
        btn_ResetDefault->setText(QApplication::translate("Robot_App_Widget", "\346\201\242\345\244\215\351\273\230\350\256\244", nullptr));
        btn_DownloadCfg->setText(QApplication::translate("Robot_App_Widget", "\344\270\213\350\275\275\351\205\215\347\275\256", nullptr));
        btn_UploadCfg->setText(QApplication::translate("Robot_App_Widget", "\344\270\212\344\274\240\351\205\215\347\275\256", nullptr));
        groupBox_Charge->setTitle(QApplication::translate("Robot_App_Widget", "\350\207\252\344\270\273\345\205\205\347\224\265", nullptr));
        label_ChargePoint->setText(QApplication::translate("Robot_App_Widget", "\345\205\205\347\224\265\347\202\271\345\220\215\347\247\260:", nullptr));
        lineEdit_ChargePoint->setText(QApplication::translate("Robot_App_Widget", "charge_point", nullptr));
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
        groupBox_Log1->setTitle(QApplication::translate("Robot_App_Widget", "\346\227\245\345\277\227\344\277\241\346\201\257", nullptr));
        groupBox_11->setTitle(QApplication::translate("Robot_App_Widget", "\347\263\273\347\273\237\344\277\241\346\201\257", nullptr));
        groupBox_2->setTitle(QApplication::translate("Robot_App_Widget", "\345\267\241\346\243\200\350\277\207\347\250\213\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Robot_App_Widget: public Ui_Robot_App_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOT_APP_WIDGET_H
