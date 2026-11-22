#include <Arduino.h>

constexpr int LED_PIN = 16;

void setup() {
  Serial.begin(115200);
  Serial.println("Task 1: PWM fade on GPIO 16");
}

void loop() {
  for (int duty = 0; duty <= 255; duty++) {
    analogWrite(LED_PIN, duty);
    delay(8);
  }

  for (int duty = 255; duty >= 0; duty--) {
    analogWrite(LED_PIN, duty);
    delay(8);
  }
}