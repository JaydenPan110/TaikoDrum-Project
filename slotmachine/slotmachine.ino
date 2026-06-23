#include <pitches.h>
#include <Servo.h>
#include <IRremote.hpp>
#include <Adafruit_NeoPixel.h>
#include <AccelStepper.h>

enum Symbol {
  SYM_CHERRY,
  SYM_SEVEN,
  SYM_LIMON,
  SYM_BAR,
  SYM_MANDERIN,
  SYM_WATERMELON,
  SYM_BELL,
  SYM_BAR2,
  SYM_BANANA,
  SYM_GRAPE
};

const String SYMBOL_NAMES[] = {
  "CHERRY",
  "Seven",
  "LIMON",
  "BAR",
  "MANDERIN",
  "WATERMELON",
  "BELL",
  "BAR2",
  "BANANA",
  "GRAPE"
};

static const int PHYS_TO_LOG[10] = {6, 7, 8, 9, 0, 1, 2, 3, 4, 5};

int getSymbol(long position) {
  return PHYS_TO_LOG[((position + 80) % 200) / 20];
}

#define IR_RECEIVE_PIN 12
#define IR_PLAY_BUTTON 0xEA15FF00

#define LDR_PIN A0
#define BUZZER_PIN 10
#define BUTTON_PIN 2

#define LED_R 6
#define LED_G 5
#define LED_B 3

const int servoPin = 9;
#define NEO_PIN 11
#define NUM_LEDS 8

Adafruit_NeoPixel strip(NUM_LEDS, NEO_PIN, NEO_GRB + NEO_KHZ800);

#define STEP_X A2
#define STEP_Y A3
#define STEP_Z A4
#define DIR_PIN A5

#define SPIN_TARGET 50000

AccelStepper stepperX(AccelStepper::DRIVER, STEP_X, DIR_PIN);
AccelStepper stepperY(AccelStepper::DRIVER, STEP_Y, DIR_PIN);
AccelStepper stepperZ(AccelStepper::DRIVER, STEP_Z, DIR_PIN);

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

int coinMelody[] = {
  NOTE_C4, REST, NOTE_G4, REST, NOTE_AS4, NOTE_C5, NOTE_AS4, REST, NOTE_F4, NOTE_DS4, REST,
  NOTE_C4, REST, NOTE_G4, REST, NOTE_AS4, NOTE_C5, NOTE_AS4, REST, NOTE_F4, NOTE_DS4, REST,
  NOTE_C4, REST, NOTE_G4, REST, NOTE_AS4, NOTE_C5, NOTE_AS4, REST, NOTE_F4, NOTE_DS4, REST,

  NOTE_C4, REST, NOTE_E4, REST, NOTE_G4, NOTE_A4, NOTE_AS4,
  NOTE_C5, REST, NOTE_C5, REST, NOTE_AS4, REST, NOTE_A4, REST,
  NOTE_AS4, REST, NOTE_AS4, NOTE_C5, REST, NOTE_AS4, NOTE_A4, REST,
  REST,
  NOTE_C5, REST, NOTE_AS4, REST, NOTE_A4, REST, NOTE_AS4, REST, NOTE_E5,
  REST,

  NOTE_C5, REST, NOTE_C5, REST, NOTE_AS4, REST, NOTE_A4, REST,
  NOTE_AS4, REST, NOTE_AS4, NOTE_C5, REST, NOTE_AS4, NOTE_A4, REST,
  REST,
  NOTE_C5, REST, NOTE_AS4, REST, NOTE_A4, REST, NOTE_AS4, REST, NOTE_E4,
  REST,
};

int coinDurations[] = {
  4, 8, 4, 8, 4, 8, 8, 16, 8, 8, 16,
  4, 8, 4, 8, 4, 8, 8, 16, 8, 8, 16,
  4, 8, 4, 8, 4, 8, 8, 16, 8, 8, 16,

  4, 8, 4, 8, 4, 4, 4,
  8, 16, 8, 16, 8, 16, 8, 16,
  8, 16, 8, 8, 16, 8, 8, 16,
  4,
  8, 16, 8, 16, 8, 16, 8, 4, 8,
  4,

  8, 16, 8, 16, 8, 16, 8, 16,
  8, 16, 8, 8, 16, 8, 8, 16,
  4,
  8, 16, 8, 16, 8, 16, 8, 4, 8,
  1
};

int spinMelody[] = {
  NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4,
  NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_C5,

  NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_A4, NOTE_A4, REST,

  NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4,
  NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_C5,

  NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_A4, NOTE_A4, REST,

  NOTE_E5, NOTE_C5,
  NOTE_D5, NOTE_B4,
  NOTE_C5, NOTE_A4,
  NOTE_GS4, NOTE_B4, REST,
  NOTE_E5, NOTE_C5,
  NOTE_D5, NOTE_B4,
  NOTE_C5, NOTE_E5, NOTE_A5,
  NOTE_GS5
};

