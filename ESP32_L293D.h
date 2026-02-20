#ifndef ESP32_L293D_H
#define ESP32_L293D_H

#include <Arduino.h>

// Define standard motor commands
#define FORWARD 1
#define BACKWARD 2
#define RELEASE 3

class ESP32_MotorShield {
  private:
    // Pin definitions
    uint8_t _clk, _en, _data, _latch;
    uint8_t _pwmPins[4];
    
    // Tracks the current 8-bit state of the shift register
    uint8_t _latch_state; 
    
    // Helper to send data to the shield
    void updateShiftRegister();

  public:
    // Constructor: tell the library which pins you wired up
    ESP32_MotorShield(uint8_t clk, uint8_t en, uint8_t data, uint8_t latch, 
                      uint8_t pwm1, uint8_t pwm2, uint8_t pwm3, uint8_t pwm4);
    
    // Setup function to initialize pins
    void begin();
    
    // Control functions
    void setSpeed(uint8_t motorNum, uint8_t speed);
    void run(uint8_t motorNum, uint8_t command);
};

#endif