#include "main.h"
#include "mechcontrol.hpp"
#include "pros/rtos.h"
#include "globals.hpp"

void moveDistance(double distance, lemlib::MoveToPointParams params)
{
    double targetX = chassis.getPose().x + distance * sin(chassis.getPose(true).theta);
    double targetY = chassis.getPose().y + distance * cos(chassis.getPose(true).theta);
    chassis.moveToPoint(targetX, targetY, 1500, params);
}

void allianceStake(int side) {
    bool a = (side == 1);
    chassis.setPose(side*-12, -62, side*90);
    chassis.setBrakeMode(E_MOTOR_BRAKE_HOLD);

    chassis.arcade(48, 0);
    delay(450);
    manualintake = true;
    setIntakeSpeed(-127, 0);
    delay(50);
    chassis.arcade(0, 0);
    delay(300);
    manualintake=false;
    
}


void soloAWPSafe() {
    // allianceStake(alliance);
    bool a = (alliance == 1);

    //goal 1
    chassis.setPose(alliance*-24, -53.6, 180);
    chassis.setBrakeMode(E_MOTOR_BRAKE_HOLD);
    manualintake=true;

    
    double xcoordinate = chassis.getPose().x;
    chassis.moveToPoint(xcoordinate, -30, 1000, {.forwards=false, .maxSpeed=127, .minSpeed=50, .earlyExitRange=16});
    chassis.moveToPoint(xcoordinate, -30, 1000, {.forwards=false, .maxSpeed=50, .minSpeed=5});
    while (chassis.getPose().y < -36) {
        delay(50);
    }
    clamp.extend();
    if (rush) {
        intake.move(127);
    }
    chassis.waitUntilDone();

    //ring 1&2
    chassis.turnToPoint((a ? -37 : 40), (a ? -15 : -9), 800);
    delay(400);
    manualintake=false;
    intake.move(0);
    stage = 0;
    setIntakeSpeed(127, 127);
    chassis.moveToPoint((a ? -37 : 40), (a ? -15 : -9), 800, {.maxSpeed=70, .minSpeed=10});
    chassis.waitUntilDone();
    delay(200);
    chassis.swingToHeading(alliance*-89, a ? DriveSide::LEFT : DriveSide::RIGHT, 800);
    chassis.moveToPoint((a ? -57 : 60), (a ? -14.5 : -9), 800, {.maxSpeed=70, .minSpeed=10});

    //ring 3
    chassis.turnToPoint(alliance*-35, (a ? -20 : -15), 500, {.forwards = false});
    chassis.moveToPoint(alliance*-35, (a ? -20 : -15), 800, {.forwards=false, .maxSpeed=90});
    chassis.waitUntilDone();
    delay(200);
    chassis.turnToPoint(alliance*-45, (a ? -26 : -20), 400);
    chassis.moveToPoint(alliance*-45, (a ? -26 : -20), 900);
    wallstake=true;

    chassis.turnToHeading(180, 1000);
    chassis.waitUntilDone();
    moveDistance(30, {});

    chassis.turnToPoint(0, -57, 1000);
    chassis.moveToPoint(0, -57, 1000);
    chassis.waitUntil(20);
    clamp.retract();

    chassis.turnToHeading(0, 1000);
    chassis.waitUntilDone();
    clamp.extend();
    chassis.arcade(-30, 0);
    delay(700);
    chassis.arcade(30, 0);
    delay(200);
    chassis.arcade(0, 0);
    wallstake=false;
    setIntakeSpeed(127, 127);
    delay(300);
    chassis.arcade(30, 0);
    delay(200);
    chassis.arcade(0, 0);

    chassis.turnToPoint(25, -45, 1000, {.forwards=false});
    chassis.moveToPoint(25, -45, 1000, {.forwards=false});

    
}
void soloAWP() {
    //alliance stake
    allianceStake(alliance);
    bool a = (alliance == 1);
    
    chassis.moveToPoint(alliance*-19, -58, 800, {.forwards=false, .maxSpeed=80, .minSpeed=10}, false);
    delay(100);
    chassis.turnToHeading(180, 700);
    chassis.waitUntilDone();
    delay(50);

    //goal 1
    double xcoordinate = chassis.getPose().x;
    chassis.moveToPoint(xcoordinate, -28, 1000, {.forwards=false, .maxSpeed=127, .minSpeed=50, .earlyExitRange=18});
    chassis.moveToPoint(xcoordinate, -28, 1000, {.forwards=false, .maxSpeed=50, .minSpeed=5});
    while (chassis.getPose().y < -32) {
        delay(50);
    }
    clamp.extend();
    chassis.waitUntilDone();
    delay(100);

    //ring 1&2
    chassis.turnToPoint((a ? -37 : 40), (a ? -14.5 : -9), 800);
    delay(200);
    setIntakeSpeed(127, 127);
    chassis.moveToPoint((a ? -37 : 40), (a ? -14.5 : -9), 800, {.maxSpeed=70, .minSpeed=10});
    chassis.waitUntilDone();
    delay(100);
    chassis.swingToHeading(alliance*-89, a ? DriveSide::LEFT : DriveSide::RIGHT, 800);
    chassis.moveToPoint((a ? -55 : 58), (a ? -15 : -9), 800, {.maxSpeed=70, .minSpeed=10});

    //ring 3
    chassis.turnToPoint(alliance*-30, (a ? -20 : -15), 500, {.forwards = false});
    chassis.moveToPoint(alliance*-30, (a ? -20 : -15), 1000, {.forwards=false, .maxSpeed=90});
    chassis.waitUntilDone();
    delay(100);
    chassis.turnToPoint(alliance*-45, (a ? -26 : -20), 400);
    chassis.moveToPoint(alliance*-45, (a ? -26 : -20), 900);

    //ring 4
    chassis.turnToPoint((a ? 28 : -21), -45, 1000, {.forwards=false});
    chassis.moveToPoint((a ? 28 : -21), -45, 1500, {.forwards=false, .maxSpeed=127, .minSpeed=80, .earlyExitRange=24});
    chassis.moveToPoint((a ? 28 : -21), -45, 1000, {.forwards=false, .maxSpeed=80, .minSpeed=10});

    chassis.waitUntilDone();
    clamp.retract();
    delay(100);
    chassis.turnToHeading(180, 800);
    chassis.waitUntilDone();
    delay(50);
    xcoordinate = chassis.getPose().x;
    chassis.moveToPoint(xcoordinate, (a ? -30 : -20), 1000, {.forwards=false, .maxSpeed=127, .minSpeed=50, .earlyExitRange=14});
    chassis.moveToPoint(xcoordinate, (a ? -30 : -20), 1000, {.forwards=false, .maxSpeed=50, .minSpeed=10});
    if (a) {
        while (chassis.getPose().y < -34) {
            delay(50);
        }
    } else {
        while (chassis.getPose().y < -23) {
            delay(50);
        }
    }
    
    clamp.extend();
    setIntakeSpeed(127, 127);
    chassis.waitUntilDone();
    delay(200);
    chassis.turnToPoint((a ? 55 : -45), (a ? -25 : -22), 800);
    chassis.moveToPoint((a ? 55 : -45), (a ? -25 : -22), 800);
    chassis.waitUntilDone();
    chassis.turnToPoint((a ? 30 : -10), (a ? -15 : -13), 300, {.forwards=false});
    chassis.moveToPoint((a ? 30 : -10), (a ? -15 : -13), 1000, {.forwards=false});
    chassis.waitUntilDone();
    setIntakeSpeed(0, 0);
}

