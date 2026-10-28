## Bus profile: SPI (Serial Peripheral Interface)

- **History and background:** SPI was developed by Motorola in the 1980s for communication between microcontrollers and peripheral devices.

- **Wires and connectors:** SPI typically uses four signal lines: SCLK (clock), MOSI (controller to peripheral), MISO (peripheral to controller), and CS (chip select), plus GND.

- **Voltage, signaling, and drive style:** SPI uses synchronous serial communication, usually with push-pull signaling. Common logic voltages are 3.3 V and 5 V, depending on the device. It supports full-duplex communication.

- **Topology and addressing:** SPI normally uses a controller-peripheral structure. Multiple devices can share the data and clock lines, but usually require separate CS signals. Standard SPI does not use device addresses.

- **Speed and maximum length:** SPI can operate at several MHz or tens of MHz, depending on the hardware. It is mainly designed for short connections on circuit boards. There is no universal maximum cable length.

- **Relation to the other buses:** SPI is usually faster than I²C but requires more wires. Unlike UART, SPI uses a shared clock. CAN and RS-485 are better suited for longer or more demanding communication links.

- **Typical use and kit example:** SPI is commonly used for SD cards, displays, ADCs and RFID readers, such as the MFRC522 connected to an ESP32.

- **Curiosities / remarkable features:**
  1. SPI supports simultaneous data transmission and reception (full-duplex).
  2. SPI uses chip-select signals instead of device addresses.
  3. SPI has no universal acknowledgement or error-checking mechanism.

- **What can go wrong / how to debug:** Common problems include incorrect wiring, wrong chip-select pins, incompatible voltage levels or incorrect clock settings. A logic analyzer can help identify these problems.

- **Sources and verification:**
  - [Arduino SPI Library](https://docs.arduino.cc/language-reference/en/functions/communication/SPI/)
  - [SPI – Wikipedia](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface)
  - Device datasheet for hardware-specific voltage and timing information.
  - Hardware verification: Not yet performed.

### Quick comparison

| Feature | SPI | I²C | UART |
|---|---|---|---|
| Signal wires | 4+ | 2 | 2 |
| Clock | Shared | Shared | No shared clock |
| Addressing | Chip select | Device address | No built-in addressing |
| Typical use | SD cards, displays | Sensors | Serial modules |
