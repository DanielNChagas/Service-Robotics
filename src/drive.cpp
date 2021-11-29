#include "drive.h"


void Drive::init(){
    right_wheel.attach(9);
    left_wheel.attach(10);

    right_wheel.write(90);
    left_wheel.write(90);

    qtrCentral.setTypeRC();
    qtrCentral.setSensorPins((const uint8_t[]){3, 4, 5}, 3);
    qtrOutter.setTypeRC();
    qtrOutter.setSensorPins((const uint8_t[]){6, 7}, 2);
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
    delay(100);
    right_wheel.write(0);
    left_wheel.write(0);
    I=0;
    delay(1100);
    /*while((outterRightSensor > LIGHT_THRESHOLD || outterLeftSensor > LIGHT_THRESHOLD || leftSensor < LIGHT_THRESHOLD) && middleSensor>LIGHT_THRESHOLD && rightSensor < LIGHT_THRESHOLD){
        getLineSensorValue();
        /*if (middleSensor < LIGHT_THRESHOLD)
            left_wheel.write(80);  
    }*/
    
}

void Drive::turnLeft(){
    delay(100);
    right_wheel.write(180);
    left_wheel.write(180);
    I=0;
    delay(1100);
    
    /*while((outterRightSensor > LIGHT_THRESHOLD || outterLeftSensor > LIGHT_THRESHOLD || rightSensor < LIGHT_THRESHOLD) && middleSensor > LIGHT_THRESHOLD && leftSensor <LIGHT_THRESHOLD){
        getLineSensorValue();
        /*if (middleSensor < LIGHT_THRESHOLD)
            right_wheel.write(100); 
    }*/
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
    qtrCentral.read(centralSensors);
    qtrOutter.read(outterSensors);

    rightSensor = centralSensors[0];
    middleSensor = centralSensors[1];
    leftSensor = centralSensors[2];
    outterRightSensor = outterSensors[0];
    outterLeftSensor = outterSensors[1];

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

    if (outterRightSensor < LIGHT_THRESHOLD && outterLeftSensor < LIGHT_THRESHOLD){

        int speed=controller();
        
        int motorspeedRight =120 - speed;
        int motorspeedLeft = 60 - speed;

        if (motorspeedRight > MAX_SPEED) {
        motorspeedRight = MAX_SPEED;
        }
        if (motorspeedLeft < 0) {
        motorspeedLeft = 0;
        }
        if (motorspeedRight < 90) {
            motorspeedRight = 90;
        }
        if (motorspeedLeft > 90) {
            motorspeedLeft = 90;
        }

        right_wheel.write(motorspeedRight);
        left_wheel.write(motorspeedLeft);
    }
        //BasicLineFollowing();
    else if (outterRightSensor > LIGHT_THRESHOLD && outterLeftSensor > LIGHT_THRESHOLD)
        stop();
    else if (leftSensor > LIGHT_THRESHOLD && outterLeftSensor > LIGHT_THRESHOLD)
        turnLeft();
    else if (outterRightSensor > LIGHT_THRESHOLD && rightSensor > LIGHT_THRESHOLD){
        turnRight(); 
    }
          
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

int Drive::controller(){
    uint16_t position = qtrCentral.readLineBlack(centralSensors);
    Serial.print("position:");
    Serial.print(position);
    int error = 1000 - position;
    P = error;
    I = I + error;
    D = error - lastError;
    lastError = error;

    int motorspeed = P*Kp + D*Kd +Ki*I;
    int motorspeedRight = 120 + motorspeed;
    int motorspeedLeft = 60 + motorspeed;
    Serial.print("right:");
    Serial.print(motorspeedRight);
    Serial.print("left:");
    Serial.println(motorspeedLeft);
    return motorspeed;
  
    if (motorspeedRight > MAX_SPEED) {
        motorspeedRight = MAX_SPEED;
    }
    if (motorspeedLeft < 0) {
        motorspeedLeft = 0;
    }
    if (motorspeedRight < 90) {
        motorspeedRight = 90;
    }
    if (motorspeedLeft > 90) {
        motorspeedLeft = 90;
    } 

}