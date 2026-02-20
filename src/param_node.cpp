#include "rclcpp/rclcpp.hpp"

class ParamNode : public rclcpp::Node
{
public:
    ParamNode() : Node("param_node")
    {
        // Declare parameters with default values
        this->declare_parameter<std::string>("robot_name", "ROS2Bot");
        this->declare_parameter<double>("max_speed", 1.5);
        this->declare_parameter<bool>("enabled", true);

        // Create timer (2000ms)
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(2000),
            std::bind(&ParamNode::timer_callback, this)
        );
    }

private:
    void timer_callback()
    {
        // Read parameters
        std::string robot_name = this->get_parameter("robot_name").as_string();
        double max_speed = this->get_parameter("max_speed").as_double();
        bool enabled = this->get_parameter("enabled").as_bool();

        RCLCPP_INFO(this->get_logger(),
                    "Robot: %s, Max Speed: %f, Enabled: %s",
                    robot_name.c_str(),
                    max_speed,
                    enabled ? "true" : "false");
    }

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ParamNode>());
    rclcpp::shutdown();
    return 0;
}
