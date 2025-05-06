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
    setIntakeSpeed(-127, 0);
    delay(50);
    chassis.arcade(0, 0);
    delay(400);
    
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
    chassis.waitUntil(17);
    clamp.extend();
    chassis.waitUntilDone();
    delay(100);

    setIntakeSpeed(127, 127);

    chassis.turnToPoint(alliance*-45, (a ? -26 : -26), 1000);
    chassis.moveToPoint(alliance*-45, (a ? -26 : -26), 1000);

    chassis.turnToPoint(alliance*-25, -43, 1000, {.forwards=false});
    chassis.moveToPoint(alliance*-25, -43, 1000, {.forwards=false});

    chassis.turnToPoint(alliance*20, (a ? -43 : -43), 1000);
    chassis.moveToPoint(alliance*20, (a ? -43 : -43), 2000, {.maxSpeed=40});
    if (a) {
        while (chassis.getPose().x < 15) {
            delay(50);
        }
    } else {
        while (chassis.getPose().x > -15) {
            delay(50);
        }
    }
    
    wallstake=true;

    chassis.waitUntilDone();
    delay(300);
    clamp.retract();


    chassis.turnToHeading(180, 1000);
    chassis.waitUntilDone();

    xcoordinate = chassis.getPose().x;
    chassis.moveToPoint(xcoordinate, (a ? -25 : -25), 1000, {.forwards=false, .maxSpeed=127, .minSpeed=50, .earlyExitRange=14});
    chassis.moveToPoint(xcoordinate, (a ? -25 : -25), 1000, {.forwards=false, .maxSpeed=50, .minSpeed=10});
    chassis.waitUntil(20);
    
    clamp.extend();
    setIntakeSpeed(127, 127);
    wallstake=false;
    chassis.waitUntilDone();
    delay(200);
    chassis.turnToPoint((a ? 45 : -45), (a ? -20 : -20), 800);
    chassis.moveToPoint((a ? 45 : -45), (a ? -20 : -20), 800);
    chassis.waitUntilDone();
    chassis.turnToPoint((a ? 15 : -15), (a ? -10 : -10), 300, {.forwards=false});
    chassis.moveToPoint((a ? 15 : -15), (a ? -10 : -10), 1000, {.forwards=false});
    chassis.waitUntilDone();
    delay(200);
    setIntakeSpeed(0, 0);
}

