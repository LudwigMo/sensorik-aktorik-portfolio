# Module 2 – Bus Systems and I²C Communication

In this module, we explored different communication bus systems, studied I²C communication, and performed practical experiments using an ESP8266, an ESP32, a temperature sensor, and an LCD1602 display.

We documented our work in Tasks 2, 3, 5, 6, 7, and 9 to demonstrate our understanding of communication buses, I²C addressing, register access, multi-device communication, and digital signal analysis.

## Learning Goals

### LG1 – Bus Comparison

Compare different communication interfaces and bus systems in terms of wiring, signaling, topology, speed, distance, and typical applications.

**Evidence:** [Task 2](#task-2-bus-systems-survey-spi) · [Task 3](#task-3-bus-systems-comparison)

### LG2 – I²C Principles

Explain the physical and logical principles of I²C communication, including SDA, SCL, pull-up resistors, device addressing, and ACK/NACK.

**Evidence:** [Task 5](#task-5-i2c-bus-scan) · [Task 9](#task-9-build-and-test-an-esp32-logic-analyzer)

### LG3 – I²C Scanning

Connect and scan an I²C bus and identify connected devices using their addresses.

**Evidence:** [Task 5](#task-5-i2c-bus-scan) · [Task 7](#task-7-two-devices-on-one-bus)

### LG4 – Register Access

Read sensor data using a library and through direct register access, reconstruct the raw values, and compare the results.

**Evidence:** [Task 6](#task-6-library-and-register-reading)

### LG5 – Multi-Device Communication

Operate multiple devices on a shared I²C bus and understand how different device addresses allow them to communicate independently.

**Evidence:** [Task 7](#task-7-two-devices-on-one-bus)

*Address-conflict resolution is not covered by our current experiment.*

### LG6 – Logic Analysis

Build and evaluate a low-cost logic analyzer to capture and analyze digital signals and communication protocols.

**Evidence:** [Task 9](#task-9-build-and-test-an-esp32-logic-analyzer)

*The class-wide selection of analysis tools is not documented as completed here.*

---

## Task 2: Bus Systems Survey (SPI)

**Proves:** [LG1](#lg1-bus-comparison)

In this task, we researched the SPI (Serial Peripheral Interface) bus. We studied its history, wiring, communication principles, advantages, applications, and possible problems.

**Portfolio evidence:**

- [SPI Bus Profile](./bus-spi.md)

## Task 3: Bus Systems Comparison

**Proves:** [LG1](#lg1-bus-comparison)

In this task, we compared different communication bus systems, including SPI, I²C/I³C, CAN, RS-232, RS-485, Modbus RTU, and OneWire.

We analyzed their wiring, signaling methods, topology, speed, and typical applications. We also discussed their advantages and limitations to understand which bus is suitable for different situations.

**Portfolio evidence:**

- [Bus Systems Comparison](./bus-comparison.md)

## Task 5: I2C Bus Scan

**Proves:** [LG2](#lg2-i2c-principles), [LG3](#lg3-i2c-scanning)

In this task, we connected an LCD1602 display with an I²C adapter to an ESP8266 D1 mini. Using the Wire library, we scanned the I²C bus and successfully detected one device at address `0x27`.

We displayed the scan results in both the Arduino Serial Monitor and on the LCD1602.

**Result:**

- I²C address: `0x27`
- Number of detected devices: 1
- SDA: D2 (GPIO4)
- SCL: D1 (GPIO5)
- I²C clock: 100 kHz

**Portfolio evidence:**

- [Serial Monitor Screenshot](./pictures/task5-i2c-scan-serial.png)
- [LCD1602 Display Photo](./pictures/task5-i2c-scan-lcd.jpg)
- [I²C Scanner Source Code](./ESP8266_I2C_Scanner.ino)

## Task 6: Library and Register Reading

**Proves:** [LG4](#lg4-register-access)

In this task, we connected an SE95 temperature sensor to an ESP8266 D1 mini via I²C.

We first read the temperature register (`0x00`) directly using the Wire library and converted the raw 13-bit value into degrees Celsius.

We then used an LM75A-compatible library to read the same sensor and compared both results.

**Result:**

- I²C address: `0x4F`
- Raw register value: `862`
- Register temperature: `26.938 °C`
- Library temperature: `26.938 °C`
- Difference: `0.000 °C`

The results agreed, confirming that the raw register data was interpreted correctly.

For ESP8266 compatibility, we commented out the unsupported `Wire.end()` call in the LM75A library.

**Portfolio evidence:**

- [Register Reading Screenshot](./pictures/task6-register-reading.png)
- [Library vs. Register Comparison Screenshot](./pictures/task6-library-register-comparison.png)
- [SE95 Direct Register Reading Code](./ESP8266_SE95_Register_Test.ino)
- [SE95 Library and Register Comparison Code](./ESP8266_SE95_Comparison.ino)

## Task 7: Two Devices on One Bus

**Proves:** [LG3](#lg3-i2c-scanning), [LG5](#lg5-multi-device-communication)

In this task, we connected an LCD1602 display and an SE95 temperature sensor to the same I²C bus using an ESP8266 D1 mini.

Both devices shared the same SDA (D2) and SCL (D1) pins.

We scanned the bus and successfully detected both I²C addresses: `0x27` for the LCD1602 and `0x4F` for the SE95 sensor.

We then developed a program to read the temperature from the SE95 sensor and display it on the LCD1602 in real time.

**Result:**

Both devices operated successfully on the same I²C bus without requiring additional GPIO pins.

The measured temperature was approximately `25.25 °C`.

Our experiment used one temperature sensor and one display module rather than two sensors.

**Portfolio evidence:**

- [Two Devices – I²C Scan](./pictures/task7-two-devices-scan.png)
- [Temperature – Serial Monitor](./pictures/task7-temperature-serial.png)
- [Temperature – LCD1602 Display](./pictures/task7-temperature-lcd.jpg)
- [ESP8266 Two Devices Source Code](./ESP8266_I2C_Two_Devices.ino)

## Task 9: Build and Test an ESP32 Logic Analyzer

**Proves:** [LG2](#lg2-i2c-principles), [LG6](#lg6-logic-analysis)

In this task, we built a digital logic analyzer using an ESP32 and the open-source ESP32_LogicAnalyzer project by lmcapacho.

We installed the firmware using Arduino IDE and connected the ESP32 to PulseView via the SUMP protocol.

To test the logic analyzer, we used a second development board (ESP8266 D1 mini) to generate a square-wave signal of approximately 1 kHz.

**Hardware connections:**

- ESP8266 D5 (GPIO14) → ESP32 GPIO21 (CH0)
- ESP8266 GND → ESP32 GND
- ESP32 GPIO22 (CLK_OUT) → GPIO23 (CLK_IN)

**Capture settings:**

- Sampling rate: 200 kHz
- Sample count: 64 k samples
- Measured period: 1010 μs
- Measured frequency: 990.10 Hz

The logic analyzer successfully captured the square-wave signal. The measured frequency was close to the expected value of 1 kHz, with a deviation of approximately 0.99%.

### I²C Protocol Decoding – Experimental Verification

To verify I²C communication, we used an ESP8266 D1 mini to generate I²C signals and an ESP32 running the lmcapacho Logic Analyzer firmware to capture them.

The signals were analyzed using PulseView.

**Hardware setup:**

- ESP8266 D2 (SDA) → ESP32 GPIO21 (CH0)
- ESP8266 D1 (SCL) → ESP32 GPIO19 (CH1)
- Common GND between both boards
- Two 4.7 kΩ pull-up resistors connected to 3.3 V
- ESP32 GPIO22 → GPIO23 for the sampling-clock loopback

**Test configuration:**

- I²C clock frequency: 10 kHz
- Logic analyzer sampling rate: 200 kHz
- Capture size: 64 k samples
- Target address: `0x29` (7-bit)

**Result:**

PulseView successfully captured and decoded the I²C communication.

The decoded transaction was:

`START → Address 0x29 → Write → NACK → STOP`

The NACK response was expected because no I²C target device was connected at address `0x29`.

**Conclusion:**

The experiment demonstrated how I²C signals can be captured and decoded using a logic analyzer. The START and STOP conditions, the device address, the write operation, and the NACK response were successfully identified.

**Portfolio evidence:**

- [Task 9 – Detailed Test Report](./scope-decision.md)
- [ESP32 Logic Analyzer – Original Project](https://github.com/lmcapacho/ESP32_LogicAnalyzer)
- [Square-wave Measurement Screenshot](./pictures/task9-square-wave-measurement.png)
- [I²C Protocol Decoding Screenshot](./pictures/task9-i2c-decoding.png)
- [ESP8266 I²C Test Source Code](./ESP8266_I2C_Test.ino)

---

## Reflection

In this module, we gained a better understanding of different communication bus systems, especially I²C. We learned how multiple devices can communicate using the same SDA and SCL lines and how each device can be identified by its own address.

During our experiments, we encountered several challenges, including connection problems, incorrect I²C addresses, and issues with LCD initialization and library compatibility. By checking the wiring, analyzing serial output, and modifying our code, we were able to identify and solve these problems.

One of the most interesting results was that we successfully connected an LCD1602 and an SE95 temperature sensor to the same I²C bus. We also learned how to read temperature data directly from registers and verify the results against a library.

Using the ESP32 logic analyzer and PulseView helped us understand I²C communication at the signal level.

Overall, this module improved our practical understanding of communication protocols, hardware debugging, and sensor integration.
