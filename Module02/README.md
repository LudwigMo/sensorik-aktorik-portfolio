# Module 2

> **Example module** from the IoT introduction class. Adjust the headings and tasks to match your actual course content.

We are going to show here notes for Task 1, 2, 3, 4, and 5 to prove

## Learning Goals

> Copy the module's learning goals from the course workbook. Keep the `LG1`, `LG2`, … IDs and a one-word keyword; under each goal, link to the task that proves it.

<a id="lg1"></a>
### LG1 — `<keyword>`

<copy the goal here>

**Evidence:** [Task 1](#task-1)

<a id="lg2"></a>
### LG2 — `<keyword>`

<copy the goal here>

**Evidence:** [Task 2](#task-2)

<a id="lg3"></a>
### LG3 — `<keyword>`

<copy the goal here>

**Evidence:** [Task 3](#task-3)

<a id="task-2"></a>
## Task 2 — Bus Systems Survey (SPI)

**Proves:** [LG2](#lg2)

In this task, I researched the SPI(Serial Peripheral Interface) bus. I studied its history, wiring, communication principles, advantages, applications, and possible problems.

**Portfolio evidence:**
[SPI Bus Profile](./bus-spi.md)

<a id="task-3"></a>
## Task 3 — `Bus Systems Comparison`

**Proves:** [LG3](#lg3)

In this task, I compared different communication bus systems, including SPI, I²C/I³C, CAN, RS-232, RS-485, Modbus RTU, and OneWire. I analyzed their wiring, signaling methods, topology, speed, and typical applications. I also discussed their advantages and limitations to understand which bus is suitable for different situations.

**Portfolio evidence:** [Bus Systems Comparison](./bus-comparison.md)

<a id="task-5"></a>

## Task 5 — `I²C Bus Scan`

**Proves:** I²C communication, device addressing and bus scanning.

In this task, we connected an LCD1602 display with an I²C adapter to an ESP8266 D1 mini. Using the Wire library, we scanned the I²C bus and successfully detected one device at address 0x27. The result was displayed in both the Serial Monitor and on the LCD1602.

**Portfolio evidence:**
- [Serial Monitor Screenshot](./pictures/task5-i2c-scan-serial.png)
- [LCD1602 Display Photo](./pictures/task5-i2c-scan-lcd.jpg)
- [I²C Scanner Source Code](./ESP8266_I2C_Scanner.ino)

 <a id="task-9"></a>
## Task 9 — `Build and Test an ESP32 Logic Analyzer`

**Proves:** Practical application of digital signal acquisition and measurement.

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

#### I²C Protocol Decoding – Experimental Verification

To verify I²C communication, we used an ESP8266 D1 mini to generate I²C signals and an ESP32 running the **lmcapacho Logic Analyzer** firmware to capture them. The signals were analyzed using PulseView.

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
- Target address: 0x29 (7-bit)

**Result:**

PulseView successfully captured and decoded the I²C communication.

The decoded transaction was:

`START → Address 0x29 → Write → NACK → STOP`

The NACK response was expected because no I²C target device was connected at address 0x29.

**Conclusion:**

The experiment demonstrated how I²C signals can be captured and decoded using a logic analyzer. The START and STOP conditions, the device address, the write operation, and the NACK response were successfully identified.

**Portfolio evidence:**
- [Task 9 — Detailed Test Report](./scope-decision.md)
- [ESP32 Logic Analyzer — Source Code](https://github.com/lmcapacho/ESP32_LogicAnalyzer)
- [Task 9 – Square-wave measurement](./pictures/task9-square-wave-measurement.png)
- [I²C protocol decoding in PulseView](./pictures/task9-i2c-decoding.png)
- [ESP8266 I²C Test](./ESP8266_I2C_Test.ino)

## Reflection 2

[Reflection 2](../Reflections/ref02.md)

If the module is longer than 1 week, you might have several reflections within it. If not, delete this and the following.

## Reflection 3
[Reflection 3](../Reflections/ref03.md)
