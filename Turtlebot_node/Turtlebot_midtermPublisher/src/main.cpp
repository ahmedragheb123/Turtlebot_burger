// Include necessary libraries for the Arduino board
#include <Arduino.h>
#include <Encoder.h>
#include <MPU6050.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <subscribe_cmd.h>

// Define wheel radius and base
#define wheel_radius  0.033  //in meters
#define wheel_base  0.16     //in meters

// Initialize ROS node handle
ros::NodeHandle nh;

MPU6050 mpu;


unsigned long previousT=0;

// Declare external variables for right and left RPM
extern float rightRPM;
extern float leftRPM;


// Initialize ROS publisher
geometry_msgs::Twist cmd_vel;
ros::Publisher pub("/cmd_vel", &cmd_vel);



// Initialize ROS publisher
void cmdVelCallback(const geometry_msgs::Twist& cmd_vel_msg) {

  CMD_TO_PWM( (float) cmd_vel_msg.linear.x, (float) cmd_vel_msg.angular.z);

  Encoder_check();
  Vector acc = mpu.readNormalizeAccel();
  Vector gyr = mpu.readNormalizeGyro();

  float vr = ((rightRPM)*2*PI) / 60; // rad/s - velocity right wheel
  float vl = (leftRPM*2*PI) / 60;   // rad/s - velocity left wheel

  float linear = (vr +vl)*wheel_radius/2;
  float angular = (float) map((long) gyr.XAxis,-2010,2010,-27,27) / 3.0;

  cmd_vel.linear.x = linear;
  cmd_vel.angular.z = angular; 

  pub.publish(&cmd_vel);
}
    


ros::Subscriber<geometry_msgs::Twist> cmd_vel_sub("our_cmd_vel", &cmdVelCallback);



void setup(){

  
  nh.getHardware()->setBaud(57600);
  // Initialize ROS node
  nh.initNode();
  nh.advertise(pub);
  nh.subscribe(cmd_vel_sub);

  // Initialize the encoder, motors, and MPU6050
  Encoder_init();
  intiate_motors();
  mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G);
 
  // Calibrate gyroscope. The calibration must be at rest.
  mpu.calibrateGyro();

}

void loop(){
  // Spin ROS node
  nh.spinOnce();
}