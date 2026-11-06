#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <chrono>
#include <memory>
#include <iostream>
#include "cgx_driver/robotapi.h"
#include "cgx_driver/basestruct.h"
#include <cmath>  




class JointStatePublisher : public rclcpp::Node {
public:
    JointStatePublisher()
        : Node("joint_state_publisher"), robotHandle(0) {
        CRresult result = cr_create_robot(&robotHandle, "192.168.6.6", 2323, "123");
        if (result != sucess) {
            RCLCPP_ERROR(this->get_logger(), "Failed to connect to the robot. Error code: %d", result);
            return;
        }
        publisher_ = this->create_publisher<sensor_msgs::msg::JointState>("/joint_states", 10);

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),  // 100ms 发布一次
            std::bind(&JointStatePublisher::publishJointStates, this));
    }

private:
    void publishJointStates() {
        double pos[6];
        CRresult result = cr_get_jointActualPos(robotHandle, pos);  
        if (result != sucess) {
            RCLCPP_ERROR(this->get_logger(), "Failed to get joint positions. Error code: %d", result);
            return;
        }

        std::vector<double> joint_positions(pos, pos + 6);
        for (double& angle : joint_positions) {
            angle = angle * M_PI / 180.0;
        }

        auto message = sensor_msgs::msg::JointState();
        message.header.stamp = this->now();
        message.name = {"G6_joint1", "G6_joint2", "G6_joint3", "G6_joint4", "G6_joint5", "G6_joint6"}; 
        message.position = joint_positions;
        publisher_->publish(message);
    }

    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    RobotHandle robotHandle;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JointStatePublisher>());
    rclcpp::shutdown();
    return 0;
}










