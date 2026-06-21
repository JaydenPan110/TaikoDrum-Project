#include <pitches.h>
#include <Servo.h>

#define LDR_PIN A0
#define BUZZER_PIN 10
#define BUTTON_PIN 2

#define LED_R 6
#define LED_G 5
#define LED_B 3


const int servoPin = 9;

char mystr[6] = "Hello";

Servo coinServo;

int melody[] = {
  NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
  NOTE_G5, REST, NOTE_G4, REST, 
  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5,NOTE_C5, NOTE_D5, NOTE_B4,
  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5,NOTE_C5, NOTE_D5, NOTE_B4,
  
  REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_E5,
  REST, NOTE_GS4, NOTE_A4, NOTE_C4, REST, NOTE_A4, NOTE_C5, NOTE_D5,
  REST, NOTE_DS5, REST, NOTE_D5,
  NOTE_C5, REST,
  
  REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_E5,
  REST, NOTE_GS4, NOTE_A4, NOTE_C4, REST, NOTE_A4, NOTE_C5, NOTE_D5,
  REST, NOTE_DS5, REST, NOTE_D5,
  NOTE_C5, REST,
  
  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  
  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5, NOTE_E5,
  REST, 
  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
  NOTE_G5, REST, NOTE_G4, REST, 
  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,
  
  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,
  
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_D5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,
  
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_B4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
  NOTE_C5, NOTE_E4, NOTE_E4, NOTE_C4,
  
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_D5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,
  
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_B4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
  NOTE_C5, NOTE_E4, NOTE_E4, NOTE_C4,
  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5, NOTE_E5,
  REST,
  
  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
  NOTE_G5, REST, NOTE_G4, REST, 
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_D5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,
  
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_B4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
  NOTE_C5, NOTE_E4, NOTE_E4, NOTE_C4,
  
  // Game over sound
  NOTE_C5, NOTE_G4, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_AS4, NOTE_GS4,
  NOTE_G4, NOTE_D4, NOTE_E4
};

int durations[] = {
  8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4, 
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4,8, 8, 4,
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4,8, 8, 4,
  
  
  4, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4,
  2, 2,
  
  4, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4,
  2, 2,
  
  8, 4, 8, 8, 8, 4,
  8, 4, 8, 2,
  
  8, 4, 8, 8, 8, 8, 8,
  1, 
  8, 4, 8, 8, 8, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8, 4,
  4, 4, 4, 4, 
  4, 8, 4, 4,
  
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4, 8, 8, 4,
  
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4, 8, 8, 4,
  
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8,
  
  8, 4, 8, 2,
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 4, 8, 8, 8, 8,
  8, 4, 8, 2,
  
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8,
  
  8, 4, 8, 2,
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 4, 8, 8, 8, 8,
  8, 4, 8, 2,
  8, 4, 8, 8, 8, 8, 8,
  1,
  
  8, 4, 8, 8, 8, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8, 4,
  4, 4, 4, 4, 
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8,
  
  8, 4, 8, 2,
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 4, 8, 8, 8, 8,
  8, 4, 8, 2,
  
  //game over sound
  4, 4, 4,
  8, 8, 8, 8, 8, 8,
  8, 8, 2
};

// Non-blocking state for buzzer
int currentNote = 0;
unsigned long noteTimer = 0;
int noteDuration = 0;
bool waitingForNote = false;

// Non-blocking state for dispenser
int coinsToDispense = 0;
int dispenseStep = 0; // 0=idle, 1=open_step, 2=wait_fall, 3=close_step, 4=wait_next
unsigned long dispenseTimer = 0;
int servoCurrentAngle = 0;
#define SERVO_STEP_DELAY 30
#define SERVO_ANGLE_STEP 3

#define LDR_THRESHOLD 5
#define JOY_THRESHOLD 50

// Non-blocking state for LDR
unsigned long ldrTimer = 0;
int prevLdrValue = 0;
unsigned long ldrDebounceTimer = 0;
bool ldrCooldown = false;
bool coinDropped = false;
#define LDR_COOLDOWN_MS 200