void ringSide(){

    //alliance stake
    bool a = (alliance == 1);

    if (!rush) {
        allianceStake(alliance);
        chassis.moveToPoint(alliance*-19, -58, 800, {.forwards=false, .maxSpeed=80, .minSpeed=10}, false);
        delay(100);
        chassis.turnToHeading(180, 700);
        chassis.waitUntilDone();
        delay(50);
    } else {
        chassis.setPose(alliance*-24, -53.6, 180);
        chassis.setBrakeMode(E_MOTOR_BRAKE_HOLD);
        manualintake=true;
    }

    //goal 1
    double xcoordinate = chassis.getPose().x;
    chassis.moveToPoint(xcoordinate, -28, 1000, {.forwards=false, .maxSpeed=127, .minSpeed=80, .earlyExitRange=18});
    chassis.moveToPoint(xcoordinate, -28, 1000, {.forwards=false, .maxSpeed=80, .minSpeed=5});
    chassis.waitUntil(20);
    clamp.extend();
    chassis.waitUntilDone();
    delay(100);

    //ring 1&2
    chassis.turnToPoint((a ? -37 : 40), (a ? -13 : -9), 800);
    delay(200);
    setIntakeSpeed(127, 127);
    chassis.moveToPoint((a ? -37 : 40), (a ? -13 : -9), 800, {.maxSpeed=70, .minSpeed=10});
    chassis.waitUntilDone();
    delay(100);
    chassis.swingToHeading(alliance*-89, a ? DriveSide::LEFT : DriveSide::RIGHT, 800);
    chassis.moveToPoint((a ? -55 : 55), (a ? -13 : -8), 800, {.maxSpeed=70, .minSpeed=10});

    //ring 3
    chassis.turnToPoint(alliance*-30, (a ? -20 : -15), 500, {.forwards = false});
    chassis.moveToPoint(alliance*-30, (a ? -20 : -15), 1000, {.forwards=false, .maxSpeed=90});
    chassis.waitUntilDone();
    delay(100);
    chassis.turnToPoint(alliance*-45, (a ? -26 : -20), 400);
    chassis.moveToPoint(alliance*-45, (a ? -26 : -20), 900);

    chassis.turnToPoint((a ? -54 : 61), (a ? -51: -48), 800, {.maxSpeed=100, .minSpeed=20});
    chassis.waitUntilDone();
    chassis.moveToPoint((a ? -54 : 61), (a ? -51: -48), 1500, {.maxSpeed=100, .minSpeed=20});
    chassis.waitUntilDone();
    stage=0;
    chassis.turnToHeading((a ? 215: 155), 500, {.maxSpeed=80, .minSpeed=30}, false);
    chassis.waitUntilDone();

    setIntakeSpeed(127, -127);
    chassis.arcade(127, 0);
    delay(300);
    chassis.arcade(0, 0);
    setIntakeSpeed(127, 127);
    delay(300);


    chassis.arcade(-127, 0);
    delay(300);
    setIntakeSpeed(127, -127);
    chassis.arcade(127, 0);
    delay(300);
    chassis.arcade(0, 0);
    setIntakeSpeed(127, 127);
    delay(100);


    chassis.turnToPoint(alliance*-52, -52, 800, {.forwards=false});
    chassis.moveToPoint(alliance*-52, -52, 800, {.forwards=false});

    chassis.turnToPoint(alliance*-15, (a ? -50 : -52), 800);
    chassis.moveToPoint(alliance*-15, (a ? -50 : -52), 1500);
    chassis.moveToPoint(alliance*25, (a ? -50 : -52), 2000, {.maxSpeed=40});
    chassis.waitUntilDone();

}

