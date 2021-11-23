#include "drive.h"


void Drive::init(){
    right_wheel.attach(9);
    left_wheel.attach(10);

    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]){3, 4, 5, 6, 7}, SENSOR_COUNT);
}

void Drive::driveForward(){
    right_wheel.write(160);
    left_wheel.write(20);
}

void Drive::stop(){
    right_wheel.write(STOP);
    left_wheel.write(STOP);
}

void Drive::turnRight(){
    right_wheel.write(80);
    left_wheel.write(45);
    while(outterRightSensor > LIGHT_THRESHOLD || outterLeftSensor > LIGHT_THRESHOLD || leftSensor < LIGHT_THRESHOLD){
        getLineSensorValue();
        
    }
}

void Drive::turnLeft(){
    right_wheel.write(135);
    left_wheel.write(100);
    while(outterRightSensor > LIGHT_THRESHOLD || outterLeftSensor > LIGHT_THRESHOLD || rightSensor < LIGHT_THRESHOLD){
        getLineSensorValue();
        
    }
}

void Drive::turnSlightlyRight(){
    right_wheel.write(100);
    left_wheel.write(70);
}

void Drive::turnSlightlyLeft(){
    right_wheel.write(110);
    left_wheel.write(80);
}

void Drive::getLineSensorValue(){
    qtr.read(sensorValues);

    rightSensor = sensorValues[0];
    middleSensor = sensorValues[1];
    leftSensor = sensorValues[2];
    outterRightSensor = sensorValues[3];
    outterLeftSensor = sensorValues[4];

    Serial.print("Outter Left:");
    Serial.print(outterLeftSensor);
    Serial.print("Left:");
    Serial.print(leftSensor);
    Serial.print("Middle:");
    Serial.print(middleSensor);
    Serial.print("Right:");
    Serial.print(rightSensor);
    Serial.print("Outter Right:");
    Serial.println(outterRightSensor);

}

void Drive::LineFollowing(){
    getLineSensorValue();
    if (outterRightSensor < LIGHT_THRESHOLD && outterLeftSensor < LIGHT_THRESHOLD)
        BasicLineFollowing();
    else if (outterRightSensor > LIGHT_THRESHOLD && outterLeftSensor > LIGHT_THRESHOLD)
        stop();
    else if (leftSensor > LIGHT_THRESHOLD && outterLeftSensor > LIGHT_THRESHOLD)
        turnLeft();
    else if (outterRightSensor > LIGHT_THRESHOLD && rightSensor > LIGHT_THRESHOLD)
        turnRight();   
}

void Drive::BasicLineFollowing(){
    if (rightSensor < LIGHT_THRESHOLD && leftSensor < LIGHT_THRESHOLD && middleSensor < LIGHT_THRESHOLD)    
        stop();
    else if (rightSensor > LIGHT_THRESHOLD && leftSensor > LIGHT_THRESHOLD && middleSensor > LIGHT_THRESHOLD)    
        stop();
    else if (rightSensor < LIGHT_THRESHOLD && leftSensor < LIGHT_THRESHOLD)
        driveForward();        
    else if(rightSensor > LIGHT_THRESHOLD)
        turnSlightlyRight();
    else if (leftSensor > LIGHT_THRESHOLD)
        turnSlightlyLeft();
    
}