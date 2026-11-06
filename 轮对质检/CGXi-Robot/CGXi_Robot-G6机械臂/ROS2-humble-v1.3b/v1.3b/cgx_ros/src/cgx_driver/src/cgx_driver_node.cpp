#include <iostream>
#include "cgx_include/robotapi.h"
#include "cgx_include/basestruct.h"
#include "rclcpp/rclcpp.hpp"
#include "cgx_driver/srv/cgx_driver_service.hpp"

using namespace std::chrono_literals;

class CgxDriverNode : public rclcpp::Node
{
public:
    CgxDriverNode()
        : Node("cgx_driver_node")
    {
        service_movej_ = this->create_service<cgx_driver::srv::CgxDriverService>(
            "cr_moveJ",
            std::bind(&CgxDriverNode::handle_movej, this, std::placeholders::_1, std::placeholders::_2));

        service_movel_ = this->create_service<cgx_driver::srv::CgxDriverService>(
            "cr_moveL",
            std::bind(&CgxDriverNode::handle_movel, this, std::placeholders::_1, std::placeholders::_2));

        service_move_joint_ = this->create_service<cgx_driver::srv::CgxDriverService>(
            "cr_move_joint",
            std::bind(&CgxDriverNode::handle_move_joint, this, std::placeholders::_1, std::placeholders::_2));

        service_move_line_ = this->create_service<cgx_driver::srv::CgxDriverService>(
            "cr_move_line",
            std::bind(&CgxDriverNode::handle_move_line, this, std::placeholders::_1, std::placeholders::_2));

        service_movejog_ = this->create_service<cgx_driver::srv::CgxDriverService>(
            "cr_moveJog",
            std::bind(&CgxDriverNode::handle_movejog, this, std::placeholders::_1, std::placeholders::_2));
    }

private:
    void handle_movej(
        const std::shared_ptr<cgx_driver::srv::CgxDriverService::Request> request,
        std::shared_ptr<cgx_driver::srv::CgxDriverService::Response> response)
    {
        execute_robot_command(request, response, "cr_moveJ");
    }

    void handle_movel(
        const std::shared_ptr<cgx_driver::srv::CgxDriverService::Request> request,
        std::shared_ptr<cgx_driver::srv::CgxDriverService::Response> response)
    {
        execute_robot_command(request, response, "cr_moveL");
    }

    void handle_move_joint(
        const std::shared_ptr<cgx_driver::srv::CgxDriverService::Request> request,
        std::shared_ptr<cgx_driver::srv::CgxDriverService::Response> response)
    {
        execute_robot_command(request, response, "cr_move_joint");
    }

    void handle_move_line(
        const std::shared_ptr<cgx_driver::srv::CgxDriverService::Request> request,
        std::shared_ptr<cgx_driver::srv::CgxDriverService::Response> response)
    {
        execute_robot_command(request, response, "cr_move_line");
    }

    void handle_movejog(
        const std::shared_ptr<cgx_driver::srv::CgxDriverService::Request> request,
        std::shared_ptr<cgx_driver::srv::CgxDriverService::Response> response)
    {
        execute_robot_command(request, response, "cr_moveJog");
    }

    void execute_robot_command(
        const std::shared_ptr<cgx_driver::srv::CgxDriverService::Request> request,
        std::shared_ptr<cgx_driver::srv::CgxDriverService::Response> response,
        const std::string& command)
    {
        // 初始化机器人连接
        RobotHandle robotHandle;
        CRresult result = cr_create_robot(&robotHandle, "192.168.6.6", 2323, "123");
        if (result != 0) {
            response->ret = -1;
            response->message = "Failed to connect to robot."+ std::to_string(result);
            return;
        }

        PointControlPara pointControlPara;
        for (int i = 0; i < 6; i++) {
            pointControlPara.pose[i] = request->pose[i];
            pointControlPara.jointpos[i] = request->jointpos[i];
            pointControlPara.speed[i] = request->speed[i];
            pointControlPara.acc[i] = request->acc[i];
            pointControlPara.tcpOffset[i] = 0;
            pointControlPara.coordinatePose[i] = 0;
            pointControlPara.jerk[i] = 60;  // 默认值
        }

        if (request->coordinate_type == "joint") {
            pointControlPara.coordinateType = jointCoordinate;
        } else if (request->coordinate_type == "base") {
            pointControlPara.coordinateType = baseCoordinate;
        } else {
            response->ret = -1;
            response->message = "Invalid coordinate type. Use 'joint' or 'base'.";
            return;
        }

        pointControlPara.tcpID = -1;
        pointControlPara.pointTransType = (request->point_trans_type == "stop") ? pointTransStop : pointTransConstantSpeed;
        pointControlPara.pointTransRadius = request->point_trans_radius;
        pointControlPara.poseTranType = poseTranMoveToTargetPose;
        pointControlPara.motiontriggerMode = MovetriggerbyOnlyRpc;

        int isBlock = request->is_block;

        if (command == "cr_moveJ") {
            result = cr_moveJ(robotHandle, pointControlPara);
        } else if (command == "cr_moveL") {
            result = cr_moveL(robotHandle, pointControlPara);
        } else if (command == "cr_move_joint") {
            result = cr_move_joint(robotHandle, pointControlPara, isBlock);
        } else if (command == "cr_move_line") {
            result = cr_move_line(robotHandle, pointControlPara, isBlock);
        } else if (command == "cr_moveJog") {
            result = cr_moveJog(robotHandle, pointControlPara);
        } else {
            response->ret = -1;
            response->message = "Invalid command.";
            return;
        }

        if (result != 0) {
            response->ret = -1;
            response->message = "Failed to execute " + command + "."+ std::to_string(result);
            return;
        }

        // 断开机器人连接
        result = cr_destroy_robot(robotHandle);
        if (result != 0) {
            response->ret = -1;
            response->message = "Failed to disconnect from robot."+ std::to_string(result);
            return;
        }

        response->ret = 0;
        response->message = command + " executed successfully.";
    }

    rclcpp::Service<cgx_driver::srv::CgxDriverService>::SharedPtr service_movej_;
    rclcpp::Service<cgx_driver::srv::CgxDriverService>::SharedPtr service_movel_;
    rclcpp::Service<cgx_driver::srv::CgxDriverService>::SharedPtr service_move_joint_;
    rclcpp::Service<cgx_driver::srv::CgxDriverService>::SharedPtr service_move_line_;
    rclcpp::Service<cgx_driver::srv::CgxDriverService>::SharedPtr service_movejog_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CgxDriverNode>());
    rclcpp::shutdown();
    return 0;
}