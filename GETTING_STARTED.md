👶 Beginner's Guide: ESP32 + L293D Motor Shield

Welcome! If you are trying to connect a standard Arduino L293D Motor Shield to an ESP32, you've probably realized they don't physically fit together, and the standard Arduino codes don't work.

Don't worry! This guide will walk you through exactly how to wire them up using jumper cables and get your first motor spinning in about 10 minutes.
⚠️ Phase 1: The Three Golden Rules

Before we plug anything in, you must follow these rules, or you will permanently damage your ESP32.

    Remove the Jumper: Look at your L293D shield. Next to the blue power terminals, there is a small plastic pin called PWR (or PWR_JMP). Pull it off and throw it away. This separates the motor power from the delicate ESP32 logic.

    Common Ground: Your ESP32 and your Motor battery must share a Ground connection.

    External Power: The ESP32 cannot power motors. You must use a separate battery (like a 9V, or a 2S LiPo) connected to the shield's blue EXT_PWR terminals.

🔌 Phase 2: Wiring it Up

Grab your female-to-male jumper wires. We need to connect 8 specific pins from the ESP32 to the pins on the shield.
Power Connections

    ESP32 VIN (or 5V) ➡️ Connect to the Shield's 5V pin.

    ESP32 GND ➡️ Connect to the Shield's GND pin.

The Brain Connections (Shift Register)

    ESP32 GPIO 16 ➡️ Shield Pin 4 * ESP32 GPIO 17 ➡️ Shield Pin 7 * ESP32 GPIO 5 ➡️ Shield Pin 8 * ESP32 GPIO 18 ➡️ Shield Pin 12 ### The Speed Connections (PWM)

    ESP32 GPIO 32 ➡️ Shield Pin 11 (Controls Motor 1)

    ESP32 GPIO 33 ➡️ Shield Pin 3 (Controls Motor 2)

    ESP32 GPIO 25 ➡️ Shield Pin 6 (Controls Motor 3)

    ESP32 GPIO 26 ➡️ Shield Pin 5 (Controls Motor 4)

Finally, screw a small DC motor into the M1 terminal block on the shield.
💻 Phase 3: Installing the Library

Since the standard libraries don't work, we will use this custom library.

    Download this repository as a .ZIP file (Click the green Code button at the top of GitHub -> Download ZIP).

    Open your Arduino IDE.

    Go to Sketch ➡️ Include Library ➡️ Add .ZIP Library...

    Select the file you just downloaded.

🚀 Phase 4: The "Hello World" Code

Let's make that motor spin! Open a new sketch in the Arduino IDE, delete everything, and paste this code:
C++

```cpp
#include <ESP32_L293D.h>

// This line tells the library exactly how we wired things up in Phase 2
ESP32_MotorShield myRobot(16, 17, 5, 18, 32, 33, 25, 26);

void setup() {
  // Wake up the shield
  myRobot.begin();
  
  // Set the speed for Motor 1 (0 is off, 255 is maximum speed)
  myRobot.setSpeed(1, 200); 
}

void loop() {
  // 1. Spin Forward
  myRobot.run(1, FORWARD);
  delay(2000); // Wait 2 seconds

  // 2. Stop
  myRobot.run(1, RELEASE);
  delay(1000); // Wait 1 second

  // 3. Spin Backward
  myRobot.run(1, BACKWARD);
  delay(2000); // Wait 2 seconds

  // 4. Stop again
  myRobot.run(1, RELEASE);
  delay(3000); // Wait 3 seconds before repeating
}
```
Upload the code to your ESP32, plug in your external motor battery, and watch it spin!