void goalSide(){
    bool a = (alliance == 1);
    chassis.setPose(alliance*35.21, -50.76, alliance*17.86);
    chassis.setBrakeMode(E_MOTOR_BRAKE_HOLD);

    setIntakeSpeed(127, 127);
    wallstake=true;

    chassis.moveToPoint((a ? 44 : -46), -22, 1000, {.maxSpeed=127, .minSpeed=50, .earlyExitRange=10});
    chassis.moveToPoint((a ? 42 : -48), (a ? -18 : -20), 1000, {.maxSpeed=127, .minSpeed=50, .earlyExitRange=3});
    delay(100);
    sweeper.extend();
    chassis.waitUntilDone();
    delay(200);
    // chassis.moveToPoint(40, -15, 1000, {.maxSpeed=127, .minSpeed=4},false);
    if (a) {
        chassis.turnToHeading(a? -20 : 3, 500);
    }
    chassis.waitUntilDone();
    chassis.moveToPoint((a ? 50 : -45), (a ? -40 : -35), 1000, {.forwards=false, .minSpeed=100});
    chassis.waitUntilDone();
    sweeper.retract();
    delay(200);
    chassis.turnToPoint((a ? 53 : -39), (a ? -29 : -27), 1000, {.forwards=false});
    chassis.moveToPoint((a ? 53 : -39), (a ? -29 : -27), 1000, {.forwards=false, .maxSpeed=60, .minSpeed=4});
    if (a) {
        while (chassis.getPose().y < -33) {
            delay(50);
        }
    } else {
        while (chassis.getPose().y < -30){
            delay(50);
        }
    }
    clamp.extend();
    manualintake=true;
    intake.move(127);
    delay(500);
    manualintake=false;
    clamp.retract();
    wallstake = false;
    stage = 0;
    chassis.waitUntilDone();
    delay(200);
    chassis.turnToPoint(alliance*26, a ? -26 : -30, 1000, {.forwards=false});
    chassis.moveToPoint(alliance*26, a ? -26 : -30, 1000, {.forwards=false, .maxSpeed=70, .minSpeed=4});
    if (a) {
        while (chassis.getPose().x > 30) {
            delay(50);
        }
    } else {
        while (chassis.getPose().x < -34){
            delay(50);
        }
    }
    clamp.extend();
    chassis.waitUntilDone();
    if (a) {
        chassis.turnToPoint(27, -54, 1000);
        setIntakeSpeed(127, 127);
        chassis.moveToPoint(27, -54, 1000);
        chassis.turnToPoint(50, -54, 1000);
        chassis.moveToPoint(50, -54, 1000, {});
        chassis.turnToHeading(135, 1000);
        chassis.waitUntilDone();
        setIntakeSpeed(127, -127);
        chassis.arcade(127, 0);
        delay(700);
        chassis.arcade(0, 0);
        setIntakeSpeed(127, 127);
        delay(100);
        chassis.arcade(-127, 0);
        delay(300);
        chassis.arcade(0, 0);

        chassis.turnToHeading(0, 1000);
        chassis.waitUntilDone();
        clamp.retract();
        moveDistance(25, {});
        chassis.turnToHeading(180, 1000);



        // sweeper.extend();
        // chassis.turnToHeading(20, 1000, {.maxSpeed=80, .minSpeed=40});
        // chassis.waitUntilDone();
        // sweeper.retract();
        // chassis.turnToHeading(70, 1000);
        // chassis.waitUntilDone();
        // moveDistance(10, {.maxSpeed=80});
        // chassis.waitUntilDone();
        // delay(100);
        // moveDistance(-10, {.forwards=false, .maxSpeed=80});
        // chassis.turnToHeading(110, 1000);
        // chassis.waitUntilDone();
        // moveDistance(10, {.maxSpeed=80});
        // chassis.waitUntilDone();
        // delay(100);
        // moveDistance(-10, {.forwards=false, .maxSpeed=80});
    } else {
        chassis.turnToHeading(200, 1000);
        chassis.waitUntilDone();
        moveDistance(15, {.maxSpeed=80});
        chassis.waitUntilDone();
        chassis.turnToPoint(-45, -55, 1000, {.maxSpeed=100, .minSpeed=20});
        chassis.waitUntilDone();
        chassis.moveToPoint(-45, -55, 1500, {.maxSpeed=100, .minSpeed=20});
        chassis.waitUntilDone();
        chassis.arcade(60, 0);
        delay(150);
        chassis.arcade(0, 0);
        chassis.turnToHeading(215, 1000, {.maxSpeed=80, .minSpeed=30}, false);
        sweeper.extend();
        delay(400);
        chassis.arcade(60, 0);
        delay(250);
        chassis.arcade(0, 0);
        chassis.turnToHeading(120, 1500, {.maxSpeed = 80, .minSpeed = 20});
        chassis.waitUntilDone();
        sweeper.retract();
        chassis.turnToHeading(170, 1000);
        chassis.waitUntilDone();
        moveDistance(9, {.maxSpeed=80});
        chassis.waitUntilDone();
        delay(100);
        moveDistance(-9, {.forwards=false, .maxSpeed=80});
        chassis.turnToHeading(190, 1000);
        chassis.waitUntilDone();
        // delay(200);
        moveDistance(9, {.maxSpeed=80});
        chassis.waitUntilDone();
        delay(100);
        moveDistance(-9, {.forwards=false, .maxSpeed=80});
        chassis.waitUntilDone();
        chassis.turnToHeading(45, 700);
        chassis.waitUntilDone();
        clamp.retract();
        chassis.turnToPoint(-30, -17, 1000, {.forwards=false});
        chassis.moveToPoint(-30, -17, 1000, {.forwards=false, .maxSpeed=80, .minSpeed=20});
        while (chassis.getPose().y < -19) {
            delay(50);
        }
        clamp.extend();
        chassis.waitUntilDone();
    }
}

