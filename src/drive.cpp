#include "drive.h"

/*Drive::Drive() : path(3){
    currentDir=3;
}*/

void Drive::init() {
    right_wheel.attach(9);
    left_wheel.attach(10);


    right_wheel.write(90);
    left_wheel.write(90);

    qtrCentral.setTypeRC();
    qtrCentral.setSensorPins((const uint8_t[]){2, 4, 5}, 3);
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

    while(outterLeftSensor > LIGHT_THRESHOLD || outterRightSensor > LIGHT_THRESHOLD)
        getLineSensorValue();
    delay(100);
    right_wheel.write(0);
    left_wheel.write(0);
    I=0;
    getLineSensorValue();
    if(middleSensor>LIGHT_THRESHOLD){
        delay(900);
        /*while( leftSensor > LIGHT_THRESHOLD || outterLeftSensor > LIGHT_THRESHOLD)
            getLineSensorValue();*/
        while(outterLeftSensor > LIGHT_THRESHOLD)
            getLineSensorValue();
    }
    else{
         while(leftSensor < LIGHT_THRESHOLD)
            getLineSensorValue();
    }
    /*while((outterRightSensor > LIGHT_THRESHOLD || outterLeftSensor > LIGHT_THRESHOLD || leftSensor < LIGHT_THRESHOLD) && middleSensor>LIGHT_THRESHOLD && rightSensor < LIGHT_THRESHOLD){
        getLineSensorValue();
        if (middleSensor < LIGHT_THRESHOLD)
            left_wheel.write(80);  
    }*/
    
}

void Drive::turnLeft(){
    while(outterLeftSensor > LIGHT_THRESHOLD || outterRightSensor > LIGHT_THRESHOLD)
        getLineSensorValue();
    delay(100);
    right_wheel.write(180);
    left_wheel.write(180);
    I=0;

    getLineSensorValue();
    if(middleSensor > LIGHT_THRESHOLD){
        delay(900);
        /*while(rightSensor < LIGHT_THRESHOLD ||outterRightSensor < LIGHT_THRESHOLD)
            getLineSensorValue();*/
        while(outterRightSensor > LIGHT_THRESHOLD)
            getLineSensorValue();
    }
    else{
        while(rightSensor < LIGHT_THRESHOLD )
            getLineSensorValue();
    }
    
    
    /*while((outterRightSensor > LIGHT_THRESHOLD || outterLeftSensor > LIGHT_THRESHOLD || rightSensor < LIGHT_THRESHOLD) && middleSensor > LIGHT_THRESHOLD && leftSensor <LIGHT_THRESHOLD){
        getLineSensorValue();
        if (middleSensor < LIGHT_THRESHOLD)
            right_wheel.write(100); 
    }*/
}

void Drive::uTurn(){
    right_wheel.write(180);
    left_wheel.write(180);
    I=0;
    delay(1100);
    while(rightSensor < LIGHT_THRESHOLD)
        getLineSensorValue();
}

/*void Drive::turnSlightlyRight(){
    right_wheel.write(100);
    left_wheel.write(70);
}

void Drive::turnSlightlyLeft(){
    right_wheel.write(110);
    left_wheel.write(80);
}*/

void Drive::getLineSensorValue(){
    qtrCentral.read(centralSensors);
    qtrOutter.read(outterSensors);
    /*Serial.print(centralSensors[0]);
    Serial.print(centralSensors[1]);
    Serial.print(centralSensors[2]);
    Serial.print("sensors:");
    Serial.print(centralSensors[0]);
    Serial.print(centralSensors[1]);
    Serial.println(centralSensors[2]);*/
    
    rightSensor = centralSensors[0];
    middleSensor = centralSensors[1];
    leftSensor = centralSensors[2];
    outterRightSensor = outterSensors[0];
    outterLeftSensor = outterSensors[1];

    /*Serial.print("Outter Left:");
    Serial.print(outterLeftSensor);
    Serial.print("Left:");
    Serial.print(leftSensor);
    Serial.print("Middle:");
    Serial.print(middleSensor);
    Serial.print("Right:");
    Serial.print(rightSensor);
    Serial.print("Outter Right:");
    Serial.println(outterRightSensor);*/

}

