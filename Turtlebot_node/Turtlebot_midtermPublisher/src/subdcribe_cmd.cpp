#include <subscribe_cmd.h>

// Motor pins
const int LEFT_PWM_PIN = 5; // PWM pin for left motor speed control
const int LEFT_INT1_PIN = 6; // Control pin 1 for left motor
const int LEFT_INT2_PIN = 7; // Control pin 2 for left motor
const int RIGHT_PWM_PIN = 9; // PWM pin for right motor speed control
const int RIGHT_INT1_PIN = 8; // Control pin 1 for right motor
const int RIGHT_INT2_PIN = 4; // Control pin 2 for right motor

// Motor calibration values
const float MAX_SPEED = 210.0; // Maximum RPM of the motor
const float WHEEL_RADIUS = 3.3; // Radius of the wheel in centimeters
const float center_distance = 16; // 


void intiate_motors(){
  pinMode(LEFT_PWM_PIN, OUTPUT);
  pinMode(LEFT_INT1_PIN, OUTPUT);
  pinMode(LEFT_INT2_PIN, OUTPUT);
  pinMode(RIGHT_PWM_PIN, OUTPUT);
  pinMode(RIGHT_INT1_PIN, OUTPUT);
  pinMode(RIGHT_INT2_PIN, OUTPUT);
}


void CMD_TO_PWM(float linear_x, float angular_z){

    // Map linear and angular velocities to left and right motor PWM signals
    float linear_vel = linear_x;
    float angular_vel = angular_z;

     // Calculate left and right wheel velocities based on linear and angular velocities
    float rpm_left = (((linear_vel*2 + center_distance*angular_vel)/(2*WHEEL_RADIUS))*60)/(2*PI); // Adjusting for angular velocity
    float rpm_right = (((linear_vel*2 - center_distance*angular_vel)/(2*WHEEL_RADIUS))*60)/(2*PI);// Adjusting for angular velocity
    
    // Set direction of motors based on velocities
    if (rpm_left >= 0) {
        digitalWrite(LEFT_INT1_PIN, LOW);
        digitalWrite(LEFT_INT2_PIN, HIGH);
    } else {
        digitalWrite(LEFT_INT1_PIN, HIGH);
        digitalWrite(LEFT_INT2_PIN, LOW);

        rpm_left *= -1;
    }

    if (rpm_right >= 0) {
        digitalWrite(RIGHT_INT1_PIN, LOW);
        digitalWrite(RIGHT_INT2_PIN, HIGH);
    } else {
        digitalWrite(RIGHT_INT1_PIN, HIGH);
        digitalWrite(RIGHT_INT2_PIN, LOW);

        rpm_right *= -1;
    }

    if(rpm_left > 100){
        rpm_left = 100;
    }
    if(rpm_right > 100){
        rpm_right = 100;
    }

    // Map wheel velocities to PWM signals
    int left_pwm = map((long)(rpm_left), 0, MAX_SPEED, 0, 255);
    int right_pwm = map((long)(rpm_right), 0, MAX_SPEED, 0, 255);

    //move the motors by the calculated pwm signals
    analogWrite(LEFT_PWM_PIN, left_pwm);
    analogWrite(RIGHT_PWM_PIN, right_pwm);
}