void ringSide(){

    //alliance stake
    bool a = (alliance == 1);

    if (aStake) {
        allianceStake(alliance);
        chassis.moveToPoint(alliance*-19, -58, 800, {.forwards=false, .maxSpeed=80, .minSpeed=10}, false);
        delay(100);
        chassis.turnToHeading(180, 700);
        chassis.waitUntilDone();
        delay(50);
    } else {
        chassis.setPose(alliance*-24, -53.6, 180);
        chassis.setBrakeMode(E_MOTOR_BRAKE_HOLD);
    }

    //goal 1
    double xcoordinate = chassis.getPose().x;
    chassis.moveToPoint(xcoordinate, -28, 1000, {.forwards=false, .maxSpeed=127, .minSpeed=127, .earlyExitRange=18});
    chassis.moveToPoint(xcoordinate, -28, 1000, {.forwards=false, .maxSpeed=60, .minSpeed=5});
    chassis.waitUntil(18);
    clamp.extend();
    chassis.waitUntilDone();
    delay(100);

    //ring 1&2
    chassis.turnToPoint((a ? -37 : 37), (a ? -13 : -12), 800);
    delay(200);
    setIntakeSpeed(127, 127);
    chassis.moveToPoint((a ? -37 : 37), (a ? -13 : -12), 800, {.maxSpeed=70, .minSpeed=10});
    chassis.waitUntilDone();
    delay(100);
    chassis.swingToHeading(alliance*-89, a ? DriveSide::LEFT : DriveSide::RIGHT, 800);
    chassis.moveToPoint((a ? -55 : 55), (a ? -11 : -10), 800, {.maxSpeed=70, .minSpeed=10});

    //ring 3
    chassis.turnToPoint(alliance*-30, (a ? -17 : -17), 500, {.forwards = false});
    chassis.moveToPoint(alliance*-30, (a ? -17 : -17), 1000, {.forwards=false, .maxSpeed=90});
    chassis.waitUntilDone();
    delay(100);
    chassis.turnToPoint(alliance*-45, (a ? -26 : -26), 400);
    chassis.moveToPoint(alliance*-45, (a ? -26 : -26), 900);

    chassis.turnToPoint((a ? -54 : 54), (a ? -50: -50), 800, {.maxSpeed=100, .minSpeed=20});
    chassis.waitUntilDone();
    chassis.moveToPoint((a ? -54 : 54), (a ? -50: -50), 1500, {.maxSpeed=100, .minSpeed=20});
    chassis.waitUntilDone();
    chassis.turnToHeading((a ? 215: 135), 500, {.maxSpeed=80, .minSpeed=30}, false);
    chassis.waitUntilDone();

    


    if (elims) {
        setIntakeSpeed(127, -80);
        chassis.arcade(50, 0);
        delay(500);
        chassis.arcade(20, 0);
        setIntakeSpeed(127, 127);
        delay(300);
    } else {
        setIntakeSpeed(127, -80);
        chassis.arcade(50, 0);
        delay(500);
        chassis.arcade(20, 0);
        setIntakeSpeed(127, 127);
        delay(500);

        chassis.arcade(-127, 0);
        delay(400);
        setIntakeSpeed(127, -127);
        chassis.arcade(127, 0);
        delay(700);
        chassis.arcade(20, 0);
        setIntakeSpeed(127, 127);
        delay(100);
    }


    chassis.turnToPoint(alliance*-50, -50, 800, {.forwards=false});
    chassis.moveToPoint(alliance*-50, -50, 800, {.forwards=false});

    if (elims) {
        chassis.turnToPoint(alliance*-20, (a ? -48 : -48), 800);
        chassis.moveToPoint(alliance*-20, (a ? -48 : -48), 1500);
        chassis.moveToPoint(alliance*20, (a ? -48 : -48), 2000, {.maxSpeed=50});
        chassis.waitUntilDone();
    } else {
        chassis.turnToPoint(alliance*-19, -19, 1000, {.forwards=false});
        chassis.moveToPoint(alliance*-19, -19, 1000, {.forwards=false});
        chassis.waitUntilDone();
        setIntakeSpeed(0, 0);
    }

}

void ringSideRush(){
    bool a = (alliance == 1);
    chassis.setPose(alliance*-48, -53.5, 0);

    setIntakeSpeed(0, 127);
    chassis.moveToPoint((a ? -50: 46), -20, 1000, {.maxSpeed=127, .minSpeed=90});
    delay(100);
    sweeper.extend();
    chassis.waitUntilDone();
    setIntakeSpeed(0, 0);
    chassis.moveToPoint((a ? -48 : 46), -30, 1000, {.forwards=false});
    chassis.waitUntilDone();
    sweeper.retract();
    delay(200);
    chassis.turnToPoint(alliance*-24, -24, 1000, {.forwards=false});
    chassis.moveToPoint(alliance*-24, -24, 1000, {.forwards=false, .maxSpeed=60});
    chassis.waitUntil(22);
    clamp.extend();
    setIntakeSpeed(127, 127);

    if (a) {
        chassis.turnToPoint(alliance*-46, -16, 1000);
        chassis.moveToPoint(alliance*-46, -16, 1000);

        chassis.turnToPoint(alliance*-50, -9, 1000);
        chassis.moveToPoint(alliance*-50, -9, 1000, {.maxSpeed=50});

        chassis.turnToPoint(alliance*-46, -18, 1000, {.forwards=false});
        chassis.moveToPoint(alliance*-46, -18, 1000, {.forwards=false});
    } else {


        setIntakeSpeed(127, 127);
        // chassis.turnToPoint(alliance*-24, -24, 1000, {.forwards=false});
        // chassis.moveToPoint(alliance*-24, -24, 1000, {.forwards=false});

        chassis.turnToPoint(alliance*-50, -17, 1000);
        chassis.moveToPoint(alliance*-50, -17, 1000);


        chassis.turnToPoint(alliance*-48, -8, 1000);
        chassis.moveToPoint(alliance*-48, -8, 1000, {.maxSpeed=50});
        chassis.waitUntilDone();

        // sweeper.extend();
        // delay(300);
        // chassis.turnToHeading(155, 1000);
        // chassis.waitUntilDone();
        // sweeper.retract();



    }

    chassis.turnToPoint((a ? -54 : 54), (a ? -50: -50), 1200, {.maxSpeed=100, .minSpeed=20});
    chassis.waitUntilDone();
    chassis.moveToPoint((a ? -54 : 54), (a ? -50: -50), 1500, {.maxSpeed=100, .minSpeed=20});
    chassis.waitUntilDone();
    chassis.turnToHeading((a ? 215: 135), 1000, {.maxSpeed=80, .minSpeed=30}, false);
    chassis.waitUntilDone();

    setIntakeSpeed(127, 127);
    chassis.arcade(60, 0);
    delay(100);
    setIntakeSpeed(127, -100);
    delay(400);
    chassis.arcade(30, 0);
    setIntakeSpeed(127, 127);
    delay(500);

    // chassis.arcade(-127, 0);
    // delay(400);
    // setIntakeSpeed(127, -127);
    // chassis.arcade(127, 0);
    // delay(700);
    // chassis.arcade(20, 0);
    // setIntakeSpeed(127, 127);
    // delay(100);

    chassis.turnToPoint(alliance*-50, -50, 800, {.forwards=false});
    chassis.moveToPoint(alliance*-50, -50, 800, {.forwards=false});

    chassis.turnToPoint(alliance*-20, (a ? -48 : -45), 800);
    chassis.moveToPoint(alliance*-20, (a ? -48 : -45), 1500);
    chassis.moveToPoint(alliance*20, (a ? -48 : -45), 2000, {.maxSpeed=50});
    chassis.waitUntilDone();
}

