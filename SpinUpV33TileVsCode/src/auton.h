#ifndef AUTON_H
#define AUTON_H

#include "vex.h"
#include <bits/stdc++.h>

void shooterReset();
int Motordeg(double inch);
int turnMotordeg(double deg);
void Turnleft(double degree, int speed);
void Turnright(double degree, int speed);
void Driveforward(double inch, int speed);
void Drivebackward(double inch, int speed);
void go(int speed, int degreel, int degreer);
void stop();
double formatHeading(double heading);
void autonroller();
double diag(double a, double b);
void InertialturnPart(double heading);
void Inertialturn(double heading);

#endif