
#include <Wire.h>

const uint8_t SE95_ADDR = 0x4F;
const uint8_t TEMP_REG = 0x00;

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);
  Wire.setClock(100000);
  Serial.println("SE95 Temperature Register Test");
}

void loop() {
  Wire.beginTransmission(SE95_ADDR);
  Wire.write(TEMP_REG);

  if (Wire.endTransmission(false) != 0) {
    Serial.println("Register selection failed");
    delay(1000);
    return;
  }

  if (Wire.requestFrom(SE95_ADDR, (uint8_t)2) != 2) {
    Serial.println("Temperature read failed");
    delay(1000);
    return;
  }

  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();

  int16_t raw = (int16_t)(
    ((uint16_t)msb << 8) | lsb
  );

  raw >>= 3;  // 13-bit signed temperature
  float temperature = raw * 0.03125f;

  Serial.print("Raw value: ");
  Serial.println(raw);

  Serial.print("Temperature: ");
  Serial.print(temperature, 3);
  Serial.println(" C");

  Serial.println("----------------");
  delay(1000);
}
