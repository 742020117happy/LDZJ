#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include "cgx_driver/robotapi.h"
#include "cgx_driver/basestruct.h"

class ReducedModeMonitor : public rclcpp::Node {
public:
    ReducedModeMonitor() 
        : Node("reduced_mode_monitor"), robotHandle(0) 
    {

        CRresult res = cr_create_robot(&robotHandle, "192.168.6.6", 2323, "123");
        if (res != sucess) {
            RCLCPP_ERROR(this->get_logger(), "Failed to connect to the robot. Error code: %d", res);

        } else {
            publisher_ = this->create_publisher<std_msgs::msg::Bool>("/reduced_mode_state", 10);
            timer_ = this->create_wall_timer(
                std::chrono::milliseconds(50),  // 50ms检测一次
                std::bind(&ReducedModeMonitor::publishReducedMode, this));
            RCLCPP_INFO(this->get_logger(), "Reduced Mode Monitor is running");
        }
    }

private:
    void publishReducedMode() {
        auto message = std_msgs::msg::Bool();
        message.data = isReducedModeActive();
        publisher_->publish(message);
    }
    bool isReducedModeActive() {
        int reduceModeReady = 0, reduceModeIO = 0;
        SafetyIOInput safeIOInput;
        
        for (int i = 0; i < 4; i++) {
            CRresult res = cr_cfg_safety_io_input_get(robotHandle, i, &safeIOInput);
            if (res != sucess) {
                RCLCPP_WARN(this->get_logger(), "Failed to get safety IO config for index %d. Error code: %d", i, res);
                continue;
            }
            
            if (safeIOInput == reducedMode) {
                reduceModeReady = 1;
                reduceModeIO = i * 2;
                break;
            }
        }

        if (reduceModeReady) {
            int reduceIO1 = 0, reduceIO2 = 0;
            CRresult res1 = cr_get_configDigitalIn(robotHandle, reduceModeIO, &reduceIO1);
            CRresult res2 = cr_get_configDigitalIn(robotHandle, reduceModeIO + 1, &reduceIO2);
            
            if (res1 != sucess || res2 != sucess) {
                return false;
            }
            
            if (reduceIO1 || reduceIO2) {
                return true;
            }
        }
        return false;
    }


    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    RobotHandle robotHandle;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ReducedModeMonitor>());
    rclcpp::shutdown();
    return 0;
}