int spinDurations[] = {
  4, 8, 8, 4, 8, 8,
  4, 8, 8, 4, 8, 8,
  4, 8, 4, 4,
  4, 4, 8, 4, 8, 8,

  4, 8, 4, 8, 8,
  4, 8, 4, 8, 8,
  4, 8, 8, 4, 4,
  4, 4, 4, 4,

  4, 8, 8, 4, 8, 8,
  4, 8, 8, 4, 8, 8,
  4, 8, 4, 4,
  4, 4, 8, 4, 8, 8,

  4, 8, 4, 8, 8,
  4, 8, 4, 8, 8,
  4, 8, 8, 4, 4,
  4, 4, 4, 4,

  2, 2,
  2, 2,
  2, 2,
  2, 4, 8,
  2, 2,
  2, 2,
  4, 4, 2,
  2
};

// Non-blocking state for buzzer
int currentNote = 0;
unsigned long noteTimer = 0;
int noteDuration = 0;
bool waitingForNote = false;
bool playingCoinSong = false;
bool playingSpinSong = false;

// Non-blocking state for dispenser
int coinsToDispense = 0;
int dispenseStep = 0; // 0=idle, 1=open_step, 2=wait_fall, 3=close_step, 4=wait_next
unsigned long dispenseTimer = 0;
int servoCurrentAngle = 0;
#define SERVO_STEP_DELAY 15
#define SERVO_ANGLE_STEP 3

#define LDR_THRESHOLD 50
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
unsigned long joyDebounceTimer = 0;
#define JOY_COOLDOWN_MS 300

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

int breathR = 255;
int breathG = 0;
int breathB = 255;
bool spinning = false;
int spinPhase = 0;

unsigned long neoPrev = 0;
unsigned int neoHue = 0;

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

void runSteppers() {
  if (!spinning) return;

  stepperX.run();
  stepperY.run();
  stepperZ.run();

  if (spinPhase == 4 && stepperX.distanceToGo() == 0 && stepperY.distanceToGo() == 0 && stepperZ.distanceToGo() == 0) {
    spinning = false;
    playingSpinSong = false;
    spinPhase = 0;
    coinDropped = false;

    int xSym = getSymbol(stepperX.currentPosition());
    int ySym = getSymbol(stepperY.currentPosition());
    int zSym = getSymbol(stepperZ.currentPosition());
    Serial.print("Symbols: ");
    Serial.print(SYMBOL_NAMES[xSym]);
    Serial.print(" ");
    Serial.print(SYMBOL_NAMES[ySym]);
    Serial.print(" ");
    Serial.println(SYMBOL_NAMES[zSym]);

    if (xSym == ySym && ySym == zSym && dispenseStep == 0) {
      coinsToDispense = 3;
      dispenseStep = 1;
      dispenseTimer = millis();
    }

    rainbowMode = true;
    rainbowTimer = millis();
  }
}

void neoRainbow() {
  for (int i = 0; i < NUM_LEDS; i++) {
    int hue = (neoHue + i * 45) % 360;
    byte r, g, b;
    hsvToRgb(hue, r, g, b);
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
}

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  coinServo.attach(servoPin);
  coinServo.write(0);
  servoCurrentAngle = 0;

  coinsToDispense = 0;
  dispenseStep = 0;

  strip.begin();
  strip.show();

  stepperX.setMaxSpeed(100.0);
  stepperX.setAcceleration(100.0);

  stepperY.setMaxSpeed(100.0);
  stepperY.setAcceleration(100.0);

  stepperZ.setMaxSpeed(100.0);
  stepperZ.setAcceleration(100.0);
}

