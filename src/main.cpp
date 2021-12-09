#include <Arduino.h>
#include <Servo.h>
#include <QTRSensors.h>
#include <Ultrasonic.h>
#include "drive.h"
#include "navigation.h"

using namespace std;

Drive drive;  //iitializes the class responsible for driving the robot

int i=0;
Ultrasonic ultrasonic(3, 1);
 
void setup() {
  drive.init();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(3, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(11, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);
}

void loop() {
   /*Serial.println("--------------------------");
    Serial.print("Outter Left:");
    Serial.print(drive.outterLeftSensor);
    Serial.print("Left:");
    Serial.print(drive.leftSensor);
    Serial.print("Middle:");
    Serial.print(drive.middleSensor);
    Serial.print("Right:");
    Serial.print(drive.rightSensor);
    Serial.print("Outter Right:");
    Serial.println(drive.outterRightSensor);*/
    drive.LineFollowing();
    // Clears the trigPin condition
  //Le as informacoes do sensor, em cm e pol
  // Clears the trigPin condition
  

  //Move forward
   //drive.LineFollowing(navigation);
   
   
    
  //Brake
  /*if (i==3)
  {
    drive.turnRight();
  }
  if(i==5){
    drive.init();
  }*/
  
    
   /* 
    //right_wheel.detatch(9);
    //left_wheel.detatch(10);
    
  //Turn left
    right_wheel.write(180);
    left_wheel.write(90);
  //Turn right
    right_wheel.write(90);
    left_wheel.write(180);*/
  
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}