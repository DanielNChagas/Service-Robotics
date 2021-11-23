#ifndef DRIVE_H
#define DRIVE_H

#include <Servo.h>
#include <QTRSensors.h>

#define MAX_SPEED 180
#define STOP 90
#define TURN_SPEED_R 110
#define TURN_SPEED_L 20

class Drive
{
private:
    Servo right_wheel;  //servo object to control the right wheel
    Servo left_wheel;   //servo object to control the left wheel
public:
    
    void init();
    void driveForward();
    void stop();
    void turnRight();
    void turnLeft();
};




#endif