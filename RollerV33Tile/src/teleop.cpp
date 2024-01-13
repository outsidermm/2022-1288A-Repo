#include "teleop.h"

using namespace vex;

void maincontroll() {
  int ls, rs;
  ls = Controller1.Axis3.position();
  rs = Controller1.Axis2.position();

  if (Controller1.Axis3.position() > -5 && Controller1.Axis3.position() < 5) {
    ls = 0;
  } else if (Controller1.Axis3.position() > 95) {
    ls = 100;
  } else if (Controller1.Axis3.position() < -95) {
    ls = -100;
  }

  if (Controller1.Axis2.position() > -5 && Controller1.Axis2.position() < 5) {
    rs = 0;
  } else if (Controller1.Axis2.position() > 95) {
    rs = 100;
  } else if (Controller1.Axis2.position() < -95) {
    rs = -100;
  }

  RD.spin(fwd, rs, pct); //(Axis3+Axis4)/2
  LD.spin(fwd, ls, pct); //(Axis3+Axis4)/2
  return;
}

void onevent_Controller1ButtonA_pressed_0() {
  shooter_charging = true;
  Shooter.spin(forward);
}

void onevent_Controller1ButtonA_released_0() {
  shooter_charging = false;
  Shooter.stop();
}

void trigger() {
  Shooter.spinFor(forward, 1080.0, degrees, true);
  Shooter.stop();
}

void trigger(bool parallel) {
  Shooter.spinFor(forward, 1080.0, degrees, parallel);
}

void autotrigger() { Shooter.spinFor(forward, 1080.0, degrees, false); }

void intake_toggle() {
  if (intake_roll_up) {
    intake_roll_up = false;
    Intake.stop();
    wait(0.15, seconds);
  } else {
    intake_roll_up = true;
    Intake.spin(forward);
    wait(0.15, seconds);
  }
}

void outake_toggle() {
  if (intake_roll_down) {
    intake_roll_down = false;
    Intake.stop();
    wait(0.15, seconds);
  } else {
    intake_roll_down = true;
    Intake.spin(reverse);
    wait(0.15, seconds);
  }
}

void expansion() {
  bool buttonUp = Controller1.ButtonUp.pressing();
  bool buttonLeft = Controller1.ButtonLeft.pressing();
  if (buttonUp && buttonLeft) {
    Expand.set(true);
    wait(1, seconds);
    Expand.set(false);
  }
}