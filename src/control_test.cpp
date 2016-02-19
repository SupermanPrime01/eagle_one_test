/*
Name: sub_nav

Testing how to subscribe to different topics that the QuadCopter publishes

Written by: Josh Saunders (jay3ss)
Date created: 1/26/2016
Modified by: Josh Saunders (jay3ss)
Date modified: 2/8/2016
*/

#include <ros/ros.h>
#include <ardrone_autonomy/Navdata.h>
#include <nav_msgs/Odometry.h>
#include <eagle_one_test/ARNavdata.h>
#include <eagle_one_test/Drone.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "sub_nav");
    ros::NodeHandle n;
    ros::Rate rate(5);

    geometry_msgs::Twist twist_msg;

    Drone qc;

    ros::Subscriber tag_info = n.subscribe("/ardrone/navdata", 1000, &Drone::set_navdata, &qc);
    ros::Publisher follow = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

    while(ros::ok())
    {
        if (qc.getTagCount() >= 1)
        {
            twist_msg.linear.x = qc.calcTagDistanceX(qc.getTagX()) / 36;
            twist_msg.linear.y = qc.calcTagDistanceY(qc.getTagX()) / 64;

            if ((qc.getYaw() > 0 ) && (qc.getYaw() <= 180))
            {
                twist_msg.angular.z = qc.calcYawDistance(qc.getYaw()) / -16;
            }
            else if ((qc.getYaw() > 180 ) && (qc.getYaw() <= 359.9999))
            {
                twist_msg.angular.z = qc.calcYawDistance(qc.getYaw()) / 16;
            }
        }
        else
        {
            twist_msg.linear.x = 0.0;
            twist_msg.linear.y = 0.0;
            twist_msg.angular.z = 0.0;
        }
        std::cout << "Tag: (" << qc.getTagX() << ", " << qc.getTagX() << ")\n";
        std::cout << "Vel: (" << twist_msg.linear.x << ", " << twist_msg.linear.y << ")\n";
        std::cout << "Yaw: (" << qc.getYaw() << ")\n";
        std::cout << "Yaw Vel: (" << twist_msg.angular.z << ")\n";
        qc.print_tag_distance();
        //twist_msg.linear.x = qc.getTagX();
        //twist_msg.linear.y = qc.getTagY();
        follow.publish(twist_msg);
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}