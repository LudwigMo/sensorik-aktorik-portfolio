# SPI – LLM Research Notes

**Module:** 2 – Buses & I²C  
**Task:** 2 – Bus Systems Survey  
**Bus:** SPI (Serial Peripheral Interface)  
**LLM used:** ChatGPT

## Prompt 1 – History and Background

**Prompt:**

Who developed SPI, when was it developed, which problem did it solve, and what design decisions from that time are still important today?

**Summary:**

SPI was developed by Motorola in the 1980s for fast and simple communication between microcontrollers and peripheral devices. Its synchronous clock, full-duplex communication and chip-select mechanism are still widely used today.

**Verification:**

The history and basic communication principles were checked against the Texas Instruments SPI overview. The general SPI characteristics are confirmed, but no hardware test has been performed.

**Source:** [Texas Instruments – Understanding the SPI Bus](https://www.ti.com/lit/ab/sboa621/sboa621.pdf)

---

## Prompt 2 – Relation to Other Buses

**Prompt:**

Compare SPI with I²C, UART, RS-232, RS-485, Modbus RTU, CAN and OneWire. What are the main advantages and disadvantages of SPI?

**Summary:**

SPI is a synchronous, high-speed interface that normally uses four signal lines. Compared with I²C, it requires more wires but is often faster. UART is asynchronous, while RS-485 and CAN are better suited for communication over longer distances or in demanding environments. SPI is mainly used for short connections between electronic components.

**Verification:**

The SPI, I²C and UART comparison was checked against the Texas Instruments SPI overview. The other bus comparisons are based on the course material and require further verification for specific applications.

**Source:** [Texas Instruments – Understanding the SPI Bus](https://www.ti.com/lit/ab/sboa621/sboa621.pdf)

---

## Prompt 3 – Curiosities and Remarkable Features

**Prompt:**

What are three remarkable design features of SPI, and why are they important for communication between electronic devices?

**Summary:**

1. **Full-duplex:** SPI can send and receive data simultaneously.
2. **Chip Select:** Multiple devices can share the bus, but each normally needs its own CS signal.
3. **Flexible communication:** SPI supports different clock modes and has no universal fixed maximum speed.

**Verification:**

These features were checked against the Analog Devices SPI introduction and Microchip documentation. The supported clock modes and maximum frequency depend on the specific hardware.

**Sources:**
- [Analog Devices – Introduction to SPI Interface](https://www.analog.com/en/resources/analog-dialogue/articles/2018/08/13/15/31/introduction-to-spi-interface.html)
- [Microchip – SPI Introduction](https://developerhelp.microchip.com/xwiki/bin/view/applications/SPI/)

---

## Prompt 4 – Failure Modes and Debugging

**Prompt:**

What are common SPI communication problems, how can they be identified, and how can a logic analyzer help with debugging?

**Summary:**

Common SPI problems include incorrect wiring, wrong chip-select signals, incompatible voltage levels and incorrect clock settings (CPOL/CPHA).

A logic analyzer can capture SCLK, MOSI, MISO and CS signals. This helps identify timing problems and incorrect data transmission.

**Verification:**

The common failure mechanisms and SPI signal behavior were compared with technical documentation from Analog Devices and Tektronix. Practical verification with a logic analyzer has not yet been performed.

**Sources:**
- [Analog Devices – Introduction to SPI Interface](https://www.analog.com/en/resources/analog-dialogue/articles/2018/08/13/15/31/introduction-to-spi-interface.html)
- [Tektronix – SPI Bus Basics](https://www.tek.com/tw/documents/primer/468111)

---

## Research Conclusion

ChatGPT helped us understand the history, communication principles, advantages and possible problems of SPI.

We learned that SPI is suitable for fast communication over short distances, but it requires more signal lines than I²C.

Technical documentation was used to check the main explanations. Hardware-specific values and practical measurements still need to be verified with the actual devices.
