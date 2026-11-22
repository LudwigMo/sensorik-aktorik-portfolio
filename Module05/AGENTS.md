# Module 5 Project Instructions

- Use PlatformIO with the Arduino framework. The black USB-C ESP32 uses `board = esp32doit-devkit-v1`.
- Task 1 uses GPIO16 (`RX2`) for PWM and a 220 Ω series resistor.
- Task 2 uses a common-cathode RGB module. Red, green, and blue use GPIO16, GPIO17, and GPIO18 respectively.
- Task 3 uses GPIO16 for NeoPixel data, eight pixels, and an output limit of 80/255 per colour channel.
- Use 115200 baud and newline-terminated serial commands for Tasks 2 and 3.
- Keep code under `codes/` and link to evidence under `pictures/` from the module README. Exclude `.pio/` build output from commits..
