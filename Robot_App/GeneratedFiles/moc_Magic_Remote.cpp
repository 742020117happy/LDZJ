/****************************************************************************
** Meta object code from reading C++ file 'Magic_Remote.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Magic_Remote.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Magic_Remote.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c_Magic_Remote_t {
    QByteArrayData data[198];
    char stringdata0[2718];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c_Magic_Remote_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c_Magic_Remote_t qt_meta_stringdata_c_Magic_Remote = {
    {
QT_MOC_LITERAL(0, 0, 14), // "c_Magic_Remote"
QT_MOC_LITERAL(1, 15, 15), // "Update_Magic_DB"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 14), // "Signal_Connect"
QT_MOC_LITERAL(4, 47, 2), // "ip"
QT_MOC_LITERAL(5, 50, 4), // "port"
QT_MOC_LITERAL(6, 55, 3), // "url"
QT_MOC_LITERAL(7, 59, 17), // "Signal_Disconnect"
QT_MOC_LITERAL(8, 77, 16), // "Signal_Set_Token"
QT_MOC_LITERAL(9, 94, 5), // "token"
QT_MOC_LITERAL(10, 100, 15), // "Signal_Send_GET"
QT_MOC_LITERAL(11, 116, 3), // "api"
QT_MOC_LITERAL(12, 120, 6), // "params"
QT_MOC_LITERAL(13, 127, 7), // "headers"
QT_MOC_LITERAL(14, 135, 16), // "Signal_Send_POST"
QT_MOC_LITERAL(15, 152, 4), // "body"
QT_MOC_LITERAL(16, 157, 15), // "Signal_Send_PUT"
QT_MOC_LITERAL(17, 173, 18), // "Signal_Send_DELETE"
QT_MOC_LITERAL(18, 192, 4), // "Init"
QT_MOC_LITERAL(19, 197, 14), // "Connect_Device"
QT_MOC_LITERAL(20, 212, 17), // "Disconnect_Device"
QT_MOC_LITERAL(21, 230, 12), // "Connect_Done"
QT_MOC_LITERAL(22, 243, 14), // "Set_Token_Done"
QT_MOC_LITERAL(23, 258, 5), // "Login"
QT_MOC_LITERAL(24, 264, 8), // "userCode"
QT_MOC_LITERAL(25, 273, 8), // "password"
QT_MOC_LITERAL(26, 282, 13), // "Refresh_Token"
QT_MOC_LITERAL(27, 296, 13), // "refresh_token"
QT_MOC_LITERAL(28, 310, 9), // "Begin_Map"
QT_MOC_LITERAL(29, 320, 8), // "map_name"
QT_MOC_LITERAL(30, 329, 12), // "Get_File_Map"
QT_MOC_LITERAL(31, 342, 13), // "Stop_Scan_Map"
QT_MOC_LITERAL(32, 356, 15), // "Cancel_Scan_Map"
QT_MOC_LITERAL(33, 372, 11), // "Get_Map_Png"
QT_MOC_LITERAL(34, 384, 10), // "Rename_Map"
QT_MOC_LITERAL(35, 395, 15), // "origin_map_name"
QT_MOC_LITERAL(36, 411, 12), // "new_map_name"
QT_MOC_LITERAL(37, 424, 12), // "Get_Map_List"
QT_MOC_LITERAL(38, 437, 19), // "Get_Single_Map_Info"
QT_MOC_LITERAL(39, 457, 7), // "Use_Map"
QT_MOC_LITERAL(40, 465, 10), // "Delete_Map"
QT_MOC_LITERAL(41, 476, 12), // "Set_Obstacle"
QT_MOC_LITERAL(42, 489, 13), // "obstacle_data"
QT_MOC_LITERAL(43, 503, 12), // "Get_Obstacle"
QT_MOC_LITERAL(44, 516, 8), // "Edit_Map"
QT_MOC_LITERAL(45, 525, 9), // "edit_data"
QT_MOC_LITERAL(46, 535, 17), // "Dynamic_Init_Pose"
QT_MOC_LITERAL(47, 553, 10), // "point_name"
QT_MOC_LITERAL(48, 564, 20), // "Temp_Point_Init_Pose"
QT_MOC_LITERAL(49, 585, 7), // "mapName"
QT_MOC_LITERAL(50, 593, 5), // "gridX"
QT_MOC_LITERAL(51, 599, 5), // "gridY"
QT_MOC_LITERAL(52, 605, 5), // "angle"
QT_MOC_LITERAL(53, 611, 4), // "type"
QT_MOC_LITERAL(54, 616, 20), // "Get_Init_Pose_Result"
QT_MOC_LITERAL(55, 637, 16), // "Static_Init_Pose"
QT_MOC_LITERAL(56, 654, 17), // "Query_Default_Map"
QT_MOC_LITERAL(57, 672, 11), // "Recover_Map"
QT_MOC_LITERAL(58, 684, 10), // "Create_Pos"
QT_MOC_LITERAL(59, 695, 8), // "pos_data"
QT_MOC_LITERAL(60, 704, 8), // "Edit_Pos"
QT_MOC_LITERAL(61, 713, 10), // "Delete_Pos"
QT_MOC_LITERAL(62, 724, 13), // "position_name"
QT_MOC_LITERAL(63, 738, 12), // "Get_Pos_List"
QT_MOC_LITERAL(64, 751, 12), // "Create_Graph"
QT_MOC_LITERAL(65, 764, 9), // "graphData"
QT_MOC_LITERAL(66, 774, 10), // "Edit_Graph"
QT_MOC_LITERAL(67, 785, 12), // "Delete_Graph"
QT_MOC_LITERAL(68, 798, 15), // "graph_path_name"
QT_MOC_LITERAL(69, 814, 14), // "Get_Graph_List"
QT_MOC_LITERAL(70, 829, 14), // "Get_Graph_Path"
QT_MOC_LITERAL(71, 844, 9), // "path_name"
QT_MOC_LITERAL(72, 854, 16), // "contains_details"
QT_MOC_LITERAL(73, 871, 17), // "Rename_Graph_Path"
QT_MOC_LITERAL(74, 889, 11), // "origin_name"
QT_MOC_LITERAL(75, 901, 8), // "new_name"
QT_MOC_LITERAL(76, 910, 17), // "Check_Graph_Point"
QT_MOC_LITERAL(77, 928, 9), // "pointData"
QT_MOC_LITERAL(78, 938, 16), // "Check_Graph_Line"
QT_MOC_LITERAL(79, 955, 8), // "lineData"
QT_MOC_LITERAL(80, 964, 17), // "Begin_Record_Path"
QT_MOC_LITERAL(81, 982, 16), // "Stop_Record_Path"
QT_MOC_LITERAL(82, 999, 15), // "Get_Record_List"
QT_MOC_LITERAL(83, 1015, 18), // "Cancel_Record_Path"
QT_MOC_LITERAL(84, 1034, 15), // "Get_Record_Path"
QT_MOC_LITERAL(85, 1050, 23), // "Edit_Record_Path_Points"
QT_MOC_LITERAL(86, 1074, 18), // "Delete_Record_Path"
QT_MOC_LITERAL(87, 1093, 18), // "Rename_Record_Path"
QT_MOC_LITERAL(88, 1112, 16), // "origin_path_name"
QT_MOC_LITERAL(89, 1129, 13), // "new_path_name"
QT_MOC_LITERAL(90, 1143, 21), // "Check_Graph_Path_Name"
QT_MOC_LITERAL(91, 1165, 6), // "map_id"
QT_MOC_LITERAL(92, 1172, 10), // "Start_Task"
QT_MOC_LITERAL(93, 1183, 8), // "taskData"
QT_MOC_LITERAL(94, 1192, 10), // "Pause_Task"
QT_MOC_LITERAL(95, 1203, 11), // "Resume_Task"
QT_MOC_LITERAL(96, 1215, 9), // "Stop_Task"
QT_MOC_LITERAL(97, 1225, 17), // "Stop_Current_Task"
QT_MOC_LITERAL(98, 1243, 22), // "Check_Task_Queue_Exist"
QT_MOC_LITERAL(99, 1266, 10), // "queue_name"
QT_MOC_LITERAL(100, 1277, 14), // "Add_Task_Queue"
QT_MOC_LITERAL(101, 1292, 9), // "queueData"
QT_MOC_LITERAL(102, 1302, 17), // "Update_Task_Queue"
QT_MOC_LITERAL(103, 1320, 19), // "Get_Task_Queue_List"
QT_MOC_LITERAL(104, 1340, 21), // "Get_Task_Queue_Detail"
QT_MOC_LITERAL(105, 1362, 17), // "Delete_Task_Queue"
QT_MOC_LITERAL(106, 1380, 15), // "task_queue_name"
QT_MOC_LITERAL(107, 1396, 20), // "Get_Task_Is_Finished"
QT_MOC_LITERAL(108, 1417, 21), // "Get_Queue_Is_Finished"
QT_MOC_LITERAL(109, 1439, 23), // "Get_Task_Process_Status"
QT_MOC_LITERAL(110, 1463, 12), // "Get_Task_Log"
QT_MOC_LITERAL(111, 1476, 10), // "start_time"
QT_MOC_LITERAL(112, 1487, 8), // "end_time"
QT_MOC_LITERAL(113, 1496, 16), // "Get_Task_Current"
QT_MOC_LITERAL(114, 1513, 17), // "Upload_Task_Image"
QT_MOC_LITERAL(115, 1531, 11), // "base64_data"
QT_MOC_LITERAL(116, 1543, 15), // "Down_Task_Image"
QT_MOC_LITERAL(117, 1559, 7), // "task_id"
QT_MOC_LITERAL(118, 1567, 17), // "Rename_Task_Queue"
QT_MOC_LITERAL(119, 1585, 8), // "old_name"
QT_MOC_LITERAL(120, 1594, 14), // "Start_Recharge"
QT_MOC_LITERAL(121, 1609, 19), // "Get_Recharge_Status"
QT_MOC_LITERAL(122, 1629, 12), // "Dis_Recharge"
QT_MOC_LITERAL(123, 1642, 23), // "Get_Dis_Recharge_Status"
QT_MOC_LITERAL(124, 1666, 14), // "Pause_Recharge"
QT_MOC_LITERAL(125, 1681, 15), // "Resume_Recharge"
QT_MOC_LITERAL(126, 1697, 15), // "Cancel_Recharge"
QT_MOC_LITERAL(127, 1713, 13), // "Get_Robot_Pos"
QT_MOC_LITERAL(128, 1727, 22), // "Get_Robot_Local_Status"
QT_MOC_LITERAL(129, 1750, 25), // "Get_Robot_Hardware_Status"
QT_MOC_LITERAL(130, 1776, 8), // "Get_Odom"
QT_MOC_LITERAL(131, 1785, 7), // "Get_IMU"
QT_MOC_LITERAL(132, 1793, 11), // "Get_Laser2D"
QT_MOC_LITERAL(133, 1805, 17), // "Get_Laser2D_Scan1"
QT_MOC_LITERAL(134, 1823, 17), // "Get_Laser2D_Scan2"
QT_MOC_LITERAL(135, 1841, 17), // "Get_Laser2D_Scan3"
QT_MOC_LITERAL(136, 1859, 14), // "Get_Laser_Grid"
QT_MOC_LITERAL(137, 1874, 11), // "Get_Laser3D"
QT_MOC_LITERAL(138, 1886, 7), // "Get_GPS"
QT_MOC_LITERAL(139, 1894, 18), // "Get_Angular_Linear"
QT_MOC_LITERAL(140, 1913, 19), // "Get_Chassis_Version"
QT_MOC_LITERAL(141, 1933, 19), // "Get_Local_Plan_Path"
QT_MOC_LITERAL(142, 1953, 24), // "Get_Local_Grid_Plan_Path"
QT_MOC_LITERAL(143, 1978, 16), // "Get_Ahl1_RGB_Img"
QT_MOC_LITERAL(144, 1995, 16), // "Get_Ahl2_RGB_Img"
QT_MOC_LITERAL(145, 2012, 17), // "Get_Ahl1D_RGB_Img"
QT_MOC_LITERAL(146, 2030, 17), // "Get_Ahl2D_RGB_Img"
QT_MOC_LITERAL(147, 2048, 16), // "Get_Front_Camera"
QT_MOC_LITERAL(148, 2065, 15), // "Get_Rear_Camera"
QT_MOC_LITERAL(149, 2081, 14), // "Get_Ultrasonic"
QT_MOC_LITERAL(150, 2096, 10), // "Robot_Move"
QT_MOC_LITERAL(151, 2107, 11), // "linearSpeed"
QT_MOC_LITERAL(152, 2119, 12), // "angularSpeed"
QT_MOC_LITERAL(153, 2132, 10), // "slip_angle"
QT_MOC_LITERAL(154, 2143, 15), // "Robot_Move_Stop"
QT_MOC_LITERAL(155, 2159, 16), // "Move_With_Params"
QT_MOC_LITERAL(156, 2176, 2), // "lv"
QT_MOC_LITERAL(157, 2179, 2), // "av"
QT_MOC_LITERAL(158, 2182, 2), // "td"
QT_MOC_LITERAL(159, 2185, 2), // "ta"
QT_MOC_LITERAL(160, 2188, 4), // "mode"
QT_MOC_LITERAL(161, 2193, 23), // "Cancel_Move_With_Params"
QT_MOC_LITERAL(162, 2217, 14), // "Down_Robot_Cfg"
QT_MOC_LITERAL(163, 2232, 16), // "Upload_Robot_Cfg"
QT_MOC_LITERAL(164, 2249, 7), // "cfgData"
QT_MOC_LITERAL(165, 2257, 20), // "Update_Robot_Setting"
QT_MOC_LITERAL(166, 2278, 7), // "setting"
QT_MOC_LITERAL(167, 2286, 19), // "Reset_Robot_Default"
QT_MOC_LITERAL(168, 2306, 12), // "Download_Map"
QT_MOC_LITERAL(169, 2319, 10), // "Upload_Map"
QT_MOC_LITERAL(170, 2330, 7), // "mapData"
QT_MOC_LITERAL(171, 2338, 12), // "Down_Map_Png"
QT_MOC_LITERAL(172, 2351, 8), // "Get_Logo"
QT_MOC_LITERAL(173, 2360, 11), // "Upload_Logo"
QT_MOC_LITERAL(174, 2372, 8), // "logoData"
QT_MOC_LITERAL(175, 2381, 15), // "Get_Logo_Base64"
QT_MOC_LITERAL(176, 2397, 21), // "Get_Background_Base64"
QT_MOC_LITERAL(177, 2419, 17), // "Upload_Background"
QT_MOC_LITERAL(178, 2437, 6), // "bgData"
QT_MOC_LITERAL(179, 2444, 14), // "Get_Sys_Status"
QT_MOC_LITERAL(180, 2459, 11), // "Get_Sys_Mac"
QT_MOC_LITERAL(181, 2471, 18), // "Get_Local_Sys_Info"
QT_MOC_LITERAL(182, 2490, 21), // "Update_Local_Sys_Info"
QT_MOC_LITERAL(183, 2512, 5), // "title"
QT_MOC_LITERAL(184, 2518, 18), // "Get_Robot_About_Us"
QT_MOC_LITERAL(185, 2537, 14), // "Get_Robot_Show"
QT_MOC_LITERAL(186, 2552, 12), // "Get_All_Logs"
QT_MOC_LITERAL(187, 2565, 8), // "log_type"
QT_MOC_LITERAL(188, 2574, 9), // "Down_Logs"
QT_MOC_LITERAL(189, 2584, 9), // "file_name"
QT_MOC_LITERAL(190, 2594, 9), // "Drop_Logs"
QT_MOC_LITERAL(191, 2604, 17), // "Get_Robot_Setting"
QT_MOC_LITERAL(192, 2622, 24), // "Reset_Robot_Base_Default"
QT_MOC_LITERAL(193, 2647, 16), // "On_Response_Done"
QT_MOC_LITERAL(194, 2664, 17), // "On_Response_Error"
QT_MOC_LITERAL(195, 2682, 9), // "error_msg"
QT_MOC_LITERAL(196, 2692, 11), // "Poll_Status"
QT_MOC_LITERAL(197, 2704, 13) // "Try_Reconnect"

    },
    "c_Magic_Remote\0Update_Magic_DB\0\0"
    "Signal_Connect\0ip\0port\0url\0Signal_Disconnect\0"
    "Signal_Set_Token\0token\0Signal_Send_GET\0"
    "api\0params\0headers\0Signal_Send_POST\0"
    "body\0Signal_Send_PUT\0Signal_Send_DELETE\0"
    "Init\0Connect_Device\0Disconnect_Device\0"
    "Connect_Done\0Set_Token_Done\0Login\0"
    "userCode\0password\0Refresh_Token\0"
    "refresh_token\0Begin_Map\0map_name\0"
    "Get_File_Map\0Stop_Scan_Map\0Cancel_Scan_Map\0"
    "Get_Map_Png\0Rename_Map\0origin_map_name\0"
    "new_map_name\0Get_Map_List\0Get_Single_Map_Info\0"
    "Use_Map\0Delete_Map\0Set_Obstacle\0"
    "obstacle_data\0Get_Obstacle\0Edit_Map\0"
    "edit_data\0Dynamic_Init_Pose\0point_name\0"
    "Temp_Point_Init_Pose\0mapName\0gridX\0"
    "gridY\0angle\0type\0Get_Init_Pose_Result\0"
    "Static_Init_Pose\0Query_Default_Map\0"
    "Recover_Map\0Create_Pos\0pos_data\0"
    "Edit_Pos\0Delete_Pos\0position_name\0"
    "Get_Pos_List\0Create_Graph\0graphData\0"
    "Edit_Graph\0Delete_Graph\0graph_path_name\0"
    "Get_Graph_List\0Get_Graph_Path\0path_name\0"
    "contains_details\0Rename_Graph_Path\0"
    "origin_name\0new_name\0Check_Graph_Point\0"
    "pointData\0Check_Graph_Line\0lineData\0"
    "Begin_Record_Path\0Stop_Record_Path\0"
    "Get_Record_List\0Cancel_Record_Path\0"
    "Get_Record_Path\0Edit_Record_Path_Points\0"
    "Delete_Record_Path\0Rename_Record_Path\0"
    "origin_path_name\0new_path_name\0"
    "Check_Graph_Path_Name\0map_id\0Start_Task\0"
    "taskData\0Pause_Task\0Resume_Task\0"
    "Stop_Task\0Stop_Current_Task\0"
    "Check_Task_Queue_Exist\0queue_name\0"
    "Add_Task_Queue\0queueData\0Update_Task_Queue\0"
    "Get_Task_Queue_List\0Get_Task_Queue_Detail\0"
    "Delete_Task_Queue\0task_queue_name\0"
    "Get_Task_Is_Finished\0Get_Queue_Is_Finished\0"
    "Get_Task_Process_Status\0Get_Task_Log\0"
    "start_time\0end_time\0Get_Task_Current\0"
    "Upload_Task_Image\0base64_data\0"
    "Down_Task_Image\0task_id\0Rename_Task_Queue\0"
    "old_name\0Start_Recharge\0Get_Recharge_Status\0"
    "Dis_Recharge\0Get_Dis_Recharge_Status\0"
    "Pause_Recharge\0Resume_Recharge\0"
    "Cancel_Recharge\0Get_Robot_Pos\0"
    "Get_Robot_Local_Status\0Get_Robot_Hardware_Status\0"
    "Get_Odom\0Get_IMU\0Get_Laser2D\0"
    "Get_Laser2D_Scan1\0Get_Laser2D_Scan2\0"
    "Get_Laser2D_Scan3\0Get_Laser_Grid\0"
    "Get_Laser3D\0Get_GPS\0Get_Angular_Linear\0"
    "Get_Chassis_Version\0Get_Local_Plan_Path\0"
    "Get_Local_Grid_Plan_Path\0Get_Ahl1_RGB_Img\0"
    "Get_Ahl2_RGB_Img\0Get_Ahl1D_RGB_Img\0"
    "Get_Ahl2D_RGB_Img\0Get_Front_Camera\0"
    "Get_Rear_Camera\0Get_Ultrasonic\0"
    "Robot_Move\0linearSpeed\0angularSpeed\0"
    "slip_angle\0Robot_Move_Stop\0Move_With_Params\0"
    "lv\0av\0td\0ta\0mode\0Cancel_Move_With_Params\0"
    "Down_Robot_Cfg\0Upload_Robot_Cfg\0cfgData\0"
    "Update_Robot_Setting\0setting\0"
    "Reset_Robot_Default\0Download_Map\0"
    "Upload_Map\0mapData\0Down_Map_Png\0"
    "Get_Logo\0Upload_Logo\0logoData\0"
    "Get_Logo_Base64\0Get_Background_Base64\0"
    "Upload_Background\0bgData\0Get_Sys_Status\0"
    "Get_Sys_Mac\0Get_Local_Sys_Info\0"
    "Update_Local_Sys_Info\0title\0"
    "Get_Robot_About_Us\0Get_Robot_Show\0"
    "Get_All_Logs\0log_type\0Down_Logs\0"
    "file_name\0Drop_Logs\0Get_Robot_Setting\0"
    "Reset_Robot_Base_Default\0On_Response_Done\0"
    "On_Response_Error\0error_msg\0Poll_Status\0"
    "Try_Reconnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c_Magic_Remote[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     139,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  709,    2, 0x06 /* Public */,
       3,    3,  710,    2, 0x06 /* Public */,
       7,    0,  717,    2, 0x06 /* Public */,
       8,    1,  718,    2, 0x06 /* Public */,
      10,    3,  721,    2, 0x06 /* Public */,
      14,    3,  728,    2, 0x06 /* Public */,
      16,    3,  735,    2, 0x06 /* Public */,
      17,    3,  742,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    0,  749,    2, 0x0a /* Public */,
      19,    2,  750,    2, 0x0a /* Public */,
      20,    0,  755,    2, 0x0a /* Public */,
      21,    1,  756,    2, 0x0a /* Public */,
      22,    1,  759,    2, 0x0a /* Public */,
      23,    2,  762,    2, 0x0a /* Public */,
      26,    1,  767,    2, 0x0a /* Public */,
      28,    1,  770,    2, 0x0a /* Public */,
      30,    0,  773,    2, 0x0a /* Public */,
      31,    0,  774,    2, 0x0a /* Public */,
      32,    0,  775,    2, 0x0a /* Public */,
      33,    1,  776,    2, 0x0a /* Public */,
      34,    2,  779,    2, 0x0a /* Public */,
      37,    0,  784,    2, 0x0a /* Public */,
      38,    1,  785,    2, 0x0a /* Public */,
      39,    1,  788,    2, 0x0a /* Public */,
      40,    1,  791,    2, 0x0a /* Public */,
      41,    2,  794,    2, 0x0a /* Public */,
      43,    1,  799,    2, 0x0a /* Public */,
      44,    2,  802,    2, 0x0a /* Public */,
      46,    2,  807,    2, 0x0a /* Public */,
      48,    5,  812,    2, 0x0a /* Public */,
      54,    0,  823,    2, 0x0a /* Public */,
      55,    2,  824,    2, 0x0a /* Public */,
      56,    0,  829,    2, 0x0a /* Public */,
      57,    1,  830,    2, 0x0a /* Public */,
      58,    1,  833,    2, 0x0a /* Public */,
      60,    1,  836,    2, 0x0a /* Public */,
      61,    2,  839,    2, 0x0a /* Public */,
      63,    2,  844,    2, 0x0a /* Public */,
      63,    1,  849,    2, 0x2a /* Public | MethodCloned */,
      64,    1,  852,    2, 0x0a /* Public */,
      66,    1,  855,    2, 0x0a /* Public */,
      67,    2,  858,    2, 0x0a /* Public */,
      69,    1,  863,    2, 0x0a /* Public */,
      70,    3,  866,    2, 0x0a /* Public */,
      70,    2,  873,    2, 0x2a /* Public | MethodCloned */,
      73,    3,  878,    2, 0x0a /* Public */,
      76,    1,  885,    2, 0x0a /* Public */,
      78,    1,  888,    2, 0x0a /* Public */,
      80,    2,  891,    2, 0x0a /* Public */,
      81,    0,  896,    2, 0x0a /* Public */,
      82,    1,  897,    2, 0x0a /* Public */,
      83,    0,  900,    2, 0x0a /* Public */,
      84,    3,  901,    2, 0x0a /* Public */,
      84,    2,  908,    2, 0x2a /* Public | MethodCloned */,
      85,    1,  913,    2, 0x0a /* Public */,
      86,    2,  916,    2, 0x0a /* Public */,
      87,    3,  921,    2, 0x0a /* Public */,
      90,    2,  928,    2, 0x0a /* Public */,
      92,    1,  933,    2, 0x0a /* Public */,
      94,    0,  936,    2, 0x0a /* Public */,
      95,    0,  937,    2, 0x0a /* Public */,
      96,    0,  938,    2, 0x0a /* Public */,
      97,    0,  939,    2, 0x0a /* Public */,
      98,    2,  940,    2, 0x0a /* Public */,
     100,    1,  945,    2, 0x0a /* Public */,
     102,    1,  948,    2, 0x0a /* Public */,
     103,    1,  951,    2, 0x0a /* Public */,
     104,    2,  954,    2, 0x0a /* Public */,
     105,    2,  959,    2, 0x0a /* Public */,
     107,    0,  964,    2, 0x0a /* Public */,
     108,    0,  965,    2, 0x0a /* Public */,
     109,    0,  966,    2, 0x0a /* Public */,
     110,    3,  967,    2, 0x0a /* Public */,
     113,    0,  974,    2, 0x0a /* Public */,
     114,    1,  975,    2, 0x0a /* Public */,
     116,    1,  978,    2, 0x0a /* Public */,
     118,    3,  981,    2, 0x0a /* Public */,
     120,    2,  988,    2, 0x0a /* Public */,
     121,    0,  993,    2, 0x0a /* Public */,
     122,    0,  994,    2, 0x0a /* Public */,
     123,    0,  995,    2, 0x0a /* Public */,
     124,    0,  996,    2, 0x0a /* Public */,
     125,    0,  997,    2, 0x0a /* Public */,
     126,    0,  998,    2, 0x0a /* Public */,
     127,    0,  999,    2, 0x0a /* Public */,
     128,    0, 1000,    2, 0x0a /* Public */,
     129,    0, 1001,    2, 0x0a /* Public */,
     130,    0, 1002,    2, 0x0a /* Public */,
     131,    0, 1003,    2, 0x0a /* Public */,
     132,    0, 1004,    2, 0x0a /* Public */,
     133,    0, 1005,    2, 0x0a /* Public */,
     134,    0, 1006,    2, 0x0a /* Public */,
     135,    0, 1007,    2, 0x0a /* Public */,
     136,    0, 1008,    2, 0x0a /* Public */,
     137,    0, 1009,    2, 0x0a /* Public */,
     138,    0, 1010,    2, 0x0a /* Public */,
     139,    0, 1011,    2, 0x0a /* Public */,
     140,    0, 1012,    2, 0x0a /* Public */,
     141,    0, 1013,    2, 0x0a /* Public */,
     142,    0, 1014,    2, 0x0a /* Public */,
     143,    0, 1015,    2, 0x0a /* Public */,
     144,    0, 1016,    2, 0x0a /* Public */,
     145,    0, 1017,    2, 0x0a /* Public */,
     146,    0, 1018,    2, 0x0a /* Public */,
     147,    0, 1019,    2, 0x0a /* Public */,
     148,    0, 1020,    2, 0x0a /* Public */,
     149,    0, 1021,    2, 0x0a /* Public */,
     150,    3, 1022,    2, 0x0a /* Public */,
     150,    2, 1029,    2, 0x2a /* Public | MethodCloned */,
     154,    0, 1034,    2, 0x0a /* Public */,
     155,    5, 1035,    2, 0x0a /* Public */,
     161,    0, 1046,    2, 0x0a /* Public */,
     162,    0, 1047,    2, 0x0a /* Public */,
     163,    1, 1048,    2, 0x0a /* Public */,
     165,    1, 1051,    2, 0x0a /* Public */,
     167,    0, 1054,    2, 0x0a /* Public */,
     168,    1, 1055,    2, 0x0a /* Public */,
     169,    2, 1058,    2, 0x0a /* Public */,
     171,    1, 1063,    2, 0x0a /* Public */,
     172,    0, 1066,    2, 0x0a /* Public */,
     173,    1, 1067,    2, 0x0a /* Public */,
     175,    0, 1070,    2, 0x0a /* Public */,
     176,    0, 1071,    2, 0x0a /* Public */,
     177,    1, 1072,    2, 0x0a /* Public */,
     179,    0, 1075,    2, 0x0a /* Public */,
     180,    0, 1076,    2, 0x0a /* Public */,
     181,    0, 1077,    2, 0x0a /* Public */,
     182,    1, 1078,    2, 0x0a /* Public */,
     184,    0, 1081,    2, 0x0a /* Public */,
     185,    0, 1082,    2, 0x0a /* Public */,
     186,    1, 1083,    2, 0x0a /* Public */,
     188,    2, 1086,    2, 0x0a /* Public */,
     190,    2, 1091,    2, 0x0a /* Public */,
     191,    0, 1096,    2, 0x0a /* Public */,
     192,    0, 1097,    2, 0x0a /* Public */,
     193,    2, 1098,    2, 0x08 /* Private */,
     194,    2, 1103,    2, 0x08 /* Private */,
     196,    0, 1108,    2, 0x08 /* Private */,
     197,    0, 1109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort, QMetaType::QString,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject, QMetaType::QJsonObject,   11,   12,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject, QMetaType::QJsonObject,   11,   15,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject, QMetaType::QJsonObject,   11,   15,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject, QMetaType::QJsonObject,   11,   12,   13,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,    4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   24,   25,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   35,   36,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,   29,   42,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,   29,   45,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   47,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Int,   49,   50,   51,   52,   53,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   47,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QJsonObject,   59,
    QMetaType::Void, QMetaType::QJsonObject,   59,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   62,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   29,   53,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QJsonObject,   65,
    QMetaType::Void, QMetaType::QJsonObject,   65,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   68,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,   29,   71,   72,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   71,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   29,   74,   75,
    QMetaType::Void, QMetaType::QJsonObject,   77,
    QMetaType::Void, QMetaType::QJsonObject,   79,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   71,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,   29,   71,   72,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   71,
    QMetaType::Void, QMetaType::QJsonObject,   77,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   71,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   29,   88,   89,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   91,   71,
    QMetaType::Void, QMetaType::QJsonObject,   93,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   99,
    QMetaType::Void, QMetaType::QJsonObject,  101,
    QMetaType::Void, QMetaType::QJsonObject,  101,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   99,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,  106,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  111,  112,   29,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  115,
    QMetaType::Void, QMetaType::QString,  117,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   29,  119,   75,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   47,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,  151,  152,  153,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,  151,  152,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int,  156,  157,  158,  159,  160,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,  164,
    QMetaType::Void, QMetaType::QJsonObject,  166,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,   29,  170,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,  174,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,  178,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  183,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  187,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  187,  189,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  187,  189,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,   11,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,  195,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void c_Magic_Remote::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c_Magic_Remote *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Update_Magic_DB(); break;
        case 1: _t->Signal_Connect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->Signal_Disconnect(); break;
        case 3: _t->Signal_Set_Token((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->Signal_Send_GET((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< QJsonObject(*)>(_a[3]))); break;
        case 5: _t->Signal_Send_POST((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< QJsonObject(*)>(_a[3]))); break;
        case 6: _t->Signal_Send_PUT((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< QJsonObject(*)>(_a[3]))); break;
        case 7: _t->Signal_Send_DELETE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< QJsonObject(*)>(_a[3]))); break;
        case 8: _t->Init(); break;
        case 9: _t->Connect_Device((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 10: _t->Disconnect_Device(); break;
        case 11: _t->Connect_Done((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->Set_Token_Done((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->Login((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 14: _t->Refresh_Token((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->Begin_Map((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->Get_File_Map(); break;
        case 17: _t->Stop_Scan_Map(); break;
        case 18: _t->Cancel_Scan_Map(); break;
        case 19: _t->Get_Map_Png((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->Rename_Map((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 21: _t->Get_Map_List(); break;
        case 22: _t->Get_Single_Map_Info((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->Use_Map((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: _t->Delete_Map((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 25: _t->Set_Obstacle((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2]))); break;
        case 26: _t->Get_Obstacle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 27: _t->Edit_Map((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2]))); break;
        case 28: _t->Dynamic_Init_Pose((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 29: _t->Temp_Point_Init_Pose((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 30: _t->Get_Init_Pose_Result(); break;
        case 31: _t->Static_Init_Pose((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 32: _t->Query_Default_Map(); break;
        case 33: _t->Recover_Map((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 34: _t->Create_Pos((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 35: _t->Edit_Pos((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 36: _t->Delete_Pos((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 37: _t->Get_Pos_List((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 38: _t->Get_Pos_List((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 39: _t->Create_Graph((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 40: _t->Edit_Graph((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 41: _t->Delete_Graph((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 42: _t->Get_Graph_List((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 43: _t->Get_Graph_Path((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 44: _t->Get_Graph_Path((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 45: _t->Rename_Graph_Path((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 46: _t->Check_Graph_Point((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 47: _t->Check_Graph_Line((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 48: _t->Begin_Record_Path((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 49: _t->Stop_Record_Path(); break;
        case 50: _t->Get_Record_List((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 51: _t->Cancel_Record_Path(); break;
        case 52: _t->Get_Record_Path((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 53: _t->Get_Record_Path((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 54: _t->Edit_Record_Path_Points((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 55: _t->Delete_Record_Path((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 56: _t->Rename_Record_Path((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 57: _t->Check_Graph_Path_Name((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 58: _t->Start_Task((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 59: _t->Pause_Task(); break;
        case 60: _t->Resume_Task(); break;
        case 61: _t->Stop_Task(); break;
        case 62: _t->Stop_Current_Task(); break;
        case 63: _t->Check_Task_Queue_Exist((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 64: _t->Add_Task_Queue((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 65: _t->Update_Task_Queue((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 66: _t->Get_Task_Queue_List((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 67: _t->Get_Task_Queue_Detail((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 68: _t->Delete_Task_Queue((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 69: _t->Get_Task_Is_Finished(); break;
        case 70: _t->Get_Queue_Is_Finished(); break;
        case 71: _t->Get_Task_Process_Status(); break;
        case 72: _t->Get_Task_Log((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 73: _t->Get_Task_Current(); break;
        case 74: _t->Upload_Task_Image((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 75: _t->Down_Task_Image((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 76: _t->Rename_Task_Queue((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 77: _t->Start_Recharge((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 78: _t->Get_Recharge_Status(); break;
        case 79: _t->Dis_Recharge(); break;
        case 80: _t->Get_Dis_Recharge_Status(); break;
        case 81: _t->Pause_Recharge(); break;
        case 82: _t->Resume_Recharge(); break;
        case 83: _t->Cancel_Recharge(); break;
        case 84: _t->Get_Robot_Pos(); break;
        case 85: _t->Get_Robot_Local_Status(); break;
        case 86: _t->Get_Robot_Hardware_Status(); break;
        case 87: _t->Get_Odom(); break;
        case 88: _t->Get_IMU(); break;
        case 89: _t->Get_Laser2D(); break;
        case 90: _t->Get_Laser2D_Scan1(); break;
        case 91: _t->Get_Laser2D_Scan2(); break;
        case 92: _t->Get_Laser2D_Scan3(); break;
        case 93: _t->Get_Laser_Grid(); break;
        case 94: _t->Get_Laser3D(); break;
        case 95: _t->Get_GPS(); break;
        case 96: _t->Get_Angular_Linear(); break;
        case 97: _t->Get_Chassis_Version(); break;
        case 98: _t->Get_Local_Plan_Path(); break;
        case 99: _t->Get_Local_Grid_Plan_Path(); break;
        case 100: _t->Get_Ahl1_RGB_Img(); break;
        case 101: _t->Get_Ahl2_RGB_Img(); break;
        case 102: _t->Get_Ahl1D_RGB_Img(); break;
        case 103: _t->Get_Ahl2D_RGB_Img(); break;
        case 104: _t->Get_Front_Camera(); break;
        case 105: _t->Get_Rear_Camera(); break;
        case 106: _t->Get_Ultrasonic(); break;
        case 107: _t->Robot_Move((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 108: _t->Robot_Move((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 109: _t->Robot_Move_Stop(); break;
        case 110: _t->Move_With_Params((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 111: _t->Cancel_Move_With_Params(); break;
        case 112: _t->Down_Robot_Cfg(); break;
        case 113: _t->Upload_Robot_Cfg((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 114: _t->Update_Robot_Setting((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 115: _t->Reset_Robot_Default(); break;
        case 116: _t->Download_Map((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 117: _t->Upload_Map((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2]))); break;
        case 118: _t->Down_Map_Png((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 119: _t->Get_Logo(); break;
        case 120: _t->Upload_Logo((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 121: _t->Get_Logo_Base64(); break;
        case 122: _t->Get_Background_Base64(); break;
        case 123: _t->Upload_Background((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 124: _t->Get_Sys_Status(); break;
        case 125: _t->Get_Sys_Mac(); break;
        case 126: _t->Get_Local_Sys_Info(); break;
        case 127: _t->Update_Local_Sys_Info((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 128: _t->Get_Robot_About_Us(); break;
        case 129: _t->Get_Robot_Show(); break;
        case 130: _t->Get_All_Logs((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 131: _t->Down_Logs((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 132: _t->Drop_Logs((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 133: _t->Get_Robot_Setting(); break;
        case 134: _t->Reset_Robot_Base_Default(); break;
        case 135: _t->On_Response_Done((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2]))); break;
        case 136: _t->On_Response_Error((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 137: _t->Poll_Status(); break;
        case 138: _t->Try_Reconnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c_Magic_Remote::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Magic_Remote::Update_Magic_DB)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (c_Magic_Remote::*)(QString , quint16 , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Magic_Remote::Signal_Connect)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (c_Magic_Remote::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Magic_Remote::Signal_Disconnect)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (c_Magic_Remote::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Magic_Remote::Signal_Set_Token)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (c_Magic_Remote::*)(QString , QJsonObject , QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Magic_Remote::Signal_Send_GET)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (c_Magic_Remote::*)(QString , QJsonObject , QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Magic_Remote::Signal_Send_POST)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (c_Magic_Remote::*)(QString , QJsonObject , QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Magic_Remote::Signal_Send_PUT)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (c_Magic_Remote::*)(QString , QJsonObject , QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Magic_Remote::Signal_Send_DELETE)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c_Magic_Remote::staticMetaObject = { {
    &c_Object::staticMetaObject,
    qt_meta_stringdata_c_Magic_Remote.data,
    qt_meta_data_c_Magic_Remote,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c_Magic_Remote::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c_Magic_Remote::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c_Magic_Remote.stringdata0))
        return static_cast<void*>(this);
    return c_Object::qt_metacast(_clname);
}

int c_Magic_Remote::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = c_Object::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 139)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 139;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 139)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 139;
    }
    return _id;
}

// SIGNAL 0
void c_Magic_Remote::Update_Magic_DB()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void c_Magic_Remote::Signal_Connect(QString _t1, quint16 _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void c_Magic_Remote::Signal_Disconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void c_Magic_Remote::Signal_Set_Token(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void c_Magic_Remote::Signal_Send_GET(QString _t1, QJsonObject _t2, QJsonObject _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void c_Magic_Remote::Signal_Send_POST(QString _t1, QJsonObject _t2, QJsonObject _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void c_Magic_Remote::Signal_Send_PUT(QString _t1, QJsonObject _t2, QJsonObject _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void c_Magic_Remote::Signal_Send_DELETE(QString _t1, QJsonObject _t2, QJsonObject _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
