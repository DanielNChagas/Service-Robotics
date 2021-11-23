#ifndef DRIVE_H
#define DRIVE_H

#include <Arduino.h>
#include <Servo.h>
#include <QTRSensors.h>

#define MAX_SPEED 180
#define STOP 90
#define SENSOR_COUNT 5
#define LIGHT_THRESHOLD 750

class Drive
{
private:
    Servo right_wheel;  //servo object to control the right wheel
    Servo left_wheel;   //servo object to control the left wheel

    QTRSensors qtr;

    uint16_t sensorValues[SENSOR_COUNT];

    
public:
    uint16_t rightSensor;
    uint16_t outterRightSensor;
    uint16_t outterLeftSensor;
    uint16_t leftSensor;
    uint16_t middleSensor;

    void init();
    void driveForward();
    void stop();
    void turnRight();
    void turnLeft();
    void turnSlightlyLeft();
    void turnSlightlyRight();

    void getLineSensorValue();
    void LineFollowing();
    void BasicLineFollowing();
    
};




#endif