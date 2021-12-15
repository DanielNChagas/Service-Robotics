#include "drive.h"
// this method initializes most of the actuators and sensors of the robot and calibrates the line sensors
void Drive::init() {
    //initialization of the claw
    limbs.init();
    // attatching the sensors to the arduino pins
    qtrCentral.setTypeRC();
    qtrCentral.setSensorPins((const uint8_t[]){12, 2, 4}, 3);
    qtrOutter.setTypeRC();
    qtrOutter.setSensorPins((const uint8_t[]){7, 8}, 2);

    for(int i=0; i<150; i++){ // calibration of the line sensors
        qtrCentral.calibrate();
        qtrOutter.calibrate();
    }
    //attatching the wheels to the arduino
    right_wheel.attach(9);
    left_wheel.attach(10);

    right_wheel.write(90);
    left_wheel.write(90);
    
}
// this function stops the robot from moving
void Drive::stop(){
    right_wheel.write(STOP);
    left_wheel.write(STOP);
}

void Drive::turnRight(){
    //this makes the sensor move to the center of the junction/turn
    while(outterLeftSensor > LIGHT_THRESHOLD || outterRightSensor > LIGHT_THRESHOLD)
        getLineSensorValue();
    
    //turns the robot right
    right_wheel.write(70);
    left_wheel.write(70);
    
    getLineSensorValue();
    //if its the robot can move forward
    if(rightSensor > LIGHT_THRESHOLD || middleSensor > LIGHT_THRESHOLD  || leftSensor > LIGHT_THRESHOLD ){
        delay(900);// the delay is used to turn over the forward line
        //turns until finds the line
        while(leftSensor < LIGHT_THRESHOLD || outterLeftSensor > LIGHT_THRESHOLD || outterRightSensor > LIGHT_THRESHOLD)
            getLineSensorValue();
    }//turns until it finds the line
    else{
         while(middleSensor < LIGHT_THRESHOLD)
            getLineSensorValue();
    }
    
}

