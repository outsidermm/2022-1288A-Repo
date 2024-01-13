#include "auton.h"
#include "teleop.h"
#include "vex.h"
#include <bits/stdc++.h>
#include <cmath>

competition Competition;
bool safetyLock = false;

event shooterResetParallel = event(shooterReset);

void pre_auton(void) {
  vexcodeInit();
  drive.setStopping(hold);
  drive.setVelocity(100, percent);
  drive.setMaxTorque(100, percent);

  Intake.setVelocity(100, percent);
  Intake.setMaxTorque(100, percent);
  Intake.setStopping(brake);

  Shooter.setVelocity(100, percent);
  Shooter.setMaxTorque(100, percent);
  Shooter.setStopping(hold);

  Inertial.setHeading(0, degrees);
  shooter_charging = false;
  intake_roll_up = false;
  intake_roll_down = false;

  Inertial.calibrate();
  while (Inertial.isCalibrating()) {
    wait(100, msec);
  }

  Inertial.setHeading(0, degrees);
  safetyLock = true;
}

void autonomous(void) {
  waitUntil(safetyLock);
  // Driveforward(double inch, int speed)
  // Drivebackward( double inch, int speed)
  // go ( int speed, int degreel, int degreer)
  // int Motordeg(double inch)
  Shooter.spinFor(forward, 300.0, degrees, false);
  Driveforward(17, 100);
  wait(500, msec);
  Inertialturn(90);

  autonroller();

  Drivebackward(10, 60);
  wait(200, msec);

  Inertialturn(218);

  Intake.spinFor(forward, 300, degrees);

  shooterResetParallel.broadcast();
  Driveforward(43, 80);

  wait(200, msec);

  Intake.setVelocity(40, percent);
  Intake.spin(reverse);
  Inertialturn(298);
  Intake.stop();
  wait(200, msec);
  Intake.setVelocity(100, percent);

  Driveforward(5.5, 30);
  trigger();
  printf("1\n");
  Intake.spin(forward);
  wait(1200, msec);
  Intake.stop();

  trigger(false);
  stop();
}

void usercontrol(void) {
  drive.setStopping(coast);
  drive.setVelocity(100, percent);
  drive.setMaxTorque(100, percent);

  Intake.setVelocity(100, percent);
  Intake.setMaxTorque(100, percent);
  Intake.setStopping(brake);

  Shooter.setVelocity(100, percent);
  Shooter.setMaxTorque(100, percent);
  Shooter.setStopping(hold);

  shooterResetParallel.broadcast();
  Controller1.ButtonR1.pressed(trigger);
  Controller1.ButtonL1.pressed(intake_toggle);
  Controller1.ButtonL2.pressed(outake_toggle);
  Controller1.ButtonA.pressed(onevent_Controller1ButtonA_pressed_0);
  Controller1.ButtonA.released(onevent_Controller1ButtonA_released_0);
  Controller1.ButtonB.pressed(shooterReset);
  while (1) {
    maincontroll();
    expansion();
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  Controller1.rumble("..");
}
