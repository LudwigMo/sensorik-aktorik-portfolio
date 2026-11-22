#include <Arduino.h>
#include <NeoPixelBus.h>
#include <cstdlib>
#include <cstring>

constexpr int DATA_PIN = 16;
constexpr int PIXEL_COUNT = 8;
constexpr int MAX_CHANNEL_OUTPUT = 80;

NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod>
    strip(PIXEL_COUNT, DATA_PIN);

bool readNumber(char *token, int maximum, int &result) {
  if (token == nullptr) {
    return false;
  }

  char *end;
  long value = std::strtol(token, &end, 10);
  if (end == token || *end != '\0' || value < 0 || value > maximum) {
    return false;
  }

  result = static_cast<int>(value);
  return true;
}

void handleCommand(char *line) {
  constexpr char separators[] = " \t";
  char *first = std::strtok(line, separators);
  if (first == nullptr) {
    return;
  }

  if (std::strcmp(first, "clear") == 0 &&
      std::strtok(nullptr, separators) == nullptr) {
    strip.ClearTo(RgbColor(0, 0, 0));
    strip.Show();
    Serial.println("Cleared");
    return;
  }

  int index, red, green, blue;
  if (!readNumber(first, PIXEL_COUNT - 1, index) ||
      !readNumber(std::strtok(nullptr, separators), 255, red) ||
      !readNumber(std::strtok(nullptr, separators), 255, green) ||
      !readNumber(std::strtok(nullptr, separators), 255, blue) ||
      std::strtok(nullptr, separators) != nullptr) {
    Serial.println("Error: enter index (0-7) and R G B (0-255), or clear.");
    return;
  }

  strip.SetPixelColor(index, RgbColor(
      red * MAX_CHANNEL_OUTPUT / 255,
      green * MAX_CHANNEL_OUTPUT / 255,
      blue * MAX_CHANNEL_OUTPUT / 255));
  strip.Show();
  Serial.printf("Applied: %d %d %d %d\n", index, red, green, blue);
}

void setup() {
  Serial.begin(115200);
  strip.Begin();
  strip.ClearTo(RgbColor(0, 0, 0));
  strip.Show();
  Serial.println("Enter index R G B, or clear.");
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
      if (tooLong) {
        Serial.println("Error: command too long.");
      } else {
        line[length] = '\0';
        handleCommand(line);
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