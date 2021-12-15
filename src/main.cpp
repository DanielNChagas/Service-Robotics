#include <Arduino.h>
#include <Servo.h>
#include <QTRSensors.h>
#include <Ultrasonic.h>
#include "drive.h"
#include "limbs.h"
#include "navigation.h"

using namespace std;

Drive drive;  //initializes the class responsible for driving the robot
 
void setup() {
  drive.init(); // initializes all classes, sensors and actuators
  
  pinMode(11, OUTPUT); // Sets the trigPin as an OUTPUT for the sonar sensor
  pinMode(6, INPUT); // Sets the echoPin as an INPUT for the sonar sensor
  pinMode(13, INPUT);

  Serial.begin(9600);
}

void loop() { 
  drive.LineFollowing();
  
}
