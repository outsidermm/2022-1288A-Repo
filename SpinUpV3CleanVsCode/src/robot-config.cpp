#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor L1 = motor(PORT2, ratio6_1, true);
motor L2 = motor(PORT7, ratio6_1, true);
motor R1 = motor(PORT4, ratio6_1, false);
motor R2 = motor(PORT5, ratio6_1, false);

inertial Inertial = inertial(PORT6);
motor ShooterMotorA = motor(PORT11, ratio36_1, false);
motor ShooterMotorB = motor(PORT12, ratio36_1, true);
motor_group Shooter = motor_group(ShooterMotorA, ShooterMotorB);
motor IntakeMotorA = motor(PORT8, ratio6_1, false);
motor IntakeMotorB = motor(PORT9, ratio6_1, false);
motor_group Intake = motor_group(IntakeMotorA, IntakeMotorB);
digital_out Expand = digital_out(Brain.ThreeWirePort.A);
controller Controller1 = controller(primary);
optical ShooterReset = optical(PORT10);
motor_group LD = motor_group(L1, L2);
motor_group RD = motor_group(R1, R2);
motor_group drive = motor_group(L1, L2, R1, R2);

int slsDelay;
bool shooter_charging;
bool intake_roll_up;
bool intake_roll_down;

bool RemoteControlCodeEnabled = true;

void vexcodeInit(void) {}