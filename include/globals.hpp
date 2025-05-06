// #ifndef _GLOBALS_HPP_
#define _GLOBALS_HPP_

#include "api.h"
#include "pros/adi.hpp"
#include "lemlib/api.hpp"
#include "pros/motors.hpp"

extern pros::Motor FL;
extern pros::Motor FR; 
extern pros::Motor CL;
extern pros::Motor CR;
extern pros::Motor BL;
extern pros::Motor BR;

// extern pros::Motor wallstakearm;
extern pros::Motor intake;
extern pros::Motor intake2;

extern pros::MotorGroup left;
extern pros::MotorGroup right;

extern pros::Controller master;

extern pros::adi::Pneumatics clamp;
extern pros::adi::Pneumatics sweeper;
extern pros::adi::Pneumatics climb;
extern pros::adi::Pneumatics intakestack;
extern pros::adi::Pneumatics wallstakearm;

extern pros::Optical optical;
extern pros::Distance ringsensor;
extern pros::Distance stakesensor;

extern pros::IMU inertial;

extern pros::Rotation horizontalEnc;
extern pros::Rotation climbEnc;

extern lemlib::TrackingWheel horizontal;

// drivetrain settings
extern lemlib::Drivetrain drivetrain;

// lateral motion controller
extern lemlib::ControllerSettings linearController;

// angular motion controller
extern lemlib::ControllerSettings angularController;

// sensors for odometry
// note that in this example we use internal motor encoders, so we don't pass vertical tracking wheels
extern lemlib::OdomSensors sensors;

// create the chassis
extern lemlib::Chassis chassis;


extern bool beep;

extern int autonnum;
extern int alliance;
extern bool autons;
extern bool wallstake;
extern bool manualintake;
extern bool aStake;
extern bool elims;
extern bool climbing;
extern bool coloursort;
extern double original_hue;
