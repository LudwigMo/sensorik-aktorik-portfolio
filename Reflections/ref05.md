# Reflection 05

## Take-away

I learned to record the conditions behind a current measurement. For the NeoPixel stick, I noted how many pixels were on, their colour, the output limit, and where the meter was connected. With all eight pixels set to white at the 80/255 output limit, the meter displayed 0.09 A for the LED stick alone.

## What was good?

I got all three projects running on the ESP32. I could see the single LED fade, change the RGB module's colour through the serial monitor, and control individual NeoPixel LEDs by index. The photo of all eight pixels lit white captured the meter reading and the test condition together.

## What was difficult?

The NeoPixel stick stopped lighting when I first inserted the multimeter into its supply line. I had to check the meter settings and the connections before I could get a reading with the LEDs on. The 10 A range also displayed current in 0.01 A steps, which limited what I could say about the standby current.

## Exploration and show stoppers

I set additional pixels to white one at a time. The meter displayed 0.01 A for one pixel, 0.02 A for two, and 0.09 A for eight. After `clear`, it displayed 0.00 A. That last reading was limited by the meter's resolution.

## Interaction with peers and instructors

I compared my results with Haocheng's experiment records. Our RGB channel currents were close, and both records showed 0.09 A for eight white pixels at the recorded brightness setting of 80/255. I checked that both current measurements covered the LED stick's supply branch.

## How did you verify AI suggestions?

The initial AI wiring guidance assumed three external 220 Ω resistors. I checked the actual RGB module and found three onboard resistors marked `151`, which indicates a nominal resistance of 150 Ω. I used that value and my measured voltage drops to calculate 7.4 mA for red, 4.3 mA for green, and 3.7 mA for blue.

## Help and extra work

I used AI assistance to set up the PlatformIO projects and troubleshoot the measurements. I tested the firmware on the ESP32, took the measurements, and documented the results with serial screenshots, a PWM fade video, and a photo of the NeoPixel current measurement.
