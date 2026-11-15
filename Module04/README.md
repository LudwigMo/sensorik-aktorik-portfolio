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

$$
h = d_0 - d
$$

where:
- $h$ is the estimated water level.
- $d_0 = 12.1\,\text{cm}$ is the empty-container distance.
- $d$ is the measured distance.

**Volume Estimation**

We used piecewise linear interpolation between neighboring calibration points to estimate the water volume:

$$
V = V_1 + \frac{d_1-d}{d_1-d_2}(V_2-V_1)
$$

where:
- $V$ is the estimated volume.
- $d$ is the measured distance.
- $d_1$ and $d_2$ are the neighboring calibration distances.
- $V_1$ and $V_2$ are their corresponding volumes.

**Validation**

In an independent validation test, we measured a distance of 6.9 cm.

Using the neighboring calibration points, we calculated:

$$
V = 205 + \frac{7.0-6.9}{7.0-6.4}(258-205)
$$

$$
V \approx 213.83\,\text{mL}
$$

We compared this estimate with the reference volume of approximately 219 mL.

The relative deviation was calculated as:

$$
\text{Relative Deviation} =
\frac{|219-213.83|}{219}\times100\%
\approx 2.36\%
$$

**Results and Limitations**

The measured distance decreased as the water volume increased. Our calibration and validation demonstrated that piecewise linear interpolation can be used to estimate water volume within the tested range.

However, we observed non-uniform changes between calibration points. Possible causes include unwanted ultrasonic reflections, sensor alignment, container geometry, and measurement uncertainty.

The 2.36% relative deviation represents one independent validation test and does not establish the sensor's accuracy across the entire measurement range.


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

$$
a = \sqrt{a_x^2 + a_y^2 + a_z^2}
$$

where:
- $a_x$ is the acceleration along the X-axis.
- $a_y$ is the acceleration along the Y-axis.
- $a_z$ is the acceleration along the Z-axis.
- $a$ is the total acceleration magnitude.

We then calculated the absolute deviation from 1 g:

$$
D = |a - 1g|
$$

We used the mean deviation within a short measurement window to classify the motion state.

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


### 6. Decision Sheet — Sensor Selection for Four Tanks

We evaluated suitable sensing principles for the four tanks on the Nordwind sailing yacht. We considered the liquid properties, required measurements, possible failures, and installation conditions.

| Tank | Decision | Mode | Principle (Primary / Failsafe) | Evidence | Failure + Installation Note |
|---|---|---|---|---|---|
| Diesel | Remaining fuel level and low-level warning | Hybrid: continuous + binary | Diesel-compatible continuous level sender / independent low-level float switch | Our ultrasonic and IMU experiments demonstrated the influence of motion on distance measurements. | Sloshing can cause unstable readings. We recommend fuel-compatible sensors, stable mounting, and filtering. |
| Fresh Water | Remaining water volume and low-level warning | Hybrid: continuous + binary | Ultrasonic level sensor / low-level float switch | Our volume calibration used seven reference points. One validation test showed a relative deviation of 2.36%. | Foam, movement, and unwanted reflections may affect readings. We recommend filtering and suitable mounting. |
| Waste Water | High-level alarm to prevent overflow | Threshold + high failsafe | Non-contact capacitive level switch / independent high-level float switch | Our HD-38 experiment demonstrated binary wet/dry detection and 300 ms software debounce. | Contamination and deposits may cause incorrect detection. We recommend verifying tank-wall compatibility and sensor reliability. |
| Bilge | Detect unwanted water accumulation | Staggered binary | Low-level water detector / independent high-level float switch | Our HD-38 sensor detected water contact at approximately 0.3 cm immersion depth. | Corrosion, salt deposits, and contamination may cause false readings. We recommend marine-rated sensors and independent alarm levels. |

#### Recommendation Summary

We recommend continuous measurement with an independent low-level alarm for the diesel and fresh-water tanks because the crew needs information about the remaining liquid volume.

For the waste-water tank, we prioritize reliable high-level detection to prevent overflow.

For the bilge, we recommend staggered binary sensing to detect unwanted water early and provide an independent emergency alarm.

Our laboratory experiments provide evidence for ultrasonic distance measurement, conductive water detection, and motion classification. The proposed fuel-compatible, capacitive, and float-switch solutions would require additional testing before installation on a real sailing yacht.


### 7. Test Cards

We summarized the sensing principles tested in our laboratory experiments, including their measurements, calibration methods, and limitations.

| Principle | Liquid / Condition | What It Measures | Works? | Calibration / Validation | Failure / Limitation |
|---|---|---|---|---|---|
| HC-SR04 Ultrasonic | Tap water | Distance to the liquid surface (continuous) | Yes | Seven calibration points; 2.36% relative deviation in one independent volume validation | Foam, tilt, liquid movement, unwanted reflections, and short measurement distances |
| HD-38 Conductive | Tap water | Electrical conductivity converted into binary wet/dry detection | Yes | Adjustable threshold; approximately 0.3 cm trigger immersion; 300 ms software debounce | Corrosion, contamination, water conductivity changes, and loose electrical connections |
| BMI270 IMU | Simulated boat motion | Three-axis acceleration and motion intensity | Yes | Three motion conditions tested; experimental thresholds for automatic classification | Threshold sensitivity, slow tilting, and possible misclassification |

#### Key Findings

- We confirmed that ultrasonic sensing can measure liquid-level changes and estimate volume after calibration.
- We demonstrated binary water detection using the HD-38 sensor and improved state stability with software debounce.
- We used the BMI270 IMU to classify three simulated boat-motion conditions.
- We identified sensor limitations that must be considered when selecting sensing principles for real tanks.

