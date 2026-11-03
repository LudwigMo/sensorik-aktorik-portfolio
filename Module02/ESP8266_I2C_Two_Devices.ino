
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const uint8_t SE95_ADDR = 0x4F;
const uint8_t TEMP_REG = 0x00;

// LCD1602 at I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  // Shared I2C bus
  // SDA = D2, SCL = D1
  Wire.begin(D2, D1);
  Wire.setClock(100000);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("I2C Two Devices");

  Serial.println("Task 7: Two Devices on One Bus");
  Serial.println("LCD: 0x27, SE95: 0x4F");
}

void loop() {
  // Select SE95 temperature register
  Wire.beginTransmission(SE95_ADDR);
  Wire.write(TEMP_REG);

  if (Wire.endTransmission(false) != 0) {
    Serial.println("SE95 register selection failed");
    lcd.setCursor(0, 1);
    lcd.print("Sensor error    ");
    delay(1000);
    return;
  }

  // Read two temperature bytes
  if (Wire.requestFrom(SE95_ADDR, (uint8_t)2) != 2) {
    Serial.println("SE95 read failed");
    lcd.setCursor(0, 1);
    lcd.print("Read error      ");
    delay(1000);
    return;
  }

  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();

  // Reconstruct signed 13-bit temperature
  int16_t raw = (int16_t)(((uint16_t)msb << 8) | lsb);
  raw >>= 3;

  float temperature = raw * 0.03125f;

  // Serial Monitor output
  Serial.print("SE95 Temperature: ");
  Serial.print(temperature, 3);
  Serial.println(" C");

  // LCD1602 output
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature, 2);
  lcd.print(" C    ");

  delay(1000);
}

