#include <Arduino.h>
#include <Servo.h>
#include <QTRSensors.h>
#include "drive.h"

Drive drive;  //iitializes the class responsible for driving the robot

int i=0;
 
void setup() {
  drive.init();

  Serial.begin(9600);
}

void loop() {


  //Move forward
   drive.turnLeft();
    i++;
  //Brake
  /*if (i==3)
  {
    drive.turnRight();
  }
  if(i==5){
    drive.init();
  }*/
  delay(1000);
    
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