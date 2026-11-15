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

### 3. Foam and Tilt Interference Tests

We investigated how foam, liquid movement, and container tilt affect ultrasonic distance measurements.

We fixed the HC-SR04 above a container with foamy water and compared the raw and filtered measurements under different conditions.

**Experimental Results**

| Test Condition | Measured Distance | Observation |
|---|---|---|
| Stable foamy water | Approximately 4.33 cm | Stable readings with small fluctuations |
| Tilted container | Approximately 5.61 cm | Several short measurement spikes |
| Maximum raw reading during tilt | Approximately 6.47 cm | Temporary peak in the raw signal |
| Returned to horizontal position | Approximately 4.33 cm | Stable readings after settling |

**Filtering**

We compared the raw ultrasonic measurements with the filtered values using the Arduino Serial Plotter.

During the tilted-container test, we observed several short spikes in the raw signal. The filtered output showed smaller fluctuations and remained more stable.

**Limitations**

Foam can change the effective reflecting surface, while container tilt and liquid movement can change the distance and angle between the sensor and the liquid surface.

We observed these effects during our experiments, but we could not isolate the influence of each factor because foam distribution and liquid position changed during the tests.

Therefore, we recommend stable sensor mounting, appropriate filtering, and additional validation for moving tanks.

### 4. Binary Water Detection

We used an HD-38 module with a two-prong conductive sensor to detect the presence of water.

We connected the sensor to the ESP32 using the following pins:

| HD-38 | ESP32 |
|---|---|
| VCC (+) | 3V3 |
| GND (-) | GND |
| DO | GPIO27 |
| AO | Not connected |

**Experimental Results**

| Test Condition | Digital Output | Observation |
|---|---|---|
| Dry probe | 1 | No water detected |
| Probe immersed in water | 0 | Water detected |
| Probe removed and dried | 1 | Returned to dry state |

We adjusted the potentiometer on the HD-38 module to set the detection threshold. Under our test conditions, the digital output changed when the probe was immersed approximately 0.3 cm into the water.

**Software Debounce**

We implemented a 300 ms software debounce to prevent short signal changes from immediately triggering a new state.

The Serial Monitor displayed the expected transitions:

```text
WATER DETECTED
DRY
```

**Limitations**

The HD-38 detects electrical conductivity between its metal probes rather than measuring the exact liquid level.

We initially encountered a loose power connection, which caused invalid readings. After restoring the 3.3 V supply and adjusting the potentiometer, the sensor successfully distinguished between dry and wet conditions.

The switching threshold may change with water conductivity, probe contamination, and corrosion. Therefore, the HD-38 is suitable for our laboratory demonstration but would require additional validation before use in a real marine environment.

### 5. IMU Motion Detection and Sea-State Classification

We used the BMI270 IMU integrated into the M5StickS3 to simulate three boat-motion conditions: In Harbor, Moving, and Rough.

We measured acceleration along the X, Y, and Z axes and calculated the acceleration magnitude:

\[
a = \sqrt{a_x^2 + a_y^2 + a_z^2}
\]

We then calculated the absolute deviation from 1 g and used the mean deviation within a short measurement window to classify the motion state.

**Experimental Results**

| Motion Condition | Mean Deviation | Observation |
|---|---|---|
| In Harbor | Approximately 0.002 g | Stable acceleration |
| Moving | Approximately 0.027–0.066 g | Moderate fluctuations |
| Rough | Approximately 0.598–1.389 g | Large fluctuations and acceleration peaks |

**Automatic Sea-State Classification**

We developed a classification program using the following experimental thresholds:

| Mean Acceleration Deviation | Classification |
|---|---|
| Below 0.025 g | IN HARBOR |
| 0.025 g to below 0.25 g | MOVING |
| 0.25 g or higher | ROUGH |

We successfully identified stationary and rough-motion conditions. During the gentle-motion test, the system mainly reported MOVING, although one measurement window was classified as IN HARBOR because its mean deviation was approximately 0.024 g.

**Relevance to Liquid-Level Measurement**

Our earlier ultrasonic experiments showed that liquid movement and container tilt can affect distance measurements.

We can use IMU data to identify motion conditions in which liquid-level readings may become less reliable. However, we did not perform synchronized ultrasonic and IMU measurements, so this remains a proposed improvement.

**Limitations**

The thresholds were selected for our laboratory demonstration and were not calibrated against real sea conditions.

Slow tilting may change individual acceleration components while the total acceleration magnitude remains close to 1 g. Therefore, additional gyroscope data and further testing would be necessary for more reliable motion detection.
