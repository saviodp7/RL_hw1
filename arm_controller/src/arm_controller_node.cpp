#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64.h"

void jointStateCallback(const sensor_msgs::JointState::ConstPtr& msg) {
    ROS_INFO("Received joint positions:");
    for (size_t i = 0; i < msg->position.size(); i++) {
        ROS_INFO("Joint %ld: %f", i, msg->position[i]);
    }
}

int main(int argc, char **argv) {
    
    ros::init(argc, argv, "arm_controller_node");
    ros::NodeHandle nh;

    // Subscribe to /arm/joint_states with a buffer of size 10
    ros::Subscriber joint_state_sub = nh.subscribe("/arm/joint_states", 10, jointStateCallback);
    // Publishers to */command topics
    ros::Publisher joint0_pub = nh.advertise<std_msgs::Float64>("/arm/joint0_position_controller/command", 1);
    ros::Publisher joint1_pub = nh.advertise<std_msgs::Float64>("/arm/joint1_position_controller/command", 1);
    ros::Publisher joint2_pub = nh.advertise<std_msgs::Float64>("/arm/joint2_position_controller/command", 1);
    ros::Publisher joint3_pub = nh.advertise<std_msgs::Float64>("/arm/joint3_position_controller/command", 1);
    ros::Rate loop_rate(10);

    double amplitude = 100; // Amplitude
    double frequency = 0.5; // Frequency
    double time = ros::Time::now().toSec();
    double command = amplitude * sin(2 * M_PI * frequency * time);

    while (ros::ok())
    {
        time = ros::Time::now().toSec();
        command = amplitude * sin(2 * M_PI * frequency * time);

        std_msgs::Float64 joint0_command;
        joint0_command.data = sin(ros::Time::now().toSec());
        joint0_pub.publish(joint0_command);

        std_msgs::Float64 joint1_command;
        joint1_command.data = cos(ros::Time::now().toSec());
        joint1_pub.publish(joint1_command);

        std_msgs::Float64 joint2_command;
        joint2_command.data = sin(ros::Time::now().toSec());
        joint2_pub.publish(joint2_command);

        std_msgs::Float64 joint3_command;
        joint3_command.data = cos(ros::Time::now().toSec());
        joint3_pub.publish(joint3_command);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
