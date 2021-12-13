#include "drive.h"

/*Drive::Drive() : path(3){
    currentDir=3;
}*/

void Drive::init() {
    
    
    limbs.init();

    qtrCentral.setTypeRC();
    qtrCentral.setSensorPins((const uint8_t[]){12, 2, 4}, 3);
    qtrOutter.setTypeRC();
    qtrOutter.setSensorPins((const uint8_t[]){7, 8}, 2);

    for(int i=0; i<150; i++){
        qtrCentral.calibrate();
        qtrOutter.calibrate();
    }
    for(int i=0; i < 3;i++){
        Serial.print(qtrCentral.calibrationOn.maximum[i]);
        Serial.print(" ");
    }
    Serial.print(qtrOutter.calibrationOn.maximum[0]);
    Serial.print(" ");
    Serial.print(qtrOutter.calibrationOn.maximum[1]);
        
    for(int i=0; i < 3;i++){
        Serial.print(qtrCentral.calibrationOn.minimum[i]);
        Serial.print(" ");
    }
    Serial.print(qtrOutter.calibrationOn.minimum[0]);
    Serial.print(" ");
    Serial.print(qtrOutter.calibrationOn.minimum[1]);
    right_wheel.attach(9);
    left_wheel.attach(10);

    right_wheel.write(90);
    left_wheel.write(90);
    
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
    //delay(50);
    right_wheel.write(70);
    left_wheel.write(70);
    //I=0;
    getLineSensorValue();
    if(rightSensor > LIGHT_THRESHOLD || middleSensor > LIGHT_THRESHOLD  || leftSensor > LIGHT_THRESHOLD ){
        delay(900);
        /*while( leftSensor > LIGHT_THRESHOLD || outterLeftSensor > LIGHT_THRESHOLD)
            getLineSensorValue();*/
        while(leftSensor < LIGHT_THRESHOLD || outterLeftSensor > LIGHT_THRESHOLD || outterRightSensor > LIGHT_THRESHOLD)
            getLineSensorValue();
    }
    else{
         while(middleSensor < LIGHT_THRESHOLD)
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
    //delay(50);
    right_wheel.write(110);
    left_wheel.write(110);
    //I=0;

    getLineSensorValue();
    if(rightSensor > LIGHT_THRESHOLD || middleSensor > LIGHT_THRESHOLD  || leftSensor > LIGHT_THRESHOLD ){
        delay(800);
        /*while(rightSensor < LIGHT_THRESHOLD ||outterRightSensor < LIGHT_THRESHOLD)
            getLineSensorValue();*/
        while(rightSensor < LIGHT_THRESHOLD || outterLeftSensor > LIGHT_THRESHOLD || outterRightSensor > LIGHT_THRESHOLD)
            getLineSensorValue();
    }
    else{
        while(middleSensor < LIGHT_THRESHOLD )
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
    while(middleSensor < LIGHT_THRESHOLD)
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
    float distance = getSonar();
    getLineSensorValue();
    bool noLine=missingLine();
    uint64_t currentTime=millis();
    if( savedPeople == 3 && (navigation.numTurns <= 11 || navigation.numTurns >= 29) && navigation.currentPathName == PATH_EXPLORE)
       navigation.setPath(PATH_HOME);
                
    if (millis() - previousPersonDropTime > 5000 && willShakePerson)
    {
        limbs.smallLift();
        willShakePerson = false;
    }
    
    //Serial.println(navigation.numTurns);
    //Dealing with cases where we have no Lines
    if((navigation.numTurns == 6 || navigation.numTurns == 29 || navigation.numTurns == 13) && noLine  /*&& !(navigation.willGoHome)*/){
            right_wheel.write(135);
            left_wheel.write(45);
        if (navigation.numTurns == 6){
            /*right_wheel.write(135);
            left_wheel.write(45);*/
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
        /*if(distance <= 10.00){
            if (navigation.numTurns == 1)
            {
                right_wheel.write(45);
                left_wheel.write(45);
            }
            else if(navigation.numTurns == 32){
                right_wheel.write(180);
                left_wheel.write(180);
            }
                delay(930);
            right_wheel.write(180);
            left_wheel.write(0);
            getLineSensorValue();
            while (rightSensor < LIGHT_THRESHOLD && middleSensor < LIGHT_THRESHOLD && leftSensor < LIGHT_THRESHOLD)
            {
                getLineSensorValue();
            }
            navigation.numTurns++;
        }*/
        //previousTime = millis()+800;
        while(rightSensor < LIGHT_THRESHOLD && middleSensor < LIGHT_THRESHOLD  && leftSensor < LIGHT_THRESHOLD )
            getLineSensorValue();
        stop();
        delay(100);
        navigation.numTurns++;
        
       /* if ( outterRightSensor > LIGHT_THRESHOLD)
        {
            right_wheel.write(45);
            left_wheel.write(45);
            while ( outterRightSensor > LIGHT_THRESHOLD)
            {
                getLineSensorValue();
            }  
        }
        else if ( outterLeftSensor > LIGHT_THRESHOLD)
        {
            right_wheel.write(135);
            left_wheel.write(135);
            while (outterLeftSensor > LIGHT_THRESHOLD)
            {
                getLineSensorValue();
            }
            
        } */
        
    }
    else {   //Deals with cases where there is a line
        /*
        else*/ if ((outterRightSensor < LIGHT_THRESHOLD && outterLeftSensor < LIGHT_THRESHOLD && !(noLine)) || currentTime-previousTime < 1800)
        {
            if (distance < 8.0){
                Serial.println("yoyo");
                right_wheel.write(45);
                left_wheel.write(135);
                delay(500);
                stop();
                right_wheel.detach();
                left_wheel.detach();
                //lower claw
                limbs.down();
                delay(500);
                right_wheel.attach(9);
                left_wheel.attach(10);
                right_wheel.write(135);
                left_wheel.write(45);
                delay(500);
                stop();
                right_wheel.detach();
                left_wheel.detach();
                //grab and put it up
                limbs.grab();
                delay(800);
                savedPeople++;
                limbs.lift();
                delay(1000);


                limbs.drop();
                delay(200);
                previousPersonDropTime = millis();
                willShakePerson = true;

                right_wheel.attach(9);
                left_wheel.attach(10);

        }

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
                
                //digitalWrite(LED_BUILTIN, HIGH);
                int turn = navigation.nextTurn();
                
                Serial.println(turn);

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
            else{

            }
                
        }
    }
    /*else if (leftSensor > LIGHT_THRESHOLD && outterLeftSensor > LIGHT_THRESHOLD)
        turnLeft();
    else if (outterRightSensor > LIGHT_THRESHOLD && rightSensor > LIGHT_THRESHOLD){
        turnRight(); }*/
    
      
}



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
    /*Serial.print("position: ");
    Serial.print(position);
    Serial.print("error: ");
    Serial.print(error);
    Serial.print(" speed left: ");
    Serial.print(motorspeedLeft);
    Serial.print("speed right: ");
    Serial.println(motorspeedRight);*/
    
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

