#include "drive.h"


void Drive::init(){
    right_wheel.attach(9);
    left_wheel.attach(10);
}

void Drive::driveForward(){
    right_wheel.write(MAX_SPEED);
    left_wheel.write(0);
}

void Drive::stop(){
    right_wheel.detach();
    left_wheel.detach();
}

void Drive::turnRight(){
    right_wheel.write(STOP);
    left_wheel.write(45);
}

void Drive::turnLeft(){
    right_wheel.write(135);
    left_wheel.write(STOP);
}