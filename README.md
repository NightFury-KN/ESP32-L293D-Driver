# ESP32 L293D Motor Shield Driver

A lightweight, bare-metal C++ library to drive the classic Arduino Uno L293D Motor Shield (v1) using an ESP32. 

The standard `AFMotor` library relies on AVR hardware timers and does not compile on the ESP32's Xtensa architecture. Furthermore, the shield is designed for a 5V logic Uno form factor. This library bypasses those limitations by directly controlling the shield's onboard 74HC595 shift register and utilizing the ESP32's native PWM capabilities.

## Features
* Controls up to 4 DC Motors independently (Forward, Backward, Release).
* Independent speed control via 8-bit PWM (0-255).
* Direct shift register manipulation for fast execution.
* Easily customizable GPIO pin mapping.

## Hardware Setup & Pin Mapping

Because the ESP32 cannot physically mount the shield, you must wire it manually. 

**CRITICAL HARDWARE NOTES:**
1. **Remove the `PWR` Jumper** on the shield to isolate the logic circuit from the motor power supply.
2. **Logic Power:** Provide 5V from the ESP32's `VIN` pin to the Shield's `5V` pin. (The 74HC595 shift register needs 5V, not 3.3V).
3. **Common Ground:** Ensure the ESP32 `GND`, Shield `GND`, and the motor power supply `GND` are all connected.

### ESP32 to Shield Wiring Table

| Shield Label | Function | ESP32 GPIO |
| :--- | :--- | :--- |
| **4** | Shift Clock | GPIO 16 |
| **7** | Shift Enable | GPIO 17 |
| **8** | Shift Data | GPIO 5 |
| **12** | Shift Latch | GPIO 18 |
| **11** | Motor 1 Speed (PWM) | GPIO 32 |
| **3** | Motor 2 Speed (PWM) | GPIO 33 |
| **6** | Motor 3 Speed (PWM) | GPIO 25 |
| **5** | Motor 4 Speed (PWM) | GPIO 26 |

## Installation

1. Download or clone this repository.
2. Place the `ESP32-L293D-Driver` folder inside your Arduino `libraries` directory (e.g., `~/Arduino/libraries/`).
3. Restart your IDE.

## Quick Start Example

```cpp
#include <ESP32_L293D.h>

// Format: (CLK, EN, DATA, LATCH, M1_PWM, M2_PWM, M3_PWM, M4_PWM)
ESP32_MotorShield shield(16, 17, 5, 18, 32, 33, 25, 26);

void setup() {
  shield.begin();
  
  // Set speed for Motor 1 to maximum (0-255)
  shield.setSpeed(1, 255);
}

void loop() {
  // Drive Motor 1 Forward
  shield.run(1, FORWARD);
  delay(2000);

  // Stop Motor 1
  shield.run(1, RELEASE);
  delay(2000);
}

## API Reference

### `ESP32_MotorShield(clk, en, data, latch, pwm1, pwm2, pwm3, pwm4)`
**Constructor:** Initializes the library with your custom GPIO pin mapping. 
* `clk`, `en`, `data`, `latch`: ESP32 pins connected to the 74HC595 shift register.
* `pwm1` - `pwm4`: ESP32 pins connected to the L293D Enable (Speed) pins.

### `void begin()`
**Initialization:** Configures all defined pins as `OUTPUT`, initializes the ESP32's native PWM channels, and sets all motor states to `RELEASE`. Call this once in `setup()`.

### `void setSpeed(uint8_t motorNum, uint8_t speed)`
**Speed Control:** Adjusts the PWM duty cycle for a specific motor.
* `motorNum`: Integer `1`, `2`, `3`, or `4`.
* `speed`: 8-bit integer from `0` (stopped) to `255` (maximum voltage).

### `void run(uint8_t motorNum, uint8_t command)`
**Direction Control:** Updates the shift register to change the H-bridge polarity.
* `motorNum`: Integer `1`, `2`, `3`, or `4`.
* `command`: Use predefined constants `FORWARD`, `BACKWARD`, or `RELEASE`.