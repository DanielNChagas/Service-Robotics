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

    QTRSensors qtrCentral;
    QTRSensors qtrOutter;

    uint16_t outterSensors[2];
    uint16_t centralSensors[3];

    float Kp = 0.035; 
    float Ki = 0.0001;
    float Kd = 0.01;

    
public:
    uint16_t rightSensor;
    uint16_t outterRightSensor;
    uint16_t outterLeftSensor;
    uint16_t leftSensor;
    uint16_t middleSensor;

    int P;
    int I=0;
    int D;
    float lastError=0;

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

    int controller();
    
};




#endif