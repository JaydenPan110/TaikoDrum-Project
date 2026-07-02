Project Name

Slot Machine

Description of Functionality

This is an interactive slot machine with three wheels. Each wheel has 10 different symbols, and if the wheels show the same symbol, the user gets a jackpot. The user inserts a coin to activate the system, then switches the joystick down to spin the physical reels. Each time after the user presses the joystick down, it stops each motor until each motor has stopped. Each motor self-adjusts to display a specific symbol to the user. If the user hits a jackpot, a specialized dispensing mechanism triggers a payout to reward the user.

Component List


Nema 17 Stepper Motors x3

M2.5 Screws and Nuts x12

Arduino UNOs x2 

3D Prints

RGB LED x1

Photoresistor x1

Servo Motor x1

12V 5A AC to DC converter x1

Jumper Wires M/M

Passive Buzzer x1

USB Cable x1

Resistors 10kΩ 

Jumper Wires M/F

Resistors 220Ω

Resistors 1kΩ

CNC Shield x1

Joystick x1

IR Remote x1

IR Receiver x1

Freenove 8 RGB LED Ring x1




**History of changes from the initial proposal and early drafts
**
In our original design, we planned for an activated button: when the user inserts a valid 25-cent coin into the coin slot, the machine plays a beep indicating that the coin has been accepted, and the user can press the button to activate it. 

The change we will make as a result of this decision will be to replace the LED where the button was with a joystick. We will detect the joystick's x and y positions and, if it's pulled up or down, the reels will spin.

Another change we made from the original proposal is the usage of the photo resistor. Previously, we used an LED that a coin would block when inserted into the slot. 

Instead, we realized that the photoresistor actually worked on contact with the coin, so we ditched the LED design and just made the photoresistor interact with the coin, and made the buzzer beep every time it detected it for testing and user purposes

Additionally, we also changed our housing design entirely.  Due to printing complications and time constraints. We had to redesign our housing using cardboard, and we’ve reached an issue of durability because it may not hold the step motors. We instead used wood to hold up the step motors and that has worked successfully






