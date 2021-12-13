#include <Arduino.h>
#include <Servo.h>
#include <QTRSensors.h>
#include <Ultrasonic.h>
#include "drive.h"
#include "limbs.h"
#include "navigation.h"

using namespace std;

Drive drive;  //iitializes the class responsible for driving the robot
int buttonState = 0;

int i=0;

 
void setup() {
  drive.init();
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(11, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(6, INPUT); // Sets the echoPin as an INPUT
  pinMode(13, INPUT);

 
  Serial.begin(9600);
}

void loop() {
    
    /*uttonState = digitalRead(13);
    Serial.println(buttonState);
    if(buttonState == HIGH)*/
      drive.LineFollowing();
    //drive.getSonar();
    /*limbs.storePerson();
    delay(3000);
    limbs.storeThirdPerson();
    delay(3000);*/
 

  
   
  
}
