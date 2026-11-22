# Module 5 – LEDs and Light as Output

In this module, we used an ESP32 to dim a single LED with PWM, mix colours on an RGB LED, and control eight addressable NeoPixel LEDs.

We documented our work in Tasks 1, 2, and 3 to demonstrate LED current limiting, PWM dimming, additive colour mixing, individual pixel control, and power budgeting.

## Learning Goals

### LG1 – LED Current Limiting

Explain why LEDs require current-limiting resistors and calculate LED current from the voltage drop across a resistor.

**Evidence:** [Task 1](#task-1-pwm-fade) · [Task 2](#task-2-rgb-led)

### LG2 – PWM Dimming

Use pulse-width modulation to adjust LED brightness and explain how duty cycle affects the perceived brightness.

**Evidence:** [Task 1](#task-1-pwm-fade)

### LG3 – Additive Colour Mixing

Control the red, green, and blue channels of an RGB LED independently and combine them to produce other colours.

**Evidence:** [Task 2](#task-2-rgb-led)

### LG4 – Reproducible PlatformIO Projects

Configure PlatformIO projects for the ESP32 and verify the programs on physical hardware.

**Evidence:** [Task 1](#task-1-pwm-fade) · [Task 2](#task-2-rgb-led) · [Task 3](#task-3-neopixel-stick)

### LG5 – Individual Pixel Control

Use a hardware peripheral to send data to an addressable LED strip and control individual pixels by index.

**Evidence:** [Task 3](#task-3-neopixel-stick)

### LG6 – Current Measurement and Power Budgeting

Measure the supply current of an addressable LED strip and estimate its power requirements at different pixel counts.

**Evidence:** [Task 3](#task-3-neopixel-stick)

---

## Task 1: PWM Fade

**Proves:** [LG1](#lg1-led-current-limiting), [LG2](#lg2-pwm-dimming), [LG4](#lg4-reproducible-platformio-projects)

We connected GPIO16 (`RX2`) to the LED anode through a 220 Ω resistor and connected the cathode to `GND`. The program increased the PWM value from 0 to 255 and then decreased it back to 0.

**Result:** The LED repeatedly faded in and out. A higher duty cycle kept the LED on for a larger fraction of each PWM period, making it appear brighter.

**Portfolio evidence:**

- [PlatformIO project](./codes/task1_led/)
- [LED fade video](./pictures/task1-pwm-fade.mp4)

## Task 2: RGB LED

**Proves:** [LG1](#lg1-led-current-limiting), [LG3](#lg3-additive-colour-mixing), [LG4](#lg4-reproducible-platformio-projects)

We used a common-cathode RGB LED module with one onboard 150 Ω resistor per channel. We connected `R` to GPIO16 (`RX2`), `G` to GPIO17 (`TX2`), `B` to GPIO18 (`D18`), and the common cathode (`−`) to `GND`.

We sent `R G B` commands through the serial monitor at 115200 baud. The program accepted the red, green, blue, yellow, and off commands. It rejected `256 0 0` as out of range. The valid white command `255 255 255` also returned an error in the recorded run, and we did not determine the cause.

**Result:** We activated one channel at a time at a PWM value of 255, measured the voltage drop across its onboard resistor, and calculated the current using `I = U / R`.

| Channel | Serial command | Measured voltage drop | Calculated current |
|---|---|---:|---:|
| Red | `255 0 0` | 1.11 V | 7.4 mA |
| Green | `0 255 0` | 0.65 V | 4.3 mA |
| Blue | `0 0 255` | 0.56 V | 3.7 mA |

**Portfolio evidence:**

- [PlatformIO project](./codes/task2_rgb/)
- [RGB serial test screenshot](./pictures/task2-serial.jpg)
- [RGB module photo](./pictures/task2-rgb.jpg)

## Task 3: NeoPixel Stick

**Proves:** [LG4](#lg4-reproducible-platformio-projects), [LG5](#lg5-individual-pixel-control), [LG6](#lg6-current-measurement-and-power-budgeting)

We controlled eight pixels using NeoPixelBus with ESP32 RMT channel 0 and GRB transmission order. We connected `DIN` to GPIO16 (`RX2`) through a series resistor, shared `GND` with the ESP32, and powered the stick from the board's USB-fed `VIN` pin.

We sent `index R G B` commands at 115200 baud. Index `0` selected the first pixel, index `7` selected the eighth pixel, and the program rejected index `8`. The `clear` command switched all pixels off.

**Result:** We inserted a UNI-T UT131C multimeter in series between `VIN` and the stick's power input to measure the stick's supply current. The firmware capped each RGB channel at 80/255.

| Pixel state | Displayed current on the 10 A range |
|---|---:|
| All pixels off after `clear` | 0.00 A |
| One pixel set to white | 0.01 A |
| Two pixels set to white | 0.02 A |
| Eight pixels set to white | 0.09 A |

The meter displayed current in 0.01 A steps on this range, so a small standby current could appear as 0.00 A.

### Power Budget

We used the worksheet's estimate of 60 mA per pixel at full white and full brightness.

| Pixel count | Estimated current | Estimated power at 5 V |
|---:|---:|---:|
| 8 | 0.48 A | 2.4 W |
| 30 | 1.80 A | 9.0 W |
| 60 | 3.60 A | 18.0 W |
| 144 | 8.64 A | 43.2 W |

The USB-fed `VIN` setup powered all eight pixels at the tested output limit. Under the worksheet's full-brightness assumption, eight pixels would use 0.48 A, leaving 0.02 A in a 0.50 A USB budget before accounting for the ESP32.

**Portfolio evidence:**

- [PlatformIO project](./codes/task3_strip/)
- [NeoPixel serial test screenshot](./pictures/task3-serial.jpg)
- [Current measurement photo showing 0.09 A](./pictures/task3-current.jpg)

## Study log

- **Task 1.** We observed that changing the PWM duty cycle changed the apparent brightness of the LED.
- **Task 2.** We measured different voltage drops and calculated different currents for the red, green, and blue channels, even though they used the same nominal resistor value.
- **Task 3.** We observed that the displayed supply current increased as we set more pixels to white, reaching 0.09 A with all eight pixels on at the configured output limit.
