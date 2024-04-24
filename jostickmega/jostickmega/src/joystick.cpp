#include <joystick.h>

// Joystick pins
const int VRX_PIN = A0; // Connect joystick VRx to analog pin A0
const int VRY_PIN = A1; // Connect joystick VRy to analog pin A1

// Joystick calibration values
const int JOY_MIN = 0;
const int JOY_MAX = 1023;

float get_linear_x(){

    //get joy_y reading
    int joy_y = analogRead(VRY_PIN);

    //to eliminate any vibrations from joystick
    if (joy_y >= 480 && joy_y <= 540)
    {
      joy_y = 512;
    }

    // Scale linear velocity from -72 to 72 range which are the maximum velocities 
    float cmd_linear_x = (float) map(joy_y, JOY_MIN, JOY_MAX, -72, 72);

    
    return cmd_linear_x;
}

float get_angular_z(){

    //get joy_y reading
    int joy_x = analogRead(VRX_PIN);

    //to eliminate any vibrations from joystick
    if (joy_x >= 500 && joy_x <= 520)
    {
      joy_x = 512;
    }

    // Scale angular velocity from -9 to 9 range which are the maximum velocities 
    float cmd_angular_z = (float) map(joy_x, JOY_MIN, JOY_MAX, -90, 90)/10.0;

    //
    return cmd_angular_z;
}
 