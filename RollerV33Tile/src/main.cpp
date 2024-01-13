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
  shooterResetParallel.broadcast();

  autonroller();

  Drivebackward(9.5, 60);
  wait(200, msec);
  Intake.spin(forward);
}

void usercontrol(void) {
  drive.setStopping(coast);
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

  while (true) {
    printf("%d\n", (int)(Inertial.heading() * 100));
    wait(100, msec);
  }
}
