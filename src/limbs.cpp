#include "limbs.h"

void Limbs::init()
{
    axle.attach(AXLE_PIN);
    axle.write(AXLE_HALF_UP_POS);

    claw.attach(CLAW_PIN);
    claw.write(CLAW_HALF_CLOSED_POS);
}

void Limbs::storePerson()
{
    down();
    delay(1500);
    grab();
    delay(1500);
    lift();
    delay(1500);
    drop();
    delay(1500);
    smallLift();
}

void Limbs::storeThirdPerson()
{
    down();
    delay(1500);
    grab();
    delay(1500);
    smallLift();
}

void Limbs::grab()
{
    claw.write(CLAW_CLOSED_POS);
}

void Limbs::lift()
{
    axle.write(AXLE_UP_POS);
}

void Limbs::smallLift()
{
    axle.write(AXLE_HALF_UP_POS);
}

void Limbs::drop()
{
    claw.write(CLAW_HALF_CLOSED_POS);
}

void Limbs::down()
{
    axle.write(AXLE_DOWN_POS);
    claw.write(CLAW_OPEN_POS);
}