float Drive::getSonar(){
  digitalWrite(3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(3, HIGH);
  delayMicroseconds(10);
  digitalWrite(3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  float duration = pulseIn(11, HIGH);
  // Calculating the distance
  float distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

bool Drive::missingLine(){
    //Serial.println(outterRightSensor < LIGHT_THRESHOLD && outterLeftSensor < LIGHT_THRESHOLD && rightSensor < LIGHT_THRESHOLD && leftSensor < LIGHT_THRESHOLD && middleSensor < LIGHT_THRESHOLD);
    return (outterRightSensor < LIGHT_THRESHOLD && outterLeftSensor < LIGHT_THRESHOLD && rightSensor < LIGHT_THRESHOLD && leftSensor < LIGHT_THRESHOLD && middleSensor < LIGHT_THRESHOLD );
}

void Drive::LineFollowing(){
    getLineSensorValue();
    bool noLine=missingLine();
    uint64_t currentTime=millis();
    float distance = getSonar();
    Serial.println(navigation.numTurns);
    //Dealing with cases where we have no Lines
    if((navigation.numTurns == 9 || navigation.numTurns == 32) && noLine){
        right_wheel.write(135);
        left_wheel.write(45);
        if(distance <= 10.00){
            if (navigation.numTurns == 9)
            {
                right_wheel.write(45);
                left_wheel.write(45);
            }
            else if(navigation.numTurns == 32){
                right_wheel.write(180);
                left_wheel.write(180);
            }
            
            /*while(distance < 60.00){
                distance = getSonar();
            }
            while( distance > 44.00)
                distance = getSonar();*/
                delay(930);
            right_wheel.write(180);
            left_wheel.write(0);
            getLineSensorValue();
            while (rightSensor < LIGHT_THRESHOLD && middleSensor < LIGHT_THRESHOLD && leftSensor < LIGHT_THRESHOLD)
            {
                getLineSensorValue();
            }
            navigation.numTurns++;
        }
    }
    else if(navigation.numTurns == 16 && noLine){

    }
    else{   //Deals with cases where there is a line
        if ((outterRightSensor < LIGHT_THRESHOLD && outterLeftSensor < LIGHT_THRESHOLD && !(noLine)) /*|| currentTime-previousTime < 2000*/)
        {

            int speed = controller();

            int motorspeedRight = 120 - speed;
            int motorspeedLeft = 60 - speed;

            if (motorspeedRight > MAX_SPEED)
            {
                motorspeedRight = MAX_SPEED;
            }
            if (motorspeedLeft < 0)
            {
                motorspeedLeft = 0;
            }
            if (motorspeedRight < 90)
            {
                motorspeedRight = 90;
            }
            if (motorspeedLeft > 90)
            {
                motorspeedLeft = 90;
            }

            right_wheel.write(motorspeedRight);
            left_wheel.write(motorspeedLeft);
        }
        // BasicLineFollowing();
        // In case the robot finds an intersection, a 90 degree turn or a dead end
        else if (((leftSensor > LIGHT_THRESHOLD && outterLeftSensor > LIGHT_THRESHOLD) || (outterRightSensor > LIGHT_THRESHOLD && rightSensor > LIGHT_THRESHOLD) || noLine) /* && currentTime-previousTime > 2000*/)
        {
            // Serial.print(turn);
            if (navigation.hasNextTurn())
            {
                digitalWrite(LED_BUILTIN, HIGH);
                int turn = navigation.nextTurn();
                Serial.println(turn);

                if (turn == 0)
                {
                    delay(2000);
                }
                else if (turn == 1)
                    turnRight();
                else if (turn == -1)
                    turnLeft();
                else if (turn == 2)
                    uTurn();
                digitalWrite(LED_BUILTIN, LOW);
                previousTime = millis();
            }
            else
                stop();
        }
    }
    /*else if (leftSensor > LIGHT_THRESHOLD && outterLeftSensor > LIGHT_THRESHOLD)
        turnLeft();
    else if (outterRightSensor > LIGHT_THRESHOLD && rightSensor > LIGHT_THRESHOLD){
        turnRight(); }*/
    
      
}

/*void Drive::BasicLineFollowing(){
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
    
}*/

int Drive::controller(){
    uint16_t position = qtrCentral.readLineBlack(centralSensors);
    
    int error = 1000 - position;
    P = error;
    I = I + error;
    D = error - lastError;
    lastError = error;

    int motorspeed = P*Kp + D*Kd +Ki*I;
    int motorspeedRight = 120 + motorspeed;
    int motorspeedLeft = 60 + motorspeed;
    
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

void Drive::printNav(){
    /*if(navigation.hasNextTurn())
        Serial.println(navigation.nextTurn());*/
}

