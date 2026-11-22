# Module 5 — LEDs and Light as Output

We used an ESP32 to dim a single LED with PWM, mix colours on an RGB LED, and control eight addressable NeoPixel LEDs.

## Learning Goals

| Goal | Evidence |
|---|---|
| LG1 — LED current limiting | [Task 1](#task-1-pwm-fade), [Task 2](#task-2-rgb-led) |
| LG2 — PWM dimming | [Task 1](#task-1-pwm-fade) |
| LG3 — Additive colour mixing | [Task 2](#task-2-rgb-led) |
| LG4 — Reproducible PlatformIO projects | [Task 1 code](codes/task1_led/), [Task 2 code](codes/task2_rgb/), [Task 3 code](codes/task3_strip/) |
| LG5 — Individual pixel control | [Task 3](#task-3-neopixel-stick) |
| LG6 — Current measurement and power budgeting | [Task 3](#task-3-neopixel-stick) |

## Task 1: PWM fade

We connected GPIO16 (`RX2`) to the LED anode through a 220 Ω resistor and connected the cathode to `GND`. The program increased the PWM value from 0 to 255 and then decreased it back to 0. The LED repeatedly faded in and out.

[Watch the LED fade in and out](pictures/task1-pwm-fade.mp4)

## Task 2: RGB LED

We used a common-cathode RGB module with one onboard 150 Ω resistor per channel. We connected `R` to GPIO16 (`RX2`), `G` to GPIO17 (`TX2`), `B` to GPIO18 (`D18`), and `−` to `GND`.

We sent `R G B` commands over the serial monitor at 115200 baud. The program accepted the red, green, blue, yellow, and off commands. It rejected `256 0 0` as out of range. In the recorded run, `255 255 255` also returned an error. The cause remains unconfirmed.

We switched on one channel at a time, measured the voltage across its onboard resistor, and calculated the current using `I = U / R`.

| Channel | Serial command | Measured voltage drop | Calculated current |
|---|---|---:|---:|
| Red | `255 0 0` | 1.11 V | 7.4 mA |
| Green | `0 255 0` | 0.65 V | 4.3 mA |
| Blue | `0 0 255` | 0.56 V | 3.7 mA |

[Serial monitor screenshot — RGB commands and input validation](pictures/task2-serial.jpg)

[RGB LED module during the colour test](pictures/task2-rgb.jpg)


## Task 3: NeoPixel stick

We controlled eight pixels using NeoPixelBus with ESP32 RMT channel 0 and GRB transmission order. We connected `DIN` to GPIO16 (`RX2`), shared `GND` with the ESP32, and powered the stick from the board's USB-fed `VIN` pin.

At 115200 baud, we used `index R G B` to set each pixel. We verified that index `0` selected the first pixel, index `7` selected the eighth pixel, and index `8` was rejected. The `clear` command switched all pixels off.

We inserted a UNI-T UT131C multimeter in series between `VIN` and the stick's power input. The firmware limited each colour channel to 80/255, and the meter measured only the stick's supply current.

| Pixel state | Displayed current on the 10 A range |
|---|---:|
| All off after `clear` | 0.00 A |
| One pixel set to white | 0.01 A |
| Two pixels set to white | 0.02 A |
| Eight pixels set to white | 0.09 A |

The meter's display step was 0.01 A on this range. A small standby current could therefore appear as 0.00 A.

[Serial monitor screenshot — individual pixel control and clear command](pictures/task3-serial.jpg)

[Eight NeoPixel LEDs set to white with the multimeter displaying 0.09 A](pictures/task3-current.jpg)


### Power budget

Using the worksheet's estimate of 60 mA per pixel at full white and full brightness, we calculated the following supply requirements.

| Number of pixels | Estimated current | Estimated power at 5 V |
|---:|---:|---:|
| 8 | 0.48 A | 2.4 W |
| 30 | 1.80 A | 9.0 W |
| 60 | 3.60 A | 18.0 W |
| 144 | 8.64 A | 43.2 W |

The USB-fed setup powered all eight pixels at the tested output limit. At full brightness, eight pixels alone would use an estimated 0.48 A, leaving only 0.02 A in a 0.50 A USB budget before accounting for the ESP32.

## Study log

- **Task 1.** We observed that a higher PWM duty cycle made the LED appear brighter because it stayed on for a larger fraction of each cycle.
- **Task 2.** We obtained different current values for the three colour channels even though they used the same nominal resistor value.
- **Task 3.** We observed that the displayed supply current increased as we set more pixels to white, reaching 0.09 A with all eight pixels on at the configured output limit.
