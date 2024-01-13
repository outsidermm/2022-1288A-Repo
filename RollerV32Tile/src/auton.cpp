#include "auton.h"

using namespace vex;

void shooterReset() {
  Shooter.spin(forward);
  while (!ShooterReset.isNearObject()) {
    wait(20, msec);
  }
  wait(220, msec);
  Shooter.stop();
}

int Motordeg(double inch) {
  double degree = inch / 0.428571429 / (4 * Pi) * 360;
  return degree;
}

int turnMotordeg(double deg) {
  double degree_rotation = 13 * Pi / 360 * deg / 0.428571429 / (4 * Pi) * 360;
  return degree_rotation;
}

void Turnleft(double degree, int speed) {
  double degree_rotation =
      13 * Pi / 360 * degree / 0.428571429 / (4 * Pi) * 360;
  drive.setVelocity(speed, percent);
  LD.spinFor(forward, -degree_rotation, degrees, false);
  RD.spinFor(forward, degree_rotation, degrees);
  return;
}

void Turnright(double degree, int speed) {
  double degree_rotation =
      13 * Pi / 360 * degree / 0.428571429 / (4 * Pi) * 360;
  drive.setVelocity(speed, percent);
  LD.spinFor(forward, degree_rotation, degrees, false);
  RD.spinFor(forward, -degree_rotation, degrees);
  return;
}

void Driveforward(double inch, int speed) {
  double degree = inch / 0.428571429 / (4 * Pi) * 360;
  drive.setVelocity(speed, percent);
  LD.spinFor(forward, degree, degrees, false);
  RD.spinFor(forward, degree, degrees);
  return;
}

void Drivebackward(double inch, int speed) {
  double degree = inch / 0.428571429 / (4 * Pi) * 360;
  drive.setVelocity(speed, percent);
  LD.spinFor(forward, -degree, degrees, false);
  RD.spinFor(forward, -degree, degrees);
  return;
}

void go(int speed, int degreel, int degreer) {
  drive.setVelocity(speed, percent);
  LD.spinFor(forward, degreel, degrees, false);
  RD.spinFor(forward, degreer, degrees);
  return;
}

void stop() { drive.stop(); }

double formatHeading(double heading) {
  while (heading > 180)
    heading -= 360;
  while (heading < -180)
    heading += 360;

  return heading;
}

void autonroller() {
  drive.spin(forward, 100, pct);
  wait(200, msec);
  waitUntil(L1.velocity(pct) <= 10 && L2.velocity(pct) <= 10 &&
            R1.velocity(pct) <= 10 && R2.velocity(pct) <= 10);
  vex::timer t;
  t.clear();
  Intake.spinFor(reverse, 500, degrees, false);
  while (!Intake.isDone() && t.time() <= 1250) {
    wait(50, msec);
  }
  return;
}

double diag(double a, double b) { return sqrt(a * a + b * b); }

void InertialturnPart(double heading) {
  double currentheading = Inertial.heading();
  if (currentheading > 180) {
    currentheading -= 360;
  }
  printf("Current Heading %d\n", (int)(currentheading * 100));

  if (heading > 180) {
    heading -= 360;
  }
  printf("Heading %d\n", (int)(heading * 100));

  double error = heading - currentheading;

  if (error > 180) {
    error -= 360;
  }

  if (error < -180) {
    error += 360;
  }
  printf("error %d\n", (int)(error * 100));

  double turndeg = turnMotordeg(error);
  printf("turndeg %d\n", (int)(turndeg * 100));
  go(40, turndeg, -turndeg);
  return;
}

void Inertialturn(double heading) {
  double lastheading = Inertial.heading();
  int still = 0;
  InertialturnPart(heading);
  wait(0.15, sec);
  while (fabs(Inertial.heading() - heading) >= 1) {

    if (Inertial.heading() - lastheading <= 0.5) {
      still++;
    }
    if (still >= 3) {
      InertialturnPart(heading);
      return;
    }
    lastheading = Inertial.heading();
    InertialturnPart(heading);
  }
}