# Module 4 – Liquid Measurement & Sensor Selection

In this module, we explore liquid-level measurement using ultrasonic and conductive sensing principles. We also investigate how liquid movement, foam, and sensor calibration affect measurement reliability.

We use an HC-SR04 ultrasonic sensor, an HD-38 water sensor, and a BMI270 IMU to perform experiments and evaluate suitable sensing solutions for four tanks on a sailing yacht.

## Learning Goals

<a id="lg1"></a>
### LG1 — Sensing Principles
Explain the differences between binary, thresholded, continuous, and hybrid liquid-level sensing.
<copy the goal here>

**Evidence**: [Task 1](#task-1-liquid-measurement-and-sensor-selection)

<a id="lg2"></a>
### LG2 —  Sensor Selection
Select suitable sensors for different tanks and liquids, considering foam, conductivity, density, hygiene, safety, and operating conditions.
<copy the goal here>

**Evidence:** [Task 1](#task-1-liquid-measurement-and-sensor-selection)

<a id="lg3"></a>
### LG3 — Calibration
Build and calibrate continuous and binary measurement systems, convert distance into liquid level and volume, and evaluate uncertainty.
<copy the goal here>

**Evidence:** [Task 1](#task-1-liquid-measurement-and-sensor-selection)

<a id="lg4"></a>
### LG4 — Motion Detection
Use an IMU to distinguish between stationary, moving, and rough-motion conditions and explain their effects on liquid-level measurements.
<copy the goal here>

**Evidence:** [Task 1](#task-1-liquid-measurement-and-sensor-selection)

<a id="lg5"></a>
### LG5 — Industrial Transfer
Recommend suitable sensing solutions and apply the results to another industrial liquid-measurement scenario.
<copy the goal here>

**Evidence:** [Task 2](#task-2-local-industrial-transfer)
## Task 1 – Liquid Measurement and Sensor Selection

**Proves:** [LG1](#lg1--sensing-principles), [LG2](#lg2--sensor-selection), [LG3](#lg3--calibration), [LG4](#lg4--motion-detection)

In this task, we investigate continuous and binary liquid-level sensing using an ESP32, an HC-SR04 ultrasonic sensor, and an HD-38 water sensor.

We also use the BMI270 IMU in the M5StickS3 to simulate different boat-motion conditions and evaluate their influence on measurement reliability.

Our experiments include:

- Ultrasonic distance measurement and volume calibration
- Foam and tilt interference tests
- Binary water detection and software debounce
- IMU motion detection and sea-state classification
- Sensor selection for four tanks on the Nordwind sailing yacht

### 1. Ultrasonic Liquid-Level Measurement

We mounted the HC-SR04 ultrasonic sensor above a transparent container and connected it to the ESP32.

The sensor measures the distance to the water surface using ultrasonic time-of-flight. As the water level increases, the measured distance decreases.

We used the following connections:

| HC-SR04 | ESP32 |
|---|---|
| VCC | VIN (5 V with USB supply) |
| GND | GND |
| TRIG | GPIO18 |
| ECHO | GPIO19 via a voltage divider |

We used two 5 kΩ resistors to reduce the ECHO signal voltage before connecting it to the ESP32.
