#ifndef _MECHCONTROL_HPP_
#define _MECHCONTROL_HPP_
extern int stage;
extern int sector;
extern int climbsection;

void intakeControl();
void ringControl();
void setIntakeSpeed(int speed1, int speed2);
void climbControl();
void wallstakeExtend();

#endif