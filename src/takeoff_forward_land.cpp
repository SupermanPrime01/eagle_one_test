/*
takeoff_forward_land

The QuadCopter (QC) will take off move forward and then land

Inputs
Outputs

Created by: Josh Saunders
Date Created: 1/29/2016

Modified by:
Date Modified:

*/
#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <ardrone_autonomy/Navdata.h>
#include <nav_msgs/Odometry.h>

// Declare modes
#define SECURE  0
#define TAKEOFF 1
#define FLYING  2
#define LANDING 3

void arTakeoffCallBack(const std_msgs::Empty::ConstPtr& msg);
int arAltdCallback(const ardrone_autonomy::Navdata::ConstPtr& msg);

int main(int argc, char** argv)
{
    ros::init(argc, argv, "takeoff_forward_land");
    // empty -> for takeoff, land
    // flight_command -> flight maneuvers
    std_msgs::Empty empty;
    geometry_msgs::Twist flight_command;
    int queue = 1000;

    // Nodehandler, publishers, subscribers
    ros::NodeHandle node;
    ros::Publisher pub_takeoff = node.advertise<std_msgs::Empty>(
        "/ardrone/takeoff", queue);
    ros::Subscriber sub_atld = node.subscribe<ardrone_autonomy::Navdata>(
                "ardrone_autonomy/Navdata", queue, &arAltdCallback);

    // We start off in secure mode
    int mode = SECURE;
    ros::Rate rate(200); // Hz

    mode = TAKEOFF;

    while(ros::ok())
    {
        switch(mode)
        {
            case TAKEOFF  :
            {
                ROS_INFO("MODE: TAKEOFF");
                pub_takeoff.publish(empty);
                ros::spinOnce();
                mode = FLYING;
                break;
            }
            case FLYING   :
            {
                ROS_INFO("MODE: FLYING");
                break;
            }
            case LANDING  :
            {
                ROS_INFO("MODE: LANDING");
                break;
            }
            default:
            {
                ROS_INFO("Quitting");
                exit(0);
            }
        }
        loop_rate.sleep();
    }

    return 0;
}

void arTakeoffCallBack(const std_msgs::Empty::ConstPtr& msg)
{

}

int arAltdCallback(const ardrone_autonomy::Navdata::ConstPtr& msg)
{

}
