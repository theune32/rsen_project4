#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include "geometry_msgs/Twist.h"
#include <std_msgs/Float64.h>

class BallChaser
{
public:
  BallChaser()
  {
    // Define a publisher for publishing commands for the robots actuator
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // Define a service for handling drive requests
    command_robot = n.advertiseService("/ball_chaser/command_robot", &BallChaser::handle_drive_request, this);
    ROS_INFO("Ready to drive requests");

  }

// Handles the drive request and publishes them towards the actuator
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
    ball_chaser::DriveToTarget::Response& res)
{

    ROS_INFO("DriveToTarget received - lin_x:%.2f, ang_z:%.2f", (float)req.linear_x, (float)req.angular_z);
    geometry_msgs::Twist msg;
    msg.linear.x = req.linear_x;    msg.angular.z = req.angular_z;

    // Publishes wheel velocties for the actuator
    motor_command_publisher.publish(msg);

    // Return a response message
    res.msg_feedback = "Requested wheel velocities set - lin_x " + std::to_string(req.linear_x) + " , ang_z: " + std::to_string(req.angular_z);
    ROS_INFO_STREAM(res.msg_feedback);

    return true;
}

private:
  ros::NodeHandle n; 
  ros::Publisher motor_command_publisher;
  ros::ServiceServer command_robot;
};

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "ball_chaser");

  //Create Ballchaser object that handles everything
  BallChaser ballChaser;

  ros::spin();

  return 0;
}