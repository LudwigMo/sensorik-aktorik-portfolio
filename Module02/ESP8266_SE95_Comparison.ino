#include <Wire.h>
#include <M2M_LM75A.h>

const uint8_t SE95_ADDR = 0x4F;
const uint8_t TEMP_REG = 0x00;

M2M_LM75A sensor(SE95_ADDR);

void setup() {
  Serial.begin(115200);

  Wire.begin(D2, D1);
  Wire.setClock(100000);

  // Do not call sensor.begin():
  // Wire has already been initialized with our ESP8266 pins.

  Serial.println("Task 6: Library vs Register");
}

void loop() {
  // Method 1: Read using the library
  float libraryTemp = sensor.getTemperature();

  // Method 2: Read the register directly
  Wire.beginTransmission(SE95_ADDR);
  Wire.write(TEMP_REG);

  if (Wire.endTransmission(false) != 0) {
    Serial.println("Register selection failed");
    delay(1000);
    return;
  }

  if (Wire.requestFrom(SE95_ADDR, (uint8_t)2) != 2) {
    Serial.println("Register read failed");
    delay(1000);
    return;
  }

  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();

  int16_t raw = (int16_t)(
    ((uint16_t)msb << 8) | lsb
  );

  raw >>= 3;
  float registerTemp = raw * 0.03125f;

  if (libraryTemp == LM75A_INVALID_TEMPERATURE) {
    Serial.println("Library read failed");
  } else {
    Serial.print("Library:  ");
    Serial.print(libraryTemp, 3);
    Serial.println(" C");

    Serial.print("Register: ");
    Serial.print(registerTemp, 3);
    Serial.println(" C");

    Serial.print("Difference: ");
    Serial.print(abs(libraryTemp - registerTemp), 3);
    Serial.println(" C");
  }

  Serial.print("Raw value: ");
  Serial.println(raw);

  Serial.println("----------------------");
  delay(1000);
}
