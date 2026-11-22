#include <Arduino.h>
#include <stdlib.h>

constexpr int RED_PIN = 16;
constexpr int GREEN_PIN = 17;
constexpr int BLUE_PIN = 18;

void setup() {
  Serial.begin(115200);
  analogWrite(RED_PIN, 0);
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN, 0);
  Serial.println("Enter R G B (0-255), for example: 255 0 0");
}

bool parseRgb(const char *input, int (&rgb)[3]) {
  for (int i = 0; i < 3; i++) {
    if (i > 0 && *input != ' ' && *input != '\t') {
      return false;
    }

    char *end;
    long value = strtol(input, &end, 10);
    if (end == input || value < 0 || value > 255) {
      return false;
    }

    rgb[i] = static_cast<int>(value);
    input = end;
  }

  while (*input == ' ' || *input == '\t') {
    input++;
  }
  return *input == '\0';
}

void loop() {
  static char line[48];
  static size_t length = 0;
  static bool tooLong = false;

  while (Serial.available() > 0) {
    char character = static_cast<char>(Serial.read());

    if (character == '\r') {
      continue;
    }

    if (character == '\n') {
      line[length] = '\0';
      int rgb[3];

      if (!tooLong && parseRgb(line, rgb)) {
        analogWrite(RED_PIN, rgb[0]);
        analogWrite(GREEN_PIN, rgb[1]);
        analogWrite(BLUE_PIN, rgb[2]);
        Serial.printf("Applied: %d %d %d\n", rgb[0], rgb[1], rgb[2]);
      } else {
        Serial.println("Error: enter three integers from 0 to 255.");
      }

      length = 0;
      tooLong = false;
    } else if (length < sizeof(line) - 1) {
      line[length++] = character;
    } else {
      tooLong = true;
    }
  }
}