void loop()
{
  int size = sizeof(durations) / sizeof(int);

  // --- LED (non-blocking) ---
  if (spinning) {
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

  // --- Stepper motors (non-blocking) ---
  runSteppers();

  // --- IR Remote (non-blocking) ---
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.decodedRawData == IR_PLAY_BUTTON && !coinDropped) {
      coinDropped = true;
      playingCoinSong = true;
      currentNote = 0;
      waitingForNote = false;
      breathR = 0;
      breathG = 255;
      breathB = 0;
      greenFadeLevel = 0;
      greenFadeRising = true;
      greenFadeTimer = millis();
      if (rainbowMode) {
        rainbowMode = false;
        greenFadeLevel = 0;
        greenFadeRising = true;
        greenFadeTimer = millis();
      }
    }
    if (dispenseStep == 0) {
      int cmd = IrReceiver.decodedIRData.command;
      int coins = 0;
      if (cmd == 12) coins = 1;
      else if (cmd == 24) coins = 2;
      else if (cmd == 94) coins = 3;
      else if (cmd == 8) coins = 4;
      else if (cmd == 28) coins = 5;
      else if (cmd == 90) coins = 6;
      else if (cmd == 66) coins = 7;
      else if (cmd == 82) coins = 8;
      else if (cmd == 74) coins = 9;
      if (coins > 0) {
        coinsToDispense = coins;
        dispenseStep = 1;
        dispenseTimer = millis();
      }
    }
    IrReceiver.resume();
  }

  // --- NeoPixel Rainbow (non-blocking) ---
  if (millis() - neoPrev >= 30) {
    neoPrev = millis();
    neoRainbow();
    neoHue = (neoHue + 5) % 360;
  }

  // --- Buzzer (non-blocking) ---
  if (playingCoinSong) {
    int coinSize = sizeof(coinDurations) / sizeof(int);
    if (!waitingForNote) {
      noTone(BUZZER_PIN);
      noteDuration = 1000 / coinDurations[currentNote];
      if (coinMelody[currentNote] != REST) tone(BUZZER_PIN, coinMelody[currentNote], noteDuration);
      noteTimer = millis();
      waitingForNote = true;
    } else {
      int pause = noteDuration * 1.10;
      if (millis() - noteTimer >= pause) {
        currentNote = (currentNote + 1) % coinSize;
        noTone(BUZZER_PIN);
        waitingForNote = false;
      }
    }
  } else if (playingSpinSong) {
    int spinSize = sizeof(spinDurations) / sizeof(int);
    if (!waitingForNote) {
      noTone(BUZZER_PIN);
      noteDuration = 1000 / spinDurations[currentNote];
      if (spinMelody[currentNote] != REST) tone(BUZZER_PIN, spinMelody[currentNote], noteDuration);
      noteTimer = millis();
      waitingForNote = true;
    } else {
      int pause = noteDuration * 1.10;
      if (millis() - noteTimer >= pause) {
        currentNote = (currentNote + 1) % spinSize;
        noTone(BUZZER_PIN);
        waitingForNote = false;
      }
    }
  } else if (rainbowMode) {
    if (!waitingForNote) {
      noTone(BUZZER_PIN);
      noteDuration = 1000 / durations[currentNote];
      tone(BUZZER_PIN, melody[currentNote], noteDuration);
      noteTimer = millis();
      waitingForNote = true;
    } else {
      int pause = noteDuration * 1.10;
      if (millis() - noteTimer >= pause) {
        currentNote = (currentNote + 1) % size;
        noTone(BUZZER_PIN);
        waitingForNote = false;
      }
    }
  }

  // --- Button (non-blocking, debounced) ---
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
    lastButtonState = reading;
  }
  if (millis() - lastDebounceTime >= debounceDelay) {
    if (lastButtonState == LOW && buttonState == HIGH) {
    }
    buttonState = lastButtonState;
  }

  // --- LDR (non-blocking, every 10ms) ---
  if (millis() - ldrTimer >= 10) {
    ldrTimer = millis();

    if (ldrCooldown && millis() - ldrDebounceTimer >= LDR_COOLDOWN_MS) {
      ldrCooldown = false;
    }

    bool calibrating = (millis() < 10000);

    if (calibrating) {
      prevLdrValue = analogRead(LDR_PIN);
    } else if (!ldrCooldown && !coinDropped) {
      int ldrValue = analogRead(LDR_PIN);
      int diff = ldrValue - prevLdrValue;
      if (diff < 0 && abs(diff) > LDR_THRESHOLD) {
        tone(BUZZER_PIN, 1000, 50);
        prevLdrValue = ldrValue;
        ldrCooldown = true;
        ldrDebounceTimer = millis();
        coinDropped = true;

        playingCoinSong = true;
        currentNote = 0;
        waitingForNote = false;
        breathR = 0;
        breathG = 255;
        breathB = 0;
        greenFadeLevel = 0;
        greenFadeRising = true;
        greenFadeTimer = millis();

        if (rainbowMode) {
          rainbowMode = false;
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
    if (abs(diff) > 3) {
      prevJoyY = joyY;
      if (diff < 0 && abs(diff) > JOY_THRESHOLD && millis() - joyDebounceTimer >= JOY_COOLDOWN_MS) {
        joyDebounceTimer = millis();
        ldrCooldown = true;
        ldrDebounceTimer = millis();
        if (spinning && spinPhase >= 1 && spinPhase <= 3) {
          if (spinPhase == 1) {
            stepperX.moveTo(((stepperX.currentPosition() / 20) + 1) * 20);
            spinPhase = 2;
          } else if (spinPhase == 2) {
            stepperY.moveTo(((stepperY.currentPosition() / 20) + 1) * 20);
            spinPhase = 3;
          } else if (spinPhase == 3) {
            long pos = stepperZ.currentPosition();
            long target = ((pos / 20) + 1) * 20;
            while (target - pos < 80) target += 20;
            stepperZ.moveTo(target);
            spinPhase = 4;
          }
        } else if (coinDropped) {
          playingCoinSong = false;
          playingSpinSong = true;
          currentNote = 0;
          waitingForNote = false;
          spinning = true;
          spinPhase = 1;
          stepperX.moveTo(stepperX.currentPosition() + SPIN_TARGET);
          stepperY.moveTo(stepperY.currentPosition() + SPIN_TARGET);
          stepperZ.moveTo(stepperZ.currentPosition() + SPIN_TARGET);
          breathR = 255;
          breathG = 0;
          breathB = 0;
          greenFadeLevel = 0;
          greenFadeRising = true;
          greenFadeTimer = millis();
        } else {
          if (!rainbowMode) {
            breathR = 0;
            breathG = 255;
            breathB = 255;
          }
        }
      }
    }
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
        if (millis() - dispenseTimer >= 1500) {
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
        if (millis() - dispenseTimer >= 2000) {
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
