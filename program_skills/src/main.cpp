/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\maxin                                            */
/*    Created:      Sun Oct 18 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2, 3, 4      
// RightRoller          motor         7               
// LeftRoller           motor         9               
// Track                motor         10              
// Uppp                 motor         20              
// Vision5              vision        5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

const int rollerSpeed = 80; //constant for roller speed
const int trackSpeed = 80; //constant for track speed

void intake() { //intakes the ball - runs rollers inwards and track clockwise
  RightRoller.setPosition(0, degrees);
  LeftRoller.setPosition(0, degrees);
  Track.setPosition(0, degrees);
  Uppp.setPosition(0, degrees);

  RightRoller.setVelocity(rollerSpeed, percent);
  LeftRoller.setVelocity(rollerSpeed, percent);
  Track.setVelocity(rollerSpeed, percent);
  Uppp.setVelocity(rollerSpeed, percent);

  RightRoller.spin(forward);
  LeftRoller.spin(forward);
  Track.spin(forward);
  Uppp.spin(forward);
}

void outtake() { //outtakes the ball - runs rollers outwards and track counterclockwise
  RightRoller.setPosition(0, degrees);
  LeftRoller.setPosition(0, degrees);
  Track.setPosition(0, degrees);
  Uppp.setPosition(0, degrees);

  RightRoller.setVelocity(rollerSpeed, percent);
  LeftRoller.setVelocity(rollerSpeed, percent);
  Track.setVelocity(rollerSpeed, percent);
  Uppp.setVelocity(rollerSpeed, percent);

  RightRoller.spin(reverse);
  LeftRoller.spin(reverse);
  Track.spin(reverse);
  Uppp.spin(reverse);
}

void stopMotors() { //stops intake motors (rollers and track)
  RightRoller.stop();
  LeftRoller.stop();
  Track.stop();
  Uppp.stop();
}

void justRollers() { //runs just the rollers   
  RightRoller.setVelocity(rollerSpeed, percent);
  LeftRoller.setVelocity(rollerSpeed, percent);

  RightRoller.spin(forward);
  LeftRoller.spin(forward);
}

void justTrack() { //runs just the track 
  Track.setVelocity(trackSpeed, percent);
  Uppp.setVelocity(trackSpeed, percent);

  Track.spin(forward);
  Uppp.spin(forward);
}

void findGoal() { //makes sure the robot is pointed towards a goal
  Vision5.takeSnapshot(Vision5__GREENGOAL); //takes snapshot of vision sensor
  if (Vision5.objectCount > 0) { //if green object is detected (assumed to be goal), end search
    return;
  } else { // else if green object is not detected (no goal), turn right until goal is found
    Drivetrain.turn(right);
    while (Vision5.objectCount == 0) {
      wait(0.02, seconds);
      Vision5.takeSnapshot(Vision5__GREENGOAL);
    }
    Drivetrain.stop(); //stops drivetrain
    return;
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Drivetrain.setDriveVelocity(30, percent); //set initial drive velocity
  Drivetrain.setTurnVelocity(25, percent); //set initial turn velocity

  ////////////////////first goal//////////////////////
  intake(); //pick up red ball in front of robot
  Drivetrain.driveFor(forward, 25, inches); //first distance
  stopMotors();

  Drivetrain.turnFor(left, 70, degrees); //right angle turn left

  intake(); //pick up red ball at border
  Drivetrain.driveFor(forward, 23, inches); //go to border
  stopMotors();

  intake(); //ensure that the red ball is in the robot's rollers
  Drivetrain.driveFor(reverse, 13, inches); //back up
  stopMotors();

  Drivetrain.turnFor(left, 45, degrees); //right angle turn left
  findGoal(); //use vision sensor to confirm that the robot is aligned with the goal

  Drivetrain.stop();
  
  Drivetrain.driveFor(forward, 25, inches); //go to goal
  justTrack(); //score 1 red
  wait(7, seconds);
  stopMotors();

  Drivetrain.stop();
  wait(1, seconds);

  ///////////////////////second goal//////////////////

  Drivetrain.driveFor(reverse, 10, inches); //back up from first goal

  Drivetrain.turnFor(right, 160, degrees); //turn around

  Drivetrain.driveFor(forward, 15, inches); //go in direction of center goal
  justRollers();
  Drivetrain.driveFor(forward, 40, inches); //turn on rollers halfway through to pick up red ball
  stopMotors();

  Drivetrain.turnFor(left, 105, degrees); //after picking up red ball, turn left towards second goal
  Drivetrain.stop();
  intake(); //pick up red ball in front of second goal
  Drivetrain.driveFor(forward, 24, inches); //go forward to the second goal
  stopMotors();

  Drivetrain.setDriveVelocity(15, percent); //slow down approach goal more precisely

  findGoal(); //use vision sensor to confirm that the robot is aligned with the goal

  intake(); //keep intake on
  Drivetrain.driveFor(forward, 7, inches); //drive to the second goal
  stopMotors();

  intake(); //score the 3 red balls and take in the 1 blue ball in the goal
  wait(12, seconds); 
  stopMotors();

  Drivetrain.stop();
  wait(1, seconds);

  intake(); //ensure that the robot has the blue ball as it leaves the second goal
  Drivetrain.driveFor(reverse, 10, inches); //back out of the second goal
  stopMotors();
}
