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

  autonroller(); // first roller
  Drivebackward(3, 100);
  wait(200, msec);

  Inertialturn(90);

  Intake.spin(forward);
  Driveforward(20, 100);
  wait(150, msec);

  Inertialturn(180);

  Driveforward(19, 75);
  wait(150, msec);

  Inertialturn(90);
  Intake.stop();

  autonroller(); // second roller

  Drivebackward(5, 70);
  wait(200, msec);

  Inertialturn(180);
  Driveforward(36, 80);
  wait(300, msec);

  autotrigger();
  wait(400, msec); // first 3 disc
  Drivebackward(35, 80);
  wait(200, msec);

  Inertialturn(222);
  Intake.spin(forward);
  Driveforward(diag(43, 43), 75);
  wait(800, msec);

  Inertialturn(134);
  Driveforward(diag(4, 4), 60);
  wait(300, msec);
  Intake.stop();
  wait(150, msec);
  autotrigger();
  Intake.spin(reverse);
  wait(400, msec); // second 3 disc

  Drivebackward(diag(17.1, 17.1), 70);
  wait(200, msec);
  Intake.stop();

  Inertialturn(223);
  Intake.spin(forward);
  Driveforward(diag(21.5, 21.5), 75);
  wait(150, msec);

  Inertialturn(180);

  Driveforward(30, 80);
  wait(150, msec);

  Inertialturn(270);

  Driveforward(5, 80);
  wait(150, msec);

  Intake.stop();
  Inertialturn(180);

  autonroller(); // third roller

  Drivebackward(4, 80);
  wait(200, msec);

  Inertialturn(270);

  Intake.spin(forward);
  Driveforward(24, 100);
  wait(150, msec);

  Inertialturn(0);
  Intake.stop();

  Driveforward(21, 100);
  wait(150, msec);

  Intake.spin(forward);
  Inertialturn(270);
  wait(150, msec);
  Intake.stop();

  autonroller(); // fourth roller

  Drivebackward(5, 80);
  wait(200, msec);

  Inertialturn(358);

  Driveforward(37, 80);
  wait(400, msec);
  autotrigger();
  wait(150, msec); // third 3 disc

  Drivebackward(36, 90);
  wait(200, msec);

  Inertialturn(39);
  Intake.spin(forward);
  Driveforward(diag(41, 41), 75);
  wait(800, msec);

  Inertialturn(311);
  Driveforward(diag(4.2, 4.2), 60);
  wait(400, msec);
  Intake.stop();
  wait(150, msec);
  autotrigger();
  wait(400, msec); // fourth 3 disc

  Intake.spin(reverse);
  Drivebackward(diag(7, 7), 60);
  wait(200, msec);

  Inertialturn(40);
  Intake.spin(reverse);
  Driveforward(diag(51, 51), 70);

  Expand.set(true);
  wait(1, sec);
  Expand.set(false);
  wait(1, sec);
  Expand.set(true);
  wait(1, sec);
  Expand.set(false);
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

  while (true) {
    printf("%d\n", (int)(Inertial.heading() * 100));
    wait(100, msec);
  }
}