void goalSide(){
    bool a = (alliance == 1);

    if (aStake) {
        allianceStake(-alliance);
        chassis.moveToPoint(alliance*19, -58, 800, {.forwards=false, .maxSpeed=80, .minSpeed=10}, false);
        delay(100);
        chassis.turnToHeading(180, 700);
        chassis.waitUntilDone();
        delay(50);
    } else {
        chassis.setPose(alliance*24, -53.6, 180);
        chassis.setBrakeMode(E_MOTOR_BRAKE_HOLD);
    }

    //goal 1
    double xcoordinate = chassis.getPose().x;
    chassis.moveToPoint(xcoordinate, -28, 1000, {.forwards=false, .maxSpeed=127, .minSpeed=127, .earlyExitRange=18});
    chassis.moveToPoint(xcoordinate, -28, 1000, {.forwards=false, .maxSpeed=60});
    chassis.waitUntil(11);
    clamp.extend();
    chassis.waitUntilDone();
    delay(100);

    setIntakeSpeed(127, 127);

    chassis.turnToPoint(alliance*45, (a ? -26 : -26), 900);
    chassis.moveToPoint(alliance*45, (a ? -26 : -26), 900);

    chassis.turnToPoint((a ? 48 : -48), (a ? -46 : -44), 800, {.maxSpeed=100, .minSpeed=20});
    chassis.waitUntilDone();
    chassis.moveToPoint((a ? 48 : -48), (a ? -46 : -44), 1500, {.maxSpeed=100, .minSpeed=20});
    chassis.waitUntilDone();
    chassis.turnToHeading((a ? 135: 215), 500, {.maxSpeed=80, .minSpeed=30}, false);
    chassis.waitUntilDone();

    setIntakeSpeed(127, -90);
    chassis.arcade(50, 0);
    delay(900);
    chassis.arcade(20, 0);
    setIntakeSpeed(127, 127);
    delay(500);
    
    
    if (elims) {
        if (a) {
            chassis.moveToPoint(alliance*50, -50, 1000, {.forwards=false, .maxSpeed=100});
            chassis.turnToPoint(alliance*13, -15, 1000);
            chassis.waitUntilDone();
            sweeper.extend();
            setIntakeSpeed(0, 0);
            delay(100);
            chassis.moveToPoint(alliance*10, -15, 1000, {.earlyExitRange=20});
            chassis.moveToPoint(alliance*10, -15, 1000, {.maxSpeed=100});
            setIntakeSpeed(0, 0);
            chassis.waitUntilDone();
            setIntakeSpeed(127, 127);
            delay(100);
            chassis.moveToPoint(alliance*50, -40, 1500, {.forwards=false});
            chassis.waitUntilDone();
            clamp.retract();
            sweeper.retract();
            wallstake = true;
            delay(200);
            chassis.turnToPoint(alliance*45, -35, 1000, {});
            chassis.moveToPoint(alliance*45, -30, 1000, {});
            chassis.turnToPoint(45, -7, 1000, {.forwards=false});
            chassis.moveToPoint(45, -7, 1000, {.forwards=false, .maxSpeed=60});
            chassis.waitUntilDone();
            clamp.extend();
            delay(100);
            wallstake = false;
            chassis.moveToPoint(alliance*43, -20, 1000);
        } else {
            chassis.moveToPoint(alliance*54, -54, 2500, {.forwards=false, .maxSpeed=100});
            chassis.waitUntilDone();
            setIntakeSpeed(127, -100);
            chassis.arcade(50, 0);
            delay(600);
            chassis.arcade(20, 0);
            setIntakeSpeed(127, 127);
            delay(500);

            chassis.moveToPoint(alliance*54, -54, 2500, {.forwards=false, .maxSpeed=100});
            chassis.waitUntilDone();
            setIntakeSpeed(127, -100);
            chassis.arcade(50, 0);
            delay(600);
            chassis.arcade(20, 0);
            setIntakeSpeed(127, 127);
            delay(500);

            chassis.moveToPoint(-54, -54, 1000, {.forwards=false});
            chassis.turnToHeading(45, 1000);
            chassis.waitUntilDone();
            clamp.retract();

            chassis.turnToPoint(-50, -14, 1000, {.forwards=false});
            chassis.moveToPoint(-50, -14, 1000, {.forwards=false, .maxSpeed=90});
            chassis.waitUntilDone();
            clamp.extend();
        }
    } else {
        if (a) {
            chassis.moveToPoint(alliance*50, -50, 1000, {.forwards=false, .maxSpeed=100});
            chassis.turnToPoint(alliance*13, -15, 1000);
            chassis.waitUntilDone();
            sweeper.extend();
            setIntakeSpeed(0, 0);
            delay(100);
            chassis.moveToPoint(alliance*10, -15, 1000, {.earlyExitRange=20});
            chassis.moveToPoint(alliance*10, -15, 1000, {.maxSpeed=100});
            setIntakeSpeed(0, 0);
            chassis.waitUntilDone();
            setIntakeSpeed(127, 127);
            delay(100);
            chassis.moveToPoint(alliance*30, -35, 1000, {.forwards=false});
            chassis.waitUntilDone();
            sweeper.retract();
            delay(100);
            chassis.turnToPoint(alliance*25, -23, 1000);
            chassis.moveToPoint(alliance*25, -23, 1000);
            chassis.waitUntilDone();
            delay(600);
            chassis.turnToPoint(alliance*10, -15, 1000);
            chassis.moveToPoint(alliance*10, -15, 1000);
            chassis.waitUntilDone();
            setIntakeSpeed(0, 0);
        } else {
            chassis.moveToPoint(alliance*54, -54, 2500, {.forwards=false, .maxSpeed=100});
            chassis.waitUntilDone();
            setIntakeSpeed(127, -100);
            chassis.arcade(50, 0);
            delay(600);
            chassis.arcade(20, 0);
            setIntakeSpeed(127, 127);
            delay(500);

            chassis.moveToPoint(alliance*54, -54, 2500, {.forwards=false, .maxSpeed=100});
            chassis.waitUntilDone();
            setIntakeSpeed(127, -100);
            chassis.arcade(50, 0);
            delay(600);
            chassis.arcade(20, 0);
            setIntakeSpeed(127, 127);
            delay(500);
            chassis.moveToPoint(-50, -50, 1000, {.forwards=false});

            chassis.turnToPoint(alliance*18, -15, 1000);
            chassis.moveToPoint(alliance*18, -15, 2000);
            chassis.waitUntilDone();
            setIntakeSpeed(0, 0);

        }
        
    }

}

