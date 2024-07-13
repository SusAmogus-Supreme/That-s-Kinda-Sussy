//*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 10, D        
// ClawMotor            motor         3               
// ArmMotor             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// Use to move
void Arcade() {
  double speedleft = controller1.Axis1.value() + controller1.Axis3.value();
  double speedright = controller1.Axis1.value() - controller1.Axis3.value();

  fl.spin(forward, speedleft, percent);
  ml.spin(forward, speedleft, percent);
  bl.spin(forward, speedleft, percent);

  fr.spin(reverse, speedright, percent);
  mr.spin(reverse, speedright, percent);
  br.spin(reverse, speedright, percent);

}

void intaking() {
  if (controller1.ButtonR2.pressing()) {
    intake.spin(forward, 350, rpm);
    
  } else if (controller1.ButtonR1.pressing()) {
    intake.spin(reverse, 80, pct);
    intake2.spin(fwd, 90, percent);

  } else {
    intake.stop(coast);
    intake2.stop(coast);
  }
  }

void clamp() {
  Mogo1.set(true);
  Mogo2.set(true);
}

void unclamp() {
  Mogo1.set(false);
  Mogo2.set(false);
}

bool clamptrue = false;
bool prevclamp = false;

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.

    Arcade();
    intaking();
    // For clamping
    if (controller1.ButtonL1.pressing()) {
      if (prevclamp == false) {
        clamptrue = !clamptrue;
        prevclamp = true;
      }
    } else {
      if (prevclamp == true) {
        prevclamp = false;
      }
    } 

    if (clamptrue) {
      clamp();
    } else if (!clamptrue) {
      unclamp();
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