void Drive::turnLeft(){
    //makes the robot go to the center of the junction/turn
    while(outterLeftSensor > LIGHT_THRESHOLD || outterRightSensor > LIGHT_THRESHOLD)
        getLineSensorValue();
    //turns to the left
    right_wheel.write(110);
    left_wheel.write(110);

    getLineSensorValue();
    //if the robot can move forward
    if(rightSensor > LIGHT_THRESHOLD || middleSensor > LIGHT_THRESHOLD  || leftSensor > LIGHT_THRESHOLD ){
        delay(800);//the delay is used to turn over the forward line
        //turns until finds the line
        while(rightSensor < LIGHT_THRESHOLD || outterLeftSensor > LIGHT_THRESHOLD || outterRightSensor > LIGHT_THRESHOLD)
            getLineSensorValue();
    }
    else{//turns until the robot finds the line
        while(middleSensor < LIGHT_THRESHOLD )
            getLineSensorValue();
    }
}
//this function makes a 180 degrees turn
void Drive::uTurn(){
    //turn
    right_wheel.write(180);
    left_wheel.write(180);
    //delay is used to skip any unwanted line
    delay(1100);
    while(middleSensor < LIGHT_THRESHOLD)//turns until it finds the line
        getLineSensorValue();
}
//this function read the values from the line sensors
void Drive::getLineSensorValue(){
    qtrCentral.read(centralSensors);
    qtrOutter.read(outterSensors);
    
    rightSensor = centralSensors[0];
    middleSensor = centralSensors[1];
    leftSensor = centralSensors[2];
    outterRightSensor = outterSensors[0];
    outterLeftSensor = outterSensors[1];

}
//this function reads the distance from the sonar sensor
float Drive::getSonar(){
  digitalWrite(11, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(11, HIGH);
  delayMicroseconds(10);
  digitalWrite(11, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  float duration = pulseIn(6, HIGH);
  // Calculating the distance
  float distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

  return distance;
}
//this function checks if any sensor senses the line
bool Drive::missingLine(){
    return (outterRightSensor < LIGHT_THRESHOLD && outterLeftSensor < LIGHT_THRESHOLD && rightSensor < LIGHT_THRESHOLD && leftSensor < LIGHT_THRESHOLD && middleSensor < LIGHT_THRESHOLD );
}
// this function is responsible for the movement of the robot
void Drive::LineFollowing(){
    //reads sensors
    float distance = getSonar();
    getLineSensorValue();
    
    uint64_t currentTime=millis();
    //checks if all people have been saved
    if( savedPeople == 3 && (navigation.numTurns <= 11 || navigation.numTurns >= 29) && navigation.currentPathName == PATH_EXPLORE)
       navigation.setPath(PATH_HOME);

    bool noLine=missingLine();
                
    if (millis() - previousPersonDropTime > 5000 && willShakePerson)
    {
        limbs.smallLift();
        willShakePerson = false;
    }

    //Dealing with cases where we have no Lines
    if((navigation.numTurns == 6 || navigation.numTurns == 29 || navigation.numTurns == 13) && noLine  /*&& !(navigation.willGoHome)*/){
            right_wheel.write(135);
            left_wheel.write(45);
        if (navigation.numTurns == 6){
            delay(1400);
            right_wheel.write(45);
            left_wheel.write(45);
            delay(900);
            right_wheel.write(135);
            left_wheel.write(45);
        }
        else if(navigation.numTurns== 13){
            delay(1400);
            right_wheel.write(135);
            left_wheel.write(135);
            delay(900);
            right_wheel.write(135);
            left_wheel.write(45);
        }
        else {
            delay(1100);
            right_wheel.write(135);
            left_wheel.write(135);
            delay(740);
            right_wheel.write(135);
            left_wheel.write(45);
        }
        //moves until it finds the line again
        while(rightSensor < LIGHT_THRESHOLD && middleSensor < LIGHT_THRESHOLD  && leftSensor < LIGHT_THRESHOLD )
            getLineSensorValue();
        stop();
        delay(100);
        navigation.numTurns++;
        
    }
    else {   //Deals with cases where there is a line
        if ((outterRightSensor < LIGHT_THRESHOLD && outterLeftSensor < LIGHT_THRESHOLD && !(noLine)) || currentTime-previousTime < 1800)
        {
            if (distance < 8.0){ // if it detects a cylinder
                //moves back
                right_wheel.write(45);
                left_wheel.write(135);
                delay(500);
                //stops
                stop();
                right_wheel.detach();
                left_wheel.detach();

                //lower claw
                limbs.down();
                delay(500);
                //moves forward
                right_wheel.attach(9);
                left_wheel.attach(10);
                right_wheel.write(135);
                left_wheel.write(45);
                delay(500);
                //stop
                stop();
                right_wheel.detach();
                left_wheel.detach();

                //grab and put it up
                limbs.grab();
                delay(800);
                
                limbs.lift();
                delay(1000);

                //drops the cylinder in the storage
                limbs.drop();
                delay(200);
                previousPersonDropTime = millis();
                willShakePerson = true;

                right_wheel.attach(9);
                left_wheel.attach(10);
                savedPeople++;
        }
            //gets the speed from the controller
            int speed = controller();

            int motorspeedRight = 130 - speed;
            int motorspeedLeft = 50 - speed;

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
        else if (((leftSensor > LIGHT_THRESHOLD && outterLeftSensor > LIGHT_THRESHOLD) || (outterRightSensor > LIGHT_THRESHOLD && rightSensor > LIGHT_THRESHOLD) || noLine)  && currentTime-previousTime >= 1800)
        {
            if ( !(navigation.hasNextTurn()) ){
                navigation.setPath(PATH_EXPLORE);
                left_wheel.detach();
                right_wheel.detach();
                delay(2000);
                right_wheel.attach(9);
                left_wheel.attach(10);
                if( savedPeople == 3){
                    left_wheel.detach();
                    right_wheel.detach();
                }
            }
            if (navigation.hasNextTurn())
            {
                
                //gets the next turn from the navigator
                int turn = navigation.nextTurn();
                
                Serial.println(turn);
                //handles the turn type
                /*0 - move forward
                * 1 - turn right
                * -1 - turn left
                * 2 - turns back
                */
                if (turn == 0)
                {
                    while(outterLeftSensor > LIGHT_THRESHOLD || outterRightSensor > LIGHT_THRESHOLD)
                        getLineSensorValue();
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
        }
    }

}


// method that implements the PID controller to return the speed to aply to the servos.
int Drive::controller(){
    uint16_t position = qtrCentral.readLineBlack(centralSensors);
    
    int error = 1000 - position;
    P = error;
    I = I + error; 
    D = error - lastError;
    lastError = error;

    int motorspeed = P*Kp + D*Kd +Ki*I;
    int motorspeedRight = 120 - motorspeed;
    int motorspeedLeft = 60 - motorspeed;
    
    return motorspeed;
}


