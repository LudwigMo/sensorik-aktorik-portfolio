
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);
  Wire.setClock(100000);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  Serial.println("I2C Scanner started");

  lcd.setCursor(0, 0);
  lcd.print("I2C Scanner");
}

void loop() {
  byte count = 0;
  byte firstAddress = 0;

  Serial.println("Scanning...");

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Found device: 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);

      if (count == 0) {
        firstAddress = address;
      }
      count++;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("I2C Devices: ");
  lcd.print(count);

  lcd.setCursor(0, 1);

  if (count > 0) {
    lcd.print("Address: 0x");
    if (firstAddress < 16) lcd.print("0");
    lcd.print(firstAddress, HEX);
  } else {
    lcd.print("No device found");
  }

  if (count == 0) {
    Serial.println("No I2C devices found");
  }

  Serial.println("----------------");
  delay(2000);
}