These results were obtained under laboratory conditions. Further validation would be required for real marine applications.


### 8. Recommendation Report

Based on our laboratory experiments and sensor selection analysis, we recommend different sensing solutions for the four tanks on the Nordwind sailing yacht.

**Diesel Tank**

We recommend a diesel-compatible continuous level sensor combined with an independent low-level float switch. The continuous sensor provides information about the remaining fuel, while the switch provides a critical low-fuel warning. Our motion experiments showed why liquid movement must be considered. For real installation, we would verify fuel compatibility and marine safety requirements.

**Fresh Water Tank**

We recommend an ultrasonic level sensor with an independent low-level float switch. Our HC-SR04 experiments demonstrated continuous distance measurement and volume estimation using seven calibration points. However, foam and liquid movement affected the readings, so we recommend filtering, stable mounting, and calibration for the actual tank geometry.

**Waste Water Tank**

We recommend a non-contact capacitive level switch for high-level detection, supported by an independent high-level float switch. This reduces direct contact between the primary sensor and contaminated liquid. We would verify the effect of tank-wall thickness, deposits, and contamination before installation.

**Bilge**

We recommend two binary water detectors installed at different heights. The lower detector provides early warning, while the higher independent switch triggers an emergency alarm. Our HD-38 experiment demonstrated basic wet/dry detection, but a real installation would require marine-rated sensors resistant to corrosion and contamination.

**Overall Recommendation**

We conclude that no single sensing principle is suitable for every tank. Continuous sensing is useful when remaining volume matters, while binary or threshold-based sensing is more appropriate for overflow prevention and water-presence detection. Independent failsafe sensors improve the robustness of critical alarms.


### 9. Theory Report

#### Ultrasonic Measurement

We used the HC-SR04 sensor to measure the distance between the sensor and the water surface. The sensor emits an ultrasonic pulse and measures the time required for the reflected signal to return.

We calculated the distance using:

$$
d = \frac{v \cdot t}{2}
$$

where:
- \(d\) is the measured distance.
- \(v\) is the speed of sound.
- \(t\) is the round-trip time.

We estimated the liquid level using:

$$
h = d_0 - d
$$

where \(d_0\) is the empty-container distance and \(d\) is the measured distance.

#### Calibration and Validation

We used seven calibration points to establish the relationship between measured distance and water volume. We estimated the water volume from its mass using the approximation 1 g ≈ 1 mL.

Because the calibration points were not evenly spaced, we used piecewise linear interpolation instead of assuming a constant relationship between level and volume.

For validation, we compared the estimated volume of 213.83 mL with a reference volume of approximately 219 mL. The relative deviation was 2.36%.

#### Binary Water Detection

We used the HD-38 sensor to detect electrical conductivity between two metal probes.

The sensor module compares the probe signal with an adjustable threshold and provides a digital output.

We observed:

- Dry: DO = 1
- Wet: DO = 0
- Trigger immersion depth: approximately 0.3 cm

We implemented a 300 ms software debounce to confirm stable state changes.

#### IMU Motion Detection

We used the BMI270 IMU to measure acceleration along three axes and calculate the acceleration magnitude.

We classified simulated boat motion using the mean absolute deviation from 1 g within a short measurement window.

We observed that our selected thresholds could distinguish stationary, gentle-motion, and rough-motion conditions, although occasional misclassification occurred near the threshold.

#### Uncertainty and Limitations

We identified several sources of uncertainty:

- Ultrasonic reflections from the container walls and liquid surface
- Foam, liquid movement, and sensor alignment
- Manual volume measurement and scale accuracy
- Changes in water conductivity and probe condition
- Motion-classification thresholds and sampling limitations

We conclude that calibration, filtering, debounce, and independent failsafe sensors can improve measurement reliability. However, further testing would be required before applying these principles to real marine tanks.



## Task 2 – Local Industrial Transfer

**Proves:** [LG2](#lg2--sensor-selection), [LG5](#lg5--industrial-transfer)

### Brewery in Bielefeld

We consider a fictional brewery in Bielefeld that needs to monitor the liquid level in a fermentation tank.

The operators need to monitor the filling level and prevent overflow. Foam formation during fermentation can interfere with level measurements, while incorrect readings may cause product loss or production interruptions.

**Sensor Selection**

We recommend an industrial radar level sensor for continuous measurement, combined with an independent high-level switch for overflow protection.

In our HC-SR04 experiments, we observed that foam and liquid movement affected ultrasonic measurements. Therefore, we would evaluate an industrial radar sensor for its suitability under foaming conditions.

Our HD-38 experiment demonstrated binary water detection. However, exposed metal probes are not ideal for hygienic brewery applications because of cleaning and contamination concerns.

**Installation and Local Display**

We would install the radar sensor at the top of the fermentation tank and place an independent high-level switch near the maximum permitted filling level.

The local display would show:

- Current liquid level
- Estimated liquid volume
- Normal or warning status
- HIGH LEVEL ALARM when the limit is reached

**Verification and Limitations**

We would calibrate the system using known filling volumes and test its response to foam, changing liquid levels, and cleaning conditions.

Our laboratory tests demonstrated ultrasonic and binary sensing principles. The proposed radar-based system remains a theoretical design that requires further validation under real brewery conditions.


### 10. Code and Experimental Evidence

**Arduino Code**

- [HC-SR04 Ultrasonic Measurement](code/ultrasonic_raw.ino)
- [HD-38 Binary Water Detection](code/water_sensor_binary.ino)
- [BMI270 IMU Measurement](code/imu_motion_test.ino)
- [IMU Sea-State Classification](code/imu_sea_state.ino)
