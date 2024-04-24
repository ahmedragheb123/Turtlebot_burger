//include libraries needed
#include<Arduino.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <joystick.h>

//intiate ros 
ros::NodeHandle nh;
geometry_msgs::Twist cmd_vel_msg;
ros::Publisher cmd_vel_pub("our_cmd_vel", &cmd_vel_msg);

//previous time and interval of the task used in rtos
unsigned long prevtime = 0;
const long interval = 100; 

void setup() {
//intiating node
  nh.initNode();
  nh.advertise(cmd_vel_pub);
}

void loop() {
   
    // Map joystick data to linear and angular velocities
    cmd_vel_msg.linear.x = get_linear_x(); 
    cmd_vel_msg.angular.z = get_angular_z(); // Scale to -1.0 to 1.0 range

    //current time used in rtos
    unsigned long currenttime = millis();

    // RTOS
    if (currenttime - prevtime >= 100)
    {
      prevtime = currenttime;

      // Publish cmd_vel message
      cmd_vel_pub.publish(&cmd_vel_msg);
    }

    nh.spinOnce();
}