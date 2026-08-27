# Arduino Slot Machine

<img width="3024" height="4032" alt="616CD408-CAEE-421D-8965-62FF21B37599_L0_001-2026-06-23, 9_50_43 AM" src="https://github.com/user-attachments/assets/3e833674-b9db-427c-a31f-230c314062d2" />


An interactive, hardware-driven slot machine featuring three physical reels, automated coin detection, a joystick lever mechanism, and a custom payout dispenser. 

---

## Project Overview

This project is a physical, interactive slot machine powered by dual Arduino microcontrollers. The system replicates a classic casino game loop using automated mechanical and electronic components:

1. **Coin Insertion:** The user inserts a coin into the slot to arm the machine.
2. **The Spin:** Pulling the joystick down triggers three independent reels to spin. 
3. **The Stop:** Each motor sequentially self-adjusts to display a specific symbol to the user.
4. **The Payout:** If all three wheels align on the same symbol, a jackpot is triggered, activating a specialized servo-driven dispensing mechanism for a physical payout.

---

## Component List

| Category | Item | Quantity |
| :--- | :--- | :--- |
| **Microcontrollers & Shields** | Arduino UNO | 2 |
| | CNC Shield | 1 |
| **Actuators & Motors** | Nema 17 Stepper Motor | 3 |
| | Servo Motor | 1 |
| **Sensors & Inputs** | Analog Joystick | 1 |
| | Photoresistor (LDR) | 1 |
| | Infrared (IR) Receiver | 1 |
| | Infrared (IR) Remote | 1 |
| **Display & Audio** | Freenove 8 RGB LED Ring | 1 |
| | RGB LED | 1 |
| | Passive Buzzer | 1 |
| **Power & Cabling** | 12V 5A AC to DC Power Converter | 1 |
| | USB Cable | 1 |
| | Jumper Wires (M/M & M/F) | Assortment |
| **Discrete Components** | Resistors (220Ω, 1kΩ, 10kΩ) | Various |
| **Hardware & Enclosure** | 3D Printed Components (Reels/Gears) | Custom |
| | M2.5 Screws and Nuts | 12 |
| | Wood Support Brackets & Housing | Custom |

## Schematic Pictures ( might be a bit outdated ) 

<img width="1919" height="1079" alt="Screenshot 2026-06-17 191529" src="https://github.com/user-attachments/assets/ae5775c6-0e2c-4cef-bafe-2a77cb37c89e" />
<img width="1620" height="883" alt="Screenshot 2026-06-17 191602" src="https://github.com/user-attachments/assets/fbe489da-55d2-48c3-8d0b-07a2e9baaac3" />


## Project Evolution & Changelog

The design of this slot machine evolved significantly during prototyping to adapt to structural requirements and improve user experience:

### Input Mechanism: From Push-Button to Joystick
* **Original Plan:** A simple arcade button to trigger the spin sequence after coin validation.
* **Revision:** Replaced the button and its status LED with an analog joystick. Pulling the joystick down provides a more tactile, satisfying "slot machine lever" feel.

### Coin Detection: From Optical Interruption to Contact Sensing
* **Original Plan:** A break-beam sensor configuration where a falling coin temporarily blocked an LED shining on a detector.
* **Revision:** Simplified to a direct-contact photoresistor setup inside the coin chute. Integrated a passive buzzer audio cue to sound a confirmation tone immediately upon reliable detection.

### Enclosure Design: From Cardboard to Reinforced Wood
* **Original Plan:** A fully 3D-printed enclosure or light cardboard housing.
* **Revision:** 3D printing the entire structural shell proved too time-consuming, while cardboard lacked the structural integrity to support the torque and weight of three Nema 17 stepper motors. The structural framing was redesigned using wood, successfully neutralizing motor vibrations and improving overall system durability.



credit to [WhiteStudio](https://makerworld.com/en/models/1272917-nanoslot-modular-arduino-based-slot-machine-w-rtp?from=search#profileId-1300082) for CAD models
