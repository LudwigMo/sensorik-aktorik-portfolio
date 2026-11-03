# Task 3 – Bus Systems Comparison

## 1. Comparison Table

The following table compares the main communication buses in terms of wiring, signaling, topology, speed, applications, and debugging methods.

| Bus | Wires | Signaling / Drive Style | Topology / Addressing | Speed / Distance | Typical Use | Debug Tool |
|---|---|---|---|---|---|---|
| RS-232 | TX, RX, GND | Single-ended, push-pull | Point-to-point | Typically up to 115.2 kbit/s; short distances | Serial device communication | Serial monitor, oscilloscope |
| RS-485 | A, B | Differential | Multi-drop; no addressing defined by the physical standard | Up to several Mbit/s at short distances; long cables possible | Industrial networks | Oscilloscope, logic analyzer with transceiver |
| Modbus RTU | Depends on physical layer, often RS-485 | Depends on physical layer | Addressed request-response communication | Depends on physical layer | PLCs, industrial sensors | Modbus analyzer |
| CAN | CAN_H, CAN_L | Differential | Multi-master, message-based identifiers | Classic CAN commonly up to 1 Mbit/s; distance depends on speed | Automotive ECUs, industrial control | CAN analyzer |
| I²C / I³C | SDA, SCL | I²C: open-drain; I³C: open-drain and push-pull | Addressed multi-device bus | I²C commonly 100/400 kbit/s; I³C SDR up to 12.5 Mbit/s; short distances | Sensors, embedded systems | Logic analyzer, PulseView |
| SPI | SCLK, MOSI, MISO, CS | Usually push-pull | Controller-peripheral, chip-select | Often several MHz or higher; short distances | Displays, flash memory, ADCs | Logic analyzer, PulseView |
| OneWire | Data, GND | Open-drain with pull-up | Multi-drop, unique device identifiers | Typically 16.3 kbit/s standard mode; short distances | DS18B20 temperature sensor | Logic analyzer |

*Note: Speeds and distances depend on the specific devices, wiring, and operating conditions.*

## 2. Discussion Questions

### Q1. Which buses are point-to-point, multi-drop, or multi-master?

- **Point-to-point:** RS-232 and typical UART connections.
- **Multi-drop:** RS-485, I²C, I³C, CAN, and OneWire.
- **Multi-master:** CAN and I²C support multiple controllers. I³C also provides multi-controller capabilities.

SPI normally uses a controller with one or more peripherals selected through chip-select signals.

### Q2. Which buses require termination? Which are differential?

RS-485 and CAN use differential signaling and normally require appropriate termination at the ends of the bus.

Differential signaling improves noise immunity, making these buses suitable for industrial and automotive environments.

I²C uses pull-up resistors rather than transmission-line termination in typical short-distance applications.

### Q3. What is the difference between open-drain, push-pull, and differential signaling?

- **Open-drain:** Devices actively pull a signal LOW or release it. Pull-up resistors provide the HIGH level. This allows multiple devices to share a line.
- **Push-pull:** Devices actively drive both HIGH and LOW levels. This allows fast transitions but requires avoiding conflicting outputs.
- **Differential:** Information is represented by the voltage difference between two signal wires, improving resistance to electrical interference.

Devices with different voltage levels may require suitable level shifters or transceivers.

### Q4. Why is I²C suitable for many small sensors on one board?

I²C requires only two signal lines, SDA and SCL. Multiple sensors can share these lines because each device is identified by its address.

This reduces GPIO usage and wiring complexity.

However, bus capacitance, address conflicts, and limited bandwidth restrict the number of devices and the communication distance.

### Q5. Which bus would you choose for different applications?

**20 m across a room: RS-485**

RS-485 is suitable because differential signaling provides good noise immunity over longer cables.

**20 sensors on one board: I²C**

I²C allows multiple sensors to share SDA and SCL, provided their addresses are compatible and the electrical limits are respected.

**Motor driver: CAN**

CAN is a suitable choice for a distributed industrial motor controller because it provides robust communication, arbitration, and error detection. For a simple motor driver on the same board, PWM or SPI may also be appropriate.

### Q6. Which bus is the oldest, and what historical design constraint remains visible?

Among the listed standards, RS-232 is the oldest, introduced in 1960.

Its point-to-point structure and relatively high positive and negative signaling voltages reflect its original purpose of connecting terminal equipment and modems.

## 3. What Surprised Me

I found it interesting that I²C allows many sensors to communicate using only two signal lines, while SPI normally requires an additional chip-select signal for each independently selected peripheral.

Another interesting point is that CAN uses message identifiers rather than conventional device addresses.

## 4. Conclusion

Different bus systems are designed for different requirements.

- I²C and SPI are suitable for short-distance communication between electronic components.
- RS-485 and CAN are more suitable for robust communication in industrial environments.
- The choice of a bus depends on distance, speed, electrical noise, number of devices, and reliability requirements.

## 5. Sources

- [NXP – I²C-bus Specification](https://www.nxp.com/docs/en/user-guide/UM10204.pdf)
- [Texas Instruments – SPI Documentation](https://www.ti.com/interface/spi/overview.html)
- [Modbus Organization](https://www.modbus.org/)
- [Analog Devices – RS-485](https://www.analog.com/en/product-category/rs-485-rs-422.html)
- [PulseView / sigrok](https://sigrok.org/wiki/PulseView)