void goalSideRush(){
    bool a = (alliance == 1);
    chassis.setPose((a ? 62.1 : -33.6), -50.4, -18.1);

    wallstake=true;

    setIntakeSpeed(0, 127);
    chassis.moveToPoint((a ? 50 : -45), (a? -17: -21), 2000, {.maxSpeed=127, .minSpeed=90});
    delay(100);
    sweeper.extend();
    chassis.waitUntilDone();
    setIntakeSpeed(0, 0);
    chassis.moveToPoint((a ? 53 : -43), -33, 1000, {.forwards=false});
    chassis.waitUntilDone();
    sweeper.retract();
    chassis.turnToPoint((a ? 57 : -40), -18, 1000, {.forwards=false});
    chassis.moveToPoint((a ? 57 : -40), -18, 1500, {.forwards=false, .maxSpeed=60});
    chassis.waitUntilDone();
    clamp.extend();
    delay(100);
    setIntakeSpeed(127, 0);
    wallstake=false;
    delay(600);
    clamp.retract();
    delay(100);
    chassis.arcade(127, 0);
    delay(200);
    chassis.arcade(0, 0);
    chassis.turnToPoint(alliance*24, -20, 1000, {.forwards=false});
    chassis.moveToPoint(alliance*24, -20, 1000, {.forwards=false, .maxSpeed=60});
    chassis.waitUntil(24);
    clamp.extend();
    setIntakeSpeed(127, 127);
    // setIntakeSpeed(127, 127);
    // chassis.turnToPoint(46, -16, 1000);
    // chassis.moveToPoint(46, -16, 1000);

    chassis.turnToPoint((a ? 54 : -53), (a ? -49: -49), 800, {.maxSpeed=100, .minSpeed=20});
    chassis.waitUntilDone();
    chassis.moveToPoint((a ? 54 : -53), (a ? -49: -49), 1500, {.maxSpeed=100, .minSpeed=20});
    chassis.waitUntilDone();
    chassis.turnToHeading((a ? 135: 215), 500, {.maxSpeed=80, .minSpeed=30}, false);
    chassis.waitUntilDone();

    setIntakeSpeed(127, -100);
    chassis.arcade(50, 0);
    delay(500);
    chassis.arcade(20, 0);
    setIntakeSpeed(127, 127);
    delay(500);

    chassis.arcade(-127, 0);
    delay(400);
    chassis.arcade(90, 0);
    delay(500);
    chassis.arcade(20, 0);
    setIntakeSpeed(127, 127);
    delay(500);

    chassis.turnToPoint(alliance*50, -50, 1000, {.forwards=false});
    chassis.moveToPoint(alliance*50, -50, 1000, {.forwards=false});

    chassis.turnToHeading((a ? -45 : 45), 1000);
    chassis.waitUntilDone();
    clamp.retract();
    delay(200);

    chassis.turnToPoint((a ? 54 : -43), (a ? -14 : -10), 1000, {.forwards=false});
    chassis.moveToPoint((a ? 54 : -43), (a ? -14 : -10), 1000, {.forwards=false, .maxSpeed=60});

    chassis.waitUntilDone();
    clamp.extend();
    delay(300);
    chassis.moveToPoint(-43, -20, 1000);



}

