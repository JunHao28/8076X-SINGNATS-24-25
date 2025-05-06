#include "main.h"
#include "pros/misc.hpp"

double test;

int intakeSpeed1;
int intakeSpeed2;

int ringUnseenCount=0;
double pendingOriginalHue=100;

void ringControl() {
    delay(1000);
    while (true) {
        if (optical.get_proximity() > 200) {
            ringUnseenCount = 0;
            Task::delay(100);
            continue;
        } else {
            ringUnseenCount += 1;
        }

        if (ringUnseenCount == 1) {
            Task::delay(50);
            pendingOriginalHue = optical.get_hue();
        } else if (abs(pendingOriginalHue - optical.get_hue()) > 10) {
            ringUnseenCount = 0;
            Task::delay(100);
            continue;
        }

        if (ringUnseenCount >= 50) {
            original_hue = pendingOriginalHue;
            ringUnseenCount = 0;
        }

        Task::delay(5);
    }
}

void intakeControl() {
    intake.tare_position();
    intake.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    int colour = 0;
    bool override = false;
    int intakejam = 0;
    // int target = 0;
    while (true) {
        if (manualintake) {
            intake.move(intakeSpeed1);
            intake2.move(intakeSpeed2);
            Task::delay(20);
            continue;
        }
        if (wallstake) {
            if (stakesensor.get_distance() < 50) {
                if (!override) {
                    delay(60);
                    intake.move(-120);
                    Task::delay(400);
                    intake.move(70);
                    Task::delay(100);
                    intake.move(0);
                    override=true;
                }
            } else {
                override=false;
                if (intake.get_actual_velocity() == 0 && intakeSpeed1 > 0){
                    intakejam++;
                    if (intakejam > 12){
                        intake2.move(-127);
                        intake.move(-40);
                        Task::delay(200);
                        intake.move(127);
                        intake2.move(127);
                        intakejam=0;
                    }
                } else {
                    intakejam=0;
                }
                intake.move(intakeSpeed1/1.2);
                
            }
        } else {
            // target = 0;
            override=false;
            if (intake.get_actual_velocity() == 0 && intakeSpeed1 > 0){
                intakejam++;
                if (intakejam > 8){
                    intake2.move(-127);
                    intake.move(-40);
                    Task::delay(200);
                    intake.move(127);
                    intake2.move(127);
                    intakejam=0;
                }
            } else {
                intakejam=0;
            }

            optical.set_led_pwm(60);

            if (coloursort) {
                if (intakeSpeed1 == 127) {
                    if ((optical.get_hue()-original_hue)/original_hue > 0.3 && alliance == 1) {
                        // Task::delay(20);
                        intake.move(-127);
                        Task::delay(100);
                        intake.move(127);
                    }else if ((optical.get_hue()-original_hue)/original_hue < -0.3 && alliance == -1){
                        // Task::delay(20);
                        intake.move(-127);
                        Task::delay(100);
                        intake.move(127);
                    } else {
                        intake.move(intakeSpeed1);
                    }
                } else {
                    intake.move(intakeSpeed1);
                }
            } else {
                intake.move(intakeSpeed1);
            }
            
        }
        intake2.move(intakeSpeed2);
        Task::delay(10);
        continue;
    }
}

//old intake control
// void intakeControl() {
        // }

        // intake2.move(intakeSpeed2);

        // if (intakeSpeed1 != 127) {
        //     intake.move(0);
        //     Task::delay(100);
        //     continue;
        // }

        // if (stage > 0) {
        //     optical.set_led_pwm(100);
        // } else {
        //     optical.set_led_pwm(0);
        // }

        // if (climbsection > 0){
        //     if (abs(int(intake.get_position())%530) - 400 > 60){
        //         intake.move(30);
        //         Task::delay(50);
        //     }
        // }

        // if (stage == 2) {
        //     if (wallstake) {
        //         if (intake.get_position() > intakeposition + 150) {
        //             if (abs(int(intake.get_position())%530) > 150){
        //                 intake.move(90);
        //             } else {
        //                 intake.move(0);
        //                 stage = 0;
        //             }
        //         }
        //     } else if (colour == 0){
        //         if (optical.get_hue() > 100) {
        //             colour = -1; 
        //             stage += 1;
        //         } else if (optical.get_hue() < 60){
        //             colour = 1;
        //             stage += 1;
        //             master.rumble(".");
        //         } else if (optical.get_proximity() < 160) {
        //             stage = 4;
        //         }
        //     }
        // } else if (stage == 3) {
        //     if (colour != alliance) {
        //         if (intake.get_position() > intakeposition + 400) {
        //             if (int(intake.get_position())%530 > 500) {
        //                 Task::delay(10);
        //                 intake.move(0);
        //                 Task::delay(300);
        //                 intake.move(127);
        //                 stage += 1;
        //             }
        //         }
        //     } else {
        //         intake.move(127);
        //         stage += 1;
        //     }
        // } else if (stage == 4) {
        //     intake.move(127);
        //     if (intake.get_position() > intakeposition + 300) {
        //         if (optical.get_proximity() > 200) {
        //             stage = 2;
        //             colour = 0;
        //             intakeposition = intake.get_position();
        //         }
        //     }
        //     if (intake.get_position() > intakeposition + 1000) {
        //         stage = 0;
        //         intakeposition = 0;
        //         colour = 0;
        //     }
        // } else if (stage == 1) {
        //     intake.move(110);
        // } else if (stage == 0) {
        //     if (abs(int(intake.get_position())%530) > 100 && !wallstake) {
        //         intake.move(70);
        //     } else {
        //         intake.move(0);
        //     }
        // } else {
        // }
        // Task::delay(5);
//     }
// }

void setIntakeSpeed(int speed1, int speed2) {
    intakeSpeed1 = speed1;
    intakeSpeed2 = speed2;
}

int climbsection = 0;

void climbControl() {
    while (true) {
        if (!climbing) {
            Task::delay(300);
            continue;
        }

        if (climbsection == 1 || climbsection == 3) {
            if (climbEnc.get_position() > -360000) {
                if (inertial.get_roll() > -2) {
                    left.move(-127);
                    right.move(-127);
                } else {
                    left.move(0);
                }
            } else {
                left.move(0);
                right.move(0);
                if (inertial.get_roll() < 2) {    
                    climbsection += 1;
                }
            }
        } else if (climbsection == 2 || climbsection == 4) {
            if (climbEnc.get_position() < 0) {
                left.move(127);
                right.move(127);
            } else {
                Task::delay(400);
                if (climbsection == 4) {
                    Task::delay(200);
                }
                climbsection += 1;
                left.move(0);
                right.move(0);
                delay(200);
            }
        } else if (climbsection == 5) {
            // left.move(80);
            // right.move(80);
            // delay(100);
            // climb.set_value(false);
            // delay(300);
            // left.move(0);
            // right.move(0);
            climbsection += 1;
        }
        Task::delay(50);
    }
}


void wallstakeExtend() {
    delay(100);
    wallstakearm.extend();
    // intake.move(0);
    delay(150);
    wallstake=false;
}