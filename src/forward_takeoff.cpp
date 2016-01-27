/*
Name: forward_takeoff

Autonomous takeoff of QuadCopter (QC) while moving forward

Inputs: None
Outputs: QC takes off while moving forward

Written by: Josh Saunders (jay3ss)
Date created: 1/21/2016
Modified by: Josh Saunders (jay3ss)
Date modified: 1/27/2016
*/
#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv)
{
	std_msgs::Empty emp_msg;
	geometry_msgs::Twist forward_msg;

	ROS_INFO("Flying AR.Drone 2.0");
	ros::init(argc, argv,"ARDrone_test");
    ros::NodeHandle node;
    ros::Rate loop_rate(50);
	ros::Publisher pub_takeoff;
	ros::Publisher pub_land;
	ros::Publisher pub_forward;

	// Values to move forward
	// -1.0 < direction < 1.0
	// Forward -> x, Backward -> -x
	// Right -> y, Left -> -y
	// Up -> z, Down -> -z
	// | x  > 0.5 is pretty fast
	forward_msg.linear.x=0.5;
	forward_msg.linear.y=0.0;
	forward_msg.linear.z=0.0;
	forward_msg.angular.x=0.0;
	forward_msg.angular.y=0.0;
	forward_msg.angular.z=0.0;

	int queue = 100;

	/* Message queue length is just 100 */
	pub_takeoff = node.advertise<std_msgs::Empty>("/ardrone/takeoff", queue);
	pub_land = node.advertise<std_msgs::Empty>("/ardrone/land", queue);
	pub_forward = node.advertise<geometry_msgs::Twist>("/cmd_vel", queue);

 	while (ros::ok())
	{
		double time_start=(double)ros::Time::now().toSec();

		/* Send command for seven seconds*/
		while ((double)ros::Time::now().toSec()< time_start+7.0)
		{
			pub_takeoff.publish(emp_msg); /* launches the drone */
			ros::spinOnce();
			loop_rate.sleep();
		}//time loop
		ROS_INFO("AR.Drone 2.0 launched");
		
		while ((double)ros::Time::now().toSec()< time_start+12.0)
		{
			ROS_INFO("AR.Drone 2.0 moving forward");
			pub_forward.publish(forward_msg);
			ros::spinOnce();
			loop_rate.sleep();
		}//time loop


		/* Message queue length is just 1 */
		pub_land.publish(emp_msg);
		ros::spinOnce();

		ROS_INFO("AR.Drone 2.0 landed");

		exit(0);
	}//ros::ok loop

}//main
