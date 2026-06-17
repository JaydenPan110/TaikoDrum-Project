
#include <AccelStepper.h>
#include <Servo.h>

// ----- Pin mappings -----
const int stepper1StepPin = A0;
const int stepper2StepPin = A1;
const int stepper3StepPin = A2;
const int directionPin = A3;
const int reel1SensorPin = 8;
const int reel2SensorPin = 7;
const int reel3SensorPin = 4;
const int servoPin = 9;

// ----- Game configuration -----
const int SYMBOLS_PER_REEL = 10;
const int STEPS_PER_SYMBOL = 320;
const int FULL_REEL_STEPS = SYMBOLS_PER_REEL * STEPS_PER_SYMBOL;
const int MICROSTEPS = 16;   // 1/16 microstepping

// ----- Motor control parameters -----
const int CALIBRATION_SPEED = 800;     // steps/sec (fast forward)
const int CALIBRATION_ACCEL = 1500;    /
const int SPIN_SPEED = 1000;          // steps/sec
const int SPIN_ACCEL = 2000;

// ----- Logical Symbol definitions -----
enum Symbol {
  SYM_CHERRY,     // logical 0 (physical index 4)
  SYM_SEVEN,      // logical 1 (physical index 5)
  SYM_LIMON,      // logical 2 (physical index 6)
  SYM_BAR,        // logical 3 (physical index 7)
  SYM_MANDERIN,   // logical 4 (physical index 8)
  SYM_WATERMELON, // logical 5 (physical index 9)
  SYM_BELL,       // logical 6 (physical index 0)
  SYM_BAR2,       // logical 7 (physical index 1)
  SYM_BANANA,     // logical 8 (physical index 2)
  SYM_GRAPE       // logical 9 (physical index 3)
};

// ----- Game variables -----
bool gameReady = false;
Symbol reelPositions[3];   // Logical reel state (updated after each spin)
Symbol targetPositions[3];

// ----- Hardware objects -----
AccelStepper stepper1(AccelStepper::DRIVER, stepper1StepPin, directionPin);
AccelStepper stepper2(AccelStepper::DRIVER, stepper2StepPin, directionPin);
AccelStepper stepper3(AccelStepper::DRIVER, stepper3StepPin, directionPin);
Servo coinServo;

// ------------------- Calibration Routine -------------------
void calibrateReels() {
  gameReady = false;

  delay(400);
  calibrateReel(stepper1, reel1SensorPin, 1);
  calibrateReel(stepper2, reel2SensorPin, 2);
  calibrateReel(stepper3, reel3SensorPin, 3);

  // Set all reel logical states to CHERRY (for reference in the game)
  for (int i = 0; i < 3; i++)
    reelPositions[i] = SYM_CHERRY;

  gameReady = true;
}



  // Used for Overshoot
  int overshoot = (FULL_REEL_STEPS * MICROSTEPS) / 4;
  stepper.move(overshoot);
  while (stepper.distanceToGo() > 0) {
    stepper.run();
  }

  // 3. Slow reverse until sensor triggers again
  stepper.setMaxSpeed(300 * MICROSTEPS);
  stepper.setAcceleration(800 * MICROSTEPS);
  while (digitalRead(sensorPin) == HIGH) {
    stepper.move(-1);
    stepper.run();
  }

  // 4. Set exact position to 0
  stepper.setCurrentPosition(0);
}

// ------------------- Game Routine -------------------
void spinAndStopReels() {
  // Extra rotations (3, 4, 5) for visual effect.
  setupReel(stepper1, targetPositions[0], 3);
  setupReel(stepper2, targetPositions[1], 4);
  setupReel(stepper3, targetPositions[2], 5);

  while (stepper1.isRunning() || stepper2.isRunning() || stepper3.isRunning()) {
    stepper1.run();
    stepper2.run();
    stepper3.run();
  }

  // After the reels stop, update the internal positions
  updateReelPositions();
}

// ------------------- Reel Spin Function -------------------
void setupReel(AccelStepper &stepper, Symbol target, int rotations) {
  long current = stepper.currentPosition();

  const float DEGREES_PER_SYMBOL = 360.0 / SYMBOLS_PER_REEL;
  const float STEPS_PER_DEGREE = (float)STEPS_PER_SYMBOL / DEGREES_PER_SYMBOL;

  // Use an offset of +4 so that a logical target of 0 lands on physical index 4 (CHERRY)
  long adjustedTarget = ((int)target + 4 + SYMBOLS_PER_REEL) % SYMBOLS_PER_REEL;
  long targetSteps = adjustedTarget * STEPS_PER_SYMBOL;
  targetSteps -= (15 * STEPS_PER_DEGREE);
  if (targetSteps < 0) {
    targetSteps += FULL_REEL_STEPS;
  }

  long distance = (targetSteps - current) + rotations * FULL_REEL_STEPS;
  // Always move forward: if distance is negative, add a full revolution.
  if (distance < 0) {
    distance += FULL_REEL_STEPS;
  }

  stepper.moveTo(current + distance);
  stepper.setMaxSpeed(SPIN_SPEED * MICROSTEPS);
  stepper.setAcceleration(SPIN_ACCEL * MICROSTEPS);
}

// ------------------- Update Reel Positions -------------------
void updateReelPositions() {
  reelPositions[0] = targetPositions[0];
  reelPositions[1] = targetPositions[1];
  reelPositions[2] = targetPositions[2];

  long pos = stepper1.currentPosition() % FULL_REEL_STEPS;
  if (pos < 0) pos += FULL_REEL_STEPS;
  stepper1.setCurrentPosition(pos);

  pos = stepper2.currentPosition() % FULL_REEL_STEPS;
  if (pos < 0) pos += FULL_REEL_STEPS;
  stepper2.setCurrentPosition(pos);

  pos = stepper3.currentPosition() % FULL_REEL_STEPS;
  if (pos < 0) pos += FULL_REEL_STEPS;
  stepper3.setCurrentPosition(pos);
}

// ------------------- Dispense Routine -------------------
void dispenseCoins() {
  for (int i = 0; i < 1; i++) {
    coinServo.write(90);
    delay(500);
    coinServo.write(0);
    delay(500);
  }
}