void skills() {

    coloursort = false;
    
    chassis.setPose(1, -62, -90);
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
    chassis.turnToPoint(2, -6, 600);
    chassis.moveToPoint(2, -6, 1000);

    //goal 1 ring 3
    chassis.turnToPoint(20, 24, 600);
    chassis.moveToPoint(20, 24, 1000);
    
    //wallstake 1 ring
    chassis.turnToPoint(43, 24, 500);
    chassis.moveToPoint(43, 24, 800);
    wallstake=true;

    //wallstake 1
    chassis.turnToPoint(40, 4, 1000);
    chassis.moveToPoint(40, 4, 1000, {.maxSpeed=80});
    chassis.waitUntilDone();
    delay(100);
    chassis.turnToHeading(90, 1200, {.maxSpeed=70});
    delay(200);
    wallstakeExtend();
    chassis.waitUntilDone();
    moveDistance(20, {.maxSpeed=120});
    setIntakeSpeed(0, 127);
    chassis.waitUntilDone();
    delay(100);
    chassis.arcade(10, -60);
    delay(200);
    chassis.arcade(0, 0);
    delay(200);
    wallstakearm.retract();

    //goal 1 ring 4 & 5
    chassis.waitUntilDone();
    moveDistance(-10, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToPoint(56, 46, 800);
    chassis.moveToPoint(56, 46, 1500);
    setIntakeSpeed(127, 127);
    chassis.waitUntilDone();
    delay(200);

    //goal 1 ring 6
    chassis.turnToPoint(45, 58, 800);
    chassis.waitUntilDone();
    delay(200);
    chassis.moveToPoint(45, 58, 1000);

    //drop goal 1
    chassis.turnToHeading(-100, 800);
    chassis.waitUntilDone();
    chassis.arcade(-60, 0);
    delay(500);
    chassis.arcade(0, 0);
    clamp.retract();
    chassis.turnToHeading(-135, 800);
    chassis.waitUntilDone();
    
    //goal 2
    moveDistance(15, {.maxSpeed=80});
    delay(200);
    setIntakeSpeed(127, -127);
    chassis.turnToPoint(-2, 51, 800, {.forwards=false});
    setIntakeSpeed(0, 0);
    chassis.moveToPoint(-2, 51, 1500, {.forwards=false, .minSpeed=40, .earlyExitRange=24});
    chassis.moveToPoint(-2, 51, 1500, {.forwards=false, .maxSpeed=40});
    while (chassis.getPose().x > 6) {
        delay(50);
    }
    clamp.extend();
    setIntakeSpeed(127, 127);
    chassis.waitUntilDone();
    delay(200);

    //goal 2 ring 1
    chassis.turnToPoint(-24, 30, 800);
    chassis.moveToPoint(-24, 30, 1000);

    //wallstake 2 ring
    chassis.turnToPoint(-45, 26, 800);
    chassis.moveToPoint(-45, 26, 1000);
    chassis.waitUntilDone();
    wallstake=true;

    //wallstake 2
    chassis.turnToPoint(-45, 5, 1000);
    chassis.moveToPoint(-45, 5, 1000, {.maxSpeed=90});
    chassis.waitUntilDone();
    delay(100);
    chassis.turnToHeading(-90, 1200, {.maxSpeed=80});
    setIntakeSpeed(0, 127);
    wallstakeExtend();
    chassis.waitUntilDone();
    moveDistance(19, {.maxSpeed=100});
    chassis.waitUntilDone();
    chassis.arcade(0, -60);
    delay(200);
    chassis.arcade(0, 0);
    delay(200);
    wallstakearm.retract();

    //goal 2 ring 2 - 5
    moveDistance(-9, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToPoint(-50, -53, 800);
    setIntakeSpeed(127, 127);
    chassis.moveToPoint(-50, -53, 1000, {.maxSpeed=100, .minSpeed=50, .earlyExitRange=36});
    chassis.moveToPoint(-50, -53, 1000, {.maxSpeed=50});

    //goal 2 ring 6
    chassis.turnToPoint(-63, -48, 800);
    chassis.moveToPoint(-63, -48, 1000);

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

    chassis.turnToPoint(-15, 60, 800);
    chassis.moveToPoint(-15, 60, 1500);
    chassis.turnToHeading(95, 800);
    chassis.waitUntilDone();
    moveDistance(-40, {.forwards=false, .maxSpeed=90});
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

    chassis.turnToPoint(-48, -36, 1000);
    chassis.moveToPoint(-48, -36, 1500);
    chassis.waitUntilDone();
    delay(100);

    // chassis.turnToHeading(0, 800);
    // chassis.waitUntilDone();
    

    chassis.turnToPoint(-24, -46, 800, {.forwards=false});
    chassis.moveToPoint(-24, -46, 1500, {.forwards=false, .maxSpeed=70});
    chassis.waitUntilDone();
    clamp.extend();
    chassis.waitUntilDone();
    delay(200);
    wallstake=false;
    setIntakeSpeed(127, 127);

    chassis.turnToPoint(-24, -24, 800);
    chassis.moveToPoint(-24, -24, 1000);
    setIntakeSpeed(127, 127);

    chassis.turnToPoint(0, -60, 800, {.forwards=false});
    chassis.moveToPoint(0, -60, 1000, {.forwards=false});
    chassis.turnToPoint(48, -24, 800);
    chassis.moveToPoint(48, -24, 1500);
    chassis.waitUntilDone();
    delay(100);

    chassis.turnToPoint(48, -48, 800);
    chassis.moveToPoint(48, -48, 1000, {.minSpeed=50, .earlyExitRange=24});
    chassis.moveToPoint(48, -48, 1000, {.maxSpeed=80});

    // chassis.turnToPoint(65, -36, 800);
    // chassis.moveToPoint(65, -36, 1000);

    chassis.turnToHeading(-60, 800);
    chassis.waitUntilDone();
    clamp.retract();
    setIntakeSpeed(0, 0);
    chassis.arcade(-60, 0);
    delay(400);
    chassis.arcade(0, 0);

    chassis.turnToPoint(12, -12, 800);
    chassis.moveToPoint(12, -12, 1000);
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

