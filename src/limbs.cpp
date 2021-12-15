#include "limbs.h"

void Limbs::init()
{
    axle.attach(AXLE_PIN);
    axle.write(AXLE_UP_POS);

    claw.attach(CLAW_PIN);
    claw.write(CLAW_HALF_CLOSED_POS);
}

//the claw grabs
void Limbs::grab()
{
    claw.write(CLAW_CLOSED_POS);
}
//the claw is lifted
void Limbs::lift()
{
    axle.write(AXLE_UP_POS);
}
//the claw moves away from the storage
void Limbs::smallLift()
{
    axle.write(AXLE_HALF_UP_POS);
}
//the claw drops the cylinder
void Limbs::drop()
{
    claw.write(CLAW_HALF_CLOSED_POS);
}
//the claw moves down and opens
void Limbs::down()
{
    axle.write(AXLE_DOWN_POS);
    claw.write(CLAW_OPEN_POS);
}