void goalSideSafe(){

    
    bool a = alliance == -1;
    if (!rush) {
        allianceStake(alliance*-1);
        chassis.moveToPoint(alliance*19, -58, 800, {.forwards=false, .maxSpeed=80, .minSpeed=10}, false);
        delay(100);
        chassis.turnToHeading(180, 700);
        chassis.waitUntilDone();
        delay(50);
    } else {
        chassis.setPose(alliance*24, -53.6, 180);
        chassis.setBrakeMode(E_MOTOR_BRAKE_HOLD);
        manualintake=true;
    }    

    //goal 1
    double xcoordinate = chassis.getPose().x;
    chassis.moveToPoint(xcoordinate, -30, 1000, {.forwards=false, .maxSpeed=127, .minSpeed=50, .earlyExitRange=16});
    chassis.moveToPoint(xcoordinate, -30, 1500, {.forwards=false, .maxSpeed=40});
    while (chassis.getPose().y < -36) {
        delay(50);
    }
    clamp.extend();
    chassis.waitUntilDone();
    setIntakeSpeed(127, 127);

    //ring 3
    chassis.turnToPoint(alliance*45, (a ? -26 : -23), 1000);
    chassis.moveToPoint(alliance*45, (a ? -26 : -23), 900);

    chassis.turnToPoint((a ? -54 : 65), (a ? -54: -50), 1000, {.maxSpeed=100, .minSpeed=20});
    chassis.waitUntilDone();
    chassis.moveToPoint((a ? -54 : 65), (a ? -54: -50), 1500, {.maxSpeed=100, .minSpeed=20});
    delay(100);
    chassis.turnToHeading(alliance*150, 1000);
    chassis.waitUntilDone();
    setIntakeSpeed(127, -127);
    chassis.arcade(127, 0);
    delay(700);
    chassis.arcade(0, 0);
    setIntakeSpeed(127, 127);
    if (elims) {
        wallstake=true;
    }
    delay(100);
    chassis.arcade(-127, 0);
    delay(300);
    chassis.arcade(0, 0);
    delay(500);

    if (!elims) {
        chassis.waitUntilDone();
        chassis.turnToPoint(alliance*17, -17, 1000, {.forwards=false});
        chassis.moveToPoint(alliance*17, -17, 1500, {.forwards=false, .maxSpeed=80, .minSpeed=10});
        setIntakeSpeed(0, 0);
        chassis.waitUntilDone();
    } else {
        chassis.arcade(-60, 0);
        delay(100);
        chassis.arcade(0, 0);
        chassis.turnToHeading(alliance*-40, 1000);
        chassis.waitUntilDone();
        clamp.retract();
        chassis.turnToPoint((a ? -42 : 55), (a ? -11 : -15), 1000, {.forwards=false, .maxSpeed=80});
        setIntakeSpeed(0, 0);
        chassis.moveToPoint((a ? -42 : 55), (a ? -11 : -15), 2500, {.forwards=false, .maxSpeed=50});
        chassis.waitUntilDone();
        // delay(200);
        clamp.extend();
        delay(300);
        wallstake=false;
        setIntakeSpeed(127, 127);
        moveDistance(10, {});
    }
    // chassis.turnToHeading(90, 1000);
    
    // chassis.moveToPoint(-14, a ? -18 : 10, 2000, {.forwards=false, .maxSpeed=80});
}

