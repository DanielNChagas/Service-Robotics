#ifndef LIMBS_H
#define LIMBS_H

#include <Arduino.h>
#include <Servo.h>

class Limbs
{
private:
    
public:
    void init();

    void grab();
    void lift();
    void smallLift();
    void drop();
    void down();
};

#endif