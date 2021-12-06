#ifndef DRIVE_H
#define DRIVE_H

#include <Arduino.h>
#include <Servo.h>
#include <QTRSensors.h>
#include "navigation.h"

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
    int rightSensor=2500;
    uint16_t outterRightSensor=2500;
    uint16_t outterLeftSensor=2500;
    uint16_t leftSensor=2500;
    uint16_t middleSensor=2500;


    int mazePath[59]={1,-1,-1,1,2,-1,-1,1,1,1,-1,-1,2,0,0,-1,-1,-1,1,1,2,-1,-1,-1,1,-1,-1,2,1,1,-1,0,-1,-1,1,2,-1,-1,1,1,-1,1,-1,-1,-1,-1,0,0,2,1,1,0,1,1,2,-1,-1,1,-1};
    static constexpr int mazePathNodes[59]={-1,14,13,-1,15,-1,13,-1,-1,-1,-1,3,1,3,4,-1,7,5,-1,-1,1,-1,-1,5,-1,-1,-1,2,-1,-1,-1,5,7,8,-1,6,-1,12,11,-1,-1,-1,-1,12,11,10,9,10,-1,14,13,-1,4,-1,13,14,-1};
    int currentNode = 16;
    int currentDir=3;
    int numTurns = 0;


    int P;
    int I=0;
    int D;
    float lastError=0;

    uint64_t previousTime=0;

    void init();
    void driveForward();
    void stop();
    void turnRight();
    void turnLeft();
    void uTurn();
    void turnSlightlyLeft();
    void turnSlightlyRight();
    bool missingLine();

    void getLineSensorValue();
    void LineFollowing();
    void BasicLineFollowing();

    int controller();
    
    void printNav();

    Navigator navigation;

    int nextTurn();
    
};




#endif