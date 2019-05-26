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
    msg.request.angular_z - ang_z;

    if(!client.call(msg))
        ROS_ERROR("Failed to accept DriveToTarget request");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    // Check for all pixels if there is a bright white one. And the relative position
    // image is segmented in 3 equal size parts
    for (int i = 0; i < img.height * img.step; i++) {
        if (img.data[i] == 255) {
            // matrix data is steps * rows
            int mod = i % img.width;
            float left_side_end = img.width / 3; //
            float right_begin = img.width * 2 / 3;
            if (mod <= left_side_end) {
                // white pixel on the left, go left
                drive_robot(0.0, 0.5);
            }
            else {
                if (mod > right_begin) {
                    // white pixel on the right, go right
                    drive_robot(0.0, -0.5);
                } else {
                    // white pixel in the middle, straight ahead
                    drive_robot(0.5, 0.0);
                }

            }
            break;
        } else {
        // no white pixel to be seen, stop!
        drive_robot(0.0, 0.0);
        } 
    }
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