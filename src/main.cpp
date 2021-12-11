#include <Arduino.h>
#include <Servo.h>
#include <QTRSensors.h>
#include <Ultrasonic.h>
#include "drive.h"
#include "navigation.h"

using namespace std;

Drive drive;  //iitializes the class responsible for driving the robot

int i=0;

 
void setup() {
  drive.init();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(11, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(6, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);
}

void loop() {

    drive.LineFollowing();
 

  
   
  
}
