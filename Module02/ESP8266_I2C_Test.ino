#include <Wire.h>

void setup() {
  Serial.begin(115200);

  // ESP8266 D1 mini
  // SDA = D2 (GPIO4)
  // SCL = D1 (GPIO5)
  Wire.begin(D2, D1);

  // I2C clock: 10 kHz
  Wire.setClock(10000);
}

void loop() {
  Wire.beginTransmission(0x29);

  byte result = Wire.endTransmission();

  if (result == 0) {
    Serial.println("ACK");
  } else {
    Serial.println("NACK");
  }

  delay(10);
}