// Non-blocking state for joystick
unsigned long joyTimer = 0;
int prevJoyY = 512;

// Button state
int lastButtonState = HIGH;
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// Rainbow LED state
unsigned long rainbowTimer = 0;
unsigned int hue = 0;

// Green breathing animation state
bool rainbowMode = true;
unsigned long greenFadeTimer = 0;
int greenFadeLevel = 0;
bool greenFadeRising = true;
unsigned long coinDropLockTimer = 0;
int breathR = 255;
int breathG = 0;
int breathB = 255;
bool spinning = false;
unsigned long spinEndTime = 0;

void setColor(int r, int g, int b)
{
  analogWrite(LED_R, 255 - r);
  analogWrite(LED_G, 255 - g);
  analogWrite(LED_B, 255 - b);
}

void hsvToRgb(unsigned int h, byte &r, byte &g, byte &b)
{
  unsigned int sector = h / 60;
  unsigned int remainder = h % 60;
  unsigned int ramp = (remainder * 255) / 60;

  byte low = 0;
  byte high = 255;

  switch (sector) {
    case 0: r = high; g = ramp; b = low; break;
    case 1: r = high - ramp; g = high; b = low; break;
    case 2: r = low; g = high; b = ramp; break;
    case 3: r = low; g = high - ramp; b = high; break;
    case 4: r = ramp; g = low; b = high; break;
    case 5: r = high; g = low; b = high - ramp; break;
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  coinServo.attach(servoPin);
  coinServo.write(0);
  servoCurrentAngle = 0;

  coinsToDispense = 3;
  dispenseStep = 1;
  dispenseTimer = millis();
}

void loop()
{
  int size = sizeof(durations) / sizeof(int);

  // --- LED (non-blocking) ---
  if (spinning) {
    if (millis() >= spinEndTime) {
      spinning = false;
      rainbowMode = true;
      rainbowTimer = millis();
    } else {
      if (millis() - greenFadeTimer >= 20) {
        greenFadeTimer = millis();
        if (greenFadeRising) {
          greenFadeLevel += 5;
          if (greenFadeLevel >= 255) {
            greenFadeLevel = 255;
            greenFadeRising = false;
          }
        } else {
          greenFadeLevel -= 5;
          if (greenFadeLevel <= 0) {
            greenFadeLevel = 0;
            greenFadeRising = true;
          }
        }
        setColor(
          (breathR * greenFadeLevel) / 255,
          (breathG * greenFadeLevel) / 255,
          (breathB * greenFadeLevel) / 255
        );
      }
    }
  } else if (rainbowMode) {
    if (millis() - rainbowTimer >= 20) {
      rainbowTimer = millis();
      byte r, g, b;
      hsvToRgb(hue, r, g, b);
      setColor(r, g, b);
      hue = (hue + 1) % 360;
    }
  } else {
    if (millis() - greenFadeTimer >= 20) {
      greenFadeTimer = millis();
      if (greenFadeRising) {
        greenFadeLevel += 5;
        if (greenFadeLevel >= 255) {
          greenFadeLevel = 255;
          greenFadeRising = false;
        }
      } else {
        greenFadeLevel -= 5;
        if (greenFadeLevel <= 0) {
          greenFadeLevel = 0;
          greenFadeRising = true;
        }
      }
      setColor(
        (breathR * greenFadeLevel) / 255,
        (breathG * greenFadeLevel) / 255,
        (breathB * greenFadeLevel) / 255
      );
    }
  }

  // // --- Buzzer (non-blocking) ---
  // if (!waitingForNote) {
  //   noteDuration = 1000 / durations[currentNote];
  //   tone(BUZZER_PIN, melody[currentNote], noteDuration);
  //   noteTimer = millis();
  //   waitingForNote = true;
  // } else {
  //   int pause = noteDuration * 1.10;
  //   if (millis() - noteTimer >= pause) {
  //     currentNote = (currentNote + 1) % size;
  //     waitingForNote = false;
  //   }
  // }

  // --- Button (non-blocking, debounced) ---
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
    lastButtonState = reading;
  }
  if (millis() - lastDebounceTime >= debounceDelay) {
    if (lastButtonState == LOW && buttonState == HIGH) {
      Serial.println("pushed");
    }
    buttonState = lastButtonState;
  }

  // --- LDR (non-blocking, every 10ms) ---
  if (millis() - ldrTimer >= 10) {
    ldrTimer = millis();

    if (ldrCooldown && millis() - ldrDebounceTimer >= LDR_COOLDOWN_MS) {
      ldrCooldown = false;
    }

    bool calibrating = (millis() < 10000) || (!rainbowMode && millis() - coinDropLockTimer < 10000);

    if (calibrating) {
      prevLdrValue = analogRead(LDR_PIN);
    } else if (!ldrCooldown) {
      int ldrValue = analogRead(LDR_PIN);
      int diff = ldrValue - prevLdrValue;
      if (diff < 0 && abs(diff) > LDR_THRESHOLD) {
        Serial.println("beep");
        tone(BUZZER_PIN, 1000, 50);
        prevLdrValue = ldrValue;
        ldrCooldown = true;
        ldrDebounceTimer = millis();
        coinDropped = true;

        if (rainbowMode) {
          rainbowMode = false;
          coinDropLockTimer = millis();
          greenFadeLevel = 0;
          greenFadeRising = true;
          greenFadeTimer = millis();
        }
      } else if (diff > 0 && abs(diff) > LDR_THRESHOLD) {
        prevLdrValue = ldrValue;
      }
    }
  }

  // --- Joystick Y-axis (non-blocking, every 20ms) ---
  if (millis() - joyTimer >= 20) {
    joyTimer = millis();
    int joyY = analogRead(A1);
    int diff = joyY - prevJoyY;
    if (diff < 0 && abs(diff) > JOY_THRESHOLD) {
      if (coinDropped) {
        Serial.println("spin");
        Serial.write(mystr, 5);
        coinDropped = false;
        spinning = true;
        spinEndTime = millis() + 5000;
        breathR = 255;
        breathG = 0;
        breathB = 0;
        greenFadeLevel = 0;
        greenFadeRising = true;
        greenFadeTimer = millis();
      } else {
        Serial.println("down");
        if (!rainbowMode) {
          breathR = 0;
          breathG = 255;
          breathB = 255;
        }
      }
    }
    prevJoyY = joyY;
  }

  // --- Dispenser (non-blocking) ---
  if (coinsToDispense > 0) {
    switch (dispenseStep) {
      case 1: // Gradually open
        if (millis() - dispenseTimer >= SERVO_STEP_DELAY) {
          servoCurrentAngle += SERVO_ANGLE_STEP;
          if (servoCurrentAngle >= 125) {
            servoCurrentAngle = 125;
            coinServo.write(servoCurrentAngle);
            dispenseTimer = millis();
            dispenseStep = 2;
          } else {
            coinServo.write(servoCurrentAngle);
            dispenseTimer = millis();
          }
        }
        break;
      case 2: // Wait at open for coin to fall
        if (millis() - dispenseTimer >= 500) {
          dispenseTimer = millis();
          dispenseStep = 3;
        }
        break;
      case 3: // Gradually close
        if (millis() - dispenseTimer >= SERVO_STEP_DELAY) {
          servoCurrentAngle -= SERVO_ANGLE_STEP;
          if (servoCurrentAngle <= 0) {
            servoCurrentAngle = 0;
            coinServo.write(servoCurrentAngle);
            dispenseTimer = millis();
            dispenseStep = 4;
          } else {
            coinServo.write(servoCurrentAngle);
            dispenseTimer = millis();
          }
        }
        break;
      case 4: // Wait before next coin
        if (millis() - dispenseTimer >= 500) {
          coinsToDispense--;
          if (coinsToDispense > 0) {
            dispenseStep = 1;
          } else {
            dispenseStep = 0;
          }
        }
        break;
    }
  }
}
