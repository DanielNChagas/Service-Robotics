#include <Arduino.h>
#include <Servo.h>
#include <QTRSensors.h>

Servo right_wheel;  //servo object to control the right wheel
Servo left_wheel;   //servo object to control the left wheel

int i=0;

QTRSensors qtr;

const uint8_t SensorCount = 3;
uint16_t sensorValues[SensorCount];

void setup()
{
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){3, 4, 5}, SensorCount);
  qtr.setEmitterPin(2);

  Serial.begin(9600);
}


void loop()
{
  // read raw sensor values
  qtr.read(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum
  // reflectance and 2500 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

  delay(250);
}




/*
void setup() {
  right_wheel.attach(9);  // attaches the right wheel servo on pin 9 to the servo object
  left_wheel.attach(10);  // attaches the left wheel servo on pin 10 to the servo object

  Serial.begin(9600);
}

void loop() {
*/

  //Move forward
 /*   right_wheel.write(180);
    left_wheel.write(0);
    i++;
  //Brake
  if (i==10)
  {
    right_wheel.detach();
    left_wheel.detach();
  }
  if (i==13)
  {
    right_wheel.attach(9);  // attaches the right wheel servo on pin 9 to the servo object
    left_wheel.attach(10);  // attaches the left wheel servo on pin 10 to the servo object
  }
  delay(1000);*/
    
   /* 
    //right_wheel.detatch(9);
    //left_wheel.detatch(10);
    
  //Turn left
    right_wheel.write(180);
    left_wheel.write(90);
  //Turn right
    right_wheel.write(90);
    left_wheel.write(180);*/
  
//}