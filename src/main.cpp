#include "main.h"
#include <iostream>
#include <ostream>
#include "globals.hpp"

void initialize()
{   
    // if (optical.get_proximity() < 200) {
    // }

    chassis.calibrate(true);

    //Mechanism Tasks (More information in Mechcontrol.cpp)
    Task ringTask(ringControl); //Detecting where the ring is
    Task intakeTask(intakeControl); //Changing the intake speed based on where the ring is 
    Task climbTask(climbControl); //Climbing sequence
    // print position to brain screen
    pros::lcd::initialize(); // initialize brain screen
    original_hue = optical.get_hue();
    // chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    // pros::Task screen_task([&]() {
    //     while (true) {
    //         // print robot location to the brain screen
    //         pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
    //         pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
    //         pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
    //         pros::lcd::print(3, "hue %f", original_hue);
    //         pros::lcd::print(4, "act hue %f", optical.get_hue());
    //         // delay to save resources
    //         pros::delay(20);
    //     }
    // });

    //Display Tasks (More information in display.cpp)
    Task displayTask(displayControl); //Brain screen with auton selector
    Task controllerTask(controllerControl);
}

void disabled() {}

void competition_initialize() {}

ASSET(path_txt);

void autonomous()
{
    double start = millis(); 
//     autons = true;

    //Switch case for auton selector
    switch (autonnum)
    {
    case 1:
        elims = false;
        ringSide();
        break;

    case 2:
        elims = true;
        ringSide();
        break;

    case 3:
        elims = false;
        goalSide();
        break;

    case 4:
        elims = true;
        goalSide();
        break;
    case 5:
        goalSideRush();
        break;
    case 6:
        soloAWP();
        break;
    case 7: 
        skills();
        break;
    }

    // chassis.waitUntilDone();

    // screen::print(TEXT_SMALL, 300, 180, "Time elapsed: %f", (millis() - start)/1000);
        // set position to x:0, y:0, heading:0
   
       // set position to x:0, y:0, heading:0
    // chassis.setPose(0, 0, 0);
//     chassis.moveToPose(
//     24, // x = 24
//     48, // y = 48
//     0, // theta = 0
//     10000, // timeout of 4000ms
//     {.lead = 0.4, .minSpeed = 100}
// );
    // chassis.
    // soloAWP();
    // goalSideRush();
    // goalSide();
    // ringSide();

    // ringSideRush();
    // goalSideRush();
    // soloAWP();
    // goalSide();
    // goalSideRush();
    chassis.waitUntilDone();
    screen::print(TEXT_SMALL, 300, 180, "Time elapsed: %f", (millis() - start)/1000);

}

void opcontrol() {
    autons = false;
    bool shift = false;
    int intakeSpeed = 0;
    bool setheight = false;
    bool wallstakeBool = false;
    bool sense;

    while (true) {

        if (!master.get_digital(E_CONTROLLER_DIGITAL_UP)) {
            sense = false;
        } else {
            sense = true;
        }

        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX;
        if (sense) {
            rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        } else {
            rightX = (master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)*0.7);
        }
        
        
        if (!climbing){
            chassis.setBrakeMode(MOTOR_BRAKE_COAST);
            left.move(leftY + rightX);
            right.move(leftY - rightX);
        }

        if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
            climbing = !climbing;
            climbsection += 1;
            setheight = true;
        }

        if (master.get_digital_new_press(DIGITAL_X)) {
            coloursort = false;
            manualintake = true;
        }

        if (master.get_digital_new_press(DIGITAL_A)) {
            coloursort = false;
            manualintake = false;
        }

        if (master.get_digital_new_press(DIGITAL_Y)) {
            coloursort = true;
            manualintake = false;
        }

        if (!setheight) {
            if (climbEnc.get_position() < -14000) {
                // climb.retract();
                beep = true;
                setheight=true;
            }
        }

        // if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
        //     wallstake = !wallstake;
        // }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
            shift = true;
        } else {
            shift = false;
        }

        if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)){
            if (shift) {
                climb.toggle();
            } else {
                clamp.toggle();
            }
        }


        if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)){
            if (shift) {
                sweeper.toggle();
            } else {
                if (wallstake) {
                    intakeSpeed=127;
                    wallstakeExtend();
                    intakeSpeed=0;
                    wallstakeBool = true;
                } else if (wallstakearm.is_extended()) {
                    wallstakearm.retract();
                    wallstakeBool = false;
                } else if (!wallstake) {
                    wallstake = true;
                }
            }
        }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !shift) {
            intakeSpeed = 127;
        } else if (master.get_digital(E_CONTROLLER_DIGITAL_L1) && shift) {
            intakeSpeed = -127;
        } else {
            intakeSpeed = 0;
        }
        
        if (wallstakeBool) {
            setIntakeSpeed(0, intakeSpeed);
        } else {
            setIntakeSpeed(intakeSpeed, intakeSpeed);
        }

        if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
            intakestack.toggle();
        }

        pros::delay(10);
    }
}