void skills() {
    
    chassis.setPose(0.5, -62, -90);
    chassis.setBrakeMode(E_MOTOR_BRAKE_HOLD);

    setIntakeSpeed(-127, 0);
    delay(600);
    setIntakeSpeed(0, 0);

    //goal 1
    chassis.swingToPoint(24, -47, DriveSide::RIGHT, 500, {.forwards=false});
    chassis.moveToPoint(24, -47, 1000, {.forwards=false, .maxSpeed=60, .minSpeed=10});
    chassis.waitUntil(16);
    clamp.extend();

    //goal 1 ring 1
    chassis.waitUntilDone();
    delay(100);
    chassis.turnToPoint(22, -28, 500);
    setIntakeSpeed(127, 127);
    chassis.moveToPoint(22, -28, 800);

    //goal 1 ring 2
    chassis.turnToPoint(2, -8, 600);
    chassis.moveToPoint(2, -8, 1000);

    //goal 1 ring 3
    chassis.turnToPoint(20, 24, 600);
    chassis.moveToPoint(20, 24, 1000);
    
    //wallstake 1 ring
    chassis.turnToPoint(43, 24, 500);
    chassis.moveToPoint(43, 24, 800);
    wallstake=true;

    //wallstake 1
    chassis.turnToPoint(40, 1, 800);
    chassis.moveToPoint(40, 1, 800, {.maxSpeed=80});
    chassis.waitUntilDone();
    delay(100);
    chassis.turnToHeading(90, 1200, {.maxSpeed=70});
    delay(200);
    wallstakeExtend();
    chassis.waitUntilDone();
    moveDistance(19, {.maxSpeed=100});
    setIntakeSpeed(0, 127);
    chassis.waitUntilDone();
    delay(200);

    //goal 1 ring 4 & 5
    chassis.waitUntilDone();
    moveDistance(-10, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToPoint(56, 46, 800);
    chassis.moveToPoint(56, 46, 1000);
    wallstakearm.retract();
    setIntakeSpeed(127, 127);
    chassis.waitUntilDone();
    delay(200);

    //goal 1 ring 6
    chassis.turnToPoint(45, 58, 500);
    chassis.waitUntilDone();
    delay(200);
    chassis.moveToPoint(45, 58, 800);

    //drop goal 1
    chassis.turnToHeading(-105, 800);
    chassis.waitUntilDone();
    chassis.arcade(-60, 0);
    delay(500);
    chassis.arcade(0, 0);
    clamp.retract();
    chassis.turnToHeading(-125, 800);
    chassis.waitUntilDone();
    
    //goal 2
    moveDistance(15, {.maxSpeed=80});
    delay(200);
    setIntakeSpeed(127, -127);
    chassis.turnToPoint(-2, 51, 800, {.forwards=false});
    setIntakeSpeed(0, 0);
    chassis.moveToPoint(-2, 51, 1500, {.forwards=false, .minSpeed=40, .earlyExitRange=24});
    chassis.moveToPoint(-2, 51, 1500, {.forwards=false, .maxSpeed=40, .minSpeed=10});
    while (chassis.getPose().x > 9) {
        delay(50);
    }
    clamp.extend();
    setIntakeSpeed(127, 127);
    chassis.waitUntilDone();
    delay(200);

    //goal 2 ring 1
    chassis.turnToPoint(-20, 30, 800);
    chassis.moveToPoint(-20, 30, 1000);

    //wallstake 2 ring
    chassis.turnToPoint(-40, 29, 800);
    chassis.moveToPoint(-40, 29, 1000);
    chassis.waitUntilDone();
    wallstake=true;

    //wallstake 2
    chassis.turnToPoint(-36, 2, 800);
    chassis.moveToPoint(-36, 2, 800, {.maxSpeed=90});
    chassis.waitUntilDone();
    delay(100);
    chassis.turnToHeading(-90, 1200, {.maxSpeed=80});
    setIntakeSpeed(0, 127);
    wallstakeExtend();
    chassis.waitUntilDone();
    moveDistance(19, {.maxSpeed=100});
    chassis.waitUntilDone();
    delay(200);

    //goal 2 ring 2 - 5
    moveDistance(-9, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToPoint(-42, -55, 800);
    wallstakearm.retract();
    setIntakeSpeed(127, 127);
    chassis.moveToPoint(-42, -55, 1000, {.maxSpeed=100, .minSpeed=50, .earlyExitRange=36});
    chassis.moveToPoint(-42, -55, 1000, {.maxSpeed=50, .minSpeed=20});

    //goal 2 ring 6
    chassis.turnToPoint(-50, -48, 800);
    chassis.moveToPoint(-50, -48, 1000);

    //drop goal 2
    chassis.turnToHeading(20, 800);
    chassis.waitUntilDone();
    clamp.retract();
    chassis.arcade(-90, 0);
    delay(500);
    chassis.arcade(0, 0);
    
    chassis.waitUntilDone();
    moveDistance(20, {});
    chassis.waitUntilDone();
    setIntakeSpeed(0, -127);

    chassis.turnToHeading(180, 800);
    chassis.waitUntilDone();
    climb.extend();
    delay(200);
    chassis.arcade(-30, 0);
    delay(300);
    chassis.arcade(0, 0);
    chassis.waitUntilDone();
    moveDistance(-45, {.forwards=false, .maxSpeed=90});
    chassis.waitUntilDone();
    climb.retract();
    delay(200);
    chassis.arcade(-30, 0);
    delay(500);
    chassis.arcade(0, 0);

    chassis.turnToPoint(-5, 58, 800);
    chassis.moveToPoint(-5, 58, 1500);
    chassis.turnToHeading(95, 800);
    chassis.waitUntilDone();
    moveDistance(-36, {.forwards=false, .maxSpeed=90});
    chassis.waitUntilDone();
    chassis.arcade(-60, 0);
    delay(400);
    chassis.arcade(0, 0);


    // chassis.turnToPoint(-26, 58, 800, {.forwards=false});
    // chassis.moveToPoint(-26, 58, 1500, {.forwards=false, .minSpeed=40, .earlyExitRange=24});
    // wallstakearm.retract();
    // chassis.moveToPoint(-26, 58, 1500, {.forwards=false, .maxSpeed=40});
    // while (chassis.getPose().y < 54) {
    //     delay(50);
    // }
    // clamp.extend();
    // delay(300);

    // setIntakeSpeed(127, 127);
    // wallstake=true;
    // chassis.turnToPoint(-48, 50, 800);
    // chassis.moveToPoint(-48, 50, 1000);

    // chassis.turnToHeading(145, 800);
    // chassis.waitUntilDone();
    // chassis.arcade(-60, 0);
    // delay(300);
    // chassis.arcade(0, 0);
    // clamp.retract();
    // setIntakeSpeed(0, 0);

    chassis.turnToPoint(-48, -24, 800);
    chassis.moveToPoint(-48, -24, 1000);
    chassis.waitUntilDone();
    delay(100);

    // chassis.turnToHeading(0, 800);
    // chassis.waitUntilDone();
    

    chassis.turnToPoint(-14, -46, 800, {.forwards=false});
    chassis.moveToPoint(-14, -46, 1500, {.forwards=false, .maxSpeed=60});

    while (chassis.getPose().y > -42) {
        delay(50);
    }
    clamp.extend();
    chassis.waitUntilDone();
    delay(200);
    wallstake=false;
    setIntakeSpeed(127, 127);

    chassis.turnToPoint(-16, -24, 800);
    chassis.moveToPoint(-16, -24, 1000);
    setIntakeSpeed(127, 127);

    chassis.turnToPoint(0, -48, 800, {.forwards=false});
    chassis.moveToPoint(0, -48, 1000, {.forwards=false});
    chassis.turnToPoint(48, -0, 800);
    chassis.moveToPoint(48, -0, 1500);
    chassis.waitUntilDone();
    delay(100);

    chassis.turnToPoint(58, -42, 800);
    chassis.moveToPoint(58, -42, 1000, {.minSpeed=50, .earlyExitRange=24});
    chassis.moveToPoint(58, -42, 1000, {.maxSpeed=80});

    // chassis.turnToPoint(65, -36, 800);
    // chassis.moveToPoint(65, -36, 1000);

    chassis.turnToHeading(-60, 800);
    chassis.waitUntilDone();
    clamp.retract();
    setIntakeSpeed(0, 0);
    chassis.arcade(-60, 0);
    delay(400);
    chassis.arcade(0, 0);

    chassis.turnToPoint(25, 0, 800);
    chassis.moveToPoint(25, 0, 1000);
    chassis.turnToHeading(-60, 800);
    chassis.waitUntilDone();
    chassis.arcade(80, 0);
    delay(300);
    climb.extend();
    chassis.arcade(60, 0);
    delay(200);
    chassis.arcade(127, 0);
    delay(1000);
    chassis.arcade(0, 0);

    climbing = !climbing;
    climbsection += 1;
}

