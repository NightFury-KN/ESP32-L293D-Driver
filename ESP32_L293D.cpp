#include "ESP32_L293D.h"

// The shield's internal wiring map for the 74HC595 shift register
// Format: { Motor1_A, Motor1_B, Motor2_A, Motor2_B, Motor3_A, Motor3_B, Motor4_A, Motor4_B }
const uint8_t motor_bits[8] = {2, 3, 1, 4, 5, 7, 0, 6};

ESP32_MotorShield::ESP32_MotorShield(uint8_t clk, uint8_t en, uint8_t data, uint8_t latch, 
                                     uint8_t pwm1, uint8_t pwm2, uint8_t pwm3, uint8_t pwm4) {
  _clk = clk;
  _en = en;
  _data = data;
  _latch = latch;
  _pwmPins[0] = pwm1;
  _pwmPins[1] = pwm2;
  _pwmPins[2] = pwm3;
  _pwmPins[3] = pwm4;
  _latch_state = 0; // All motors off by default
}

void ESP32_MotorShield::begin() {
  pinMode(_clk, OUTPUT);
  pinMode(_en, OUTPUT);
  pinMode(_data, OUTPUT);
  pinMode(_latch, OUTPUT);

  // Set all PWM pins as outputs
  for(int i = 0; i < 4; i++) {
    pinMode(_pwmPins[i], OUTPUT);
    analogWrite(_pwmPins[i], 0); 
  }

  // Enable shift register and clear it
  digitalWrite(_en, LOW);
  updateShiftRegister();
}

void ESP32_MotorShield::updateShiftRegister() {
  digitalWrite(_latch, LOW);
  shiftOut(_data, _clk, MSBFIRST, _latch_state);
  digitalWrite(_latch, HIGH);
}

void ESP32_MotorShield::setSpeed(uint8_t motorNum, uint8_t speed) {
  if (motorNum >= 1 && motorNum <= 4) {
    analogWrite(_pwmPins[motorNum - 1], speed);
  }
}

void ESP32_MotorShield::run(uint8_t motorNum, uint8_t command) {
  if (motorNum < 1 || motorNum > 4) return;
  
  uint8_t a_bit = motor_bits[(motorNum - 1) * 2];
  uint8_t b_bit = motor_bits[(motorNum - 1) * 2 + 1];

  if (command == FORWARD) {
    _latch_state |= (1 << a_bit);   // Set A bit HIGH
    _latch_state &= ~(1 << b_bit);  // Set B bit LOW
  } 
  else if (command == BACKWARD) {
    _latch_state &= ~(1 << a_bit);  // Set A bit LOW
    _latch_state |= (1 << b_bit);   // Set B bit HIGH
  } 
  else if (command == RELEASE) {
    _latch_state &= ~(1 << a_bit);  // Set A bit LOW
    _latch_state &= ~(1 << b_bit);  // Set B bit LOW
  }
  
  updateShiftRegister();
}