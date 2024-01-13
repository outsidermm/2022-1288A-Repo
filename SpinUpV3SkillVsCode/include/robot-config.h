using namespace vex;

extern brain Brain;

extern motor L1;
extern motor L2;
extern motor R1;
extern motor R2;
extern inertial Inertial;
extern controller Controller1;
extern digital_out Expand;
extern optical ShooterReset;
extern motor_group Intake;
extern motor_group Shooter;
extern int slsDelay;
extern bool shooter_charging;
extern bool intake_roll_up;
extern bool intake_roll_down;
extern motor_group LD;
extern motor_group RD;
extern motor_group drive;

void  vexcodeInit( void );