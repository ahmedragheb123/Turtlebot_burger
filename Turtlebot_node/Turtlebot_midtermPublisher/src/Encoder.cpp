#include <Encoder.h>

// Constants for encoder pins
const int encoderPinsRight[2] = {2, 10}; // Encoder pins for right motor
const int encoderPinsLeft[2] = {3, 11}; // Encoder pins for left motor

// Interval in milliseconds for RPM calculation
const int interval = 1000; 

// Global variables for encoder counts and RPM values
volatile long rightEncoderCount = 0;
volatile long leftEncoderCount = 0;
unsigned long previousMillis = 0;
float rightRPM = 0;
float leftRPM = 0;


// Interrupt service routine for right motor encoder
void rightEncoder() {
  if (digitalRead(encoderPinsRight[0]) == digitalRead(encoderPinsRight[1])) {
    rightEncoderCount++;
  } else {
    rightEncoderCount--;
  }
}

// Interrupt service routine for left motor encoder
void leftEncoder() {
  if (digitalRead(encoderPinsLeft[0]) == digitalRead(encoderPinsLeft[1])) {
    leftEncoderCount--;
  } else {
    leftEncoderCount++;
  }
}

// Setup function to initialize encoder pins and attach interrupts
void Encoder_init() {
  // Set encoder pins as inputs
  for (int i = 0; i < 2; i++) {
    pinMode(encoderPinsRight[i], INPUT_PULLUP);
    pinMode(encoderPinsLeft[i], INPUT_PULLUP);
  }

  // Attach encoder interrupts
  attachInterrupt(digitalPinToInterrupt(encoderPinsRight[0]), rightEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinsLeft[0]), leftEncoder, CHANGE);
}

// Main loop function
void Encoder_check() {
  unsigned long currentMillis = millis();

  // Calculate RPM for right motor
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    rightRPM = ((rightEncoderCount / 2.0) / PPR) * 60;
    rightEncoderCount = 0;

    // Calculate RPM for left motor
    leftRPM = ((leftEncoderCount / 2.0) / PPR) * 60;
    leftEncoderCount = 0;
  }
}
