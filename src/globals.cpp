#include "lemlib/chassis/trackingWheel.hpp"
#include "main.h" 
#include "lemlib/api.hpp"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

Motor FL(-14, MotorGears::blue, MotorUnits::degrees);
Motor CL(-13, MotorGears::blue, MotorUnits::degrees);
Motor BL(-12, MotorGears::blue, MotorUnits::degrees);
Motor FR(17, MotorGears::blue, MotorUnits::degrees);
Motor CR(18, MotorGears::blue, MotorUnits::degrees);
Motor BR(19, MotorGears::blue, MotorUnits::degrees);

// Motor wallstakearm(7, MotorGears::green, MotorUnits::degrees);
Motor intake(-20, MotorGears::blue, MotorUnits::degrees);
Motor intake2(-11, MotorGears::blue, MotorUnits::degrees);
Optical optical(8);

// motor groups
MotorGroup left({-14, -13, -12}); // left motor group
MotorGroup right({17, 18, 19}); // right motor group

// controller
Controller master(pros::E_CONTROLLER_MASTER);


adi::Pneumatics clamp('C', false);
adi::Pneumatics sweeper('D', false);
adi::Pneumatics climb('B', false);
adi::Pneumatics intakestack('E', false);
adi::Pneumatics wallstakearm('A', false);

// Inertial Sensor
Imu inertial(15);
// Distance autoclamp(3);
Distance ringsensor(1);
Distance stakesensor(7);

// tracking wheels
Rotation horizontalEnc(16);
Rotation verticalEnc(1);
Rotation climbEnc(3);

// horizontal tracking wheel. 2" diameter, 3.7" offset, back of the robot
lemlib::TrackingWheel horizontal(&horizontalEnc, 2, -3.76); //-3.76 was the previous offset
// vertical tracking wheel. 2" diameter, " -1.4375" offset
lemlib::TrackingWheel vertical(&verticalEnc, 2.05, -1.248); 


// drivetrain settings
lemlib::Drivetrain drivetrain(&left, // left motor group
                              &right, // right motor group
                              12, // 12 inch track width
                              3.25, // using new 3.25" omnis
                              450, // drivetrain rpm is 450
                              2 // chase power is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(20, // proportional gain (kP) 20
                                            0,
                                            50, // derivative gain (kD) 50
                                            0,
                                            1, // small error range, in inches 1
                                            50, // small error range timeout, in milliseconds 50
                                            3, // large error range, in inches 3
                                            100, // large error range timeout, in milliseconds 100
                                            32// maximum acceleration (slew) 32
);

// angular motion controller
lemlib::ControllerSettings angularController(3.75, // proportional gain (kP)
                                             0,
                                             22.5, // derivative gain (kD)
                                             0, //prev was 0
                                             1, // small error range, in degrees
                                             50, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             100, // large error range timeout, in milliseconds
                                             127 // maximum acceleration (slew)
);

// sensors for odometry
// note that in this example we use internal motor encoders, so we don't pass vertical tracking wheels
lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel 1
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have one
                            &horizontal, // horizontal tracking wheel 1
                            // nullptr,
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &inertial // inertial sensor
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);

int autonnum = 3;
int alliance = -1;
bool autons = true;
bool autoclampBool = true;
bool wallstake = false;
bool manualintake = false;
bool aStake = true;
bool elims = false;
bool climbing = false;
bool coloursort = true;
double original_hue;