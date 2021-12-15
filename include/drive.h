#ifndef DRIVE_H
#define DRIVE_H

#include <Arduino.h>
#include <Servo.h>
#include <QTRSensors.h>
#include "navigation.h"
#include "limbs.h"

#define MAX_SPEED 180
#define STOP 90
#define SENSOR_COUNT 5
#define LIGHT_THRESHOLD 550

#define NUM_NODES 17
#define NUM_EXPLORE_PATH_TURNS 60
#define MAX_NUM_TURNS NUM_EXPLORE_PATH_TURNS

class Drive
{
private:
    Servo right_wheel;  //servo object to control the right wheel
    Servo left_wheel;   //servo object to control the left wheel

    QTRSensors qtrCentral;
    QTRSensors qtrOutter;

    Limbs limbs;

    uint16_t outterSensors[2];
    uint16_t centralSensors[3];

    float Kp = 0.037; 
    float Ki = 0.0001;
    float Kd = 0.01;

    

    
public:
    //Drive();
    int rightSensor=2500;
    uint16_t outterRightSensor=2500;
    uint16_t outterLeftSensor=2500;
    uint16_t leftSensor=2500;
    uint16_t middleSensor=2500;

    Navigator navigation;

    int savedPeople=0;

    int P;
    int I=0;
    int D;
    float lastError=0;

    uint64_t previousTime=0;
    uint64_t previousPersonDropTime=0;
    boolean willShakePerson = false;

    void init();

    void stop();
    void turnRight();
    void turnLeft();
    void uTurn();

    bool missingLine();

    void getLineSensorValue();
    float getSonar();
    void LineFollowing();

    int controller();   
};




#endif