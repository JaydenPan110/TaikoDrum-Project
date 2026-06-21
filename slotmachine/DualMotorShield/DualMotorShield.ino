// DualMotorShield.pde
// -*- mode: C++ -*-
//
// Shows how to run 3 simultaneous steppers
// using the Itead Studio Arduino Dual Stepper Motor Driver Shield
// model IM120417015
// This shield is capable of driving 2 steppers at 
// currents of up to 750mA
// and voltages up to 30V
// The third stepper requires an additional driver (e.g., A4988).
// Runs all steppers forwards and backwards, accelerating and decelerating
// at the limits.
//
// Copyright (C) 2014 Mike McCauley
// $Id:  $

#include <AccelStepper.h>

// The X Stepper pins 
#define STEPPER1_DIR_PIN 5
#define STEPPER1_STEP_PIN 2
// The Y stepper pins
#define STEPPER2_DIR_PIN 6
#define STEPPER2_STEP_PIN 3
// The Z stepper pins (requires separate driver, e.g. A4988)
#define STEPPER3_DIR_PIN 7
#define STEPPER3_STEP_PIN 4

#define SPIN_DURATION_MS 5000

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEPPER2_STEP_PIN, STEPPER2_DIR_PIN);
AccelStepper stepper3(AccelStepper::DRIVER, STEPPER3_STEP_PIN, STEPPER3_DIR_PIN);

String inputString = "";
bool spinning = false;
unsigned long spinEndTime = 0;
int joyYValue = 512;

void spinMotors() {
    spinning = true;
    spinEndTime = millis() + SPIN_DURATION_MS;
    Serial.println("SPINNING");
    digitalWrite(LED_BUILTIN, HIGH);
}

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    stepper1.setMaxSpeed(1000.0);
    stepper1.setAcceleration(800.0);
    stepper1.setSpeed(1000.0);

    stepper2.setMaxSpeed(1000.0);
    stepper2.setAcceleration(800.0);
    stepper2.setSpeed(1000.0);

    stepper3.setMaxSpeed(1000.0);
    stepper3.setAcceleration(800.0);
    stepper3.setSpeed(1000.0);

    Serial.println("MOTOR_READY");
}

void loop()
{
    while (Serial.available()) {
        char c = Serial.read();
        Serial.write(c);
        if (c == '\n') {
            if (inputString == "spin") {
                spinMotors();
            } else if (inputString.startsWith("Y")) {
                joyYValue = inputString.substring(1).toInt();
                float speed = map(joyYValue, 0, 1023, 200, 1000);
                stepper1.setSpeed(speed);
                stepper2.setSpeed(speed);
                stepper3.setSpeed(speed);
            }
            inputString = "";
        } else if (c != '\r') {
            inputString += c;
        }
    }

    if (spinning) {
        stepper1.runSpeed();
        stepper2.runSpeed();
        stepper3.runSpeed();
        if (millis() >= spinEndTime) {
            spinning = false;
            digitalWrite(LED_BUILTIN, LOW);
            Serial.println("DONE");
        }
    }
}
