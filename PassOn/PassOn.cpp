#include "custom_msgs/msg/ros2_xeno.hpp"
#include "std_msgs/msg/float64.hpp" 
#include "rclcpp/rclcpp.hpp"
#include <functional>

class PassOn : public rclcpp::Node {
public:
    PassOn() : Node("pass_on")
    {
        // Initialize cross buffers & polling
        initialize();
    }

    void initialize()
    {
        RCLCPP_INFO(this->get_logger(), "Creating publisher for topic 'Ros2Xeno'");
        publisher_ = this->create_publisher<custom_msgs::msg::Ros2Xeno>("Ros2Xeno", 1000);

        RCLCPP_INFO(this->get_logger(), "Subscribing to topic 'left_motor_setpoint_vel'");
        subscriptionL_ = this->create_subscription<std_msgs::msg::Float64>("left_motor_setpoint_vel", 10, std::bind(&PassOn::motor_setpoint_callbackL, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "Subscribing to topic 'right_motor_setpoint_vel'");
        subscriptionR_ = this->create_subscription<std_msgs::msg::Float64>("right_motor_setpoint_vel", 10, std::bind(&PassOn::motor_setpoint_callbackR, this, std::placeholders::_1));

        setpointL = 0.0; // Initialize to 0.0
        setpointR = 0.0; // Initialize to 0.0
    }

    void motor_setpoint_callbackR(const std_msgs::msg::Float64::SharedPtr msg)
    {
        setpointR = msg->data;
        publishSetpoints();
    }

    void motor_setpoint_callbackL(const std_msgs::msg::Float64::SharedPtr msg)
    {
        setpointL = msg->data;
        publishSetpoints();
    }

    void publishSetpoints()
    {
        custom_msgs::msg::Ros2Xeno msg;
        msg.x = setpointR;
        msg.y = setpointL;
        publisher_->publish(msg);
    }

private:
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscriptionL_;
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscriptionR_;

    rclcpp::Publisher<custom_msgs::msg::Ros2Xeno>::SharedPtr publisher_;

    double setpointL; // Change the type to double
    double setpointR; // Change the type to double
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PassOn>());
    rclcpp::shutdown();
    return 0;
}
