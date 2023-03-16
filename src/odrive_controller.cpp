#include "ros/ros.h"
#include "sensor_msgs/JointState.h"

#include <sstream>

#define PI 3.14159265359

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "bolt_controller");
  ros::NodeHandle n;

  ros::Publisher joint_desire_pub = n.advertise<sensor_msgs::JointState>("joint_set", 5);

  ros::Rate loop_rate(200);

  int count = 0;
  bool increasing_state = true;

  while (ros::ok())
  {
    sensor_msgs::JointState joint_setmsg;

    joint_setmsg.name = {"L_Hip_AA", "L_Hip_FE", "L_Knee", "R_Hip_AA", "R_Hip_FE", "R_Knee"};
    
    // for (int i = 0; i < msg.name.size(); i++)
    // {
    //     joint_setmsg.effort[i] = 0.5;
    // }


    // joint_setmsg.effort = {count * 0.0001,0,0,0,0,0};
    joint_setmsg.position = {count * PI/500.0,0,0,0,0,0};

    // joint_setmsg.effort[0] = 0.5;
    // joint_setmsg.effort[1] = 0.0;
    // joint_setmsg.effort[2] = 0.0;
    // joint_setmsg.effort[3] = 0.0;
    // joint_setmsg.effort[4] = 0.0;
    // joint_setmsg.effort[5] = 0.0;
    
    joint_desire_pub.publish(joint_setmsg);

    ros::spinOnce();

    loop_rate.sleep();
    if (count < 500 && increasing_state)
      count++;
    else if (count == 500)
    {
      increasing_state = false;
      count--;
    }
    else
     {
      count--; 
      if(count < -500)
        increasing_state = true;
     }
  }


  return 0;
}