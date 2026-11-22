# Reflection 1 — Module 01: Foundations, Measurement and Sensor Chain

## Take-away

I learned how sensors convert physical quantities into digital data and how an ESP32 processes these signals. I also understood the difference between ADC resolution and measurement accuracy. My main takeaway is that reliable measurements require both correct hardware connections and careful data analysis.

## What was good?

I successfully controlled an LED with a button and implemented software debouncing. I used the Serial Monitor and Serial Plotter to observe digital signals. I also compared 10-bit and 12-bit ADC resolutions and collected 120 LDR readings under different lighting conditions.

## What was difficult?

Understanding ADC resolution and interpreting the measurements were challenging. Some ADC experiments were interrupted and had to be repeated. During the LDR experiment, the initial dark measurements were inconsistent because the sensor was not completely covered. I improved the covering method and repeated the measurements.

## Exploration and show stoppers

I found it interesting to observe how the LDR readings changed under different lighting conditions. Comparing the ADC resolutions also helped me understand quantization. A limitation was that I did not have a multimeter, so I could not independently verify the measured voltages. Task 5 filtering was not performed because the required scope ended at Task 4.

## Interaction with peers and instructors

I worked with my classmates during the hardware experiments. We discussed circuit connections, compared observations, and helped each other troubleshoot problems. I also followed the instructor's guidance on the required task scope.

## How did you verify AI suggestions?

I used AI to help understand the Arduino code, ADC resolution, voltage-divider calculations, and measurement results. I checked the suggestions against the actual ESP32 serial output, captured plots, and repeated experiments. I also distinguished calculated voltage estimates from independently measured values, which were not available.

## Help and extra work

My classmates helped during the experiments, and AI supported my understanding and documentation. I organized the programs, photographs, serial captures, and measurement data in my GitHub Portfolio. I also added supplementary notes on measurement terminology, quantization, sampling, and aliasing.
