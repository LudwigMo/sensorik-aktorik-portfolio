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

### 2. Volume Calibration and Validation

We calibrated the HC-SR04 sensor using a transparent container, a measuring cup, and a digital scale. We gradually added water and recorded the corresponding ultrasonic distance measurements.

We used the mass of water to estimate its volume, assuming approximately 1 g = 1 mL.

**Calibration Results**

| Water Volume (mL) | Distance (cm) | Estimated Level (cm) |
|---|---|---|
| 0 | 12.1 | 0.0 |
| 42 | 11.5 | 0.6 |
| 103 | 9.6 | 2.5 |
| 156 | 8.9 | 3.2 |
| 205 | 7.0 | 5.1 |
| 258 | 6.4 | 5.7 |
| 309 | 4.9 | 7.2 |

We calculated the estimated water level using:

\[
h = d_0 - d
\]

where \(d_0 = 12.1\) cm is the empty-container distance and \(d\) is the measured distance.

**Validation**

We used piecewise linear interpolation to estimate the water volume from the measured distance.

In an independent validation test, we recorded:

- Reference volume: approximately 219 mL
- Measured distance: 6.9 cm
- Estimated volume: 213.83 mL
- Absolute deviation: 5.17 mL
- Relative deviation: 2.36%

The measured distance decreased as the water volume increased. The validation result suggests that the calibration method can estimate liquid volume within the tested range.

However, we observed non-uniform changes between calibration points. Therefore, this single validation result does not establish the sensor's accuracy across the entire range.
