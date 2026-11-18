# Reflection — Module 2

## Take-away

I learned that understanding a communication protocol requires both theory and practical measurements. Comparing buses helped me understand their differences, while the logic analyzer made digital signals visible. My advice is to check the wiring, common ground, pull-up resistors, and acquisition settings before changing the code.

## What was good?

I successfully connected the ESP32 Logic Analyzer to PulseView and obtained visible waveforms after troubleshooting. Comparing the bus characteristics also helped me understand how wiring, addressing, and timing affect sensor communication.

## What was difficult?

Initially, PulseView could not detect the analyzer, and later some captures showed no useful waveform. Several possible causes overlapped: serial-port settings, wiring, and sampling configuration. I learned to check these separately instead of assuming that the sensor or program was faulty.

## Exploration and show stoppers

Exploring a low-cost ESP32 logic analyzer was useful because I could observe signals directly. I obtained a usable capture with 64k samples at 200 kHz. However, a visible waveform alone does not prove that the communication is correct; the sampling rate must also be suitable for the signal being measured.

## Interaction with peers and instructors

My setup and captured waveforms provide a concrete basis for discussion with peers and instructors. A useful question for further feedback is whether my acquisition settings are sufficient to interpret the bus timing reliably.

## How did you verify AI suggestions?

I asked AI for explanations of bus protocols, wiring, and logic-analyzer settings. I checked the practical suggestions by inspecting my connections and running captures in PulseView. The initially tried 1 MHz setting did not produce a useful capture in my setup, while 200 kHz did. This showed me that suggested settings need testing and that a successful capture does not automatically verify every explanation.

## Help and extra work

AI helped me structure the troubleshooting process and understand the communication concepts. I also spent extra time configuring the analyzer, checking connections, and organizing the screenshots and links in my GitHub documentation. These steps made my work easier to review and reproduce.
