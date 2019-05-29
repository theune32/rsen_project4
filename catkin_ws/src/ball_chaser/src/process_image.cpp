#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

class ProcessImage
{
public:
    ProcessImage()
    {
        // Create service for creating service request for moving the robot
        client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

        // Subscribe to /camera/rgb/image_raw to receive the camera images
        sub = n.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback,this);
        
    }

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    //Message created with the requested linx and angz values and call is made.
    ball_chaser::DriveToTarget msg;
    msg.request.linear_x = lin_x;
    msg.request.angular_z = ang_z;

    if(!client.call(msg))
        ROS_ERROR("Failed to accept DriveToTarget request");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    float req_lin_x = 0;
    float req_ang_z = 0;
    // size_t n = sizeof(img.data)/sizeof(img.data[0]);
    // ROS_INFO("height: %i width: %i step: %i", img.height, img.width, img.step);
    // ROS_INFO("size is: %lu", n);
    for (int i = 0; i < img.height * img.step; i += 3) {
        // check for all 3 color channels if the value is 255
        if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel) {
            ROS_DEBUG("white detected");
            // Make sure to use step instead of width, this is due to the 3 color channels, so step is 3 * width
            int mod = (i % img.step);
            float left_side_end = img.step / 3; 
            float right_begin = img.step * 2 / 3;
            if( mod < left_side_end ) {
                ROS_DEBUG("Left");
                req_ang_z = 0.5;
            } 
            else if (mod > right_begin) {
                ROS_DEBUG("Right");
                req_ang_z = -0.5;
            } 
            else {
                ROS_DEBUG("Straight ahead");
                req_lin_x = 0.5;
                }
            drive_robot(req_lin_x, req_ang_z);
            ROS_DEBUG("linx %f angz %f", req_lin_x, req_ang_z);
            break;
        } 
    }
    drive_robot(req_lin_x, req_ang_z);
}

private:
    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::ServiceClient client;
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "process_image");

    // Create ProcessImage object to handle all things
    ProcessImage procesImage;

    ros::spin();

    return 0;
}