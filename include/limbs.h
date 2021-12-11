#ifndef LIMBS_H
#define LIMBS_H

#include <Arduino.h>
#include <Servo.h>

#define AXLE_PIN 9
#define CLAW_PIN 11
#define AXLE_DOWN_POS 45
#define AXLE_UP_POS 135
#define AXLE_HALF_UP_POS 115
#define CLAW_OPEN_POS 0
#define CLAW_CLOSED_POS 55
#define CLAW_HALF_CLOSED_POS 45

class Limbs
{
private:
    Servo axle;
    Servo claw;
public:
    void init();

    void storePerson();
    void storeThirdPerson();

    void grab();
    void lift();
    void smallLift();
    void drop();
    void down();
};

#endif